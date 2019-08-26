# *******************************************************************************************
# *******************************************************************************************
#
#		Name : 		a16.py
#		Purpose :	RCA18016 Assembler
#		Date :		25th August 2019
#		Author : 	Paul Robson (paul@robsons.org.uk)
#
# *******************************************************************************************
# *******************************************************************************************

import sys,os,re

class AssemblerException(Exception):
	pass

# *******************************************************************************************
#
#							Expression Evaluator Worker (strict l->r)
#
# *******************************************************************************************

class EvaluatorWorker(object):
	#
	#						Evaluate an expression
	#
	def evaluate(self,expr,identifiers = {}):
		self.identifiers = identifiers
		expr = expr.lower().replace(" ","")								# remove spaces,l/c
		expr = re.split("([\\$a-z0-9\\_]*)",expr)						# split into terms/operators
		expr = [x for x in expr if x != ""]								# and check the basics
		if len(expr) % 2 == 0 or re.match("^[a-z0-9\\_\\$]*$",expr[0]) is None:
			raise AssemblerException("Bad Expression")
		value = self.term(expr[0])										# first term
		for i in range(1,len(expr),2):									# do subsequent
			if expr[i] == "+":											# depending on operator
				value = value + self.term(expr[i+1])
			elif expr[i] == "-":
				value = value - self.term(expr[i+1])
			elif expr[i] == "*":
				value = value * self.term(expr[i+1])
			elif expr[i] == "/":
				n = self.term(expr[i+1])
				if n == 0:
					raise AssemblerException("Division by zero")
				value = int(value / n)
			elif expr[i] == ">>":
				value = value >> self.term(expr[i+1])
			elif expr[i] == "<<":
				value = value << self.term(expr[i+1])
			elif expr[i] == "&":
				value = value & self.term(expr[i+1])
			elif expr[i] == "|":
				value = value | self.term(expr[i+1])
			elif expr[i] == "^":
				value = value ^ self.term(expr[i+1])
			else:
				raise AssemblerException("Bad Operator")
		return value
	#
	#							Evaluate a term.
	#
	def term(self,s):
		if re.match("^\\-?\\d+$",s) is not None:						# decimal
			return int(s)
		if re.match("^\\$([0-9a-f]+)$",s) is not None: 					# hexadecimal
			return int(s[1:],16)
		if s in self.identifiers:										# identifier.
			return self.identifiers[s]
		raise AssemblerException("Bad term "+s)

# *******************************************************************************************
#
#									Instruction classes
#
# *******************************************************************************************

class SimpleOpcode(object):
	def __init__(self,opcode):
		self.opcode = opcode

	def assemble(self,operand):
		if operand is not None:
			raise AssemblerException("Opcode takes no parameter")
		return [ self.opcode ]

class ImmediateOpcode(SimpleOpcode):			
	def assemble(self,operand):
		if operand is None:
			raise AssemblerException("Opcode requires a parameter")		
		return [ self.opcode,operand & 0xFF,(operand >> 8) & 0xFF ]

class RegisterOpcode(SimpleOpcode):
	def assemble(self,operand):
		if operand is None:
			raise AssemblerException("Opcode requires a parameter")		
		if operand < 0 or operand > 15:
			raise AssemblerException("Bad register value")
		return [ self.opcode+operand ]

class PortOpcode(SimpleOpcode):
	def assemble(self,operand):
		if operand is None:
			raise AssemblerException("Opcode requires a parameter")		
		if operand < 1 or operand > 7:
			raise AssemblerException("Bad register value")
		return [ self.opcode+operand ]

# *******************************************************************************************
#
#											Opcodes
#
# *******************************************************************************************

Opcodes = {
	"inc":RegisterOpcode(0x10),"dec":RegisterOpcode(0x20),

	"glo":RegisterOpcode(0x80),"ghi":RegisterOpcode(0x90),
	"plo":RegisterOpcode(0xA0),"phi":RegisterOpcode(0xB0),

	"lda":RegisterOpcode(0x40),"str":RegisterOpcode(0x50),

	"ldx":SimpleOpcode(0xF0),"or":SimpleOpcode(0xF1),
	"and":SimpleOpcode(0xF2),"xor":SimpleOpcode(0xF3),
	"add":SimpleOpcode(0xF4),"sd":SimpleOpcode(0xF5),
	"sm":SimpleOpcode(0xF7),

	"ldi":ImmediateOpcode(0xF8),"ori":ImmediateOpcode(0xF9),
	"ani":ImmediateOpcode(0xFA),"xri":ImmediateOpcode(0xFB),
	"adi":ImmediateOpcode(0xFC),"sdi":ImmediateOpcode(0xFD),
	"smi":ImmediateOpcode(0xFF),

	"shr":SimpleOpcode(0xF6),

	"br":ImmediateOpcode(0x30),"bz":ImmediateOpcode(0x32),
	"bdf":ImmediateOpcode(0x33),
	"b1":ImmediateOpcode(0x34),"b2":ImmediateOpcode(0x35),
	"b3":ImmediateOpcode(0x36),"b4":ImmediateOpcode(0x37),

	"skp":SimpleOpcode(0x38),"bnz":ImmediateOpcode(0x3A),
	"bnf":ImmediateOpcode(0x3B),
	"bn1":ImmediateOpcode(0x3C),"bn2":ImmediateOpcode(0x3D),
	"bn3":ImmediateOpcode(0x3E),"bn4":ImmediateOpcode(0x3F),

	"idl":SimpleOpcode(0x00),

	"sep":RegisterOpcode(0xD0),"sex":RegisterOpcode(0xE0),

	"ret":SimpleOpcode(0x70),"dis":SimpleOpcode(0x71),
	"sav":SimpleOpcode(0x78),

	"out":PortOpcode(0x60),"inp":PortOpcode(0x68),

	"ldn":RegisterOpcode(0x00),	
	"adc":SimpleOpcode(0x74),"adci":ImmediateOpcode(0x7C)
}

# *******************************************************************************************
#
#									Assembler Worker
#
# *******************************************************************************************

if __name__ == "__main__":
	ew = EvaluatorWorker()
	print(ew.evaluate("2*x1+$14",{"x1":4}))
	
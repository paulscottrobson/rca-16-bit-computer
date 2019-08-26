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
		if expr.startswith("-"):										# lazy unary minus
			expr = "0"+expr
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
	def __init__(self,opcode):											# opcode which is just that
		self.opcode = opcode

	def assemble(self,operand):
		if operand is not None:
			raise AssemblerException("Opcode takes no parameter")
		return [ self.opcode ]

class ImmediateOpcode(SimpleOpcode):									# immediate or branch opcode
	def assemble(self,operand):											# (e.g. with 2 byte operand)
		if operand is None:
			raise AssemblerException("Opcode requires a parameter")		
		return [ self.opcode,operand & 0xFF,(operand >> 8) & 0xFF ]

class RegisterOpcode(SimpleOpcode):										# register opcode.
	def assemble(self,operand):
		if operand is None:
			raise AssemblerException("Opcode requires a parameter")		
		if operand < 0 or operand > 15:
			raise AssemblerException("Bad register value")
		return [ self.opcode+operand ]

class PortOpcode(SimpleOpcode):											# input/output opcode
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
	"inc":RegisterOpcode(0x10),"dec":RegisterOpcode(0x20),				# List of 18016 opcodes.

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

class AssemblerWorker(object):
	def __init__(self,baseAddress = 0):
		self.evaluator = EvaluatorWorker()								# for evaluation
		self.baseAddress = 0 											# address it starts at
		self.identifiers = {}											# known identifiers
		self.opcodes = Opcodes 											# known opcodes
		for i in range(0,16):											# define RX opcodes.
			self.identifiers["r{0}".format(i)] = i
			self.identifiers["r{0:x}".format(i)] = i
		self.setPass(1)
	#
	#		Start a new pass
	#
	def setPass(self,p,listing = None):
		self.passID = p 												# save pass,listing stream
		self.listing = listing
		self.pc = self.baseAddress 										# and the current address
		self.binary = []												# binary put here.
	#
	#		Assemble one instruction only. (no lables, equates, comments etc.)
	#
	def assembleInstruction(self,instr):
		m = re.match("^([a-z1-4]+)\\s*(.*)$",instr)						# split into opcode/operand
		if m is None:
			raise AssemblerException("Syntax error")
		code = None
		if m.group(1).lower() in self.opcodes:							# if known opcode
			operand = None
			if m.group(2) != "":										# get operand if exists
				operand = self.pc 										# dummy value pass 1
				if self.passID == 2:									# must be defined pass 2
					operand = self.evaluator.evaluate(m.group(2),self.identifiers)
																		# get the associated code.
				code = self.opcodes[m.group(1).lower()].assemble(operand)

		else: 															# try things like byte etc.
			code = self.assembleControl(m.group(1).lower(),m.group(2).lower())

		if code is not None:											# code generated
			if self.passID == 2:										# on pass 2
				self.binary += code 									# add to binary
				if self.listing is not None:							# output listing if required
					hexCode = " ".join("{0:02x}".format(c) for c in code)
					if len(hexCode) > 22:
						hexCode = hexCode[:20]+" ..."
					self.listing.write("{0:06x}:{1:26} {2}\n".format(self.pc,hexCode,instr))
			self.pc += len(code)										# adjust pointe.
	#
	#		Assemble other things like byte, word, text and so on.
	#
	def assembleControl(self,command,operand):
		if command == "byte" or command == "word" or command == "long":
			operand = [x for x in operand.split(",") if x.strip() != ""]
			operand = [self.evaluator.evaluate(x,self.identifiers) for x in operand]
			if command == "byte":
				operand = [x & 255 for x in operand]
				return operand
			if command == "word":
				result = []
				for op in operand:
					result.append(op & 0xFF)
					result.append((op >> 8) & 0xFF)
				return result
			if command == "long":
				result = []
				for op in operand:
					result.append(op & 0xFF)
					result.append((op >> 8) & 0xFF)
					result.append((op >> 16) & 0xFF)
					result.append((op >> 24) & 0xFF)
				return result
		if command == "text":
			return [ord(c) for c in operand.strip()]

		raise AssemblerException("Unknown "+command+" "+operand)

if __name__ == "__main__":
	aw = AssemblerWorker()
	for asmPass in range(1,3):
		aw.setPass(asmPass,sys.stdout)
		aw.assembleInstruction("adc")	
		aw.assembleInstruction("sep 2")	
		aw.assembleInstruction("br $4A2")
		aw.assembleInstruction("lda rc")
		aw.assembleInstruction("byte 1,2,3,4,511")
		aw.assembleInstruction("word 510,6,7,8")
		aw.assembleInstruction("long -2")
		aw.assembleInstruction("text hello world")

#
#	Labels/equates/complete.
#
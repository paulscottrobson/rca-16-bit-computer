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

if __name__ == "__main__":
	ew = EvaluatorWorker()
	print(ew.evaluate("2*x1+$14",{"x1":4}))
	
# ********************************************************************************
#
#						Convert 18016.def to compileable code
#
# ********************************************************************************

import os,re

def process(s,opcode):
	s = s.replace("@P",str(opcode & 7))
	s = s.replace("@R","{0:X}".format(opcode & 15))
	s = s.replace("@F",str(opcode % 4 + 1))
	return s

target = "../emulator/generated/".replace("/",os.sep)					# output directory.
#
#									Load source
#
src = open("18016.def").readlines()										# read in source
src = [x if x.find("//") < 0 else x[:x.find("//")] for x in src]		# strip comments
src = [x.replace("\t"," ").strip() for x in src if x.strip() != ""]		# tabs,spaces
#
#						Create C file with 18016 functions
#
h = open(target+"18016_code.h","w")										# output code lines
h.write("\n".join([x[1:] for x in src if x.startswith(":")]))
h.close()
src = [x for x in src if not x.startswith(":")]							# remove them.
#
#						Create default port includes
#
h = open(target+"18016_ports.h","w")
for port in range(1,7+1):
	h.write("#ifndef INPUT{0}\n#define INPUT{0}() (0)\n#endif\n".format(port))
	h.write("#ifndef OUTPUT{0}\n#define OUTPUT{0}(n) {{}}\n#endif\n".format(port))
for flag in range(1,4+1):
	h.write("#ifndef EFLAG{0}\n#define EFLAG{0}() (0)\n#endif\n".format(flag))
h.close()

#
#						Create switch handler
#
mnemonics = [ None ] * 256
code = [ None ] * 256
for l in src:
	m = re.match('^([0-9A-Fa-f\\-]+)\\s*\\"(.*)\\"\\s*(.*)$',l)			# Analyse
	assert m is not None,l
	opc = m.group(1) if len(m.group(1)) == 5 else m.group(1)+"-"+m.group(1)
	for opcode in range(int(opc[:2],16),int(opc[3:],16)+1):
		assert mnemonics[opcode] is None,"Duplicated {0:02x}".format(opcode)

		mnemonics[opcode] = process(m.group(2),opcode).lower()
		code[opcode] = process(m.group(3),opcode)+";break;"
		# print("{0:02x} {1:6} {2}".format(opcode,mnemonics[opcode],code[opcode]))
#
#							Output Mnemonics
#
for i in range(0,256):
	if mnemonics[i] is None:
		mnemonics[i] = "byte {0:02x}".format(i)
h = open(target+"18016_mnemonics.h","w")
m = ",".join(['"'+x+'"' for x in mnemonics])
h.write("static const char *_mnemonics[256] = {{ {0} }};\n".format(m))
h.close()
#
#							Output switch code
#
h = open(target+"18016_switch.h","w")
for i in range(0,256):
	if code[i] is not None:
		h.write("case 0x{0:02x}: // *** ${0:02x} {1} ***\n\t{2}\n".format(i,mnemonics[i],code[i]))
h.close()		
#
print("Generated C 18016 CPU.")
import random 
import sys


blipkeys = ["set", "var", "output", "text"]
binops = ['+', '-', '*', '/', '%', '&&', '||', '<', '>', '<=', '>=', '!=', '==']
unaryops = ['!','~']
names = ["aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx", "yy", "zz"]
initialized = []
nums = map(str,range(11))
lines = open('strway.txt').read().splitlines()
exprnum = 100
max_depth = 6

def formCommand(token,depth):
	global max_depth
	space = " "
	
	if depth >= max_depth:
		return space + random.choice(nums)

	if (token in names) | (token in nums): # token is a var or a num
		return space + token

	if token in binops:
		str1 = formCommand(random.choice(binops+unaryops+initialized+nums),depth+1)
		str2 = formCommand(random.choice(binops+unaryops+initialized+nums),depth+1)
		return space + token + str1 + str2

	if token in unaryops:
		str1 = formCommand(random.choice(binops+unaryops+initialized+nums),depth+1)
		return space + token + str1

	if token in blipkeys:
		if token == "text":
			return token +  space + '"' + random.choice(lines).strip("\n") + '\\n"'
		elif (token == "var") | (token == "set"):
			operand = formCommand(random.choice(binops+unaryops+initialized+nums),depth+1)
			return token + space + random.choice(names) + operand
		else:
			operand = formCommand(random.choice(binops+unaryops+initialized+nums),depth+1)
			return token + space + operand

def outCmdStr(outstr):
	return 'text "' + outstr.replace('"',"'").replace("\\n","") + '\\n"'

if __name__ == "__main__":
	#parse the args
	if '-n' in sys.argv:
		exprnum = int(sys.argv[sys.argv.index('-n') + 1])
	if '-d' in sys.argv:
		max_depth = int(sys.argv[sys.argv.index('-d') + 1])

	#write the file
	blp = open("test_grader.blip",'w+');
	for k in range(exprnum):
		outstr = formCommand(random.choice(blipkeys),0)
		blp.write(outCmdStr(outstr) + "\n")
		blp.write(outstr + "\n")


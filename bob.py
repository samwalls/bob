import re
import random
from collections import OrderedDict

class Bob(object):

	builtinReflective = OrderedDict({
		r"i" : "you",
		r"me" : "you",
		r"my" : "your",
		r"you" : "me",
		r"am" : "are",
		r"you'd" : "I'd",
		r"i'd" : "you'd",
		r"wasn't" : "weren't",
		r"was" : "were",
		r"were" : "was",
		#r"you (\w+)" : "I {m[1]}",
		#r"I (\w+)" : "you {m[1]}",
	})

	builtinKeys = OrderedDict({})
	builtinKeys[r"^(.*)I would (.+),? but(.+)$"] = [
		"why is {3} stopping you?",
		"why would one {2}?",
		"why would you {2}?",
	]
	builtinKeys[r"^(.*)I would (.+),? but(.*)$"] = [

	]
	builtinKeys[r"^(.*)I want (.+) ?(.*)$"] = [
		"think carefully, do you really want that?",
		"why?",
		"think carefully, do you really want that?",
		"what makes you want {2}?",
	]
	builtinKeys[r"^(.*)my birthday today(.*)$"] = [
		"a happy birthday to you!",
	]
	builtinKeys[r"^(.*)birthday today(.*)$"] = [
		"a happy birthday to them!",
	]
	builtinKeys[r"^(.+)$"] = [
		"{0}",
		"what else?",
		"what do you mean?",
		"what do you mean by that?",
		"what do you mean {0}?",
	]
	builtinKeys[r"^(.*)$"] = [
		"{0}",
		"what else?",
		"what do you mean?",
		"what do you mean by that?",
	]

	def __init__(self):
		self = self

	def response(self, input):
		for key in Bob.builtinKeys.keys():
			match = re.search(key, input.rstrip(".!?"))
			if match != None:
				#print "matched " + str(match.groups())
				rsp = random.choice(Bob.builtinKeys[key])
				# get reflected group strings
				modifiedGroups = ()
				matches = [match.group(0)]
				matches.extend(match.groups())
				for grp in matches:
					tokens = grp.lower().split()
					for i, token in enumerate(tokens):
						if token in Bob.builtinReflective:
							tokens[i] = Bob.builtinReflective[token]
					modifiedGroups += (" ".join(tokens),)
				#print modifiedGroups
				return rsp.format(*modifiedGroups)

import re
import random
from collections import OrderedDict
import markovbot

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
		r"i'll" : "you'll",
		r"you'll" : "I will",
		r"i've" : "you've",
		r"you've" : "I've",
		r"you're" : "I'm",
		r"i'm" : "you're",
	})

	# Some rules copied adapted from here: http://norvig.com/paip/eliza1.lisp
	builtinKeys = OrderedDict({})
	builtinKeys[r"^(.*)I would (.+),? but(.+)$"] = [
		"why is the fact that {3} stopping you?",
		"why do you  {2}?",
	]
	builtinKeys[r"^(.*)I (think)? would (.+),? and (.*)$"] = [
		"which is more important: to {3}; or {4}?",
		"do youo feel if you {3} it would make you happy?",
	]
	builtinKeys[r"^(.*)I (.*)want (.+) ?(.*)$"] = [
		"think carefully, do you really want that?",
		"why do you want {3}?",
		"think carefully, do you really want that?",
		"what makes you want {3}?",
		"what would it mean if you had {3}?",
		"is {3} essential?",
	]
	builtinKeys[r"^(.*) (I (feel|think)) (.*)$"] = [
		"what makes you feel that way",
		"explain why {4}",
	]
	builtinKeys[r"^(.*) if (.*)$"] = [
		"do you think it is really likely that {2} would happen?",
		"you think that if you {1}; then {2}, correct?",
		"what do you think about {2}",
	]
	builtinKeys[r"^(I'm |I am |it's |all |sort of )?(good|fine|ok|not bad)(.*)$"] = [
		"is there more to it than that?",
		"oh?",
	]
	builtinKeys[r"^well,? ?(.*)$"] = [
		"you seem uneasy about that",
		"are you sure?",
		"please explain further",
	]
	builtinKeys[r"^(.*)I was (.*)$"] = [
		"interesting...",
		"were you really?",
		"were you really {2}?",
	]
	builtinKeys[r"^(.*)my birthday today(.*)$"] = [
		"a happy birthday to you!",
		"how does that make you feel?",
	]
	builtinKeys[r"^(.*)birthday today(.*)$"] = [
		"I wish them a happy birthday!",
	]
	builtinKeys[r"^(.*)I don't know ?(.*)$"] = [
		"take your time...",
		"oh, but I think you do know {2}",
	]
	builtinKeys[r"^(.*)yes ?(.*)$"] = [
		"interesting",
		"that's interesting",
	]
	builtinKeys[r"^(.*)no ?(.*)$"] = [
		"why not?",
		"where do you think this negativity is coming from?",
		"that's a shame",
	]
	builtinKeys[r"^(.*)(hello|hi) ?(.*)$"] = [
		"hello there",
		"what's up?",
		"how are you?",
		"what's on your mind?",
	]
	builtinKeys[r"^(.*)sorry (.+)(.*)$"] = [
		"no need to apologize",
		"that's fine",
		"you don't need to be sorry about {2}",
	]
	builtinKeys[r"^(.*)sorry ?(.*)$"] = [
		"no need to apologize",
		"that's fine",
	]
	builtinKeys[r"^(.*)\?$"] = [
		"Do you know?",
		"I think you maybe know more about this than you lead on",
		"Can you tell me? {1}?",
		"{1} - I'm not too sure what the answer is...",
	]
	builtinKeys[r"^(.+)$"] = [
		"{0}",
		"{0}?",
		"what else?",
		"what do you mean?",
		"what do you mean by that?",
		"what about {0}?",
		"tell me about {0}",
		"how do you feel about {0}?",
		"explain...",
		"how does that make you feel?",
		"I see...",
	]
	builtinKeys[r"^(.*)$"] = [
		"{0}",
		"...",
		"what else?",
		"is there anything else I can help you with?"
	]

	def __init__(self, path):
		self.__markovBot = markovbot.MarkovBot(2, 1, path)
		self.__markovBot.train()

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
					if grp != None:
						tokens = grp.lower().split()
						for i, token in enumerate(tokens):
							if token in Bob.builtinReflective:
								tokens[i] = Bob.builtinReflective[token]
					if modifiedGroups == ():
						modifiedGroups += (" ".join(tokens).title(),)
					else:
						modifiedGroups += (" ".join(tokens),)
				#print modifiedGroups
				return rsp.format(*modifiedGroups) + " " + self.__markovBot.response("")

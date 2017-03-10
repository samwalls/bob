import os
import random
import tokenizer
import re

class MarkovBot(object):

	endToken = re.compile(r"^[!?.]+$")

	def __init__(self, keyBufferSize, valBufferSize, trainingFilePath):
		self.__keyBufferSize = keyBufferSize
		self.__valBufferSize = valBufferSize
		self.__trainingFilePath = trainingFilePath
		self.__ngrams = {}

	# Start training based on the training file
	def train(self):
		tokens = []
		for token in tokenizer.Tokenizer(self.__trainingFilePath):
			tokens.append(token)
		position = 0
		while position < len(tokens) and position + self.__keyBufferSize + self.__valBufferSize < len(tokens):
			# create an n-gram for the key and value each
			key = ()
			val = ()
			for i in range(self.__keyBufferSize):
				key += (tokens[position + i],)
			for i in range(self.__valBufferSize):
				val += (tokens[position + self.__keyBufferSize + i],)
			# update the frequency for this ngram-value combination
			if key in self.__ngrams and val in self.__ngrams[key]:
				self.__ngrams[key][val] += 1
			else:
				self.__ngrams[key] = {}
				self.__ngrams[key][val] = 1
			position += 1
			#print str(position) + " / " + str(len(tokens))

	def response(self, input):
		buff = []
		# TODO use input as a seed to get a markov chain output
		k = random.choice(self.__ngrams.keys())
		for el in k:
			buff.append(el)
		v = self.__ngrams[k]
		position = 0
		while position < len(buff) and position < 20:
			v = self.__ngrams[k]
			# TODO use ngram frequency to determine probability
			# randomly pick a value to move to
			v = random.choice(v.keys())
			for el in v:
				buff.append(el)
			k = ()
			for i in range(self.__keyBufferSize):
				k += (buff[position + 1 + i],)
			position += 1
		output = ""
		for item in buff:
			output = output + " " + item
		return output

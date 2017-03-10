# -*- coding: utf-8 -*-
import io
import re

class Tokenizer(object):

	# matches 4 groups (prefix brackets)(word)(suffix brackets)(extra punctuation)
	punctuation = re.compile(r"^([(\[{\"`\'])?.*?([a-zA-Z0-9_\-@%£$^*]*).*?([)\]}\"`\'])?([!?.,:;=+\-_]*).*?$")

	def __init__(self, filePath):
		self.__filePath = filePath
		self.__file = io.open(filePath, "r")
		self.__currentLine = []

	def __iter__(self):
		return self

	def next(self):
		# if we need to read a new line, do it
		if len(self.__currentLine) <= 0:
			if self.__file.closed:
				self.__file.open(self.__filePath)
			line = self.__file.readline()
			while line == "\n":
				line = self.__file.readline()
			if line == "":
				raise StopIteration
			line = line.split()
			# take certain punctuation marks and promote them to tokens
			for element in line:
				m = Tokenizer.punctuation.search(element)
				if m == None:
					self.__currentLine.append(element)
					break
				prefix = m.group(1)
				if prefix != "" and prefix != None:
					self.__currentLine.append(prefix)
				word = m.group(2)
				if word != "" and word != None:
					self.__currentLine.append(word)
				suffix = m.group(3)
				if prefix != "" and prefix != None and suffix != "" and suffix != None:
					self.__currentLine.append(suffix)
				modifier = m.group(4)
				if modifier != "":
					self.__currentLine.append(modifier)
		if len(self.__currentLine) <= 0:
			raise StopIteration
		else:
			v = self.__currentLine[0]
			del self.__currentLine[0]
			return v

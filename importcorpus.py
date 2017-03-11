from __future__ import print_function
import csv
import os
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

# For transforming the  files into a processable source for the markov bot.

# Data by:
#	Danescu-Niculescu-Mizil, C. and Lee, L. (2011). Chameleons in imagined
#	conversations: A new approach to understanding coordination of linguistic
#	style in dialogs. In Proceedings of the Workshop on Cognitive Modeling and
#	Computational Linguistics, ACL 2011.

if len(sys.argv) < 2:
	sys.stderr.write("expected path to preprocess\n")
	sys.exit(1)

inputPath = sys.argv[1]
script_dir = os.path.dirname(__file__)

abs_input_dir = os.path.join(script_dir, inputPath)
#print abs_input_dir
abs_output_dir = os.path.join(script_dir, "data/corpus.txt")
#print abs_output_dir

with open(abs_input_dir,"rb") as movie_lines, open(abs_output_dir, "wb") as txtout:
	#we can't read multi-character delimiters, so replace this thing with @ (doesn't exist in the file)
    movie_lines = csv.reader((line.replace("+++$+++","@") for line in movie_lines), delimiter='@')
    for row in movie_lines:
        count = len(row[4])
        if count >= 5:
            print(row[4].decode("iso-8859-2").encode("utf-8"), file=txtout)

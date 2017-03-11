# Bob
###### A distant relative of Eliza - so we think.

Bob is a chatbot built using very similar principles to that of ELIZA (Weizenbaum J., 1966 [1]) in combination with the use of a Markov chain, trained on a corpus of input text, for added interest.

# Running Bob

Bob is written in python 2, so run `main.py` using `python2`, if you have it.

I have included a script to download and preprocess the data of the "Cornell Movie--Dialogs Corpus".
Feel free, of course, to try other corpuses, but I found that this one worked quite well given the context.

Simply run `make`, the necessary files will be downloaded, and a bob-ready corpus will then reside in `data/corpus.txt`

# References
[1] - Weizenbaum, J., 1966. ELIZA—a computer program for the study of natural language communication between man and machine. Communications of the ACM, 9(1), pp.36-45.

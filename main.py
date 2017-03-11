#import markovbot
import bob
import sys

#if len(sys.argv) < 2:
#	sys.stderr.write("expected path to a training corpus\n")
#	sys.exit(1)
#path = sys.argv[1]

#bot = markovbot.MarkovBot(2, 1, path)
#bot.train()

bot = bob.Bob()

# start a REPL
inp = ""
sys.stdout.write("you: ")
try:
	while True:
		inp = sys.stdin.readline()
		if inp == "quit\n":
			break
		sys.stdout.write("\n")
		response = bot.response(inp)
		print "bob: " + response + "\n"
		sys.stdout.write("you: ")
except (KeyboardInterrupt, SystemExit):
	#this is fine
	print "\n\n[you leave abruptly...]"
	print "\nbob: was it something I said?"
	sys.exit(0)

print "\nbob: see you later"

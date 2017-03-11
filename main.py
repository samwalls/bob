#import markovbot
import bob
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

if len(sys.argv) < 2:
	sys.stderr.write("expected path to a training corpus\n")
	sys.exit(1)

path = sys.argv[1]
bot = bob.Bob(path)

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
	print "\nbob: Was it something I said?"
	sys.exit(0)

print "\nbob: See you later..."

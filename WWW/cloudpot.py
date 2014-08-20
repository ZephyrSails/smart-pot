# this is for flask server && connection of pi and realworld!
from flask import Flask, render_template, request
app = Flask(__name__)
import serial
import time
s = serial.Serial('/dev/ttyUSB0',9600)
time.sleep(12)

@app.route("/")
def main():
	
	s.write("r")
	time.sleep(0.2)
	n = s.inWaiting()
	if (n != 0):
		data = s.read(n)
		temp = data[0:2]
		water = data[3:5]
		light = data[6:8]
		state = data[9:10]
		#print(temp +" " + water + " " + light)
		s.flush()
	time.sleep(0.05)
	templateData = {
		'temp'  : temp,
		'water' : water,
		'light' : light,
		'state' : state
	}
	return render_template('cloudpot.html', **templateData)

@app.route("/<action>")
def action(action):

	if (action == "p"):
		s.write("p")
	if (action == "s"):
		s.write("s")

	time.sleep(0.2)
	n = s.inWaiting()
	if (n != 0):
		data = s.read(n)
		temp = data[0:2]
		water = data[3:5]
		light = data[6:8]
		state = data[9:10]
		#print(temp +" " + water + " " + light)
		s.flush()
	time.sleep(0.05)
	templateData = {
		'temp'  : temp,
		'water' : water,
		'light' : light,
		'state' : state
	}
	return render_template('cloudpot.html', **templateData)

if __name__ == "__main__":
   app.run(host='192.168.1.122', port=88, debug=True)


#def getData(com):
	#strInput = raw_input('send your command: ')
#	s.write("r")
#	time.sleep(0.2)
#	n = s.inWaiting()
#	if (n != 0):
#		data = s.read(n)
#		temp = data[0:2]
#		water = data[3:5]
#		light = data[6:8]
#		print(temp +" " + water + " " + light)
#		s.flush()
#	time.sleep(0.05)
#
#def pullWater():
#	s.write("p")
#def stopWater():
#	s.write("s")
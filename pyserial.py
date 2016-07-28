import serial
from time import strftime

arduino = serial.Serial("COM3", 9600)
data_file = None

#Trial Data
mass = 1.5 #kg
k = 117

def main(trial=1):    
  while (arduino.isOpen()):
    line = arduino.readline()[:-2]
    
    if line == "COMMAND: start_recording":
      print "STARTING RECORDING"
      data_file = open("[DATA] " +strftime("%Y-%m-%d %H.%M.%S") + " trial " + str(trial) + ".csv", "w")
    elif line == "COMMAND: stop_recording":
      data_file.close()
      print "FINSIHED RECORDING"
      trial += 1
    elif line[-1] == "C":
      print line
    else:
      data = line.split(" ")
      time = round(float(data[0]) / 1000.0, 4)
      pos = float(data[1])
    
      if pos < 0.06 and pos > -0.06: #Prevents outliers
        write = str(time) + "," + str(pos) + "\n"
        data_file.write(write)
        print write

if __name__ == '__main__':
  main()

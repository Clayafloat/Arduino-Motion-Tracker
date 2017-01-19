def main(path, newFile):
"""Processes and cleans the raw data collected from the arduino into a csv 

	path -- path to raw data csv file
	newFile -- file name to output
"""

    f = open(path, 'r')
    w = open(newFile + ".csv", 'w')

	TRIAL_TIME_SEC = 120.0
    record = {}
    prevTime = 0.0
    largest = -9999999.9 
    temp = 0.0

    subtract = float(f.readline().split(',')[0])

    data = list(f)

    subtract = subtract - 0.001

    for line in data:
        data = line.split(",")
        pos = float(data[1])

        if pos > largest and pos > temp:
            largest = pos
            prevTime = data[0]
        elif pos == largest and pos:
            temp = pos
        else:
            if (largest != -9999999.9 and float(prevTime) <= TRIAL_TIME_SEC):
                w.writelines(str(float(prevTime) - subtract) + "," + str(largest) + "\n")
                decay = largest
            largest = -9999999.9
            temp = 0.0
            
    f.close()
    w.close()

if __name__ == '__main__':
    import sys
    main(sys.argv[1], sys.argv[2])

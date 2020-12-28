"""

Used Dataset:

https://data.cityofchicago.org/Education/Chicago-Public-Schools-Progress-Report-Cards-2011-/9xs2-f89t

"""

data = open("./Chicago_Public_Schools_-_Progress_Report_Cards__2011-2012_.csv", "r") # openned .csv file in only-read mode
file = open("./public_high_schools_of_chicago.txt", "w") # created new file in write mode

content = data.read()
rows = content.split('\n') # separate content line by line (one school per line)
rows.pop(0) # remove first row
full_data = []
scholl = 0

for row in rows:
	split_row = row.split(',')
	full_data.append(split_row)

file.write("School ID, Name of School, ZIP Code")
file.write('\n')
for scholl in range(len(full_data)-1):
	if full_data[scholl][2] == "HS":
		file.write(str(full_data[scholl][0]))
		file.write(', ')
		file.write(str(full_data[scholl][1]))
		file.write(', ')
		file.write(str(full_data[scholl][6]))
		file.write('\n')

file.close()
data.close()

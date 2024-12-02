#readCSV.py
#this program is made to import a csv file given via command line argument
#example python3 readCSV.py ./feed_data.csv
#this imports feed_data.csv and does basic statistical analysis on it
#printing out the mean, min, max, values as well as the sum and total number of
#values
#made by Shawn Farnham on 12-2-2024

import csv
import sys

infile = open(sys.argv[1])
reader= csv.reader(infile)
headings = []
headings = next(reader)
count=0
sum=0
mean=0
rows=[]
min=100
max=0

for line in reader:
  rows.append(float(line[1]))
  count +=1

for x in range(count):
  sum= sum + rows[x]
  if min > rows[x]:
    min = rows[x]
  if max < rows[x]:
    max = rows[x]

mean = sum/count

print("Count: ", count)
print("Sum: ", sum)
print("Mean: ", mean)
print("Min: ", min)
print("Max: ", max)

#By Tarik Blaoui
#Class CSCI 49900
#Porfessor Soumik Dey
#This file is for individual project


import os
import random 

try:
	os.remove("/my_file_system/linked_disk") 
except FileNotFoundError:
	pass


i = 0
block_list = []
while i < 100:
	block_list.append(i)
	i +=1

data = ''
i = 0 
while i < 100:
	data = data + "||||||||||||||||||| "
	i +=1 

random.shuffle(block_list)


data = list(data)

for i in block_list:
	try:
		overwrite = str(block_list[i+1]).zfill(3)
	except IndexError:
		overwrite = "|||"

	start_number = i*20


	for n in range(3):
		data[start_number + n] = overwrite[n]

with open("/my_file_system/linked_disk", 'w+') as f:
	f.write(''.join(data))

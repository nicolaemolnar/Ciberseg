
import os

dict_file = open('../wordlists/snow_brute.txt', 'r') # Open wordlist file
res_file = open('result.txt', 'r') # Output file from the snow execution

count = 0
for line in dict_file:
    print("Trying with: %10s, tried: %5d times."%(line.replace('\n',''),count),end='\r')
    
    # Run stegsnow against 'line' passphrase
    os.system('stegsnow -Q -p "%s" flags/flag4.txt result.txt' % line) 
    
    # Read the output file and check for 'flag' string in its content
    text = res_file.read()
    count += 1
    if 'flag' in res_file.read():
        print(line)
        break
else:
	print("The file flag4.txt couldn't be extracted with any passphrase of snow_brute")

# Close the opened streams
res_file.close()
dict_file.close()
    

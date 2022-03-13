
import os

dict_file = open('../wordlists/rockyou.txt', 'r')
res_file = open('result.txt', 'r')

count = 0
for line in dict_file:
    print("Trying with: %10s, tried: %5d times."%(line.replace('\n',''),count),end='\r')
    os.system('../Utilities/snow/snow -C -Q -p "%s" flag.txt result.txt' % line)
    
    text = res_file.read()
    count += 1
    if 'flag' in res_file.read():
        print(line)
        break

res_file.close()
dict_file.close()
    

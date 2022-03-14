import argparse
import os

from numpy import char

# Command line arguments parsing
parser = argparse.ArgumentParser()
parser.add_argument("-f", "--file", help="Target file", required=True)
parser.add_argument("-n", "--number", help="Number of characters to overload", required=True)
args = parser.parse_args()

# Create the overflow string
char_seq = "A" * int(args.number)

# If the target file exists, execute it and write 'char_seq' as its input
if (os.path.exists(args.file)):
    # Execute the file with char_seq as input  
    os.system("echo " + char_seq + " | ./" + args.file)
else:
    print(char_seq)
    print("[!] File not found")
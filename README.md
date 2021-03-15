# xor
This script takes an input file contaning lines of hex-data. It performs XOR on each byte to all possible single value key combinations. It outputs the most likely unencoded results based on sum weighted sum of the relative frequencies of characters occurring in English language.

### The variables: input_file and results_to_show can be changed.
input_file is a string that points to the text file to be parsed.  
results_to_show is an int and will change how many unencoded results to output.  
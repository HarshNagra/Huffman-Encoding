# Huffman-Encoding
Huffman Encoding algorithm with a few changes in the implementation technique. 

##Difference in the implementation technique
1. The letter with the smallest ASCII code is the representative of a subtree.
2. In case of ambiguity, select the two trees with the smallest representatives and when 
combining the two trees, the one with the smaller representative will be on the left. 
3. Displays the average number of bits used for each symbol.

##Working
Input - The input message contains normal English text.
Output - “code.txt” stores the codewords for each symbol and the average number of 
                    bits used for each symbol.
         “encodemsg.txt” stores the encoded message.


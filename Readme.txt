Plagarism Detector by Aditya Gupta (AG68834)

Files: makefile (provide your own or use mine), cheaters.cpp (main file), hash.cpp (hashtable main), hash.h (hashtable header)

Testers: Accepts .txt files (and similar) that are unzipped and in a directory. 

Steps: 
1. Open Linux Machine (such as Kamek)
2. put all program files in to the current directory. Can unzip zips in linux. 
3. do: make -f makefile
4. Prepare the set of documents that you wish to check and get the path from the current directory to that directory. Lets call this path p
Note: Do not put a slash after the last file in the path. It may still work but I better to be safe than sorry. 
Example p: testDir/sm_doc_set
5. to run do ./plagiarismCatcher number-n-word-chunks minimum-number-of-collisions 
to run the program.
6. output is printed to console. 

Github Link: https://github.com/AdityaG2000/cheaters_ag68834 
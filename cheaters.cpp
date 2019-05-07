#include <sys/types.h>
#include <dirent.h>
#include <errno.h> //error number usage
#include <iostream>
#include <ctype.h>
#include "hash.h"
#include <fstream>
#include <stdlib.h>



using namespace std;

int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp -> d_name));
    }
    closedir(dp);
    return 0;
}


//Helper function
//parses each string from the file and cleans it (i.e. make it all lower case words)
//input is the string from the file
void cleanString (string& str) {
    string result; //result will be "passed out" through input str

    for (int i = 0; i < str.length(); i++) {

        if ((str[i] >= 'a') && (str[i] <= 'z')) { //making it all UPPER case
            int delta = 'a' - 'A'; //finding the difference between upper and lower case in ascii value (as a decimal)
            result += (str[i] - delta);
        }
        else if (isalnum(str[i])) { //case of already being number or capital letter
            result += str[i];
        }
        //for case of punctuation etc just simply don't add it to the result which is taken care of by above statements
    }
    str = result;
}

int main(int argc, char * argv[]) {
    //string dir = string("sm_doc_set");
    string dir = argv[1];
    int minimumNumCollisions = atoi(argv[3]); //4th element in command line argument will be the number of collisions
    if (minimumNumCollisions > 2) {
	minimumNumCollisions--; //to account for an off by one error but still have some results for 1. 
    }
    int numWordsInSeq = atoi(argv[2]);
    vector<string> files = vector<string>();
    Hash * myHashTable = new Hash();
    getdir(dir, files);

    //cleaning up the list of files
    //we need to do this here so that the hash table does not have entries with trash extra files (i.e. start with dot)
    for (unsigned int i = 0; i < files.size(); i++) {
        if (files[i][0] == '.') { //for erasing files like ".DSstore" and the like
            files.erase(files.begin() + i); //iterator usage to remove that file
            i--; //works because files.size() is not constant, hence it will work
        }
    }

    ifstream myFile;

    for (int i = 0; i < files.size(); i++) {
        string filePtr = dir + '/' + files[i];

        myFile.open(filePtr.c_str());
        if (myFile.good() && myFile.is_open()) {
            string word;
            vector <string> stringQueue;

            while (!myFile.eof()) {

                while (stringQueue.size() < numWordsInSeq && !myFile.eof()) { //for adding elements into the queue
                    myFile >> word;
                    cleanString(word);
                    if (word.length() > 0) {
                        stringQueue.push_back(word);
                    }
                }
                string myString;

                for (int j = 0; j < stringQueue.size(); j++){
                    myString += stringQueue[j]; //getting the string from queue that will be soon hashed
                }
                myHashTable -> hashFunction(myString, i); //using the hash function to record into hash table
                stringQueue.erase(stringQueue.begin() + 0); //erase leftmost item in the queue
            }
        }
        else {
            cout << "Error... files not found!";
            return 0;
        }
        myFile.close();
    }
    myHashTable -> getCollisions(files.size(), files, minimumNumCollisions);
    delete(myHashTable);
}

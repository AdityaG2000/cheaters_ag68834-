#include <iostream>
#include "hash.h"

//Default constructor
//Makes an empty linked list at every entry of the array (that array is hashTable)
Hash::Hash() {
    //setting array all to null
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
};

// given an n word string, insert it into the right place in the hash map after hashfunction-based encryption
void Hash::hashFunction (string &str, int fileNumber) {
    int currentMultiplier = 1; //starts at 1 and will increase
    int myPrimeMultiplier = 19; //should be a prime number that is 1 or 2 digits
    int index = 0;

    for (int i = 0; i < str.length(); i += 2){
        currentMultiplier *= myPrimeMultiplier;
        index += (str[i]* currentMultiplier);
        index = index % TABLE_SIZE; //to maintain the size of index to be a reasonable number (i.e. less than
        //the total size of the hash table.
    }


    if (index < 0) { //absolute value of index (may be) needed
        index = -index;
    }

    HashNode * temp = new HashNode; //now adding our entry to the hash table
    temp -> data = fileNumber; //for use in collision functions obviously
    temp -> next = hashTable[index]; //so it points to NULL or to the next HashNode
    hashTable[index] = temp; //adding at the head of the linked list
}


void Hash::getCollisions(int numDocs, vector<string> &files, int minimumNumCollisions){

    int collisionArray [numDocs][numDocs];

    //make the collisionArray initially all zeros
    for (int i = 0; i < numDocs; i++) {
        for (int j = 0; j < numDocs; j++) {
            collisionArray [j][i] = 0;
        }
    }

    for(int i = 0; i < TABLE_SIZE; i++) { //going through each linked list, so each item in the hashtable (array)

        while (hashTable[i] != NULL) { //while there is something in the linked list still
            HashNode * nodePtr = hashTable[i];
            int nodeData = nodePtr -> data; //get head of linked list's data

            while (nodePtr != NULL) { //going though the row-specific linked list
                if (nodeData != nodePtr -> data) { //if there is a collision
                    collisionArray[nodeData][nodePtr -> data] += 1; //don't worry about use of half of this table yet
                }
                nodePtr = nodePtr -> next; //next element in the linked list
            }
            HashNode * tempPtr = hashTable[i]; //temp pointer for saving the head of the linked list to delete
            hashTable[i] = hashTable[i] -> next; //remove the head of the linked list
            delete(tempPtr); //delete that head of the linked list
        }
    }

    //working with the table
    //just incase
    for(int i = 0; i < numDocs; i++) {
        for (int j = 0; j < numDocs; j++){
            if (i != j) {
                if (collisionArray[i][j] > 0) {
                    collisionArray[j][i] += collisionArray[i][j]; //combining collision pairs in the 2D array
                }
            }
        }
    }

    cout << "The following files have collisions:" << endl;
    vector <string> outputList;
    vector <int> intList;


    //finding the number of collisions
    for(int i = 0; i < numDocs; i++) {

        for (int j = i + 1; j < numDocs; j++){

            if (collisionArray[j][i] > minimumNumCollisions) {
                int intTemp = collisionArray[j][i];
                intList.push_back(intTemp);
                string strTemp = " collisions with files: " + files[i] + " and " + files[j] + "\n";
                outputList.push_back(strTemp);
            }
        }
    }

    for (int i = 0; i < intList.size(); i++) {

        for (int j = i + 1; j < intList.size(); j++) {

            if (intList[j] > intList[i]) {
                int tempInt = intList[j];
                string tempStr = outputList[j];
                intList[j] = intList[i];
                outputList[j] = outputList[i];
                intList[i] = tempInt;
                outputList[i] = tempStr;
            }
        }
    }

    for (int i = 0; i < intList.size() ; i++) {
        cout << intList[i] << outputList[i];
    }

}













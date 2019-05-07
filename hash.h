#ifndef HASH_H
#define HASH_H


#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Hash
{
private:

    static const int TABLE_SIZE = 2000003; //must be a prime number
    struct HashNode
    {
        int data; //this is the file number
        HashNode *next;
    };
    HashNode * hashTable [TABLE_SIZE]; //Hashtable is an array of pointers to HashNode structures

public:

    Hash();
    void hashFunction (string &s, int key);
    void getCollisions(int numDocs, vector<string> &files, int minCollisions); 
    //no destructor needed as heap is taken care of. 
};






#endif

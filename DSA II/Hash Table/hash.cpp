#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include "hash.h"

using namespace std;

unsigned int hashTable::getPrime( int size ){
	
	vector<int> primes;
	//double prime size 7 times for potential rehashing
	primes.push_back(100003);
	primes.push_back(200003);
    primes.push_back(505919);
    primes.push_back(1054007);
    primes.push_back(2380481);
    primes.push_back(4114741);
    primes.push_back(8487821);

    int i = 0;
    while(primes[i] <= size) i++;

    return primes[i];
}


//initialize the hash table
hashTable::hashTable(int size){ //constructor
    
    filled = 0;
    capacity = getPrime(size);
    data.resize(capacity);
    
    for(int i=0; i<data.size();i++){
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }

}

int hashTable::hash(const string &key ){
    //hash function for string
    int hashValue = 0;

    for(int i = 0; i < key.length(); i++) hashValue = hashValue * 101 + key[i];

    hashValue %= capacity;
    
    if( hashValue < 0 ) hashValue += capacity;

    return hashValue;
}

int hashTable::insert(const string &key, void *pv ){
    
    if(filled > (capacity/2) ) { //cut of as half of capacity to rehash
        
        if( rehash() ) {
            return 0; //success
        }else {
            return 2; //failure
        }
    }

    if( contains(key) ) return 1; // key already inserted'

    int index = hash(key) % capacity;

    if (index < 0) index += capacity;

    //linear probing method
    while(data[index].isOccupied == true){
        index++;
        index %= capacity;
    }

    if((data[index].isOccupied == false) || (data[index].isDeleted == true)){
        data[index].key = key;
        data[index].isOccupied = true;
        data[index].isDeleted = false;
        data[index].pv = NULL;
        filled++;
        return 0;
    }

    return -1; //insertion failed
}

int hashTable::findPos(const string &key){
    
    int index = hash(key) % capacity;

    while(data[index].isOccupied == true ) {

        // if statement checks if this item has been inserted already, if so, return current index number
        if((data[index].key == key) && (data[index].isDeleted == false)) {
            return index;
        }

        //if this item has not been inserted and current index number is occupied, 
        //then using linear probe to locate next index location
        index++;
    }

    return -1; //-1 means failed to locate index, or cannot locate new index
}

bool hashTable::contains(const string &key){
    int index = findPos(key);
    if(index == -1) {
        return false;
    }else{
        return true;
    }
}


bool hashTable::rehash(){
    
    try{

        vector<hashItem> oldTable = data;
        capacity = getPrime(capacity);
        
        filled=0;
        data.clear();
        data.resize(capacity);
        
        for(int i=0; i < oldTable.size(); i++){
            if((oldTable[i].isOccupied == true) && (oldTable[i].isDeleted == false))
                insert(oldTable[i].key);
        }
        
        return true;
    }
    catch( exception &error) {
        cerr << "Rehash failed: " << error.what() << endl;
        return false;
    }
}

void *hashTable::getPointer( const std::string &key, bool *b ) {
    int idx = findPos( key );

    if( idx != -1 && !data[idx].isDeleted ) {
        *b = true;
        return data[idx].pv;
    }

    *b = false;
    return NULL;
}

int hashTable::setPointer( const std::string &key, void *pv ) {
    int idx = findPos( key );

    if( idx == -1 )
        return 1;

    data[idx].pv = pv;

    return 0;
}



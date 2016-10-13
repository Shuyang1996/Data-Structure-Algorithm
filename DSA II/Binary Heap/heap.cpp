#include "heap.h"

//constructor
heap::heap (int capacity) {
	this->capacity = capacity;
	this->currentSize = 0;
	data.resize( capacity + 1 );
	hashMap = new hashTable ( capacity *2 );
}

//percolateUp function
void heap::percolateUp( int key ) {
	node hole = data[key];

	//position of parent node of each node is also at i/2
	//based on heap order, if child node is smaller than parent then we keep percolating up
	while ( (key > 1) && ( hole.key < data[key/2].key ) ) {
		data[key] = data[key/2]; //push hold into parent node
		hashMap->setPointer ( data[key].id, &data[key] );
		key = key / 2;
	}

	// key will be the new value 
	data[key] = hole;
	hashMap->setPointer( data[key].id, &data[key] );
	return;
}

//percolateDown function

void heap::percolateDown( int key ) {

}

// Returns true if the given index needs to be percolated up 
bool heap::needPercolateUp( int key ) {
    return ( data[key].key < data[key/2].key );
}


// Returns true if the given index needs to be percolated down
bool heap::needPercolateDown( int key ) {
	return ( ( ( key * 2 <= filled ) && ( data[key].key > data[key*2].key ) ) || ( ( idx * 2 + 1 <= filled ) && ( data[idx].key > data[idx*2+1].key ) ) || ( idx == 1 ) );
}

//insertion
int heap::insert (const std:string &id, int key, void *pv ) {
	if( currentSize >= capacity ) return 1;  // return 1 if the heap is already filled to capacity

	if( hashMap->contains(id) ) return 2;
	//   2 if a node with the given id already exists (but the heap is not filled to capacity)

	currentSize++ // if none of the above statements were true, then increase currentSize by 1, 
	//also first item index starts from 1 in order to maintain the math logic
    
	//then store new data
    data[currentSize].id = id;
    data[currentSize].key = key;
    data[currentSize].ptr = pv;

    hashMap->insert(id, &data[currentSize]);
    percolateUp (currentSize);
    return 0; // return 0 means successfully insert an item

}
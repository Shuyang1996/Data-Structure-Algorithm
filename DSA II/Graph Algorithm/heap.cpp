#include "heap.h"

//constructor
heap::heap (int capacity) {
	this->capacity = capacity;
	this->currentSize = 0;
	data.resize( capacity + 1 );
	hashMap = new hashTable ( capacity * 2 );
}

//percolateUp function
void heap::percolateUp( int key ) {
	//create a hole
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
	node hole = data[key]; // this will 
	int tmp;

	while( ( key * 2) <= currentSize ) { //check if we have put the last element into proper position
		tmp = key * 2;

		if( tmp != currentSize && data[tmp+1].key < data[tmp].key ) tmp++; // push smaller value item into hole, and push hole one level below

		if( data[tmp].key < hole.key ) {

			//swap;
			data[key] = data[tmp];
			hashMap->setPointer(data[key].id, &data[key] );
		} else 
			break;

		//update new position and repeat percolate procedure again
		key = tmp;

	}

	// swap the value
	data[key] = hole;
	hashMap->setPointer(data[key].id, &data[key] );
}

// Returns true if the given index needs to be percolated up 
bool heap::needPercolateUp( int key ) {
    return ( data[key].key < data[key/2].key );
}


// Returns true if the given index needs to be percolated down
bool heap::needPercolateDown( int key ) {
	return ( ( ( key * 2 <= currentSize ) && ( data[key].key > data[key*2].key ) ) || ( ( key * 2 + 1 <= currentSize ) && ( data[key].key > data[key*2+1].key ) ) || ( key == 1 ) );
}

int heap::getPosition( node *pn ) {
    return ( pn - &data[0] );
}

//insertion
int heap::insert (const std::string &id, int key, void *pv ) {
	if( currentSize >= capacity ) return 1;  // return 1 if the heap is already filled to capacity

	if( hashMap->contains(id) ) return 2;
	//   2 if a node with the given id already exists (but the heap is not filled to capacity)

	currentSize++; // if none of the above statements were true, then increase currentSize by 1, 
	//also first item index starts from 1 in order to maintain the math logic
    
	//then store new data
    data[currentSize].id = id;
    data[currentSize].key = key;
    data[currentSize].ptr = pv;

    hashMap->insert(id, &data[currentSize]);
    percolateUp (currentSize);
    return 0; // return 0 means successfully insert an item

}

//delete the node with the specified id from the binary heap
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
	if(currentSize == 0) {
		return 1; //cannot remove element if current heap is 0
	}

	if( pId )
        *pId = data[1].id; // id of root element
    if( pKey )
        *pKey = data[1].key; // key of root element
	if( ppData )
		*(static_cast<void **> (ppData)) = data[1].ptr;

    // Remove first item and replace with last
    // then percoalteDown
    hashMap->remove( data[1].id );
    data[1] = data[currentSize--];
    hashMap->setPointer( data[1].id, &data[1] );
    percolateDown( 1 );

    return 0;

}

int heap::setKey(const std::string &id, int key) {
	bool exist = false;
	node *pn = static_cast<node *> ( hashMap->getPointer( id, &exist ) );

	if( !exist )
		return 1; // if this does not exist

	//find position
    int index = getPosition( pn );

    //update new key
    data[index].key = key;
    
    // after update the key value on of this item, check if we need to move this item up/down to a proper position
    if( needPercolateDown( index ) )
        percolateDown( index );
    else if( needPercolateUp( index ) )
        percolateUp( index );

    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
	bool exist = false;
	node *pn = static_cast<node *> ( hashMap->getPointer( id, &exist ) );

	if( !exist )
		return 1;

    int index = getPosition( pn );

    // update pKey and ppData value if they are given
    if( pKey )
        *pKey = data[index].key;
	if( ppData )
		*(static_cast<void **> (ppData)) = data[index].ptr;

    hashMap->remove( data[index].id );
    data[index] = data[currentSize--];

    
    if( currentSize == 0 )
        return 0;

    // Update pointer 
    hashMap->setPointer( data[index].id, &data[index] );

    // Perform appropriate percolate
    if( needPercolateDown( index ) )
        percolateDown( index );
    else if( needPercolateUp( index ) )
        percolateUp( index );

    return 0;
}




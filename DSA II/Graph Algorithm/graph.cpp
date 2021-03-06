#include "graph.h"

//initial constructor
graph::graph ( ifstream &input ) {
	//create hash table;
	this->vertexLookup =  new hashTable (1000); 

	//load graph;
	string line;
	string source;
	string destination;
	int cost;

	while ( getline(input, line) ) {
		istringstream stream (line);
		stream >> source >> destination >> cost;
		this->addEdge(source, destination, cost);
	}
}

bool graph::isVertex( string name ) {
	return this->vertexLookup->contains( name );
}

bool graph::addVertex( string name ) {
	//check if a certain vertex has been added already
	if ( this->isVertex(name) ) 
		return false;

	vertex * newVertex = new vertex();
	newVertex->name = name;

	this->vertexLookup->insert( name, newVertex );
	this->vertexList.push_back( newVertex );

	return true;
}

void graph::addEdge( string source, string destination, int cost ) {
	
	this->addVertex( source );
	this->addVertex( destination );
	
	bool exists;
	vertex * sourceVertex = static_cast < vertex * > ( this->vertexLookup->getPointer( source, &exists) );
	vertex * destinationVertex = static_cast < vertex * > ( this->vertexLookup->getPointer( destination, &exists) );

	edge * newEdge = new edge();
	newEdge->cost = cost;
	newEdge->destination = destinationVertex;

    sourceVertex->adjacent.push_back( newEdge );
	
	return;
}

void graph::dijkstra ( string source ) {
	//intialize binary heap
	heap bh ( this->vertexList.size() + 1 );

	list <vertex * > :: iterator a;

	//initialize all nodes;

	for( a = this->vertexList.begin(); a != this->vertexList.end(); a++ ) {
		if( (*a)->name == source ) {
			(*a)->distance = 0;
		} else {
			(*a)->distance = INT_MAX;
		}

		(*a)->known = false;
		(*a)->prev = NULL;
		bh.insert( (*a)->name, (*a)->distance, (*a) );
	}

	vertex * d;

	while( bh.deleteMin( NULL, NULL, &d ) != 1 ) {
		d->known = true; 
		if( d->distance == INT_MAX ) // No path to vertex 
            continue;

        list < edge * > :: iterator b;
        int cost;

        for ( b = d->adjacent.begin(); b!= d->adjacent.end(); b++ ) {
        	cost = d->distance + (*b)->cost;

        	if( cost < (*b)->destination->distance ) { // If cost is better than best cost so far
                (*b)->destination->distance = cost; // Update cost in vertex
                bh.setKey( (*b)->destination->name, cost ); // Update cost in heap to percolate 
                (*b)->destination->prev = d; // Best known vertex
            }
        }
	}
	return;
}


void graph::write( ofstream &output ) {
	
	list < vertex * > :: iterator c;
	vertex * v;
	string vname;

	for ( c = this->vertexList.begin(); c !=  this->vertexList.end(); c++ ) {
		
		output << (*c)-> name << ": ";

		if( (*c)-> distance == INT_MAX ){
			output << "NO PATH" << endl;
		} else if ( (*c)->distance == 0 ) { //itself
			output << (*c)->distance << " [" << (*c)->name << "]" << endl;
		} else { // multiple vertices
			output << (*c)-> distance << " [";
			vname = (*c)->name;
			while( (*c)->prev != NULL ) {
				vname = (*c)->prev->name + ", "+ vname;
				(*c) = (*c)->prev;
				
			}
			output << vname <<"]" << endl;
		}

	}
	return;
}

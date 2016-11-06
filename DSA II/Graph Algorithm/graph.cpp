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
		this -> addEdge(source, destination, cost);
	}
}

bool graph::isVertex( string name ) {
	return this->vertexLookup->contains( name );
}

void graph::addVertex( string name ) {
	//check if a certain vertex has been added already
	if ( this->isVertex ) 
		return false;

	vertex * newVertex = new vertex();
	newVertex->name = name;

	this->vertexLookup->insert( name, newVertex );
	this->vertexList.push_back( newVertex );
}

void graph::addEdge( string source, string destination, int cost ) {
	this->addVertex( source )
	this->addVertex( destination );

	bool exists;
	vertex * sourceVertex = static_cast < vertex * > ( this->vertexLookup->getPointer(source) );
	vertex * destinationVertex = static_cast < vertex * > ( this->vertexLookup->getPointer(destination) );

	edge * newEdge = new edge();
	newEdge->cost = cost;
	newEdge->destination = destinationVertex;

	sourceVertex->ajacent.push_back( newEdge );

	return; 

}













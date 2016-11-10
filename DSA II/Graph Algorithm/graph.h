#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"

#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class graph {

	public:
		//initial constructor
		graph ( ifstream &input );

		//dijkstra algorithm (what is src in this case? )
		void dijkstra( string source );

		//write graph to a specific output file
		void write( ofstream &output );

		//check if a given string a vertex in the graph
		bool isVertex( string name );

	private:
		//adds a vertex to the graph and return false if this vertex has been processed already
		bool addVertex (string name);

		//adds an edge to graph
		void addEdge ( string source, string destination, int cost );

		class edge;
		class vertex;

		class edge {
			public:
				int cost;
				vertex * destination;
		};

		class vertex {
			public:
				string name;
				list < edge * > adjacent; //ajacent edges associated with each vertex
				vertex * prev; // previous vertex that leads to this vertex
				bool known;
				int distance;
		};

		//list of vertices
		list <vertex * > vertexList;

		//hash table for a vertex to ptr lookup
		hashTable * vertexLookup;
};

 
#endif //_GRAPH_H
#include "graph.h"

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main () {
	string buf;

	//prompt for input file
	cout << "Enter name of graph file: ";
	cin >> buf;

	//open graph file
	ifstream graphFile ( buf.c_str() );
	
	if( !graphFile.is_open() ){
		cout << "File \"" << buf << "\" was not found." << endl;
		exit(1);
	}

	//create graph based on input file
	graph directedGraph (graphFile); 
	//enter starting vertex
	for( ;; ) {
		cout << "Enter a valid vertex id for the starting vertex: ";
		cin >> buf;
		if( directedGraph.isVertex(buf) )  break; // if the entered vertex is valid then exit this for loop;

		//if the entered vertex is not valid, then execute the code below
		// clear cin and then skips to the next new line
		cin.clear(); 
		cin.ignore( 1000, '\n');

	}

	//calculate time
	clock_t t1 = clock();
	directedGraph.dijkstra(buf);
	clock_t t2 = clock();

	double time = ( (double) (t2 - t1) ) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time << endl;

	// prompt for output file
	cout << "Enter name of output file: ";
	cin >> buf;


	//open output file
	ofstream output ( buf.c_str() );

	if ( !output.is_open() ) {
		cout << "File \"" << buf << "\" was not found." << endl;
		exit(1);
	}

	//write to output file
	directedGraph.write(output);

	return 0;
}
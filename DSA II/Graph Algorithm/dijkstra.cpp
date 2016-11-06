#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "graph.h"

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
	graph g (input); // need to revise on this one

	//enter starting vertex


	//calculate time
	clock_t t1 = clock();
	g.dijkstra(buf);
	clock_t t2 = clock();

	double time = ( (double) (t2 - t1) ) / CLOCKS_PER_SEC;


	// prompt for output file


	//write to output file


	return 0;
}
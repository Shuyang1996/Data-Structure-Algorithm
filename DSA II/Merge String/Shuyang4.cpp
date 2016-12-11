#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#define A 0
#define B 1
#define C 2

#define MAX 1001

int arr[MAX][MAX] = {0}; //initialize matrix
string checker( string *str );

int main () {

	string str[3]; // store three input strings
	string buffer; // temprorary storage area

	cout << "Enter name of input file: "; // prompt for input and output files, return 1 if failure ocurred.
	cin >> buffer;
	ifstream input( buffer.c_str() );

	if( !input.is_open() ) { // opening input file failed
		cout << "File \"" << buffer <<"\" was not found." << endl;
		return 1;
	}

	cout << "Enter name of output file: "; //prompt for input and output files, return 2 if failure ocurred
	cin >> buffer;
	ofstream output( buffer.c_str() );
	if( !output.is_open() ) {
		cout << "Unable to open output file \"" << buffer << "\""<< endl;
		return 2; 
	}

	while( getline(input, str[A]) && getline(input, str[B]) && getline(input,str[C]) ) {
		output << checker(str) << endl;
	}

	input.close();
	output.close();

	return 0;
}

// string merge checker
string checker( string *str ) {
	
	int length[3] = { str[A].length(), str[B].length(), str[C].length() };
	
	// basic check: merged string size, if it is not correct, end program immediately in order to save time and memory.
	if ( (length[A] + length[B]) != length[C] )  return "*** NOT A MERGE ***";
	

	//initialize array
	memset( arr, 0, sizeof( arr ) );
	arr[0][0] = 1;

	// fill up matrix in order to merge the paths
	for ( int i = 0; i <= length[A]; i++ ) {
		for (int j = 0; j <= length[B]; j++ ) {
			if( arr[i][j] == 0 ) continue;
			if( str[C][i+j] == str[A][i] ) arr[i+1][j] = 1;
			if( str[C][i+j] == str[B][j] ) arr[i][j+1] = 1;
		}
	}

	//if it does not reach last character of both strings, string is not properly merged
	if ( arr[length[A]][length[B]] == 0 ) return "*** NOT A MERGE ***";

	// Trace path backwards

	while (length[A] > 0 && length[B] >= 0 ) {
		
		if( arr[length[A]][length[B]] == 1 && ( length[B] == 0 || arr[length[A]][length[B]-1] == 0 ) ) {
            str[C][length[A]+length[B]-1] = toupper( str[C][length[A]+length[B]-1] );
            length[A]--;

        } else {
            str[C][length[A]+length[B]-1] = tolower( str[C][length[A]+length[B]-1] );
            length[B]--;
        }
	}

	return str[C];
}
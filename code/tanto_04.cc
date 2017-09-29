#include "Integer.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
string rotate( string in );
Integer next( const char * in );
string build_string( int len, int ceros, int near, int gap );

int main( int argc, char * argv[] ) {

	// test de Integer number
	Integer bigInt = argv[1];
	bigInt.print();
	bigInt.setbase(2);
	bigInt.print();
	cout << digits(bigInt,2) << "\n";
	bigInt.setbase(10);
	bigInt.print();

	Integer sq = Sqrt( bigInt );
	sq.print();

	// build a string of ONES
	int ones_len = digits( sq, 2 );
	string ones( ones_len, '1' );
	const char * num = ones.c_str();
	Integer new_int( num, 2 );
	new_int.print();

	// build a string of CEROS
	int ceros_len = 1;
	string ceros( ones_len, '0' );

	string test = build_string( ones_len, 3, 3, 2 );
	cout << test << "\n";
}

// Rotacion de la string
string rotate( string in ){

	string::size_type len = in.length();
	string out;
	out = in.substr(1, len - 1) + in[0];
	return out;

}

// Siguiente Integer binario
Integer next( const char * in ){

	string str = in;
	str = rotate( str );
	const char * num = str.c_str();
	Integer out( num, 2 );
	return out;

}

// Build a binary string
string build_string( int len, int ceros, int near, int gap ){

	int i, j;
	string out( len, '1' );
	int mul = (len - (ceros * near) - ((ceros - 1) * gap));
	for( i = (len - 1); i >= mul; i -= (gap+1) ){
		for( j = 0; j < near; j++ ){
			out[ i-- ] = '0';
		}
	}
	return out;
}


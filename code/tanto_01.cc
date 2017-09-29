#include "Integer.h"
#include "bitset.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
string rotate( string in );
Integer next( const char * in );

int main( int argc, char * argv[] ) {

	// test de bitset
	static int vec = 10;
	bitset vector;
	vector.set_size(vec);
	vector.print();

	// test de Integer number
	Integer bigInt = "20938476454736534252437397328734634664";
	bigInt.print();
	bigInt.setbase(2);
	bigInt.print();
	cout << digits(bigInt,2) << "\n";
	bigInt.setbase(10);
	bigInt.print();

	// test de Integer desde char * en base 2
	const char * number = "1111111111111111111111111111111111111111111111111111111111111111111111111111111110";
	Integer newInt(number,2);
	newInt.print();
	newInt.setbase(10);
	newInt.print();

	newInt = next( number );
	newInt.print();

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

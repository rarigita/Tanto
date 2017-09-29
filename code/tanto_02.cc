#include "Integer.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
string rotate( string in );
Integer next( const char * in );

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
	string test = "";

	while( ceros_len < ones_len ){
		
		test = ones.substr(1,ones_len-ceros_len) + ceros.substr(1,ceros_len);
		const char * new_num = test.c_str();
		Integer w_int( new_num, 2 );
		w_int.print();
		for( int i = 0 ; i < (ones_len - ceros_len - 1) ; i++ ){
			test = rotate( test );
			new_num = test.c_str();
			w_int = new_num;
			w_int.print();
		}
		ceros_len++;
	}
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

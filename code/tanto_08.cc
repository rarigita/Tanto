/* Introduzco Random Generators */

#include "Integer.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#include <sys/time.h>
#include "randomc/randomc.h"
#include "randomc/userintf.cpp"
#include "randomc/mother.cpp"

using namespace std;

string rotate( string in );
Integer next( string in );
string build_determ_string( int len, int count, int near, int gap );
string build_random_string( int len );
void determ_loop( Integer key );

int main( int argc, char * argv[] ) {

	// test de Integer number
	Integer key = argv[1];
	key.print();
	key.setbase(2);
	key.print();

	Integer sq = Sqrt( key );
	sq.print();

	// build a string of ONES
	int sq_len = digits( sq, 2 );
	string ones( sq_len, '1' );
	const char * num = ones.c_str();
	Integer new_int( num, 2 );

	string test = build_determ_string( sq_len, 2, 3, 2 );
	cout << test << "\n";

	string rand = build_random_string( sq_len );
	cout << rand << "\n";

	determ_loop( key );
}

// Rotacion de la string
string rotate( string in ){

	string::size_type len = in.length();
	string out;
	out = in.substr(1, len - 1) + in[0];
	return out;

}

// Return Integer binario a partir de la string
Integer next( string in ){

	Integer out( in.c_str(), 2 );
	out.setbase(10);
	return out;

}

// Build a binary string
string build_determ_string( int len, int count, int near, int gap ){

	int i, j;
	string out( len, '1' );
	int mul = (len - count);
	for( i = (len - 1); i >= mul; i -= (gap) ){
		for( j = 0; j < near; j++ ){
			out[ i-- ] = '0';
		}
	}
	return out;
}

string build_random_string( int len ){

	struct timeval * tv1 = new timeval ;
	struct timezone * tz = NULL ;
	gettimeofday(tv1,tz);
	int32 seed = tv1->tv_usec ;			// random seed
	int i;					// loop counter
	double r;				// random number
	int32 ir;				// random integer number
	string out( len, '1' );
	TRandomMotherOfAll mother( seed );	// make instance of random number generator
	for ( i = 1 ; i < len ;  i++ ) {
		ir = mother.IRandom( 0, 1 );
		if( ir != 1 ){
			out[i] = '0';
		} 
	}
	return out;
}

// generate all posible parameters for build_determ_string()
void determ_loop( Integer key ){

	int a = 0;
	int b = 1;
	int c = 0;
	int exit = 0;
	int count = 0;

	Integer sq = Sqrt( key );
	int MAX_LEN = digits( key, 2 );
	int MIN_LEN = digits( sq, 2 );

	string determ_string;
	string random_string;

	Integer vector_d;
	Integer vector_r;
	Integer yo, li, left, right;

	while( !exit ){

		count = ( a * b ) + ((a-1) * c );

		if( MIN_LEN  > count ){
			// output test.. change to call build_determ_string()
			// cout << build_determ_string( MIN_LEN, count, b, c ) << "  ";
			// cout << build_random_string( MIN_LEN ) << "\n";

			determ_string = build_determ_string( MIN_LEN, count, b, c );
			random_string = build_random_string( MIN_LEN );

			vector_d = next( determ_string );
			vector_r = next( random_string );

			left = key * vector_d;
			right= key - vector_d;
			yo = gcd( left, right );
			
			left = key * vector_r;
			right= key - vector_r;
			li = gcd( left, right );

			if( yo != 1 || li !=1 ){
				yo.print();
				li.print();
				exit = 1;
			}

			a++;
			
		}
		else if( a > 2 ){
			a = 2;
			b++;
			if( b == 2 && c == 0 ){
				a = 2;
				b = 1;
				c++;
			}
		}
		else if( a >= 2 && b !=1 ){
			a = 2;
			b = 1;
			c++;
		}
		else if( MIN_LEN <= MAX_LEN ){
			a = 0;
			b = 1;
			c = 0;
			MIN_LEN++;
		}
		else{
			exit = 1;
		}
	
	}

}

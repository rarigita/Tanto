/* Introduzco Random Generators from stocc.h*/
/* Memory leak !! */

#include "Integer.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#include <sys/time.h>
#include "randomc/randomc.h"
#include "randomc/userintf.cpp"
#include "randomc/mersenne.cpp"
#include "randomc/stocc.h"
#include "randomc/stoc1.cpp"

using namespace std;

string * rotate( string in[] );
string rotate( string in );
Integer next( string in );
string build_determ_string( int len, int count, int near, int gap );
string * build_random_string( int len );
void determ_loop( Integer key );

int main( int argc, char * argv[] ) {

	// test de Integer number
	Integer key = argv[1];
	// run main loop
	determ_loop( key );

}

// Rotacion de array de strings
string * rotate( string in[] ){

	int i;
	string * out = new string[3];
	string tmp = "";
	string::size_type len = in[0].length();
	for( i = 0; i < 3; i++ ){
		tmp = in[i].substr(1, len - 1);
		out[i] = "1" + tmp.substr(1, len - 1) + tmp[0];
	}
	return out;

}

// Rotacion de una string
string rotate( string in ){
	int i;
	string out = "";
	string tmp = "";
	string::size_type len = in.length();
	tmp = in.substr(1, len-1);
	out = "1" + tmp.substr(1, len-1) + tmp[0];
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

// Build 3 random strings with different distributions
string * build_random_string( int len ){

	string * out = new string[3];
	string ones( len, '1' );
	struct timeval * tv1 = new timeval ;
	struct timezone * tz = NULL ;
	gettimeofday(tv1,tz);
	int32 seed = tv1->tv_usec ;		// random seed
	int i,j;				// loop counter
	double r;				// random number
	int32 ir;				// random integer number
	StochasticLib1 stoc( seed );		// make instance of random number generator
	out[0] = ones;
	out[1] = ones;
	out[2] = ones;
	for ( i = 1 ; i < len ;  i++ ) {
		ir = stoc.IRandom( 0, 1 );
		if( ir != 1 ){
			out[0][i] = '0';
		}
		ir = stoc.Binomial( 2, 0.25 );
		if( ir != 1 ){
			out[1][i] = '0';
		}
		ir = stoc.Hypergeometric( 1, 1, 2 );
		if( ir != 1 ){
			out[2][i] = '0';
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
	int rota = 0;

	Integer sq = Sqrt( key );
	int MAX_LEN = digits( key, 2 ) + 1;
	int MIN_LEN = digits( sq, 2 ) - 1;

	string determ_string;
	string * random_string = new string[3];

	Integer vector_d;
	Integer vector_r1, vector_r2, vector_r3;
	Integer yo, li, ma, ry, left, right;

	cout << "Key bits length: " << MAX_LEN-1 << "\n";
	cout << "Sqr bits length: " << MIN_LEN+1 << "\n";

	while( !exit ){

		count = ( a * b ) + ( (a-1) * c );

		if( MIN_LEN  > count ){

			determ_string = build_determ_string( MIN_LEN, count, b, c );
			random_string = build_random_string( MIN_LEN );

			while( (rota < MIN_LEN - 1) && !exit ){

				// Test: send strings to cout

				vector_d = next( determ_string );
				vector_r1 = next( random_string[0] );
				vector_r2 = next( random_string[1] );
				vector_r3 = next( random_string[2] );

				left = key * vector_d;
				right= key - vector_d;
				yo = gcd( left, right );
		
				left = key * vector_r1;
				right= key - vector_r1;
				li = gcd( left, right );

				left = key * vector_r2;
				right= key - vector_r2;
				ma = gcd( left, right );

				left = key * vector_r3;
				right= key - vector_r3;
				ry = gcd( left, right );

				if( yo != 1 || li !=1 || ma != 1 || ry != 1 ){
					yo.print();
					li.print();
					ma.print();
					ry.print();
					exit = 1;
				}

				// test output of rotate function
				// vector_d.print();
				determ_string = rotate( determ_string );
				random_string = rotate( random_string );
				rota++;
			}

			a++;
			rota = 0;	
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

/**************************************************************
 *  Factorization Algorithms by Rodrigo Arigita, Feb 2003     *
 **************************************************************
 *  Lenstra.cc                                                *
 *    Uses Lenstra algorithm to factorize a large Integer     *
 *                                                            *
 *  Compile:                                                  *
 *    g++ -g -o Lenstra Lenstra.cc Integer.o -lgmp            *
 *                                                            *
 *  Run:                                                      *
 *    ./Lenstra <number_to_factor> [ Initial K ]              *
 **************************************************************/

#include <sys/time.h>
#include "Integer.h"

#define A_INCR	30
#define MAX_As  (A_INCR * 40)	// number of a changes before making new curve
#define START_X  1		// x coordinate of the initail point to try
#define START_Y  1		// y coordinate of the initail point to try
#define DISC(a,b) (Integer) ( (4*a*a*a) + (27*b*b) ) 	// Compute discriminant

Integer get_K( Integer ) ;
Integer get_factor( Integer, Integer ) ;

int main( int argc , char * argv[] ) {

	// Structures to control initial,
	// final and total running time
	struct timeval * tv1 = new timeval ;
	struct timeval * tv2 = new timeval ;
	struct timeval * tvt = new timeval ;
	struct timezone * tz = NULL ;

	Integer key, factor, K ;

	// get start time
	gettimeofday(tv1,tz);

	cout << "\n\tLenstra's Factoring Algorithm\n" ;
	cout << "\t-----------------------------\n" << flush ;

	if ( argc < 2 ) {
		cerr << "Usage: " << argv[ 0 ] << " <number_to_factor> [ Initial K ]" << endl ;
		cerr << "For an example: " << argv[ 0 ] << " 1715761513 25" << endl ;
		return -1 ;
	}

	key = argv[ 1 ] ;
	if ( argc == 3 ) K = argv[ 2 ] ;
	else K = get_K( key ) ;            // default K if none given

	cout << "Number to factor: " << key << endl ;
	cout << "Factors found: " << flush ;

	if ( isprime( key ) ) {
		cout << key << " is prime !" << endl ;
		return 0 ;
	}

	// main loop
	while ( ! isprime( key ) ) {
		factor = get_factor( key , K ) ;
		cout << factor << " x " << flush ;
		key /= factor ;
		if ( argc != 3 ) K = get_K( key ) ;
	}

	cout << key << endl ;

	// get finish time
	gettimeofday(tv2,tz);
	// get total time
	timersub(tv2,tv1,tvt);
	cout << "Total Running time: " << tvt->tv_sec << "s " ;
	cout << tvt->tv_usec << "mcs\n\n" ;

	return 0 ;
}


Integer get_K( Integer n ) {
	Integer K ;
	K = (int) logn( n , 10 ) ;
	K = K * K / 2 ;
	if ( K < 2 ) K = 2 ;
	return K ;
}


Integer get_factor( Integer key , Integer K ) {

	Integer a, b, k, g, x, y ;
	Integer tmp_x, tmp_y, sum_x, sum_y, grad;
	int bits ;
	bool newcurve ;

	if ( key % 2 == 0 ) return 2 ;
	if ( key % 3 == 0 ) return 3 ;
	if ( key % 5 == 0 ) return 5 ;
	if ( key % 7 == 0 ) return 7 ;

	a = 1 ;
	k = LCM( K ) ;
	bits = log2( k ) ;

	for ( ; ; ) {

		x = START_X ;
		y = START_Y ;
		b = ( y * y ) - ( x * x * x ) - ( a * x ) ;

		// Make a valid curve
		g = gcd( DISC( a , b ) , key ) ;
		while ( g != 1 ) {
			if ( g < key ) {
				if ( ! isprime( g ) )
					return get_factor( g , K ) ;
				else return g ;
			}
			else {
				a += A_INCR ;
				b = ( y * y ) - ( x * x * x ) - ( a * x ) ;
				g = gcd( DISC( a , b ) , key ) ;
			}
		}

		sum_x = 0 ;
		sum_y = 0 ;
		newcurve = false ;

		if ( a < MAX_As ) {

			for ( int i = 1 ; i <= bits ; i ++ ) {	// compute k*(x, y)
								// using powers of 2
				tmp_x = x ;
				tmp_y = 2 * y ;
				g = gcd( tmp_y , key ) ;

				if ( 1 < g && g < key ) {
					if ( ! isprime( g ) )
						return get_factor( g , K ) ;
					else return g ;
				}
				if ( g == key ) {
					newcurve = true ;
					break ;
				}

				grad = InvModN( tmp_y , key ) * ( 3 * ( x * x ) + a ) ;
				x = ( grad * grad - 2 * x ) % key ;
				y = ( grad * ( tmp_x - x ) - y ) % key ;

				if ( ! testbit( k , i ) )
					continue ;
				if ( ! sum_y ) {
					sum_x = x ;
					sum_y = y ;
					continue ;
				}

				//Need to add {x,y} in to sum_{x,y}
				tmp_x = ( x - sum_x ) % key ;	// 2P = (x-sum_x,y)
				tmp_y = ( y - sum_y ) % key ;
				g = gcd( tmp_x , key ) ;
				if ( 1 < g && g < key ) {
					if ( ! isprime( g ) )
						return get_factor( g , K ) ;
					else return g ;
				}
				if ( g == key ) {
					newcurve = true ;
					break ;
				}
				grad = InvModN( tmp_x , key ) * tmp_y ;
				tmp_x = ( ( grad * grad - sum_x ) - x ) % key ;
				tmp_y = ( grad * ( sum_x - tmp_x ) - sum_y ) % key ;
				sum_x = tmp_x ;
				sum_y = tmp_y ;
			}
		}
		else newcurve = true ;

		if (newcurve) {
			while ( k == LCM(K) ) K ++ ;
			a = 1 ;
			k = LCM(K) ;
			bits = log2(k) ;
		}
		else a += A_INCR ;
	}
}

/* <rou@papelmail.com> */

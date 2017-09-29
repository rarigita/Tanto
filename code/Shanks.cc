/**************************************************************
 *  Factorization Algorithms by Rodrigo Arigita, Feb 2003     *
 **************************************************************
 *  Shanks.cc                                                 *
 *    Factor any integer using Shank's algorithm              *
 *                                                            *
 *  Compile:                                                  *
 *    g++ -g -o Shanks Shanks.cc Integer.o -lgmp              *
 *                                                            *
 *  Run:                                                      *
 *    ./Shanks <number_to_factor>                             *
 **************************************************************/

#include <sys/time.h>
#include "Integer.h"

Integer get_factor( Integer ) ;

int main ( int argc , char * argv[] ) {

	// Structures to control initial,
	// final and total running time
	struct timeval * tv1 = new timeval ;
	struct timeval * tv2 = new timeval ;
	struct timeval * tvt = new timeval ;
	struct timezone * tz = NULL ;

	Integer key , factor ;

	// get start time
	gettimeofday(tv1,tz);

	cout << "\n\tShank's SQUFOF Factoring Algorithm\n" ;
	cout << "\t----------------------------------\n" << flush ;

	if ( argc != 2 ) {
		cerr << "Usage: " << argv[0] << " <number_to_factor>" << endl ;
		return -1 ;
	}

	key = argv[1] ;

	cout << "Number to factor: " << key << endl ;
	cout << "Factors found: " << flush ;

	if ( isprime( key ) ) {
		cout << key << " is prime !" << endl ;
		return 0 ;
	}

	// main loop
	while ( ! isprime( key ) ) {
		factor = get_factor( key ) ;
		cout << factor << " x " << flush ;
		key /= factor ;
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


Integer get_factor( Integer key ) {

	Integer factor, num, sqrt, den;
	Integer	Q_i, x_i, b_i, A_0, A_1, A_i ;
	int i = 0;

	if ( key % 2 == 0 ) return 2 ;
	if ( key % 3 == 0 ) return 3 ;
	if ( key % 5 == 0 ) return 2 ;
	if ( key % 7 == 0 ) return 3 ;
	
	sqrt = Sqrt( key ) ;
	if ( issquare( key ) ) return sqrt ;

	b_i = sqrt ;
	x_i = sqrt ;
	A_0 = sqrt ;
	A_1 = 1 ;
	num = 1 ;

	for( ; ; ) {
		i ++ ;
		Q_i = key - ( x_i * x_i ) ;
		Q_i /= num ;
		b_i = ( sqrt + x_i ) / Q_i ;
		x_i = ( Q_i * b_i ) - x_i ;
		num = Q_i ;
		if( issquare( Q_i ) && i % 2 == 0 ) {
			den = Sqrt( Q_i ) ;
			factor = gcd( A_i - den , key ) ;
			if( factor > 1 && factor < key ) {
				if( isprime( factor ) ) return factor ;
				else return get_factor( factor ) ;
			}
		}
		A_i = ( ( b_i * A_0 ) + A_1 ) % key ;
		A_1 = A_0 ;
		A_0 = A_i ;
	}

}

/* <rou@papelmail.com> */

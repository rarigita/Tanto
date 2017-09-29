/**************************************************************
 *  Factorization Algorithms by Rodrigo Arigita, Feb 2003     *
 **************************************************************
 *  Trial_division.cc                                         *
 *    Factor any integer using trial division                 *
 *    algorithm with 2, 3, 6k-+1 for k=1,2,..                 *
 *                                                            *
 *  Compile:                                                  *
 *    g++ -g -o Trial Trial_division.cc Integer.o -lgmp       *
 *                                                            *
 *  Run:                                                      *
 *    ./Trial <number_to_factor>                              *
 **************************************************************/

#include <sys/time.h>
#include "Integer.h"

Integer get_factor( Integer ) ;

int main(int argc, char *argv[]) {

	// Structures to control initial,
	// final and total running time
	struct timeval * tv1 = new timeval ;
	struct timeval * tv2 = new timeval ;
	struct timeval * tvt = new timeval ;
	struct timezone * tz = NULL ;

	Integer key , factor ;

	// get start time
	gettimeofday(tv1,tz);

	cout << "\n\tTrial Division Factoring Algorithm\n" ;
	cout << "\t----------------------------------\n" << flush ;

	if ( argc < 2 ) {
		cerr << "Usage: " << argv[0] << " <number_to_factor>" << endl ;
		return -1 ;
	}

	key = argv[ 1 ] ;
	factor = 5 ;
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

	Integer factor = 5 ;
	if ( key % 2 == 0 ) return 2 ;
	if ( key % 3 == 0 ) return 3 ;

	for ( ; ; ) {
		if ( key % factor == 0 ) {
			if ( isprime( factor ) ) return factor ;
			else return get_factor( factor ) ;
		}
		else if ( key % ( factor + 2 ) == 0 ) {
			if ( isprime( factor + 2 ) ) return ( factor + 2 ) ;
			else return get_factor( factor + 2 ) ;
		}
		else {
			factor += 6 ;
		}
	}
} 

/* <rou@papelmail.com> */

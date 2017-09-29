/**************************************************************
 *  Factorization Algorithms by Rodrigo Arigita, Feb 2003     *
 **************************************************************
 *  Fermat.cc                                                 *
 *    Uses Fermat method to factor a large Integer            *
 *                                                            *
 *  Compile:                                                  *
 *    g++ -g -o Fermat Fermat.cc Integer.o -lgmp              *
 *                                                            *
 *  Run:                                                      *
 *    ./Fermat <number_to_factor>                             *
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

	cout << "\n\tFermat's Factoring Algorithm\n" ;
	cout << "\t----------------------------\n" << flush ;

	if ( argc != 2 ) {
		cerr << "Usage: " << argv[0] << " <number_to_factor>" << endl ;
		return -1 ;
	}

	key = argv[ 1 ] ;
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

	Integer root, diff , trpone ;

	if ( key % 2 == 0 ) return 2 ;
	if ( key % 3 == 0 ) return 3 ;
	if ( key % 5 == 0 ) return 5 ;

	root = Sqrt( key ) ;
	if ( issquare( key ) ) {
		if ( isprime( root ) ) return root ;
		else return get_factor( root ) ;
	}

	root ++ ;
	trpone = ( 2 * root ) + 1 ;
	diff = ( root * root ) - key ;
	while ( ! issquare( diff ) ) {
		diff += trpone ;
		trpone += 2 ;
		root ++ ;
	}
	return ( root + Sqrt( diff ) ) ;
}

/* <rou@papelmail.com> */

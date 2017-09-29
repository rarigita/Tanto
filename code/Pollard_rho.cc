/**************************************************************
 *  Factorization Algorithms by Rodrigo Arigita, Feb 2003     *
 **************************************************************
 *  Pollard_rho.cc                                            *
 *    Uses Pollard rho method to factorize a large Integer    *
 *                                                            *
 *  Compile:                                                  *
 *    g++ -g -o Pollard_rho Pollard_rho.cc Integer.o -lgmp    *
 *                                                            *
 *  Run:                                                      *
 *    ./Pollard_rho <number_to_factor>                        *
 **************************************************************/

#include <sys/time.h>
#include "Integer.h"

Integer get_factor( Integer, int, Integer ) ;

int main ( int argc, char *argv[] ) {

	// Structures to control initial,
	// final and total running time
	struct timeval * tv1 = new timeval ;
	struct timeval * tv2 = new timeval ;
	struct timeval * tvt = new timeval ;
	struct timezone * tz = NULL ;
	
	Integer key , factor , x0 ;
	int a ;

	// get start time
	gettimeofday(tv1,tz);
	
	cout << "\n\tPollard rho Factoring Algorithm\n" ;
	cout << "\t-------------------------------\n" << flush ;

	if ( argc != 2 ) {
		cerr << "Usage: " << argv[ 0 ] << " <number_to_factor>" << endl ;
		return -1 ;
	}

	key = argv[ 1 ] ;
	x0 = 2 ;
	a = -1 ;
	
	cout << "Number to factor: " << key << endl ;
	cout << "Factors found: " << flush ;
	
	if ( isprime( key ) ) {
		cout << key << " is prime !" << endl ;
		return 0 ;
	}
	
	while ( !isprime( key ) ) {
		factor = get_factor( key , a , x0 ) ;
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


Integer get_factor( Integer key , int a , Integer x ) {

	Integer y , q , g ;

	if ( key % 2 == 0 ) return 2 ;
	if ( key % 3 == 0 ) return 3 ;
	if ( key % 5 == 0 ) return 5 ;
	if ( key % 7 == 0 ) return 7 ;
  
	y = x ; q = 1 ;

	for ( int i = 1 ; ; i++ ) {
	  
		x  = ( ( x * x ) + a )  %  key ;
		y  = ( ( y * y ) + a )  %  key ;
		y  = ( ( y * y ) + a )  %  key ;
		q *= ( x - y ) ;
		q  = q % key ; 
	
		if ( ( i % 10 ) == 0 ) {
			g = gcd( key , q ) ;
			if ( g > 1 && g < key ) {
				if ( !isprime( g ) )
					return get_factor( g , a , x ) ;
				else return g ;
			}
		} 
	} 
} 

/* <rou@papelmail.com> */

/**************************************************************
 *  Factorization Algorithms by Rodrigo Arigita, Feb 2003     *
 **************************************************************
 *  Special Thank's to Mike Roig for his collaboration in     *
 *  this algorithm and the bitset.{cc,h} class.  Feb 2003     *
 **************************************************************
 *  QS.cc                                                     *
 *    Uses Pomerance's Quadratic Sieve algorithm to factorize *
 *    a large composite Integer                               *
 *                                                            *
 *  Compile:                                                  *
 *    g++ -g -o QS QS.cc bitset.cc Integer.o -lgmp            *
 *                                                            *
 *  Run:                                                      *
 *    ./QS <number_to_factor>                                 *
 **************************************************************/

#include "Integer.h"
#include "bitset.h"
#include <math.h>
#include <sys/time.h>

// Silverman et. al. and Pomerance
// Thresold, Factor Base length and Sieve range
#define LN(x) ( log2(x) * log(2) )
#define T ( 0.0268849 * len + 0.783929 )
#define M(n) ( (pow(exp(sqrt(LN(n)*LN(LN(n)))) , 3*(sqrt(2)/4))) )
#define THRESHOLD(n,p) ( (int) (0.7 * LN(n) + log(M(n)) - T * log(p)) )

// Use only one of the B_LEN definitions, not both, for large numbers use Silverman's

// Pomerance's Base Length:
#define B_LEN ( (int) (pow(exp(sqrt(LN(key)*LN(LN(key)))) , (sqrt(2)/4))) )

// Silverman's Base Length:
// #define B_LEN ( (int) (2.93 * (len * len) - 164.4 * len + 2455) )
#define EXTRA 5
#define BLOCK 20000


void init ( void ) ;
void sieve ( Integer ) ;
bool divide ( Integer , bitset & ) ;
void matrix( void ) ;
void reduce ( void ) ;

int * factor_base , base_length ;
int * roots , * logs ;
int threshold , len , siev_block ;
bitset * exmatrix , * idmatrix ;
Integer key , sqrt_key , range , * fx , * xx , * pfx , * pxx ;

main( int argc , char *argv[] ) {

	// Structures to control initial,
	// final and total running time
	struct timeval * tv1 = new timeval ;
	struct timeval * tv2 = new timeval ;
	struct timeval * tvt = new timeval ;
	struct timezone * tz = NULL ;

	// get start time
	gettimeofday(tv1,tz);

	cout << "\nPomerance's Quadratic Sieve Factoring Algorithm\n" ;
	cout << "-----------------------------------------------\n\n" << flush ;

	if ( argc < 2 ) {
		cerr << "Usage: " << argv[0] << " <number_to_factor> " << endl ;
		return 1 ;
	}

	key = argv[ 1 ] ;
	len = strlen( argv[1] ) ;

	cout << "Entering Init phase...\n" ;
	init() ;
        cout << "...Init phase done!\n\n" << flush ;

	cout << "Building exponent matrix...\n" << flush ;
	matrix() ;
	cout << "...exponent matrix done!\n\n" ;

	cout << "Entering Reduce phase..." << flush ;
	reduce() ;

	// get finish time
	gettimeofday(tv2,tz);
	// get total time
	timersub(tv2,tv1,tvt);
	cout << "Total Running time: " << tvt->tv_sec << "s " ;
	cout << tvt->tv_usec << "mcs\n\n" ;

	return 0 ;
}

void init ( void ) {

	sqrt_key = Sqrt( key ) ;
	cout << "\tNumber to factor: " << key << '\n' ;
	cout << "\t[ sqrt( key ) ] = " << sqrt_key << '\n' ;

	base_length = B_LEN ;
	range = M( key ) ;

	if ( 2 * range < BLOCK )
		siev_block = 2 * range ;
	else siev_block = BLOCK ;

	// init factor base
	factor_base = new int [ base_length ] ;
	cout << "\tBuilding factor base..." ;
	Integer prime = 2 ;
	int i = 0 ;
	while ( i < base_length ) {
		if ( Legendre( key , prime ) == 1 ) {
			factor_base[i] = prime ;
			++ i ;
		}
		prime = nextprime( prime ) ;
	}
	cout << "done! \n" ;

	// init Threshold
	threshold = THRESHOLD( key , factor_base[ base_length - 1 ] ) ;

	// init roots array: key = x^2 mod p
	roots = new int [ base_length ] ;
	cout << "\tlooking for roots of N mod p..." ;
	for ( int i = 0 ; i < base_length ; ++ i ) {
		roots[i] = SqrtModN ( key , factor_base[i] ) ;
	}
	cout << "done! \n" ;

	// init logs, f(x)'s, x's arrays
	logs = new int [ siev_block ] ;
	fx = new Integer[ siev_block ] ;
	xx = new Integer[ siev_block ] ;

	// init array of good fx's and x's ;-)
	pfx = new Integer [ base_length + EXTRA ] ;
	pxx = new Integer [ base_length + EXTRA ] ;

	// init 2 matrices (exponents and id)
	exmatrix = new bitset [ base_length + EXTRA ] ;
	idmatrix = new bitset [ base_length + EXTRA ] ;
	for ( int x = 0 ; x < base_length + EXTRA ; ++ x ) {
		exmatrix[ x ].set_size( base_length ) ;
		idmatrix[ x ].set_size( base_length + EXTRA ) ;
	}
}

# define binlog(x) ( log(x) / log(2) )

void sieve ( Integer n ) {

	int p , k = 0 ;
	Integer x ;

	for ( int i = 0 ; i < siev_block ; i++ ) {
		x = n + i ;
		xx[ i ] = x ;
		x = x * x - key ;
		fx[ i ] = x ;
		logs[ i ] = log2( x ) ;
	}

	// for each factor in factor base
	for ( int i = 0 ; i < base_length ; ++ i ) {
		int r = roots[ i ] ;
		x = n ;
		p = factor_base[i] ;
		// find x congruent to r1 mod p
		while( x < ( n + siev_block ) ) {
			if( x % p == r )
				break ;
			else ++ x ;
		}
		k = (int) ( x - n ) ;
		while( k < siev_block ) {
			logs[ k ] -= (int) binlog( p ) ;
			k += p ;
		}
		// find x congruent to r2 mod p
		x = n ;
		r = p - roots[i] ;
		while( x < ( n + siev_block ) ) {
			if( x % p == r )
				break;
			else ++ x ;
		}
		k = (int) ( x - n ) ;
		while( k < siev_block ) {
			logs[ k ] -= (int) binlog( p ) ;
			k += p ;
		}
	}
}

void matrix( void ) {
	int k = 0 ;
	Integer block = 0 ;
	int needed = base_length + EXTRA ;
	cout << "\tTotal f(x)'s needed: " << needed << '\n' << flush ;
	while ( k < needed ) {
		sieve( sqrt_key - ( range - block ) ) ;
		for ( int i = 0 ; i < siev_block ; ++ i ) {
			if ( logs[i] <= threshold ) {
				if ( k < needed ) {
					if ( divide( fx[ i ] , exmatrix[ k ] ) ) {
						pxx[ k ] = xx[ i ] ;
						pfx[ k ] = fx[ i ] ;
						idmatrix[ k ].flip( k ) ;
						k++ ;
					}
				}
				else break ;
			}
		}
		cout << "\tSieving... f(x)'s factorized: " << k << '\r' << flush ;
		block += siev_block ;
	}
	cout << '\n' << flush ;
}

bool divide ( Integer fx , bitset & row ) {
	int trial ;
	int i = 0 ;
	if ( fx < 0 ) {
		fx = -fx ;
	}
	while ( i < base_length ) {
		trial = factor_base[ i ] ;
		if ( fx % trial == 0 ) {
			row.flip(i) ;
			fx /= trial ;
		}
		else i++ ;
	}
	if ( fx <= factor_base[ base_length - 1 ] ) {
		return true ;
	}
	else {
		row.reset() ;
		return false ;
	}
}

void reduce( void ) {
	bool pivot = false ;
	Integer X , Y ;
	bitset * expivot , * idpivot , btmp ;
	for ( int x = 0 ; x < base_length ; x++ ) {
		for ( int y = x ; y < base_length + EXTRA ; y++ ) {
			if ( !pivot && exmatrix[y][x] ) {
				// swap ex and id rows
				btmp.set_size( base_length ) ;
				btmp = exmatrix[ y ] ;
				exmatrix[ y ] = exmatrix[ x ] ;
				exmatrix[ x ] = btmp ;
				btmp.set_size( base_length + EXTRA ) ;
				btmp = idmatrix[ y ] ;
				idmatrix[ y ] = idmatrix[ x ] ;
				idmatrix[ x ] = btmp ;
				//
				expivot = & exmatrix[ x ] ;
				idpivot = & idmatrix[ x ] ;
				pivot = true ;
				y ++ ;
			}
			if ( y == base_length + EXTRA ) continue ;
			if ( pivot && exmatrix[y][x] ) {
				exmatrix[ y ] += * expivot ;
				idmatrix[ y ] += * idpivot ;
			}
		}
		pivot = false ;
	}

	for ( int i = base_length ; i < base_length + EXTRA ; i++ ) {
		X = 1 , Y = 1 ;
		for ( int j = 0 ; j < base_length + EXTRA ; j++ ) {
			if ( idmatrix[i][j] ) {
				Y *= pfx[ j ] ;
				X *= pxx[ j ] ;
			}
		}
		if( Y < 0 ) Y = -Y ;
		X = X % key ;
		Y = Sqrt( Y ) % key ;
		X = gcd( X-Y , key ) ;
		if ( ! ( X == 1 || X == key ) ) break ;
	}
	cout << " Factors: " << X << " x " << key/X << "\n\n" ;
}

/* <rou@papelmail.com> */
/* <rtx@papelmail.com> */

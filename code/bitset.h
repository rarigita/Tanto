/************************************************************
 * bitset.h                                                 *
 *      bitset object type and operations needed by         *
 *      Pomerance's Quadratic Sieve Algorithm               *
 *                                                          *
 *      Courtesy of                                         *
 *          Mike Roig <rtx@papelmail.com>                   *
 *      in collaboration with                               *
 *          R. Arigita <rou@papelmail.com>                  *
 *                                                          *
 *      Canterbury, UK, Feb 2003.                           *
 *                                                          *
 ************************************************************/


# ifndef MATRIX
# define MATRIX

# include <iostream>
using std :: ostream ;

class bitset {

public :
	bitset () ;
	bitset ( bitset & ) ;
	bitset ( int size , bool value = 0 ) ;
	~ bitset () ;

	int get_size ( void ) ;		// get size
	void set_size ( int size ) ;	// set size
	void flip ( int bit ) ;		// bit = ! bit
	void set ( int bit ) ;		// bit = 1
	void reset_bit ( int bit ) ;	// bit = 0
	void reset ( void ) ;		// bitset = 0
	void print ( void ) ;		// print to screen


	bool operator [] ( int bit ) ;	// get bit
	bitset & operator += ( bitset & ) ;
	bitset & operator = ( bitset & ) ;

private :
	typedef long unsigned int block ;

	block * blocks ;
	int size_in_bits ;

	int num_blocks ( int ) ;
	int block_of_bit ( int ) ;
	int weight ( int ) ;
} ;

ostream & operator << ( ostream & , bitset & ) ;

# endif

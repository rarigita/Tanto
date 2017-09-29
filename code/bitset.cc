/************************************************************
 * bitset.cc                                                *
 *      bitset object type and operations needed by         *
 *      Pomerance's Quadratic Sieve Algorithm               *
 *                                                          *
 *      Courtesy of                                         *
 *          Mike Roig <rtx@papelmail.com>                   *
 *      in collaboration with                               *
 *          R. Arigita <rou@papelmail.com>                  *
 *                                                          *
 *      Canterbury, UK, Feb 2003                            *
 *                                                          *
 ************************************************************/

# include "bitset.h"
# include <iostream>

using std :: ostream ;

// Constructors

bitset :: bitset () : size_in_bits( 0 ) , blocks ( ( block * ) 0 ) { }

bitset :: bitset ( bitset & rhs ) {
	set_size( rhs.get_size() ) ;
	for ( int i = 0 ; i < num_blocks ( get_size() ) ; ++ i )
		blocks[i] = rhs.blocks[i] ;
}

bitset :: bitset ( int size , bool value ) : size_in_bits( size ) {
	blocks = new block [ num_blocks( size ) ] ;
	for ( int i = 0 ; i < num_blocks( size ) ; ++ i )
		blocks[i] = value ? ~ (block) 0 : (block) 0 ;
}

// Destructor

bitset :: ~ bitset () {
	if ( blocks ) delete [] blocks ;
}

// Public operators 

int bitset :: get_size ( void ) {
	return size_in_bits ;
}

void bitset :: set_size ( int size ) {
	if ( blocks ) delete [] blocks ;
	blocks = new block [ num_blocks( size ) ] ;
	size_in_bits = size ;
	for ( int i = 0 ; i < num_blocks( size ) ; ++ i )
                blocks[i] = 0 ;
}
	
void bitset :: flip ( int bit ) {
	blocks [ block_of_bit( bit ) ] ^= weight ( bit ) ;
}

void bitset :: set ( int bit ) {
	blocks [ block_of_bit( bit ) ] |= weight ( bit ) ;
}

void bitset :: reset_bit ( int bit ) {
	blocks [ block_of_bit( bit ) ] &= ~ weight ( bit ) ;
}

void bitset :: reset ( void ) {
        for ( int i = 0 ; i < num_blocks( get_size() ) ; ++ i )
		blocks[i] = 0 ;
}

void bitset :: print ( void ) {
	std :: cout << (* this) ;
	std :: cout << '\n' ;
}

bool bitset :: operator [] ( int bit ) {
	block * b = blocks + block_of_bit( bit ) ;
	bool r = ( (*b) & weight( bit ) ) ;
	return r ;
}

bitset & bitset :: operator = ( bitset & rhs ) {
	for ( int i = 0 ; i < num_blocks( get_size() ) ; i++ ) {
		blocks[ i ] = rhs.blocks[ i ] ;
	}
	return * this ;
}

bitset & bitset :: operator += ( bitset & rhs ) {
	for ( int i = 0 ; i < num_blocks( get_size() ) ; i++ ) {
		blocks[ i ] ^= rhs.blocks[ i ] ;
	}
	return * this ;
}

ostream & operator << ( ostream & str , bitset & m ) {
	int bitset_size = m.get_size() ;
	for ( int i = 0 ; i < bitset_size ; ++ i ) {
		str << m[i] ;
	}
}

// Private operators

int bitset :: block_of_bit ( int bit ) {
	return ( bit / ( sizeof( block ) * 8 ) ) ;
}

int bitset :: weight ( int bit ) {
	return ( 1 << bit ) ;
}

int bitset :: num_blocks ( int size ) {
	static bool extra_block = ( size % ( sizeof(block)*8 ) ? 0 : 1 ) ;
	return ( size / sizeof( block ) * 8 + extra_block ) ;
}


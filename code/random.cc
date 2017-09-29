#include "Integer.h"
#include <iostream>
#include <stdlib.h>
int main( int argc, char * argv[] ){
	Integer num = argv[1];
	Integer ran = random( num );
	ran.print();

	mpz_random(num,10);
	num.print();
}

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

int main( int argc, char * argv[] ) {

  int key ;
  double c, d, e, f, sq, k, k0, k1, k2, k3;
  key = atoi( argv[1] );
  k = key;
  sq = sqrt( k );
  c = 1.; d = 2.; e = 2.; f = 3.;

  cout << "Key: " << key << ", Raiz: " << sq << "\n";

  while( (c+d) < sq ){
    while( (e+f) < key ){

      k0 = c*e+c*f+1;
      k1 = c*e+d*e;
      k2 = c*f+d*f;
      k3 = d*e+d*f-1;
      if( k0 == k1 && k2 == k3 ){
        cout << c << "\t" << d << "\t" << e << "\t" << f << " :\t";
        cout << k0 << " = " << k1 << "\t\t" << k2 << " = " << k3 << "\t" << k0 + k2 << "\n";
      }
      f = f+1;

    }
    e = e+1;
    f = e;
    if( (e+f) >= key ){
      d = d+1;
      if( (c+d) > sq ){
        c = c+1;
        d = c+1;
      }
      e = c;
      f = d;
    }
  }
}


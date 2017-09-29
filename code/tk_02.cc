#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

int main( int argc, char * argv[] ) {

  int key, c, d, e, f, k3 ,k4;
  double sq, k, k0, k1, k2, k5, k6;
  key = atoi( argv[1] );
  k = key;
  sq = sqrt( k );
  c = 1; d = 2; e = 2; f = 3;

  cout << "Key: " << key << ", Raiz: " << sq << "\n";

  while( (c+d) < sq ){
    while( (e+f) < key ){
      cout << c << "\t" << d << "\t" << e << "\t" << f << " : ";
/*
      k0 = ( c*(c*f+1)/d ) + ( f*(c*f+1)/e ) + 2*c*f+1;
      k1 = ( c*f^2+2*f*c*e+c*e^2+f+e ) / e;
      k2 = ( (c^2*f+c)/d ) + 2*c*f+1+d*f;
      k3 = c*e+2*c*f+1+d*f;
      k4 = c*e+c*f+d*e+d*f;
      k5 = (d*e^2-f+2*d*e*f+d*f^2-e) / f;
*/
      k6 = (c+d)*(c*e+d*e-1) / c;

      cout /* << k0 << ", " << k1 << ", " << k2 << ", " << k3 << ", " << k4 << ", " << k5 << ", " */ << k6 << "\n";

      f = key-e;

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


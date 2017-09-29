#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

int main( int argc, char * argv[] ) {

  int key ;
  double c, d, e, f, sq, k, k0, k1, k2, k3, r16, r17, r18, r19;
  key = atoi( argv[1] );
  k = key;
  sq = sqrt( k );
  c = 1.; d = 2.; e = 2.; f = 3.;

  cout << "Key: " << key << ", Raiz: " << sq << "\n";

  while( (c+d) < sq ){
    while( (e+f) < key ){

      k0 = (-0.5)*(1+2*d*f-sqrt(1+4*f*key*d))/f;
      k1 = ((-e-f+key*e)/(f*f+2*e*f+e*e));
      k2 = (d*e-1)/f;
      k3 = (-0.5)*(2*d*e-1-key+sqrt(1+2*key+key*key-4*key*d*e))/e;

      r16=(0.5)*(k-2*c*f-1+sqrt(1+k*k-2*k-4*f*k*c))/f;
      r17=(e+f+k*f)/(f*f+2*e*f+e*e);
      r18=(-0.5)*(2*c*e-1-sqrt(1+4*e*k*c))/e;
      r19= (c*f+1)/e;

      cout << c << "\t" << d << "\t" << e << "\t" << f << " :\t";
      cout << k0 << ", " << k1 << ", " << k2 << ", " << k3 << "\t - ";
      cout << r16 << ", " << r17 << ", " << r18 << ", " << r19 <<"\n";
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


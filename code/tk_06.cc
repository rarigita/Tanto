#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>

using namespace std;

int main( int argc, char * argv[] ) {

  int c,d,e,f,key ;
  double k0, k1, k2, k3, k4, k5, k6;
  double sq, k, k12, k13, k14, k15, r16, r17, r18, r19;
  double r20, r21, r22, r23, r24, r25, r26, r27;
  key = atoi( argv[1] );
  k = key;
  sq = sqrt( k );
  c = 1; d = 2; e = 2; f = 3;

  cout << "Key: " << key << ", Raiz: " << sq << "\n";

  while( (c+d) < sq ){
    while( (e+f) < key ){

      // block for K //
      k0 = ( c*(c*f+1)/d ) + ( f*(c*f+1)/e ) + 2*c*f+1;
      k1 = (c*f*f+2*f*c*e+c*e*e+f+e)/e;
      k2 = ((c*c*f+c)/d)+2*c*f+1+d*f;
      k3 = c*e+2*c*f+1+d*f;
      k4 = c*e+c*f+d*e+d*f;
      k5 = (d*e*e-e-f+2*d*e*f+d*f*f)/f;
      k6 = (c+d)*(c*e+d*e-1)/c;

      // block for c //
      k12 = (-0.5)*(1+2*d*f-sqrt(1+4*f*key*d))/f;
      k13 = ((-e-f+key*e)/(f*f+2*e*f+e*e));
      k14 = (d*e-1)/f;
      k15 = (-0.5)*(2*d*e-1-key+sqrt(1+2*key+key*key-4*key*d*e))/e;

      // block for d //
      r16 = (0.5)*(k-2*c*f-1+sqrt(1+k*k-2*k-4*f*k*c))/f;
      r17 = (e+f+k*f)/(f*f+2*e*f+e*e);
      r18 = (-0.5)*(2*c*e-1-sqrt(1+4*e*k*c))/e;
      r19 = (c*f+1)/e;

      // block for e //
      r20 = (0.5-d*f+0.5*sqrt(1+4*f*k*d))/d;
      r21 = (c+d+k*c)/(2*c*d+d*d+c*c);
      r22 = (c*f+1)/d;
      r23 = (-c*f-0.5+0.5*k-0.5*sqrt(-2*k-4*f*k*c+1+k*k))/c;

      // block for f //
      r24 = -2*(d*e-1)*e/(2*d*e-1-k+sqrt(-4*k*d*e+1+2*k+k*k));
      r25 = (-c+k*d-d)/(2*c*d+d*d+c*c);
      r26 = ((-0.5)-c*e+0.5*sqrt(1+4*e*k*c))/c;
      r27 = (d*e-1)/c;

      printf("%3d %3d %3d %3d :   ", c, d, e, f);
      printf("%6.2f  %6.2f  %6.2f  %6.2f", k12, k13, k14 ,k15);
      printf("  |  %6.2f  %6.2f  %6.2f  %6.2f", r16, r17, r18, r19);
      printf("  |  %6.2f  %6.2f  %6.2f  %6.2f", r20, r21, r22, r23);
      printf("  |  %6.2f  %6.2f  %6.2f  %6.2f\n", r24, r25, r26, r27);

      f = f+1;

    }
    e = e+1;
    f = d+1;
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


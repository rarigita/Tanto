#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

int main( int argc, char * argv[] ) {

  int c,d,e,f,key ;
  double sq, k, k0, k1, k2, k3, k4, k5, k6, med;

  if( argc < 2 ){
    printf("Please type Key number, and factors\n");
  }
  else {
    key = atoi( argv[1] );
    k = key;
    sq = sqrt( k );
    cout << "Key: " << key << ", Raiz: " << sq << "\n"; 
  }
  if( argc == 2 ){
    c = 1; d = 2; e = 2; f = 3;
    while( (c+d) < sq ){
      while( (e+f) < key ){

        printf("%3d %3d %3d %3d : ", c, d, e, f);
        k0 = ( c*(c*f+1)/d ) + ( f*(c*f+1)/e ) + 2*c*f+1;
        k1 = (c*f*f+2*f*c*e+c*e*e+f+e)/e;
        k2 = ((c*c*f+c)/d)+2*c*f+1+d*f;
        k3 = c*e+2*c*f+1+d*f;
        k4 = c*e+c*f+d*e+d*f;
        k5 = (d*e*e-e-f+2*d*e*f+d*f*f)/f;
        k6 = (c+d)*(c*e+d*e-1)/c;
        med= (k0+k1+k2+k3+k4+k5+k6)/7;
        printf(" %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  ->  %7.2f\n", k0, k1, k2, k3, k4, k5, k6, med);

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
  else if( argc > 2 && argc < 6 ){
    printf("Please type 4 factors\n");
  }
  else if( argc == 6 ){
    c = atoi(argv[2]);
    d = atoi(argv[3]);
    e = atoi(argv[4]);
    f = atoi(argv[5]);
    printf("%3d %3d %3d %3d : ", c, d, e, f);
    k0 = ( c*(c*f+1)/d ) + ( f*(c*f+1)/e ) + 2*c*f+1;
    k1 = (c*f*f+2*f*c*e+c*e*e+f+e)/e;
    k2 = ((c*c*f+c)/d)+2*c*f+1+d*f;
    k3 = c*e+2*c*f+1+d*f;
    k4 = c*e+c*f+d*e+d*f;
    k5 = (d*e*e-e-f+2*d*e*f+d*f*f)/f;
    k6 = (c+d)*(c*e+d*e-1)/c;
    med= (k0+k1+k2+k3+k4+k5+k6)/7;
    printf(" %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  ->  %7.2f\n", k0, k1, k2, k3, k4, k5, k6, med);
    printf("%15s : ", " ");
    printf(" %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f\n", k0-key, k1-key, k2-key, k3-key, k4-key, k5-key, k6-key);
  }
}

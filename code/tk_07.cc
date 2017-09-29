#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

int main( int argc, char * argv[] ) {

  int c,d,e,f,key,i ;
  float sq, k, k0, k1, k2, k3, k4, k5, k6, med;
  float r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27;

  if( argc < 2 ){
    printf("Please type Key number, and factors\n");
  }
  else if( argc > 1 && argc < 6 ){
    printf("Please type 4 factors\n");
  }
  else if( argc == 6 ){
    key = atoi( argv[1] );
    k = key;
    sq = sqrt( k );
//    cout << "Key: " << key << ", Raiz: " << sq << "\n";
    c = atoi(argv[2]) - 1;
    d = atoi(argv[3]) - 1;
    e = atoi(argv[4]) - 1;
    f = atoi(argv[5]) - 1;

    i = 3;
    while( i-- > 0 ){

      printf("\n%3d %3d %3d %3d : ", c, d, e, f);

      // block for K
      k0 = ( c*(c*f+1)/d ) + ( f*(c*f+1)/e ) + 2*c*f+1;
      k1 = (c*f*f+2*f*c*e+c*e*e+f+e)/e;
      k2 = ((c*c*f+c)/d)+2*c*f+1+d*f;
      k3 = c*e+2*c*f+1+d*f;
      k4 = c*e+c*f+d*e+d*f;
      k5 = (d*e*e-e-f+2*d*e*f+d*f*f)/f;
      k6 = (c+d)*(c*e+d*e-1)/c;
      med= (k0+k1+k2+k3+k4+k5+k6)/7;

      // Output for K block
      printf(" %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f\n", k0, k1, k2, k3, k4, k5, k6);
      printf("%15s : ", " ");
      printf(" %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f  %7.0f\n", k0-key, k1-key, k2-key, k3-key, k4-key, k5-key, k6-key);
      printf("%15s : ------------------------------------------------------------------\n", " ");

      // block for c //
      r12 = (-0.5)*(1+2*d*f-sqrt(1+4*f*key*d))/f;
      r13 = ((-e-f+key*e)/(f*f+2*e*f+e*e));
      r14 = (d*e-1)/f;
      r15 = (-0.5)*(2*d*e-1-key+sqrt(1+2*key+key*key-4*key*d*e))/e;

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
  
      // Output for c, d, e, f
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n", " ", r12, r16, r20, r24);
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n", " ", r13, r17, r21, r25);
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n", " ", r14, r18, r22, r26);
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n", " ", r15, r19, r23, r27);
      printf("\n");
/*
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n", " ", (r12-c), (r16-d), (r20-e), (r24-f));
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n", " ", (r13-c), (r17-d), (r21-e), (r25-f));
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n", " ", (r14-c), (r18-d), (r22-e), (r26-f));
      printf("%15s : %12.3f   %12.3f   %12.3f   %12.3f\n\n", " ", (r15-c), (r19-d), (r23-e), (r27-f));
*/
      c++;d++;e++;f++;
    }
  }
}

#ifndef COSMOD
#define COSMOD
#include<math.h>
#include<stdlib.h>
#include"quickspeq.cpp"

int good[12] = {1, 2, 10, 11, 5, 6, 8, 9, 7, 4, 3, 0};

int find_(int num){
  int i;
  for (i = 0; i < 12; i++){
    if (good[i] == num)
      return(i);
  }
  //return(-100500);
}
double getQualInterval( int a, int b ){
  int period;
  period = abs((a % 12) - (b % 12));
  return(find_(period) / 12.);
}



double findCos(struct qs a){
  int i; int j;
  double r=7    ;
  for (i = 0; i < a.tones *(int)a.oqs; i++){
    for (j = i + 1; j < a.tones *(int)a.oqs; j++){
      r+=a.ks[i]*a.ks[j]   *getQualInterval(i,j);
      //printf("gqi: %lf \n", getQualInterval(i,j));
      
    }
  }
  return r;
}
#endif

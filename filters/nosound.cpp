#include<math.h>
#ifndef NOSOUNDMOD
#define NOSOUNDMOD

extern int screenH;
extern int screenW;


void transformMega(int&x, int&y, double fl){
	/* x=(x-w/2) ;
	y=(y-h/2);
	int a=at[y+1024][x+1024];
	int l = pf[abs(x)][abs(y)]/32.;
	l = pw[l][(int) ((1/fl + 20) * 2)];
	x=(cs[a]*l+2048)/(4096) +w/2;
	y=(sn[a]*l+2048)/(4096) +h/2;
	 */
	double a,h,w;
	w=screenW;
	h=screenH;
   	
	
	double dgf = sqrt(h*h/4+w*w/4);	
	x-=w/2;
	y-=h/2;
	int dgp = sqrt(x*x+y*y);
	a=atan2(y,x);
	double l=dgp/dgf;
	l=pow(l,fl);
	x= w/2+l*dgf*cos(a);
	y= h/2+l*dgf*sin(a);
}

#endif
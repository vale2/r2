#include<math.h>
#ifndef SPIRANMOD
#define SPIRALMOD
double turnx(double ang, double x, double y) {
	return cos(ang) * x + sin(ang) * y;
}

double turny(double ang, double x, double y) {
	return cos(ang) * y - sin(ang) * x;
}
int fltransformSpiral,screenW,screenH,diag,spa,spb;
void transformSpiral(int &i,int &j){
    spa=i-screenW/2;
    spb=j-screenH/2;
    i=turnx(fltransformSpiral*(diag-sqrt(pow(spa,2)+pow(spb,2)))/diag/20,spa,spb)+screenW/2;
    j=turny(fltransformSpiral*(diag-sqrt(pow(spa,2)+pow(spb,2)))/diag/20,spa,spb)+screenH/2;
}
#endif

#ifndef EDITPANNELSMOD
#define EDITPANNELSMOD
#include"koefs.cpp"
#define PREGDOEFS 3
#define ROWS (PREGDOEFS+(KOEFNUM))
double maxPannelValue[DRAWKOEFNUM];
#define PANNELS 14

int curEditPannel=0;
int curEditParam=0;
#define LAYEROPTS 15
double layerOpt[LAYEROPTS]={0.4,0.1,0,0,0,0.1,0.1,0,0,0.1,0,0,1,0,0};
int panel_no[PANNELS]={16,17,-1,14,12,11,13,0,15,3,4,8,7,5};

#endif 

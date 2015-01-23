#ifndef HSVMOD
#define HSVMOD

#ifdef REVERCERGB
struct rgb{
    unsigned char b,g,r,o; 
};
struct reverce_rgb{
    unsigned char r,g,b,o; 
};

#else
struct rgb{
    unsigned char r,g,b,o; 
};
struct reverce_rgb{
    unsigned char b,g,r,o; 
};

#endif

struct hsv_colour{
    float s,h,v;

};
struct rgb_colour{
    float r,g,b;
}; 

struct rgb hsv2rgb(int h,double s,double v){// h =0.. 360  s=0..1  v=0..1
    int h1;
    double x,c,m,r,g,b;    
    struct rgb res;
    c=v*s;
    h1=h / 60;
    x=c*(1-abs((h1%2) - 1));    
    switch (h1){
        case 0:r=c ; g=x ; b=0 ;break;
        case 1:r=x ; g=c ; b=0 ;break;
        case 2:r=0 ; g=c ; b=x ;break;
        case 3:r=0 ; g=x ; b=c ;break;
        case 4:r=x ; g=0 ; b=c ;break;
        case 5:r=c ; g=0 ; b=x ;break;
    }
    m=v-c;
    r+=m;
    g+=m;
    b+=m;
    res.r=r*255;
    res.g=g*255;
    res.b=b*255;
    return res;
}


struct rgb rgb_colour2rgb(rgb_colour*rgb){
    struct rgb c;
    c.r=rgb->r*255.;
    c.g=rgb->g*255.;
    c.b=rgb->b*255.;
    return c;
}
#define mmax(a,b) ((a)>(b)?(a):(b))
#define mmin(a,b) ((a)<(b)?(a):(b))
struct hsv_colour rgb2hsv(struct rgb c){
 float r,g,b;
 struct hsv_colour res;
 r=c.r/255.; g=c.g/255.; b=c.b/255.;
 float  minRGB =  mmin(r,mmin(g,b));
 float  maxRGB =  mmax(r,mmax(g,b));

 if (fabs(minRGB-maxRGB)<0.001) {
    res.v = minRGB;
    res.h=0;
    res.s=0;
  return res;
 }

 // Colors other than black-gray-white:
 double d = (fabs(r-minRGB)<0.00001) ? g-b : (((fabs(b-minRGB)<0.001)) ? r-g : b-r);
 double h = (fabs(r-minRGB)<0.00001) ? 3 : (((fabs(b-minRGB)<0.001)) ? 1 : 5);
 res.h = 60./360*(h - d/(maxRGB - minRGB));
 res.s = (maxRGB - minRGB)/maxRGB;
 res.v = maxRGB;
 return res;
}

struct rgb r_rgb_colour2rgb(rgb_colour*rgb){
    struct rgb c;
    c.b=rgb->r*255.;
    c.g=rgb->g*255.;
    c.r=rgb->b*255.;
    c.o=255;
    return c;
}

struct rgb color(double h,double s,double v){
   struct rgb r;
   /*
    * Purpose:
    * Convert HSV values to RGB values
    * All values are in the range [0.0 .. 1.0]
    */
   float S, H, V, F, M, N, K;
   int   I;
   
   S = s;  /* Saturation */
   H = h;  /* Hue */
   V = v;  /* value or brightness */
   if(S>1.0)
      S=1.0;
   if(S<0.0)
      S=0.0;
   if(V>1.0)
      V=1.0;
   if(V<0.0)
      V=0.0;
   if ( S == 0.0 ) {
      /* 
       * Achromatic case, set level of grey 
       */
      r.r = 255*V;
      r.g = 255*V;
      r.b = 255*V;
   } else {
      /* 
       * Determine levels of primary colours. 
       */
      if (H >= 1.0) {
         H = 0.0;
      } else {
         H = H * 6;
      } /* end if */
      I = (int) H;   /* should be in the range 0..5 */
      F = H - I;     /* fractional part */

      M =255* V * (1 - S);
      N =255* V * (1 - S * F);
      K =255* V * (1 - S * (1 - F));
      V = V * 255;

      if (I == 0) { r.b = V; r.g = K; r.r = M; }
      if (I == 1) { r.b = N; r.g = V; r.r = M; }
      if (I == 2) { r.b = M; r.g = V; r.r = K; }
      if (I == 3) { r.b = M; r.g = N; r.r = V; }
      if (I == 4) { r.b = K; r.g = M; r.r = V; }
      if (I == 5) { r.b = V; r.g = M; r.r = N; }
   } /* end if */

   return r;

}

int hsv2rgb( struct hsv_colour *hsv, struct rgb_colour *rgb ) {
   /*
    * Purpose:
    * Convert HSV values to RGB values
    * All values are in the range [0.0 .. 1.0]
    */
   float S, H, V, F, M, N, K;
   int   I;
   
   S = hsv->s;  /* Saturation */
   H = hsv->h;  /* Hue */
   V = hsv->v;  /* value or brightness */
   if(S>1.0)
      S=1.0;
   if(S<0.0)
      S=0.0;
   if(V>1.0)
      V=1.0;
   if(V<0.0)
      V=0.0;
   if ( S == 0.0 ) {
      /* 
       * Achromatic case, set level of grey 
       */
      rgb->r = V;
      rgb->g = V;
      rgb->b = V;
   } else {
      /* 
       * Determine levels of primary colours. 
       */
      if (H >= 1.0) {
         H = 0.0;
      } else {
         H = H * 6;
      } /* end if */
      I = (int) H;   /* should be in the range 0..5 */
      F = H - I;     /* fractional part */

      M = V * (1 - S);
      N = V * (1 - S * F);
      K = V * (1 - S * (1 - F));

      if (I == 0) { rgb->r = V; rgb->g = K; rgb->b = M; }
      if (I == 1) { rgb->r = N; rgb->g = V; rgb->b = M; }
      if (I == 2) { rgb->r = M; rgb->g = V; rgb->b = K; }
      if (I == 3) { rgb->r = M; rgb->g = N; rgb->b = V; }
      if (I == 4) { rgb->r = K; rgb->g = M; rgb->b = V; }
      if (I == 5) { rgb->r = V; rgb->g = M; rgb->b = N; }
   } /* end if */

   return 0;
} /* end function hsv2rgb */



 typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb_percent;

    typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv_degrees_percent;

    static hsv_degrees_percent      rgb2hsv(rgb_percent in);
    static rgb_percent      hsv2rgb(hsv_degrees_percent in);

hsv_degrees_percent rgb2hsv(rgb_percent in)
{
    hsv_degrees_percent          out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) {
        out.s = (delta / max);                  // s
    } else {
        // r = g = b = 0                        // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}


rgb_percent hsv2rgb(hsv_degrees_percent in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb_percent      out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

struct rgb rgb_percent2rgb(rgb_percent rgb){
    struct rgb c;
    c.r=rgb.r*2.55;
    c.g=rgb.g*2.55;
    c.b=rgb.b*2.55;
    return c;
}
void zeroSoundKoefsColor(){
    int i;
    for(i=0;i<10;i++){
        setOpt("soundKoefsColorH",i,((double)i)/10.);
        setOpt("soundKoefsColorS",i,1.);
    }
    setOpt("soundKoefsColorH",10,0);
    setOpt("soundKoefsColorS",10,0);

}

#endif

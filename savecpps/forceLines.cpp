int npNP[1024][768];
int nph,npw;
void lines(struct layer* l, int f){
	int p,q,r,s, mi, ma,d,h=l->h,w=l->w;
	nph=l->h;
	npw=l->w;
	for(int i=0;i<w-f;i+=f){
		for(int j=0;j<h-f;j+=f){
			p=l->p[i+j*w];
			q=l->p[i+f+j*w];
			r=l->p[i+(j+f)*w];
			s=l->p[i+f+(j+f)*w];
			if (p>q && p>r && p>s) ma=0;
			if (q>=p && q>r && q>s) ma=1;
			if (r>=p && r>=q && r>s) ma=2;
			if (s>=p && s>=q && s>=r) ma=3;
			
			if (p<q && p<r && p<s) mi=0;
			if (q<=p && q<r && q<s) mi=1;
			if (r<=p && r<=q && r<s) mi=2;
			if (s<=p && s<=q && s<=r) mi=3;
			d=(ma==0?p:(ma==1?q:(ma==2?r:s)))-(mi==0?p:(mi==1?q:(mi==2?r:s)));
			//printf("%d %d %d %d\n", i, j, ma, mi);
			npNP[i][j] = 16*d+4*ma+mi;
		}
	}
	
}

void linesDraw (SDL_Surface*output, int f) {
	int h = output->h, w = output->w;
	for (int i = 0; i < w-f; i += f){
		for (int j = 0; j < h-f; j += f){
			drawColoredLineSeq2(output, (i + (npNP[i][j]%16/4%2*f))*w/npw, (j + (npNP[i][j]%16/4/2*f))*h/nph, (i + (npNP[i][j]%16%4%2*f))*w/npw, (j + (npNP[i][j]%16%4/2*f))*h/nph/*,npNP[i][j]*/);//magic			
		}		
	}
}

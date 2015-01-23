#include<stdio.h>
#include<string.h>

#include"sendrecive.cpp"
char *loadTimeStamp=NULL;

char currentFile[128];
extern double hearingVolume;
extern double amplifierKoef;
extern double amplifierKoefHighValue;
extern double amplifierKoefLowValue;
extern int faded;
extern int rgbMixerDepth;
extern int rgbMixerDepthAuto;
extern int noiseC;
extern int noiseV;
extern int noiseColor;
extern double pifColorSpeedr;
extern double pifColorSpeedg;
extern double pifColorSpeedb;
extern int pifDeep;
extern int pifNaked;
extern int pifColored;
extern double pifDWind;
extern double pifDScale;
extern double pifDAngle;
extern int pifPosition;
extern int showColorSeq;

struct playList{
    char name[128];
    int len;
    struct rabbit *rabbits;
    
};
struct rabbit{
    char name[128];
    char *pic;
    int h,w;
};

//#include <stdlib.h>
//#include <stdio.h>

#include <dirent.h>
#include <fnmatch.h>
int compare(char*a,char*b){
    int aa,bb;
    if(strstr(a,"quick_")==a && strstr(b,"quick_")==b){
        
        sscanf(a,"quick_%d",&aa);
        sscanf(b,"quick_%d",&bb);
        return bb-aa;
    }
    if(strstr(a,"timestamp_")==a&&strstr(b,"quick_")==b)
        return -1;
    if(strstr(a,"quick_")==a&&strstr(b,"timestamp_")==b)
        return 1;
        
    return -strcmp(a,b);
}
void sortRabbits(struct rabbit* r,int len){
    struct rabbit t;
    for(int i=0;i<len;i++){
        for(int j=0;j<i;j++){
            if(compare(r[i].name,r[j].name)<0){
                t=r[i];
                r[i]=r[j];
                r[j]=t;           
            }
        
        }
    }


}
void loadPreview(struct rabbit*r){
    char s[128];
    sprintf(s,"saves/%s.preview",r->name);
    FILE*f;
    f=fopen(s,"r");
    if(f!=NULL){
        fread(&(r->w),sizeof(int),1,f);
        fread(&(r->h),sizeof(int),1,f);
        r->pic=(char*)malloc(r->h*r->w*4);
        if(r->pic==NULL){
            r->h=0;
            r->w=0;
        
        
        }else{
            fread(r->pic,r->h*r->w,4,f);
        }
        fclose(f);
    }else{
        r->h=0;
        r->w=0;
        r->pic=NULL;
    }
}
struct rabbit* loadAllRabbits(int&rn){
    int len,i;
    len=0;
    struct rabbit*r;
    struct dirent **namelist;
    int n;
    n = scandir("./saves", &namelist, 0, alphasort); 
   for(i=0;i<n;i++) { //*.[ch]", filename,
            if(!fnmatch("*.r2",namelist[i]->d_name, FNM_PATHNAME)){
                len++;
            }
        } 
   
   
   r=(struct rabbit*)malloc(len*sizeof(struct rabbit));
   rn=0;
   if(r==NULL)
      return NULL;
   
   len=0;
   for(i=0;i<n;i++) { //*.[ch]", filename,
            if(!fnmatch("*.r2",namelist[i]->d_name, FNM_PATHNAME)){
                strncpy(r[len].name,namelist[i]->d_name,127);
                loadPreview(r+len);
              //  fprintf(stderr,"%s\n",r[len].name);

                len++;
            } 
            
            free(namelist[i]); 
   
    }   
    rn=len;
    free(namelist);
    sortRabbits(r,len); 
  //  for(i=0;i<len;i++){
//        fprintf(stderr,"%s\n",r[i].name);

    //}
    return r;
}
int existSave(char* s){
    char rname[128];
    sprintf(rname,"saves/%s",s);
    FILE*f;
    f=fopen(rname,"r");
    if(f==NULL)
        return 0;
    fclose(f);
    return 1;
}
struct rabbit* loadPLRabbits(char*name,int &rn){
    FILE*f;
    char rname[128];
    int l=0;
//    fprintf(stderr,"LPLRABBIRS:%s\n",name);

    sprintf(rname,"saves/%s",name);
    f=fopen(rname,"r");
    rn=0;
    if(f==NULL)
        return NULL;
    while(!feof(f)){
        fscanf(f,"%s",rname);
        if(existSave(rname))
            l++;
    }
    fclose(f);
    fprintf(stderr,"%d rabbits in ",l);
    fprintf(stderr,"%s playlist\n",name);
    fflush(stderr);

    struct rabbit*r;
    r=(struct rabbit*)malloc(l*sizeof(struct rabbit));
    if(r==NULL)
        return NULL;

    sprintf(rname,"saves/%s",name);

    f=fopen(rname,"r");
    rn=0;
    if(f==NULL){            
        return NULL;
    }
    int i;
    for(i=0;i<l;){
        fscanf(f,"%s",rname);
        if(existSave(rname)){
            strcpy(r[i].name,rname);
//            fprintf(stderr,"%s\n",r[i].name);
            i++;
        }                
    }
    fclose(f);
    rn=l;
    return r;
}

struct playList* loadPlaylists(int&rn){
    int len,i;
    len=1;
    struct playList*r;
    struct dirent **namelist;
    int n;
   fprintf(stderr,"LoadPlayLists\n");
   fflush(stderr);

    n = scandir("./saves", &namelist, 0, alphasort); 
   for(i=0;i<n;i++) { //*.[ch]", filename,
            if(!fnmatch("*.r2pl",namelist[i]->d_name, FNM_PATHNAME)){
                len++;
            }
        } 
   
   rn=0;
   r=(struct playList*)malloc(len*sizeof(struct playList));
   if(r==NULL)
      return NULL;
   fprintf(stderr,"%d playlists\n",len);
   fflush(stderr);


   r[0].name[0]=0;
   r[0].len=0;
   r[0].rabbits=loadAllRabbits(r[0].len);
   fprintf(stderr,"%d rabbits in default playlist\n",r[0].len);
   fflush(stderr);

   len=1;
   for(i=0;i<n;i++) { //*.[ch]", filename,
            if(!fnmatch("*.r2pl",namelist[i]->d_name, FNM_PATHNAME)){
                strncpy(r[len].name,namelist[i]->d_name,127);
              //  fprintf(stderr,"%s\n",r[len].name);
                r[len].rabbits=loadPLRabbits(r[len].name,r[len].len);
                len++;
            }
            free(namelist[i]); 
    }   
    rn=len;
    free(namelist); 
    fflush(stderr);
    return r;
}



struct playList* freePL(struct playList*p){
    if(p!=NULL&&p->rabbits!=NULL){
            for(int j=0;j<p->len;j++){
                if(p->rabbits[j].pic!=NULL){
                    free(p->rabbits[j].pic);
                }
            }

        free(p->rabbits);
    }
    if(p!=NULL)
        free(p);
    return NULL;
}
struct playList* freePLs(struct playList*p,int n){
    if(p!=NULL){
        for(int i=0;i<n;i++){
            for(int j=0;j<p[i].len;j++){
                if(p[i].rabbits[j].pic!=NULL){
                    free(p[i].rabbits[j].pic);
                }
            }
            if(p[i].rabbits!=NULL){
                free(p[i].rabbits);    
            }
        }
        free(p);
    }
    return NULL;
}
extern struct playList*pls;
extern int plsn;
extern int    curpls;
extern int    curRabbit;

void freePlayLists(){
    if(pls!=NULL && plsn>0)
        freePLs(pls,plsn);
    pls=NULL;
    plsn=0;
    curpls=0;
    curRabbit=-100;

}
void zeroFilters(){
    orblurd=0;
    faded=50;
    rgbMixerDepth=0;
    
    for(int i=0;i<LAYEROPTS;i++)
        layerOpt[i]=0.5;
        layerOpt[6]=0.;

}


int save_rabbit(const char*name){
    FILE*f;
    char s[128];
    sprintf(s,"saves/%s",name);
    f=fopen(s,"w");
    if(f==NULL){
        return -1;
    }
    sendAllMass(f,1,0);
    writeSoundControllValue(f,1);
    sendFilters(f,1);
    fclose(f);
    zeroLValues();   
    strcpy(currentFile,name);
    return 0;
}

void saveCurrent(){
   save_rabbit(currentFile);    
}
void saveCurPreview(char*pic,int w,int h){
    FILE*f;
    char s[128];
    sprintf(s,"saves/%s.preview",currentFile);
    f=fopen(s,"w");
    if(f==NULL){
        return;
    }
    fwrite(&w,sizeof(int),1,f);
    fwrite(&h,sizeof(int),1,f);
    fwrite(pic,h*w,4,f);
    fclose(f);
}





char loadBuf[1024];

char timeStampBuf[32];

char* getTimeStampFromName(const char*name){
    unsigned int r;
    char s[256];
    s[0]=0;
    sscanf(name,"quick_%s.r2",s);
    if(s[0]!=0){
        strcpy(timeStampBuf,"0");
        return timeStampBuf;
    }
    s[0]=0;
    sscanf(name,"timestamp_%s.r2",s);
    
    if(s[0]!=0){
        strcpy(timeStampBuf,s);
        return timeStampBuf;
    }

    time_t ltime;
    ltime=time(NULL);
    struct tm *tm;
    tm=localtime(&ltime);

    sprintf(timeStampBuf,"%04d%02d%02d%02d%02d%02d", tm->tm_year+1900, tm->tm_mon, 
            tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  return timeStampBuf;


}

int load_rabbit(const char*name){
    FILE*f;
    char s[128];
    sprintf(s,"saves/%s",name);
    f=fopen(s,"r");
    if(f==NULL){
        return -1;
    }
    loadTimeStamp=getTimeStampFromName(name);
    setZeroPifControllKoef();
    zeroGlOpt();  
    zeroOqColorLine();
    zeroFilters();
    //freeOpts();
    zeroOpts();
    while(!feof(f)){
        fgets(loadBuf,1024,f);
//        syntaxControll
        syntaxControll(loadBuf);
    }
    zeroLValues();   
    fclose(f);
    strcpy(currentFile,name);
    loadTimeStamp=NULL;
    return 0;
}

char nameReturn[128];
char*saveNext(){
    for(int n=0;n<1024;n++){
        FILE*f;
        sprintf(nameReturn,"saves/quick_%d.r2",n);

        f=fopen(nameReturn,"r");
        if(f==NULL){
            f=fopen(nameReturn,"w");
            if(f!=NULL){
                fclose(f);
                sprintf(nameReturn,"quick_%d.r2",n);
                if(!save_rabbit(nameReturn)){
                    return nameReturn;
                }
            }
            
        }
        fclose(f);
    }
    return NULL;
}
char*saveTimeStamp(){
    
    FILE*f;
    char timestamp[32];
    unsigned u;
    time_t ltime;
    ltime=time(NULL);
    struct tm *tm;
    tm=localtime(&ltime);

    sprintf(timestamp,"%04d%02d%02d%02d%02d%02d", tm->tm_year+1900, tm->tm_mon, 
            tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        
    sprintf(nameReturn,"saves/timestamp_%s.r2",timestamp);
    f=fopen(nameReturn,"r");
    if(f==NULL){
        f=fopen(nameReturn,"w");
        if(f!=NULL){
            fclose(f);
            f=NULL;
            sprintf(nameReturn,"timestamp_%s.r2",timestamp);
            if(!save_rabbit(nameReturn)){
                return nameReturn;
            }
        }
        
    }
    if(f!=NULL)
        fclose(f);
    return NULL;
}
char*addPlsTimeStamp(){
    FILE*f;
    char timestamp[32];
    unsigned u;
    time_t ltime;
    ltime=time(NULL);
    struct tm *tm;
    tm=localtime(&ltime);

    sprintf(timestamp,"%04d%02d%02d%02d%02d%02d", tm->tm_year+1900, tm->tm_mon, 
            tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        
    sprintf(nameReturn,"saves/timestamp_%s.r2pl",timestamp);
    f=fopen(nameReturn,"r");
    if(f==NULL){
        f=fopen(nameReturn,"w");
        if(f!=NULL){
            fclose(f);
            return nameReturn;
        }
        
    }
    if(f!=NULL)
        fclose(f);
    return NULL;
}


char*loadNextShuffle(){
   if(pls==NULL){
       fprintf(stderr,"loadNextShuffle:PLS==NULL\n");
   }else {
       fprintf(stderr,"loadNextShuffle:plsn=%d, pls[curpls].len=%d\n",plsn,pls[curpls].len);
       fprintf(stderr,"loadNextShuffle:curpls=%d, curRabbit=%d\n",curpls,curRabbit);   
   }
   if(pls==NULL||plsn<=0||curpls>=plsn||curpls<0||curRabbit<0||curRabbit>=pls[curpls].len){
      int n;
      sscanf(currentFile,"quick_%d.r2",&n);
      n++;
      if(n<0||n>=1024)
          n=0;
      for(;n<1024;n++){
          FILE*f;
          sprintf(nameReturn,"saves/quick_%d.r2",n);
          f=fopen(nameReturn,"r");
          if(f!=NULL){
              fclose(f);
              sprintf(nameReturn,"quick_%d.r2",n);
              if(!load_rabbit(nameReturn))
                  return nameReturn;
          }
     }
     return NULL;
   }else{
        curRabbit=rand()%pls[curpls].len;
        fprintf(stderr,"Loading (%s) ",pls[curpls].rabbits[curRabbit].name);
        fprintf(stderr,"(%d, %d)...",curpls,curRabbit);
        fflush(stderr);

        if(!load_rabbit(pls[curpls].rabbits[curRabbit].name)){
                    fprintf(stderr,"success\n");
                    fflush(stderr);
                    fprintf(stderr,"LoadNext:%s",pls[curpls].rabbits[curRabbit].name);
                    fprintf(stderr," pl=%d,r=%d\n",curpls,curRabbit);                    
                    return pls[curpls].rabbits[curRabbit].name;
        }
        fprintf(stderr,"unsuccess\n");
         fflush(stderr);
        return NULL;
    }

}
char*loadNext(){
   if(pls==NULL){
       fprintf(stderr,"LOADNEXT:PLS==NULL\n");
   }else {
       fprintf(stderr,"LOADNEXT:plsn=%d, pls[curpls].len=%d\n",plsn,pls[curpls].len);
       fprintf(stderr,"LOADNEXT:curpls=%d, curRabbit=%d\n",curpls,curRabbit);   
   }
   if(pls==NULL||plsn<=0||curpls>=plsn||curpls<0||curRabbit<0||curRabbit>=pls[curpls].len){
      int n;
      sscanf(currentFile,"quick_%d.r2",&n);
      n++;
      if(n<0||n>=1024)
          n=0;
      for(;n<1024;n++){
          FILE*f;
          sprintf(nameReturn,"saves/quick_%d.r2",n);
          f=fopen(nameReturn,"r");
          if(f!=NULL){
              fclose(f);
              sprintf(nameReturn,"quick_%d.r2",n);
              if(!load_rabbit(nameReturn))
                  return nameReturn;
          }
     }
     return NULL;
   }else{
        curRabbit++;
        while(curRabbit>=pls[curpls].len)
            curRabbit-=pls[curpls].len;
        fprintf(stderr,"Loading (%s) ",pls[curpls].rabbits[curRabbit].name);
        fprintf(stderr,"(%d, %d)...",curpls,curRabbit);
        fflush(stderr);

        if(!load_rabbit(pls[curpls].rabbits[curRabbit].name)){
                    fprintf(stderr,"success\n");
                    fflush(stderr);
                    fprintf(stderr,"LoadNext:%s",pls[curpls].rabbits[curRabbit].name);
                    fprintf(stderr," pl=%d,r=%d\n",curpls,curRabbit);                    
                    return pls[curpls].rabbits[curRabbit].name;
        }
        fprintf(stderr,"unsuccess\n");
         fflush(stderr);
        return NULL;
    }

}
/*
extern struct playList*pls;
extern int plsn;
extern int    curpls;
extern int    curRabbit;
*/
char*loadPrev(){
    if(pls==NULL||plsn<=0||curpls>=plsn||curpls<0||curRabbit<0||curRabbit>=pls[curpls].len){
        int n;
        sscanf(currentFile,"quick_%d.r2",&n);
        n--;
        if(n<0||n>=1024)
            n=1023;
        for(;n>0;n--){
            FILE*f;
            sprintf(nameReturn,"saves/quick_%d.r2",n);
            f=fopen(nameReturn,"r");
            if(f!=NULL){
                fclose(f);
                sprintf(nameReturn,"quick_%d.r2",n);
                if(!load_rabbit(nameReturn))
                    return nameReturn;
            }
       }
       return NULL;
    }else{
        curRabbit--;
        while(curRabbit<0)
            curRabbit+=pls[curpls].len;
        fprintf(stderr,"Loading %s ...",pls[curpls].rabbits[curRabbit].name);
        fflush(stderr);
        if(!load_rabbit(pls[curpls].rabbits[curRabbit].name)){
                    fprintf(stderr,"success\n");
                    fflush(stderr);
                   return pls[curpls].rabbits[curRabbit].name;
        }
        fprintf(stderr,"unsuccess\n");
         fflush(stderr);

        return NULL;
    }

}





int netprintf(const char*s){
    mySend(s);
    return strlen(s);
}
char sendBuf[65536];

int netprintf(const char*s,int a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}
int netprintf(const char*s,double a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}

int netprintf(const char*s,char*a,int b,double c){
    sprintf(sendBuf,s,a,b,c);
    mySend(sendBuf);
    return strlen(sendBuf);
}
int netprintf(const char*s,double b,double c){
    sprintf(sendBuf,s,b,c);
    mySend(sendBuf);
    return strlen(sendBuf);
}

int netprintf(const char*s,char*a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}

int netprintf(const char*s,const char*a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}
int netprintf(const char*s,char*a,int b){
    sprintf(sendBuf,s,a,b);
    mySend(sendBuf);
    return strlen(sendBuf);
}




int netfprintf(FILE*f,const char*s){
    if(f==stdout){
        mySend(s);
    }else{
        fwrite(s,strlen(s),1,f);
    }
    return strlen(s);
}


int netfprintf(FILE*f,const char*s,int a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
/*int netfprintf(FILE*f,const char*s,Uint32 a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}*/
int netfprintf(FILE*f,const char*s,double a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}

int netfprintf(FILE*f,const char*s,const char*a,int b,double c){
    sprintf(sendBuf,s,a,b,c);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,const char*a,int b){
    sprintf(sendBuf,s,a,b);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}

int netfprintf(FILE*f,const char*s,int a,int b,int c){
    sprintf(sendBuf,s,a,b,c);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,char*a,int b,double c){
    sprintf(sendBuf,s,a,b,c);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}

int netfprintf(FILE*f,const char*s,int a,int b){
    sprintf(sendBuf,s,a,b);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,unsigned  a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(const char*s,unsigned  a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}

int netfprintf(FILE*f,const char*s,const char*a,const char*b){
    sprintf(sendBuf,s,a,b);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,double b,double c){
    sprintf(sendBuf,s,b,c);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}

int netfprintf(FILE*f,const char*s,char*a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}


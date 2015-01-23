#ifndef STRINGIDMOD
#define STRINGIDMOD
#define STRIDS 10000
int ids_count=0;
char*ids_strings[STRIDS];

int string2id(const char*s){
    int i;
    for(i=0;i<ids_count;i++){
        if(!strcmp(s,ids_strings[i])){
            return i;
        }
    }
    if(ids_count<STRIDS){
        ids_strings[ids_count]=(char*)malloc(strlen(s)+1);
        if(ids_strings[ids_count]==NULL){
            return -1;
        }
        strcpy(ids_strings[ids_count],s);
        return ids_count++;
    }
    return -2;
}
char* id2string(int id){
    if(id<0||id>=ids_count)
        return NULL;
    return ids_strings[id];
}
void clearStringIds(){
    for(int i=0;i<ids_count;i++){
        if(ids_strings[i]!=NULL)
            free(ids_strings[i]);
    }
    ids_count=0;

}
#endif
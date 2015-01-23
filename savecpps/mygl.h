#include <GL/glew.h>
#include <GL/glu.h>

#ifndef MYGLMOD
#define MYGLMOD
void init_GL(){
    GLenum err = glewInit();
    if (GLEW_OK != err){
        fprintf(stderr, "Error: %s\n",(char*) glewGetErrorString(err));
    }else{
       fprintf(stderr, "Status: Using GLEW %s\n",(char*) glewGetString(GLEW_VERSION));
    }
}
#endif

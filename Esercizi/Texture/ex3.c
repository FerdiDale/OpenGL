#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../texture.c"

float DEG_TO_RAD = 3.14/180;
float ballRotation [3] = {0, 0, 0};
float pointOfView [3] = {0, 3, 3};
float eyeDistance = 4;
byte forward = 1;
unsigned *image, *imagea; 
GLsizei imageWidth, imageHeight, components; 

GLvoid initTexture( unsigned *image, GLsizei imageWidth, GLsizei imageHeight ) {  
    GLsizei sWidth=256, sHeight=256;  
    unsigned *sImage;  
    glTexParameterf(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_NEAREST);  
    sImage = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );  
    gluScaleImage( GL_RGBA, imageWidth, imageHeight,  GL_UNSIGNED_BYTE, image,  sWidth, sHeight, GL_UNSIGNED_BYTE, sImage );  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,  0, GL_RGBA, GL_UNSIGNED_BYTE, sImage);  
    glEnable( GL_TEXTURE_2D ); 
} 

void timeFunc (int value) {
    ballRotation[0]+=1;
    ballRotation[1]+=2;
    ballRotation[2]+=3;
    glutPostRedisplay();
    glutTimerFunc(25, timeFunc, 0);
}

GLvoid drawScene(void) {  
    glClearColor(0.1, 0.4, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  
    glPushMatrix(); 
    gluLookAt(pointOfView[0], pointOfView[1], pointOfView[2], 0, 0, 0, 0, 1, 0);
    float scaleS = 1.1, scaleT = 1.2;
    float s[4] = { scaleS, 0, 0, 0 };
    float t[4] = { 0, scaleT, 0, 0 };
    glTexGenfv( GL_S, GL_OBJECT_PLANE, s );
    glTexGenfv( GL_T, GL_OBJECT_PLANE, t );
    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    glEnable( GL_TEXTURE_GEN_S );   
    glEnable( GL_TEXTURE_GEN_T );
    glRotatef(ballRotation[0], 1, 0, 0);
    glRotatef(ballRotation[1], 0, 1, 0);
    glRotatef(ballRotation[2], 0, 0, 1);
    glutSolidSphere(1, 100, 100);
    glPopMatrix();
    glutSwapBuffers(); 
} 

int main(int argc, char** argv) {
 
    GLsizei width=640, height=480;  
    GLdouble aspect;  
    glutInit( &argc, argv );  
    image = read_texture("../fish.rgba", &imageWidth, &imageHeight, &components); 
    imagea = read_texture("../fisha.rgba", &imageWidth, &imageHeight, &components); 
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    initTexture( image, imageWidth, imageHeight );  
    aspect = (GLdouble) width / (GLdouble) height;  
    glMatrixMode( GL_PROJECTION );  
    glLoadIdentity();  
    gluPerspective( 45.0, aspect, 1.0, 50.0 );  
    glMatrixMode( GL_MODELVIEW );  
    glLoadIdentity();  
    glutDisplayFunc( drawScene );  
    glutTimerFunc(10, timeFunc, 0);
    glutMainLoop(); 
}
#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../texture.c"

float DEG_TO_RAD = 3.14/180;
float fishPosition [3] = {-6.28, 0, 0};
float pointOfView [3] = {0, 0, -8};
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
    if (forward) {
        fishPosition[0]+=0.1;
        if (fishPosition[0] >= 6.28) {
            forward = 0;
            initTexture( imagea, imageWidth, imageHeight );  
        }
    }
    else {
        fishPosition[0]-=0.1;
        if (fishPosition[0] <= -6.28) {
            forward = 1;
            initTexture( image, imageWidth, imageHeight );  
        }
    }
    fishPosition[1]=sin(fishPosition[0]);
    glutPostRedisplay();
    glutTimerFunc(10, timeFunc, 0);
}

GLvoid drawScene(void) {  
    float v0[3] = { -1.5, -1.0, 0.0 };  
    float v1[3] = { 1.5, -1.0, 0.0 };  
    float v2[3] = { 1.5, +1.0, 0.0 };  
    float v3[3] = { -1.5, +1.0, 0.0 };  
    float t0[2] = { 0.0, 0.0 };  
    float t1[2] = { 1.0, 0.0 };  
    float t2[2] = { 1.0, 1.0 };  
    float t3[2] = { 0.0, 1.0 };  
    glClear( GL_COLOR_BUFFER_BIT );  
    glColor3f( 1.0, 1.0, 1.0);  
    glPushMatrix();
    gluLookAt(pointOfView[0], pointOfView[1], pointOfView[2], fishPosition[0], pointOfView[1], 0, 0, 1, 0);
    // glRotatef(-cos(fishPosition[0])*10, 0, 0, 1);
    glTranslatef(0, fishPosition[1], 0);
    glBegin( GL_QUADS );  
    glTexCoord2fv( t0 );    glVertex3fv( v0 );  
    glTexCoord2fv( t1 );    glVertex3fv( v1 );  
    glTexCoord2fv( t2 );    glVertex3fv( v2 );  
    glTexCoord2fv( t3 );    glVertex3fv( v3 );  
    glEnd(); 
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
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); 
    aspect = (GLdouble) width / (GLdouble) height;  
    glMatrixMode( GL_PROJECTION );  
    glLoadIdentity();  
    gluPerspective( 45.0, aspect, 1.0, 50.0 );  
    glMatrixMode( GL_MODELVIEW );  
    glLoadIdentity();  
    glTranslatef( 0.0, 0.0, -12.0 );  
    glutDisplayFunc( drawScene );  
    glutTimerFunc(10, timeFunc, 0);
    glutMainLoop(); 
}
#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../texture.c"

float DEG_TO_RAD = 3.14/180;
float pointOfView [3] = {0, 0, 5};
unsigned *image, *imagea; 
unsigned *sImage;  
GLsizei imageWidth, imageHeight, components; 

float xzAngle = 1;
float startX;
float deltaX;
byte lPressed;
float eyeDistance = 4;

 void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case '1':
        glTexParameterf(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);  
            glutPostRedisplay();
            break;

        case '2':
            glTexParameterf(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);  
            glutPostRedisplay();
            break;
            
        case '3':
            glTexParameterf(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);  
            glutPostRedisplay();
            break;

        case '4':
            glTexParameterf(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);  
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
}

void motionFunc(int x, int y) {
    if (lPressed) {
        deltaX = x-startX;
        startX = x;
        xzAngle-=deltaX/100;
        if (xzAngle <= 0)
            xzAngle = 0.01;
        glutPostRedisplay();
    }
}

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lPressed = 1;
            startX = x;
        }
        else
            lPressed = 0;
    }

}

GLvoid initTexture( unsigned *image, GLsizei imageWidth, GLsizei imageHeight ) {  
    GLsizei sWidth=256, sHeight=256;  
    sImage = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );  
    gluScaleImage( GL_RGBA, imageWidth, imageHeight,  GL_UNSIGNED_BYTE, image,  sWidth, sHeight, GL_UNSIGNED_BYTE, sImage );  
    glEnable( GL_TEXTURE_2D ); 
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, sImage);
    glTexParameterf(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);  
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
    gluLookAt(pointOfView[0], pointOfView[1], pointOfView[2], 0, 0, 0, 0, 1, 0);
    glScalef(xzAngle, xzAngle, xzAngle);
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
    glutMotionFunc(motionFunc);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(keyboard);
    initTexture( image, imageWidth, imageHeight );  
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); 
    aspect = (GLdouble) width / (GLdouble) height;  
    glMatrixMode( GL_PROJECTION );  
    glLoadIdentity();  
    gluPerspective( 45.0, aspect, 1.0, 50.0 );  
    glMatrixMode( GL_MODELVIEW );  
    glLoadIdentity();  
    glutDisplayFunc( drawScene );  
    glutMainLoop(); 
}
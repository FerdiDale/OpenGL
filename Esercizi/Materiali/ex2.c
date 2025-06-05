#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float DEG_TO_RAD = 3.14/180;
float xzAngle = 0;
float yzAngle = 0;
float startX, startY;
float deltaX, deltaY;
byte lPressed;
float lookX = 0, lookY = 0, lookZ = 0;
float eyeDistance = 10;
float translateZ = 0;
float translateX = 0;
float hallDepth = 30, hallWidth = 15, hallHeight = 15;
float bitSize = 0.5;

void motionFunc(int x, int y) {
    if (lPressed) {
        deltaX = x-startX;
        deltaY = y-startY;
        startX = x;
        startY = y;
        xzAngle+=deltaX;
        yzAngle+=deltaY;
        lookX = eyeDistance*sin(DEG_TO_RAD*xzAngle)*cos(DEG_TO_RAD*yzAngle);
        lookY = eyeDistance*sin(DEG_TO_RAD*yzAngle);
        lookZ = eyeDistance*cos(DEG_TO_RAD*xzAngle)*cos(DEG_TO_RAD*yzAngle);
        glutPostRedisplay();
    }
}

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case 'w':
            translateZ++;
            glutPostRedisplay();
            break;

        case 's':
            translateZ--;
            glutPostRedisplay();
            break;
            
        case 'a':
            translateX++;
            glutPostRedisplay();
            break;

        case 'd':
            translateX--;
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
}

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lPressed = 1;
            startX = x;
            startY = y;
        }
        else
            lPressed = 0;
    }

}

GLvoid errorCallback(GLenum errorCode) { 
    const GLubyte *estring;
    estring = gluErrorString(errorCode);
    fprintf (stderr, "Errore QUADRICHE: %s\n", estring);
    exit (0);
}

GLvoid buildHall() {
        float y = -hallHeight/2;
        for (float x = -hallWidth/2; x < hallWidth/2; x+=bitSize) {
             for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
                glNormal3f(0, 1, 0);
                glBegin(GL_POLYGON);
                glVertex3f(x, y, z);
                glVertex3f(x, y, z+bitSize);
                glVertex3f(x+bitSize, y, z+bitSize);
                glVertex3f(x+bitSize, y, z);
                glEnd();
             }
        }

        y = hallHeight/2;
        for (float x = -hallWidth/2; x < hallWidth/2; x+=bitSize) {
             for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
                glNormal3f(0, -1, 0);
                glBegin(GL_POLYGON);
                glVertex3f(x, y, z);
                glVertex3f(x, y, z+bitSize);
                glVertex3f(x+bitSize, y, z+bitSize);
                glVertex3f(x+bitSize, y, z);
                glEnd();
             }
        }

        float x = -hallHeight/2;
        for (float y = -hallWidth/2; y < hallWidth/2; y+=bitSize) {
             for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
                glNormal3f(1, 0, 0);
                glBegin(GL_POLYGON);
                glVertex3f(x, y, z);
                glVertex3f(x, y, z+bitSize);
                glVertex3f(x, y+bitSize, z+bitSize);
                glVertex3f(x, y+bitSize, z);
                glEnd();
             }
        }

        x = hallHeight/2;
        for (float y = -hallWidth/2; y < hallWidth/2; y+=bitSize) {
             for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
                glNormal3f(-1, 0, 0);
                glBegin(GL_POLYGON);
                glVertex3f(x, y, z);
                glVertex3f(x, y, z+bitSize);
                glVertex3f(x, y+bitSize, z+bitSize);
                glVertex3f(x, y+bitSize, z);
                glEnd();
             }
        }
}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    // glEnable(GL_LIGHT2);
    // glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        gluLookAt(0+translateX, 0, -hallWidth/2+translateZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

        buildHall();

        // y = hallHeight/3;
        // x = -hallWidth/2+0.01;
        float x = 0, y = 0;
        float z = 0;
        GLfloat diffuse [4] = {1, 1, 1, 1}; 
        // for (float z = -hallDepth/2+1; z < hallDepth/2-1; z+=(hallDepth-2)/4) {
            GLfloat position1 [4] = {x, y, z, 0};
            glLightfv(GL_LIGHT1, GL_POSITION, position1);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
            glLightfv(GL_LIGHT1, GL_SPECULAR, diffuse);
        // }

    glPopMatrix();
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motionFunc);
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
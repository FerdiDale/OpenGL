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
float eyeX = 0, eyeY = 0, eyeZ = 6;
float eyeDistance = 6;

struct vertex {
    float x; 
    float y;
    float z;
} typedef tVertex;

struct polygon {
    tVertex* vertices;
    int nVertices;
    tVertex normal;
} typedef tPolygon;

struct polyhedron {
    tPolygon* faces;
    int nFaces;
    tVertex* vertices;
    int nVertices;
} typedef tPolyhedron;

void motionFunc(int x, int y) {
    if (lPressed) {
        deltaX = x-startX;
        deltaY = y-startY;
        startX = x;
        startY = y;
        xzAngle-=deltaX;
        yzAngle+=deltaY;
        if (yzAngle > 60)
            yzAngle = 60;
        if (yzAngle < -60)
            yzAngle = -60;
        eyeX = eyeDistance*sin(DEG_TO_RAD*xzAngle)*cos(DEG_TO_RAD*yzAngle);
        eyeY = eyeDistance*sin(DEG_TO_RAD*yzAngle);
        eyeZ = eyeDistance*cos(DEG_TO_RAD*xzAngle)*cos(DEG_TO_RAD*yzAngle);
        glutPostRedisplay();
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

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 8);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 1.0, 1.5, 2.0, 0.0, 1.0, 0.0);

    glBegin( GL_POLYGON );
    glColor4f(1.0, 0.0, 0.0, 1.0);

    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(2, 0, 4);
    glVertex3f(0, 0, 4);
    glEnd();
    
    glBegin( GL_POLYGON );
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glVertex3f(2, 0, 0);
    glVertex3f(2, 2, 0);
    glVertex3f(2, 2, 4);
    glVertex3f(2, 0, 4);
    glEnd();

    glBegin( GL_POLYGON );
    glColor4f(1.0, 0.0, 1.0, 1.0);
    glVertex3f(2, 2, 0);
    glVertex3f(1, 3, 0);
    glVertex3f(1, 3, 4);
    glVertex3f(2, 2, 4);
    glEnd();

    glBegin( GL_POLYGON );
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3f(1, 3, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 2, 4);
    glVertex3f(1, 3, 4);
    glEnd();

    glBegin( GL_POLYGON );
    glColor4f(0.0, 1.0, 1.0, 1.0);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 4);
    glVertex3f(0, 2, 4);
    glEnd();

    glBegin( GL_POLYGON );
    glColor4f(1.0, 1.0, 1.0, 1.0);

    glVertex3f(0, 0, 4);
    glVertex3f(0, 2, 4);
    glVertex3f(1, 3, 4);
    glVertex3f(2, 2, 4);
    glVertex3f(2, 0, 4);

    glEnd();

    glBegin( GL_POLYGON );
    glColor4f(1.0, 1.0, 1.0, 1.0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(1, 3, 0);
    glVertex3f(2, 2, 0);
    glVertex3f(2, 0, 0);

    glEnd();

    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutMainLoop(); //Ciclo principale
}
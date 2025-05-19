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
float eyeDistance = 4;

GLfloat controlPoints[4][4][3] = { {{-3, -3, -3}, {-3, -1, -3},{-3, 1, -3}, {-3, 3, -3}},
                                        {{-1, -3, -3}, {-1, -1, 3}, {-1, 1, 3},  {-1, 3, -3}},
                                        {{1, -3, -3},  {1, -1, 3},  {1, 1, 3},   {1, 3, -3}},
                                        {{3, -3, -3},  {3, -1, -3}, {3, 1, -3},  {3, 3, -3}}};
GLUnurbsObj *theNurb;
GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};


void motionFunc(int x, int y) {
    if (lPressed) {
        deltaX = x-startX;
        startX = x;
        xzAngle-=deltaX;
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

GLvoid errorCallback(GLenum errorCode) { 
    const GLubyte *estring;
    estring = gluErrorString(errorCode);
    fprintf (stderr, "Errore QUADRICHE: %s\n", estring);
    exit (0);
}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    gluLookAt(0, eyeDistance/2, -eyeDistance, 0, 0, 0, 0.0, 1.0, 0.0);
    GLfloat position2 [4] = {0, 0, -eyeDistance, 0};
    GLfloat diffuse2 [3] = {1, 0, 0};
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);

    glPushMatrix();
    glRotatef(xzAngle, 0, 1, 0);

    GLfloat position1 [4] = {1, 1, 0, 0};
    GLfloat diffuse1 [3] = {1, 1, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);

    GLUquadricObj *qsphere1, *qsphere2; 
    qsphere1 = gluNewQuadric(); //Creazione 
    gluQuadricCallback(qsphere1, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
    gluQuadricDrawStyle(qsphere1, GLU_FILL); 
    gluQuadricOrientation(qsphere1, GLU_OUTSIDE); 
    gluQuadricNormals(qsphere1, GLU_SMOOTH); 
    glPushMatrix();
    glTranslatef(0, 0, 1);
    gluSphere(qsphere1, 1.25, 15, 10); //raggio, longit., latit.
    glPopMatrix();

    qsphere2 = gluNewQuadric(); //Creazione 
    gluQuadricCallback(qsphere2, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
    gluQuadricDrawStyle(qsphere2, GLU_FILL); 
    gluQuadricOrientation(qsphere2, GLU_OUTSIDE); 
    gluQuadricNormals(qsphere2, GLU_SMOOTH); 
    glPushMatrix();
    glTranslatef(0, 0, -1);
    gluSphere(qsphere2, 1.25, 15, 10); //raggio, longit., latit.
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutMotionFunc(motionFunc);
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
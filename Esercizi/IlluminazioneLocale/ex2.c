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
float eyeX = 0, eyeY = 0, eyeZ = 5;
float eyeDistance = 5;
byte light1On = 0, light2On = 0, light3On = 0;

GLfloat controlPoints[4][4][3] = { {{-3, -3, -3}, {-3, -1, -3},{-3, 1, -3}, {-3, 3, -3}},
                                        {{-1, -3, -3}, {-1, -1, 3}, {-1, 1, 3},  {-1, 3, -3}},
                                        {{1, -3, -3},  {1, -1, 3},  {1, 1, 3},   {1, 3, -3}},
                                        {{3, -3, -3},  {3, -1, -3}, {3, 1, -3},  {3, 3, -3}}};
GLUnurbsObj *theNurb;
GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};


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

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case 'q':
            if (light1On) {
                light1On = 0;
                glDisable(GL_LIGHT1);
            }
            else {
                light1On = 1;
                glEnable(GL_LIGHT1);
            }
            glutPostRedisplay();
            break;

        case 'w':
            if (light2On) {
                light2On = 0;
                glDisable(GL_LIGHT2);
            }
            else {
                light2On = 1;
                glEnable(GL_LIGHT2);
            }
            glutPostRedisplay();
            break;

        case 'e':
            if (light3On) {
                light3On = 0;
                glDisable(GL_LIGHT3);
            }
            else {
                light3On = 1;
                glEnable(GL_LIGHT3);
            }
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

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0.0, 1.0, 0.0);

    GLfloat modelAmbient [4] = {1, 1, 1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmbient);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

    GLfloat position1 [4] = {0, -4, -4, 0};
    GLfloat diffuse1 [3] = {1, 1, 0};
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);

    GLfloat position2 [4] = {-4, 4, 0, 0};
    GLfloat diffuse2 [3] = {0, 1, 1};
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);

    GLfloat position3 [4] = {4, 4, 0, 0};
    GLfloat diffuse3 [3] = {1, 0, 1};
    glLightfv(GL_LIGHT3, GL_POSITION, position3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);

    GLUquadricObj *qsphere, *qcylinder, *qdisk; 
    qsphere = gluNewQuadric(); //Creazione 
    gluQuadricCallback(qsphere, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
    gluQuadricDrawStyle(qsphere, GLU_FILL); 
    gluQuadricOrientation(qsphere, GLU_OUTSIDE); 
    gluQuadricNormals(qsphere, GLU_SMOOTH); 
    glPushMatrix();
    glTranslatef(0, 0, 2);
    gluSphere(qsphere, 0.75, 15, 10); //raggio, longit., latit.
    glPopMatrix();
    qcylinder = gluNewQuadric(); //Creazione 
    gluQuadricCallback(qcylinder, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
    gluQuadricDrawStyle(qcylinder, GLU_FILL); 
    gluQuadricOrientation(qcylinder, GLU_OUTSIDE); 
    gluQuadricNormals(qcylinder, GLU_SMOOTH); 
    glPushMatrix();
    glTranslatef(2, 0, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(qcylinder, 0.75, 0.75, 1.5, 15, 10);
    glPopMatrix();
    qdisk = gluNewQuadric(); //Creazione 
    gluQuadricCallback(qdisk, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
    gluQuadricDrawStyle(qdisk, GLU_FILL); 
    gluQuadricOrientation(qdisk, GLU_OUTSIDE); 
    gluQuadricNormals(qdisk, GLU_SMOOTH); 
    glPushMatrix();
    glTranslatef(-1, 0, -1);
    glRotatef(-90, 1, 0, 0);
    gluDisk(qdisk, 0.25, 0.75, 15, 10);
    glPopMatrix();

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
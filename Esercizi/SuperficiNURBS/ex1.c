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

int numberUValues = 30, numberVValues = 8;
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(eyeX, eyeY, eyeZ, 1.5, 1.5, 1.5, 0.0, 1.0, 0.0);

    theNurb=gluNewNurbsRenderer();
    gluBeginSurface(theNurb); 
    gluNurbsProperty(theNurb, GLU_U_STEP, 20); 
    gluNurbsProperty(theNurb, GLU_V_STEP, 100); 
    gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL); 
    // gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
    gluNurbsSurface(theNurb,8, knots, 8, knots,4 * 3, 3, &controlPoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);

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
    glEnable(GL_AUTO_NORMAL);
    glMapGrid2f(numberUValues, 0, 1, numberVValues, 0, 1);
    glutMainLoop(); //Ciclo principale
}
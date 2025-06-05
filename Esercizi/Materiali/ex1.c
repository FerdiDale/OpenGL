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
        gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0.0, 1.0, 0.0);

        GLfloat position1 [4] = {2.5, 1, 0.5, 0};
        GLfloat diffuse [4] = {1, 1, 1, 1};
        glLightfv(GL_LIGHT1, GL_POSITION, position1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, diffuse);

        GLfloat position2 [4] = {-1.5, 1.5, 1.5, 0};
        glLightfv(GL_LIGHT2, GL_POSITION, position2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, diffuse);

        glPushMatrix();
            glTranslatef(0, 0, 2);
            glRotatef(-90, 1, 0, 0);
            GLfloat emissionTorusMaterial [4] = {1, 1, 0, 1};
            GLfloat defaultEmission [4] = {0, 0, 0, 1};
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionTorusMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, defaultEmission);
            glutSolidTorus(0.25, 0.5, 24, 24);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, defaultEmission);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(2, 0, 0);
            glRotatef(-90, 1, 0, 0);
            GLfloat diffuseConeMaterial [4] = {0, 0, 1, 1};
            GLfloat defaultDiffuse [4] = {0.8, 0.8, 0.8, 1};
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseConeMaterial);
            glutSolidCone(0.5, 1, 24, 24);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1, 0, -1);
            GLfloat diffuseSphereMaterial [4] = {1, 0, 0, 1};
            GLfloat specularSphereMaterial [4] = {1, 1, 1, 1};
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseSphereMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularSphereMaterial);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
            glutSolidSphere(1, 24, 24);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaultEmission);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
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
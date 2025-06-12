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
float hallDepth = 90, hallWidth = 10, hallHeight = 15;
float bitSize = 0.5;

void motionFunc(int x, int y) {
    if (lPressed) {
        deltaX = x-startX;
        deltaY = y-startY;
        startX = x;
        startY = y;
        if (abs(yzAngle+deltaY/3) <= 30)        
            yzAngle+=deltaY/3;
        if (abs(xzAngle+deltaX/3) <= 30)
            xzAngle+=deltaX/3;
        lookX = xzAngle;
        lookY = yzAngle;
        lookZ = eyeDistance*cos(DEG_TO_RAD*xzAngle)*cos(DEG_TO_RAD*yzAngle);
        glutPostRedisplay();
    }
}

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case 'w':
            if (translateZ-1 > -hallDepth) {
                translateZ--;
                printf("%f", translateZ);
            }
            glutPostRedisplay();
            break;

        case 's':
            if (translateZ < 0)
                translateZ++;
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

        float x = -hallWidth/2;
        for (float y = -hallHeight/2; y < hallHeight/2; y+=bitSize) {
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

        x = hallWidth/2;
        for (float y = -hallHeight/2; y < hallHeight/2; y+=bitSize) {
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
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 80);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        
        gluLookAt(0, -hallHeight/10, -hallDepth/2, lookX, lookY, lookZ, 0.0, 1.0, 0.0);
        glTranslatef(0, 0, translateZ);

        float y = hallHeight/3;
        float x = -hallWidth/2+1;
        GLint lightId = GL_LIGHT0;
        for (float z = -hallDepth/2+1; z <= hallDepth/2-1; z+=(hallDepth-2)/2) {
            lightId++;
            GLfloat position1 [4] = {x, y, z, 1};
            GLfloat diffuse [4] = {1, 1, 1, 1};
            glLightfv(lightId, GL_POSITION, position1);
            glLightfv(lightId, GL_DIFFUSE, diffuse);
            glLightfv(lightId, GL_SPECULAR, diffuse);
            glLightf(lightId, GL_CONSTANT_ATTENUATION, 1.0);
            glLightf(lightId, GL_LINEAR_ATTENUATION, 0.05);
            glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.01);
        }
        y = hallHeight/3;
        x = hallWidth/2-1;
        for (float z = -hallDepth/2+1; z <= hallDepth/2-1; z+=(hallDepth-2)/2) {
            lightId++;
            GLfloat position1 [4] = {x, y, z, 1};
            GLfloat diffuse [4] = {1, 1, 1, 1};
            glLightfv(lightId, GL_POSITION, position1);
            glLightfv(lightId, GL_DIFFUSE, diffuse);
            glLightfv(lightId, GL_SPECULAR, diffuse);
            glLightf(lightId, GL_CONSTANT_ATTENUATION, 1.0);
            glLightf(lightId, GL_LINEAR_ATTENUATION, 0.05);
            glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.01);
        }
        buildHall();    

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
    glEnable(GL_AUTO_NORMAL);
    glutMainLoop(); //Ciclo principale
}
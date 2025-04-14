#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vertex {
    float x; 
    float y;
    float z;
} typedef tVertex;

float cellSpace = 0.6;
float k = 0;
byte active = 0;

float getParametricY (float x, float z) {
    float modifiedSquaredSum = sqrt(pow(x, 2) + pow(z, 2))-k*3.14/32;
    return ((2*sin(modifiedSquaredSum))/modifiedSquaredSum);
}

tVertex getSquareNormal (tVertex* square) {
    float nx = 0;
    float ny = 0;
    float nz = 0;
    for (int i = 0; i < 4; i++) {
        tVertex currVertex = square[i];
        tVertex nextVertex = square[(i+1)%4];
        nx += ((currVertex.y-nextVertex.y)*(currVertex.z+nextVertex.z));
        ny += ((currVertex.z-nextVertex.z)*(currVertex.x+nextVertex.x));
        nz += ((currVertex.x-nextVertex.x)*(currVertex.y+nextVertex.y));
    }
    return (tVertex){nx, ny, nz};
}

void timeFunc (int value) {
    if (active) {
        k++;
        glutPostRedisplay();
        glutTimerFunc(32, timeFunc, 0);
    }
}

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (!active) {
                active = 1;
                glutTimerFunc(32, timeFunc, 0);
            }
            else {
                active = 0;
            }
        }
    }
}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 35);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(30, 1.0, 0.0, 0.0);

    float y;
    tVertex currSquare [4];
    for (float x = -10; x < 10; x+=cellSpace) {
        for (float z = -10; z < 10; z+=cellSpace) {
            currSquare[0] = (tVertex){x, getParametricY(x,z), z};
            currSquare[1] = (tVertex){x, getParametricY(x,z+cellSpace), z+cellSpace};
            currSquare[2] = (tVertex){x+cellSpace, getParametricY(x+cellSpace,z+cellSpace), z+cellSpace};
            currSquare[3] = (tVertex){x+cellSpace, getParametricY(x+cellSpace,z), z};
            tVertex normal = getSquareNormal(currSquare);
            glNormal3f(normal.x, normal.y, normal.z);
            glColor4f(1.0, 1.0, 1.0, 1.0);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 4; i++) {
                glVertex3f(currSquare[i].x, currSquare[i].y, currSquare[i].z);
            }
            glEnd();
        }
    }

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMouseFunc(mouseFunc);
    glutMainLoop(); //Ciclo principale
}
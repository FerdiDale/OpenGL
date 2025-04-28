#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numberTValues = 30;
GLfloat ***controlPoints;
int nCurves = 1;
int *degree;
GLfloat currVertex [3];

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            currVertex[0] = (x/250.0)-1;
            currVertex[1] = ((y/250.0)-1)*(-1);
            currVertex[2] = 0;
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {

        }
    }

}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    
    glScalef(0.9, 0.9, 0.0);
    // glBegin( GL_LINE_STRIP );
    // glColor4f(1.0, 0.0, 0.0, 1.0);
    // for (int i = 0; i < degree+1; i++) {
    //     currVertex = controlPoints[i];
    //     glVertex3f(currVertex.x, currVertex.y, currVertex.z);
    // }
    // glEnd();
    // if (lState) {
    //     glBegin(GL_LINE_STRIP );
    //     glColor4f(1.0, 0.0, 1.0, 1.0);
    //     for (float t = 0; t < 1; t+=(1.0/numberTValues)) {
    //         currVertex = casteljauAlgorithm(controlPoints, degree, t);
    //         glVertex3f(currVertex.x, currVertex.y, currVertex.z);
    //     }
    //     currVertex = casteljauAlgorithm(controlPoints, degree, 1);
    //     glVertex3f(currVertex.x, currVertex.y, currVertex.z);
    //     glEnd();
    // }
    // if (rState) {
    //     glColor4f(1.0, 1.0, 0.0, 1.0);
    //     glEvalMesh1(GL_LINE, 0, 30);
    // }
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    // glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &controlPointsv[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glMapGrid1f(30, 0.0, 1.0);
    glutMainLoop(); //Ciclo principale
}
#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numberTValues = 30;
GLfloat **controlPoints;
int nCurves = 1;
int *degree;
GLfloat currVertex [3];
int MAX_DEGREE = 9;
int MAX_NCURVES = 20;

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (degree[nCurves-1] == MAX_DEGREE)
                return;
            currVertex[0] = (x/250.0)-1;
            currVertex[1] = ((y/250.0)-1)*(-1);
            currVertex[2] = 0;
            degree[nCurves-1]++;
            for (int i = 0; i < 3; i++) {
                controlPoints[nCurves-1][degree[nCurves-1]*3+i] = currVertex[i];
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (nCurves == MAX_NCURVES)
                return;
            nCurves++;
            degree[nCurves-1] = 0;
            for (int i = 0; i < 3; i++)
                controlPoints[nCurves-1][degree[nCurves-1]*3+i] = currVertex[i];

        }
    }

}

void initStructures () {
    controlPoints = (GLfloat**)(malloc(MAX_NCURVES*sizeof(GLfloat*)));
    for (int i = 0; i < MAX_NCURVES; i++) {
        controlPoints[i] = (GLfloat*)(malloc((MAX_DEGREE+1)*3*sizeof(GLfloat)));
    }
    degree = (int*)(malloc(20*sizeof(int)));
    degree[0] = -1;
}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    
    glScalef(0.9, 0.9, 0.0);
    GLfloat *currVertex;
    for (int i = 0; i < nCurves; i++) {
        glBegin( GL_LINE_STRIP );
        glColor4f(1.0, 0.0, 0.0, 1.0);
        if (i == nCurves-1) {
            for (int j = 0; j < degree[i]+1; j++) {
                currVertex = controlPoints[i];
                printf("%d %f %f %f\n", j, currVertex[j*3+0], currVertex[j*3+1], currVertex[j*3+2]);
                glVertex3f(currVertex[j*3+0], currVertex[j*3+1], currVertex[j*3+2]);
            }
        }
        glEnd();
        if (degree[i] > 0) {
            glColor4f(1.0, 1.0, 1.0, 1.0);
            glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, degree[i]+1, &controlPoints[i][0]);
            glEvalMesh1(GL_LINE, 0, 30);
        }
    }
    glFlush();
}


int main(int argc, char** argv) {
    initStructures();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glEnable(GL_MAP1_VERTEX_3);
    glMapGrid1f(30, 0.0, 1.0);
    glutMainLoop(); //Ciclo principale
}
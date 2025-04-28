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

int numberTValues = 30;
tVertex *controlPoints;
GLfloat controlPointsv [4][3] = {
    {-1.0, -1.0, 0.0},
    {-0.5, 1.0, 0.0},
    {0.5, -1.0, 0.0},
    {1.0, 1.0, 0.0}
};
int degree = 3;
byte lState = 0, rState = 0;

void initControlPoints () {
    controlPoints = (tVertex*)(malloc(4*sizeof(tVertex)));
    controlPoints[0] = (tVertex){-1.0, -1.0, 0.0};
    controlPoints[1] = (tVertex){-0.5, 1.0, 0.0};
    controlPoints[2] = (tVertex){0.5, -1.0, 0.0};
    controlPoints[3] = (tVertex){1.0, 1.0, 0.0};
}

tVertex weightedSumTwoVertices (tVertex v1, tVertex v2, float t) {
    return (tVertex){(1-t)*v1.x+t*v2.x, (1-t)*v1.y+t*v2.y, (1-t)*v1.z+t*v2.z};
}

tVertex casteljauAlgorithm (tVertex *controlPoints, int degree, float t) {
    int nPoints = degree+1;
    tVertex** pointsMatrix = (tVertex **)(malloc(nPoints*sizeof(tVertex *)));
    for (int i = 0; i < nPoints; i++) {
        pointsMatrix[i] = (tVertex *)(malloc((nPoints-i)*sizeof(tVertex)));
    }
    for (int i = 0; i < nPoints; i++) {
        pointsMatrix[0][i] = controlPoints[i];
    }
    for (int r = 1; r < nPoints; r++) {
        for (int i = 0; i < nPoints - r; i++) {
            pointsMatrix[r][i] = weightedSumTwoVertices(pointsMatrix[r-1][i],pointsMatrix[r-1][i+1], t);
        }
    }
    tVertex ret = pointsMatrix[degree][0];
    for (int i = 0; i < nPoints; i++) {
        free(pointsMatrix[i]);
    }
    free(pointsMatrix);
    return ret;
}

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (lState) {
                lState = 0;
            }
            else {
                lState = 1;
                rState = 0;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (rState) {
                rState = 0;
            }
            else {
                rState = 1;
                lState = 0;
            }
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
    glBegin( GL_LINE_STRIP );
    glColor4f(1.0, 0.0, 0.0, 1.0);
    tVertex currVertex;
    for (int i = 0; i < degree+1; i++) {
        currVertex = controlPoints[i];
        glVertex3f(currVertex.x, currVertex.y, currVertex.z);
    }
    glEnd();
    if (lState) {
        glBegin(GL_LINE_STRIP );
        glColor4f(1.0, 0.0, 1.0, 1.0);
        for (float t = 0; t < 1; t+=(1.0/numberTValues)) {
            currVertex = casteljauAlgorithm(controlPoints, degree, t);
            glVertex3f(currVertex.x, currVertex.y, currVertex.z);
        }
        currVertex = casteljauAlgorithm(controlPoints, degree, 1);
        glVertex3f(currVertex.x, currVertex.y, currVertex.z);
        glEnd();
    }
    if (rState) {
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, 30);
    }
    glFlush();
}


int main(int argc, char** argv) {
    initControlPoints();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &controlPointsv[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glMapGrid1f(30, 0.0, 1.0);
    glutMainLoop(); //Ciclo principale
}
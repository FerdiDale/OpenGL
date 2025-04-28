#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numberTValues;
tVertex *controlPoints;
int degree;


struct vertex {
    float x; 
    float y;
    float z;
} typedef tVertex;

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

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // glEnable(GL_DEPTH_TEST);
    
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(90, 1, 1, 20);
    // glMatrixMode(GL_MODELVIEW);
    // glPushMatrix();
    // gluLookAt(eyeX, eyeY, eyeZ, 1.0, 1.5, 2.0, 0.0, 1.0, 0.0);
    
    glBegin(GL_LINE);
    tVertex currVertex;
    for (float t = 0; t < 1; t+=(1/numberTValues)) {
        currVertex = casteljauAlgorithm(controlPoints, degree, t);
        glVertex3f(currVertex.x, currVertex.y, currVertex.z);
    }
    currVertex = casteljauAlgorithm(controlPoints, degree, 1);
    glVertex3f(currVertex.x, currVertex.y, currVertex.z);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
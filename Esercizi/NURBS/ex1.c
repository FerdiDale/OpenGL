#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numberTValues;
int degree;

GLfloat cp [4][3] = {{-4.0,-4.0,0.0}, {-2.0, 4.0, 0.0}, {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};
GLUnurbsObj *theNurb;
GLfloat knots [8] = {0, 0, 0, 0, 1, 1, 1, 1};

GLvoid drawScene(GLvoid) {

    glScalef(0.2, 0.2, 0.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluBeginCurve(theNurb);
    gluNurbsCurve(theNurb, 8, knots, 3, &cp[0][0], 4, GL_MAP1_VERTEX_3);
    gluEndCurve(theNurb);
    glFlush();

}


int main(int argc, char** argv) {
    theNurb = gluNewNurbsRenderer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
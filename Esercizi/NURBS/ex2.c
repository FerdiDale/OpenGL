#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numberTValues;
int degree;

GLfloat cp [7][3] = {{0.3,0.6,0}, {0.3,0.9,0}, {0.9, 0.9, 0}, {0.9, 0.6, 0}, {0.9, 0.3, 0}, {0.3, 0.3, 0}, {0.3, 0.6, 0}};
GLUnurbsObj *theNurb;
GLfloat knots [10] = {0, 0, 0, 0.25, 0.5, 0.5, 0.75, 1, 1, 1};
GLfloat w [7] = {1, 0.5, 0.5, 1, 0.5, 0.5, 1};
GLfloat cpw [7][4];

GLvoid drawScene(GLvoid) {

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", cpw[i][j]);
        }
        printf("\n");
    }

    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluBeginCurve(theNurb);
    gluNurbsCurve(theNurb, 10, knots, 4, &cpw[0][0], 3, GL_MAP1_VERTEX_4);
    gluEndCurve(theNurb);
    glFlush();

}

GLvoid nurbsError(GLenum errorCode) { 
    const GLubyte *estring;
    estring = gluErrorString(errorCode);
    fprintf (stderr, "Errore NURBS: %s\n", estring);
    exit (0);
}

void fillWeights (GLfloat (*cp)[3], GLfloat *w, GLfloat (*cpw)[4], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            cpw[i][j] = cp[i][j]*w[i];
        }
        cpw[i][3] = w[i];
    }
}


int main(int argc, char** argv) {
    fillWeights(cp, w, cpw, 7);
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_U_STEP, 100);
    gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD,
        GLU_DOMAIN_DISTANCE);
    gluNurbsCallback(theNurb, GLU_ERROR, (GLvoid(*))nurbsError);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
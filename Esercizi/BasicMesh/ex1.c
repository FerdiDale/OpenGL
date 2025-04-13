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

struct vertex {
    float x; 
    float y;
    float z;
} typedef tVertex;

struct polygon {
    int nVertices;
    int* vIndexes;
    tVertex normal;
} typedef tPolygon;

struct polyhedron {
    int nFaces;
    tPolygon* faces;
    int nVertices;
    tVertex* vertices;
} typedef tPolyhedron;

tPolyhedron polyhedron;


tVertex getNthIndexedVertex (tPolygon face, int n, tPolyhedron refPolyhedron) {
    return refPolyhedron.vertices[face.vIndexes[n]];
}

int nextI (int i, int N) {
    return ((i+1)%N);
}

tVertex getNormal (tPolygon face, tPolyhedron refPolyhedron) {
    float nx = 0;
    float ny = 0;
    float nz = 0;
    int N = face.nVertices;
    for (int i = 0; i < N; i++) {
        tVertex currVertex = getNthIndexedVertex(face, i, refPolyhedron);
        tVertex nextVertex = getNthIndexedVertex(face, nextI(i, N), refPolyhedron);
        nx += ((currVertex.y-nextVertex.y)*(currVertex.z+nextVertex.z));
        ny += ((currVertex.z-nextVertex.z)*(currVertex.x+nextVertex.x));
        nz += ((currVertex.x-nextVertex.x)*(currVertex.y+nextVertex.y));
    }
    return (tVertex){nx, ny, nz};
}

tPolyhedron initializePolyhedron (tPolyhedron* polyhedron) {

    polyhedron->nFaces = 7;
    polyhedron->faces = (tPolygon*)(malloc(7*sizeof(tPolygon)));

    polyhedron->nVertices = 10;
    polyhedron->vertices = (tVertex*)(malloc(10*sizeof(tVertex)));
    polyhedron->vertices[0] = (tVertex){0, 0, 0};
    polyhedron->vertices[1] = (tVertex){2, 0, 0};
    polyhedron->vertices[2] = (tVertex){2, 2, 0};
    polyhedron->vertices[3] = (tVertex){1, 3, 0};
    polyhedron->vertices[4] = (tVertex){0, 2, 0};
    polyhedron->vertices[5] = (tVertex){0, 0, 4};
    polyhedron->vertices[6] = (tVertex){2, 0, 4};
    polyhedron->vertices[7] = (tVertex){2, 2, 4};
    polyhedron->vertices[8] = (tVertex){1, 3, 4};
    polyhedron->vertices[9] = (tVertex){0, 2, 4};

    polyhedron->faces[0].nVertices = 4;
    polyhedron->faces[1].nVertices = 4;
    polyhedron->faces[2].nVertices = 4;
    polyhedron->faces[3].nVertices = 4;
    polyhedron->faces[4].nVertices = 4;
    polyhedron->faces[5].nVertices = 5;
    polyhedron->faces[6].nVertices = 5;

    for (int i = 0; i < 7; i++) {
        polyhedron->faces[i].vIndexes = (int*)(malloc(polyhedron->faces[i].nVertices*sizeof(int)));
    }

    polyhedron->faces[0].vIndexes[0] = 0;
    polyhedron->faces[0].vIndexes[1] = 1;
    polyhedron->faces[0].vIndexes[2] = 6;
    polyhedron->faces[0].vIndexes[3] = 5;

    polyhedron->faces[1].vIndexes[0] = 1;
    polyhedron->faces[1].vIndexes[1] = 2;
    polyhedron->faces[1].vIndexes[2] = 7;
    polyhedron->faces[1].vIndexes[3] = 6;

    polyhedron->faces[2].vIndexes[0] = 2;
    polyhedron->faces[2].vIndexes[1] = 3;
    polyhedron->faces[2].vIndexes[2] = 8;
    polyhedron->faces[2].vIndexes[3] = 7;

    polyhedron->faces[3].vIndexes[0] = 3;
    polyhedron->faces[3].vIndexes[1] = 4;
    polyhedron->faces[3].vIndexes[2] = 9;
    polyhedron->faces[3].vIndexes[3] = 8;

    polyhedron->faces[4].vIndexes[0] = 9;
    polyhedron->faces[4].vIndexes[1] = 4;
    polyhedron->faces[4].vIndexes[2] = 0;
    polyhedron->faces[4].vIndexes[3] = 5;

    polyhedron->faces[5].vIndexes[0] = 6;
    polyhedron->faces[5].vIndexes[1] = 7;
    polyhedron->faces[5].vIndexes[2] = 8;
    polyhedron->faces[5].vIndexes[3] = 9;
    polyhedron->faces[5].vIndexes[4] = 5;

    polyhedron->faces[6].vIndexes[0] = 0;
    polyhedron->faces[6].vIndexes[1] = 4;
    polyhedron->faces[6].vIndexes[2] = 3;
    polyhedron->faces[6].vIndexes[3] = 2;
    polyhedron->faces[6].vIndexes[4] = 1;

    for (int i = 0; i < 7; i++) {
        polyhedron->faces[i].normal = getNormal(polyhedron->faces[i], *polyhedron);
    }

}

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
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(eyeX, eyeY, eyeZ, 1.0, 1.5, 2.0, 0.0, 1.0, 0.0);
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Luce bianca
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    GLfloat light_position[] = { -150, 150, 150, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
    
    tVertex currVertex;
    for (int i = 0; i < polyhedron.nFaces; i++) {
        tPolygon currFace = polyhedron.faces[i];
        tVertex currNormal = currFace.normal;
        glNormal3f(currNormal.x, currNormal.y, currNormal.z);
        glBegin( GL_POLYGON );
        for (int j = 0; j < currFace.nVertices; j++) {
            currVertex = getNthIndexedVertex(currFace, j, polyhedron);
            glVertex3f(currVertex.x, currVertex.y, currVertex.z);
        }
        glEnd();
    }

    glPopMatrix();

    glFlush();
}


int main(int argc, char** argv) {
    initializePolyhedron(&polyhedron);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutMainLoop(); //Ciclo principale
}
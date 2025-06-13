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
    float nx;
    float ny;
    float nz;
} typedef tVertex;

struct polygon {
    int nVertices;
    int* vIndexes;
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

tPolyhedron readPolyhedron (char* pathname, tPolyhedron* polyhedron) {

    FILE *fileptr;
    fileptr = fopen(pathname, "r");

    if (fileptr == NULL) {
        perror("Impossibile aprire il file");
        exit(1);
    }

    fscanf(fileptr, "element vertex %d\n", &(polyhedron->nVertices));
    fscanf(fileptr, "element face %d\n", &(polyhedron->nFaces));

    perror("1");

    int nVertices = polyhedron->nVertices;
    int nFaces = polyhedron->nFaces;

    polyhedron->faces = (tPolygon*)(malloc(nFaces*sizeof(tPolygon)));
    polyhedron->vertices = (tVertex*)(malloc(nVertices*sizeof(tVertex)));
    tVertex *currVertex;
    for (int i = 0; i < nVertices; i++) {
        currVertex = &(polyhedron->vertices[i]);
        fscanf(fileptr, "%f %f %f %f %f %f\n", &(currVertex->x), &(currVertex->y), &(currVertex->z), 
        &(currVertex->nx), &(currVertex->ny), &(currVertex->nz));
    }
    
    perror("2");

    tPolygon *currFace;
    for (int i = 0; i < nFaces; i++) {
        currFace = &(polyhedron->faces[i]);
        currFace->vIndexes = (int*)(malloc(polyhedron->faces[i].nVertices*sizeof(int)));
        perror("3");
        fscanf(fileptr, "%d ", &(currFace->nVertices));
        int currFaceNVertices = currFace->nVertices;
        for (int j = 0; j < currFaceNVertices; j++) {
            perror("4");
            fscanf(fileptr, "%d ", &(currFace->vIndexes[j]));
        }
    }
    
    // printf("POLIEDRO FACCE %d VERTICI %d\n", polyhedron->nFaces, polyhedron->nVertices);
    // for (int i = 0; i < nVertices; i++) {
    //     currVertex = &(polyhedron->vertices[i]);
    //     printf("VERTICE %f %f %f NORMALE %f %f %f\n", currVertex->x, currVertex->y, currVertex->z,
    //         currVertex->nx, currVertex->ny, currVertex->nz);
    // }
    // for (int i = 0; i < nFaces; i++) {
    //     currFace = &(polyhedron->faces[i]);
    //     printf("\nFACCIA NUMERO %d NVERTICI %d VERTICI ", i, currFace->nVertices);
    //     int currFaceNVertices = currFace->nVertices;
    //     for (int j = 0; j < currFaceNVertices; j++) {
    //         printf("%d ", (currFace->vIndexes[j]));
    //     }
    // }

    fclose(fileptr);

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
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(eyeX, eyeY, eyeZ, 1.0, 1.5, 2.0, 0.0, 1.0, 0.0);
    
    tVertex currVertex;
    for (int i = 0; i < polyhedron.nFaces; i++) {
        tPolygon currFace = polyhedron.faces[i];
        glBegin( GL_POLYGON );
        for (int j = 0; j < currFace.nVertices; j++) {
            currVertex = getNthIndexedVertex(currFace, j, polyhedron);
            glNormal3f(currVertex.nx, currVertex.ny, currVertex.nz);
            glVertex3f(currVertex.x, currVertex.y, currVertex.z);
        }
        glEnd();
    }

    
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    for (int i = 0; i < polyhedron.nFaces; i++) {
        tPolygon currFace = polyhedron.faces[i];
        glBegin( GL_LINES );
        for (int j = 0; j < currFace.nVertices; j++) {
            currVertex = getNthIndexedVertex(currFace, j, polyhedron);
            glVertex3f(currVertex.x, currVertex.y, currVertex.z);
            glVertex3f(currVertex.x+currVertex.nx, currVertex.y+currVertex.ny, currVertex.z+currVertex.nz);
        }
        glEnd();
    }
    glPopMatrix();

    glFlush();
}


int main(int argc, char** argv) {
    if (argc != 2) {
        perror("Numero di parametri errato");
        exit(1);
    }
    readPolyhedron(argv[1], &polyhedron);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutMainLoop(); //Ciclo principale
}
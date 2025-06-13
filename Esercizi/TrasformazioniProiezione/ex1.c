#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <math.h>

float additionalWidth = 0, additionalHeight = 0, additionalDepth = 0, angle = 0;

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case 'q':
            additionalWidth++;
            glutPostRedisplay();
            break;

            
        case 'w':
            additionalHeight++;
            glutPostRedisplay();
            break;

            
        case 'e':
            additionalDepth++;
            glutPostRedisplay();
            break;

        case 'a':
            additionalWidth--;
            glutPostRedisplay();
            break;

            
        case 's':
            additionalHeight--;
            glutPostRedisplay();
            break;

            
        case 'd':
            additionalDepth--;
            glutPostRedisplay();
            break;

        case ' ':
            angle+=45;
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
}

GLvoid drawScene(GLvoid) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    glFrustum(-1-additionalWidth, 1+additionalWidth, -1-additionalHeight, 1+additionalHeight, 1-additionalDepth, 5);
    // gluPerspective(90+additionalWidth, 1, 1-additionalDepth, 5);
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 1.0, 0.0, 0.0 , 1.0);
    glVertex3f(0.2, 0.2, -0.5);
    float radius = 0.5;
    for (int i = 0; i < 8 ; i++)
    {
        float angle = i*6.28/8;
        float x = 0.2+radius*cos(angle);
        float y = 0.2+radius*sin(angle);
        float z = -0.5;
        glVertex3f(x, y, z);
    }
    glVertex3f(0.7, 0.2, -0.5);
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 0.0, 1.0, 0.0 , 1.0);
    glVertex3f(0.2, 0.2, -1.5);
    for (int i = 0; i < 8 ; i++)
    {
        float angle = i*6.28/8;
        float x = 0.2+radius*cos(angle);
        float y = 0.2+radius*sin(angle);
        float z = -1.5;
        glVertex3f(x, y, z);
    }
    glVertex3f(0.7, 0.2, -1.5);
    glEnd();

    glBegin( GL_QUAD_STRIP );
    glColor4f( 0.0, 0.0, 1.0 , 1.0);
    for (int i = 0; i < 8 ; i++)
    {
        float angle = i*6.28/8;
        float x = 0.2+radius*cos(angle);
        float y = 0.2+radius*sin(angle);
        glVertex3f(x, y, -1.5);
        glVertex3f(x, y, -0.5);
    }
    glVertex3f(0.7, 0.2, -1.5);
    glVertex3f(0.7, 0.2, -0.5);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutKeyboardFunc(keyboard);
    glutMainLoop(); //Ciclo principale
}
#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>

GLvoid drawTriangle(GLfloat red, GLfloat green, GLfloat blue)
{
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();
}

GLvoid drawScene(GLvoid) {
    glClearColor(0.6, 0.6, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle(0.0, 0.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    drawTriangle(0.3, 0.3, 0.3);
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(-15.0, 0.0, 0.0, 1.0);
    drawTriangle(0.7, 0.7, 0.7);
    glTranslatef(0.5, 0.0, 0.0);
    glScalef(-0.5, 0.5, 0.5);
    drawTriangle(1.0, 1.0, 1.0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize ( 1000, 1000 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}


#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glut.h> //Inclusione libreria GLU
#include <stdio.h>
#include <math.h>

void checkError (char *label)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        printf("%s: %s\n", label, gluErrorString(error));
    }
}

void redraw(void) {  
    glClear( GL_COLOR_BUFFER_BIT );
    glBegin( GL_QUAD_STRIP );
    for (float angle = 0; angle <= 6.28; angle+=(6.28/20)) {
        float x = 0.25*cos(angle);
        float y = 0.25*sin(angle);
        glColor4f( 1.0, 0.0, 0.0 , 1.0);
        glVertex2f(x, y);
        x*=2;
        y*=2;
        glColor4f( 0.0, 0.0, 1.0 , 1.0);
        glVertex2f(x, y);
    }
    glColor4f( 1.0, 0.0, 0.0 , 1.0);
    glVertex2f(0.25, 0.0);
    glColor4f( 0.0, 0.0, 1.0 , 1.0);
    glVertex2f(0.5, 0.0);
    glEnd(); //Fine disegno primitive
    glFlush(); //Richiesta visualizzazione primitiva (definita in glBegin - glEnd)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(redraw); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}

#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glut.h> //Inclusione libreria GLU
#include <stdio.h>
#include <math.h>

float red = 0;
float blue = 0;
float green = 0;

void checkError (char *label)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        // printf("%s: %s\n", label, gluErrorString(error));
    }
}

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case ' ':
            red = (float)(rand())/(float)(RAND_MAX);
            blue = (float)(rand())/(float)(RAND_MAX);
            green = (float)(rand())/(float)(RAND_MAX);
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
}

void redraw(void) {  
    glClear( GL_COLOR_BUFFER_BIT );
    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 1.0, 0.0, 0.0 , 1.0);
    glVertex2f(0.0, 0.0);
    glColor4f( 0.0, 0.0, 1.0 , 1.0);
    for (float angle = 0; angle < 6.28; angle+=(3.14/10)) {
        float x = 0.5*cos(angle);
        float y = 0.5*sin(angle);
        glVertex2f(x, y);
    }
    glVertex2f(0.5, 0.0);
    glEnd(); //Fine disegno primitive
    glFlush(); //Richiesta visualizzazione primitiva (definita in glBegin - glEnd)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(redraw); //Richiamo funzione di disegno
    // glutKeyboardFunc(keyboard);
    glutMainLoop(); //Ciclo principale
}


#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>

float red = 0;
float blue = 0;
float green = 0;

void checkError (char *label)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        printf("%s: %s\n", label, gluErrorString(error));
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
    glClearColor(red, green, blue, 1); //Pulizia buffer del colore (per questo tutto nero)
    glClear(GL_COLOR_BUFFER_BIT);
    glEnd(); //Fine disegno primitive
    glFlush(); //Richiesta visualizzazione primitiva (definita in glBegin - glEnd)
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(redraw); //Richiamo funzione di disegno
    glutKeyboardFunc(keyboard);
    glutMainLoop(); //Ciclo principale
}


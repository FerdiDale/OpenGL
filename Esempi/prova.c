#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glut.h> //Inclusione libreria GLU

float red = 0;
float blue = 0;
float green = 0;

void init() { }
void redraw(void) {  
    glClearColor(red, blue, green, 1); //Pulizia buffer del colore (per questo tutto nero)
    glEnd(); //Fine disegno primitive
    glFlush(); //Richiesta visualizzazione primitiva (definita in glBegin - glEnd)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Punto"); //Creazione finestra
    glutDisplayFunc(redraw); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
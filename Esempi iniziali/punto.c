#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glut.h> //Inclusione libreria GLU

void init() { }
void redraw(void) {  
    glClear(GL_COLOR_BUFFER_BIT); //Pulizia buffer del colore (per questo tutto nero)
    glBegin(GL_POINTS); //Inizio disegno primitive
    glVertex2f(0.0, 0.0); //Disegno punto
    glEnd(); //Fine disegno primitive
    glFlush(); //Richiesta visualizzazione primitiva (definita in glBegin - glEnd)
    }

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Punto"); //Creazione finestra
    glutDisplayFunc(redraw); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <math.h>

float posX = 0, posY = 0;
float angle = 0, scaleX = 1, scaleY = 1;

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case 'q':
            angle-=15;
            glutPostRedisplay();
            break;

            
        case 'w':
            angle+=15;
            glutPostRedisplay();
            break;

            
        case '.':
            scaleX*=2;
            scaleY*=2;
            glutPostRedisplay();
            break;

        
        case ',':
            scaleX/=2;
            scaleY/=2;
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
}

void specialKeyboard (int key, int x, int y) {
    switch (key){

        case GLUT_KEY_RIGHT:
            posX += 0.5;
            glutPostRedisplay();
            break;

            
        case GLUT_KEY_LEFT:
            posX -= 0.5;
            glutPostRedisplay();
            break;

        case GLUT_KEY_UP:
            posY += 0.5;
            glutPostRedisplay();
            break;

        
        case GLUT_KEY_DOWN:
            posY -= 0.5;
            glutPostRedisplay();
            break;
    }
}

GLvoid drawScene(GLvoid) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(posX, posY, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(scaleX, scaleY, 1);

    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 1.0, 1.0, 1.0 , 1.0);
    glVertex2f(0.0, 0.0);
    float radius;
    for (int i = 0; i < 10 ; i++)
    {
        if (i%2==0)
            radius = 0.15;
        else
            radius = 0.7;
        float angle = i*6.28/10;
        float x = radius*cos(angle);
        float y = radius*sin(angle);
        glVertex2f(x, y);
    }
    glVertex2f(0.15, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    glutMainLoop(); //Ciclo principale
}
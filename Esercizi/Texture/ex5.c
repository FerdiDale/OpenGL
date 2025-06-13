#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../texture.c"

float DEG_TO_RAD = 3.14/180;
float xzAngle = 0;
float yzAngle = 0;
float startX, startY;
float deltaX, deltaY;
byte lPressed;
float lookX = 0, lookY = 0, lookZ = 0;
float eyeDistance = 10;
float translateZ = 0;
float hallDepth = 60, hallWidth = 10, hallHeight = 15;
float bitSize = 2;

GLfloat lightEmissionMaterial [4] = {0.5, 0.45, 0.35, 1};
GLfloat defaultEmissionMaterial [4] = {0, 0, 0, 1};
GLfloat defaultDiffuse [4] = {0.8, 0.8, 0.8, 1};
GLfloat diffuseBlueMaterial [4] = {0, 0, 0.6, 1};
GLfloat beigeDiffuseMaterial [4] = {1, 0.95, 0.85, 1};
GLfloat specularMaterial [4] = {1, 1, 1, 1};
GLfloat defaultSpecularMaterial [4] = {0, 0, 0, 1};
GLfloat defaultEmissiveMaterial [4] = {0, 0, 0, 1};
GLUquadricObj *qcylinder; 

unsigned *imageFloor, *imageWalls, *imageVelvet; 
unsigned *sImage;  
GLsizei imageWidth, imageHeight, components; 
static GLuint texnames[3];

void motionFunc(int x, int y) {
    if (lPressed) {
        deltaX = x-startX;
        deltaY = y-startY;
        startX = x;
        startY = y;
        if (abs(yzAngle+deltaY/3) <= 30)        
            yzAngle+=deltaY/3;
        if (abs(xzAngle+deltaX/3) <= 30)
            xzAngle+=deltaX/3;
        lookX = xzAngle;
        lookY = yzAngle;
        lookZ = eyeDistance*cos(DEG_TO_RAD*xzAngle)*cos(DEG_TO_RAD*yzAngle);
        glutPostRedisplay();
    }
}

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case 'w':
            if (translateZ-1 > -hallDepth) {
                translateZ--;
            }
            glutPostRedisplay();
            break;

        case 's':
            if (translateZ < 0)
                translateZ++;
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
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


GLvoid initTexture( int index, unsigned *imageFloor, GLsizei imageWidth, GLsizei imageHeight ) {  
    glBindTexture(GL_TEXTURE_2D, texnames[index]); 
    GLsizei sWidth=1024, sHeight=1024;  
    sImage = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );  
    gluScaleImage( GL_RGBA, imageWidth, imageHeight,  GL_UNSIGNED_BYTE, imageFloor,  sWidth, sHeight, GL_UNSIGNED_BYTE, sImage ); 
    glTexParameterf(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1024, 1024, GL_RGBA, GL_UNSIGNED_BYTE, sImage); 
} 

GLvoid errorCallback(GLenum errorCode) { 
    const GLubyte *estring;
    estring = gluErrorString(errorCode);
    fprintf (stderr, "Errore QUADRICHE: %s\n", estring);
    exit (0);
}

GLvoid buildAppliques() {
    float x = -hallWidth/2;
    float y = hallHeight/3-1;
    glMaterialfv(GL_FRONT, GL_EMISSION, lightEmissionMaterial);

    glBindTexture(GL_TEXTURE_2D, texnames[2]); 
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        for (float z = -hallDepth/2+10; z <= hallDepth/2-10; z+=(hallDepth-20)/2) {
            glPushMatrix();
                glTranslatef(x, y, z);
                glRotatef(-90, 1, 0, 0);

                gluCylinder(qcylinder, 0, 1.5, 1.5, 50, 50);
                glPopMatrix();
        }
        x = hallWidth/2;
        for (float z = -hallDepth/2+10; z <= hallDepth/2-10; z+=(hallDepth-20)/2) {
            glPushMatrix();
                glTranslatef(x, y, z);
                glRotatef(-90, 1, 0, 0);

                gluCylinder(qcylinder, 0, 1.5, 1.5, 50, 50);
                glPopMatrix();
        }
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, defaultEmissionMaterial);
    glDisable(GL_TEXTURE_2D);
}

GLvoid buildHall() { 
    float v0[3] = { -1.5, -1.0, 0.0 };  
    float v1[3] = { 1.5, -1.0, 0.0 };  
    float v2[3] = { 1.5, +1.0, 0.0 };  
    float v3[3] = { -1.5, +1.0, 0.0 };  
    float t0[2] = { 0.0, 0.0 };  
    float t1[2] = { 1.0, 0.0 };  
    float t2[2] = { 1.0, 1.0 };  
    float t3[2] = { 0.0, 1.0 };  

    glBindTexture(GL_TEXTURE_2D, texnames[0]); 
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
    float y = -hallHeight/2;
    for (float x = -hallWidth/2; x < hallWidth/2; x+=bitSize) {
            for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
            glNormal3f(0, 1, 0);
            glBegin(GL_POLYGON);
            glTexCoord2fv( t0 );
            glVertex3f(x, y, z);
            glTexCoord2fv( t1 );
            glVertex3f(x, y, z+bitSize);
            glTexCoord2fv( t2 );
            glVertex3f(x+bitSize, y, z+bitSize);
            glTexCoord2fv( t3 );
            glVertex3f(x+bitSize, y, z);
            glEnd();
            }
    }
    glMaterialfv(GL_FRONT, GL_SPECULAR, defaultSpecularMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0);
    glDisable( GL_TEXTURE_2D );
    
    y = hallHeight/2;
    for (float x = -hallWidth/2; x < hallWidth/2; x+=bitSize) {
            for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
            glNormal3f(0, -1, 0);
            glBegin(GL_POLYGON);
            glVertex3f(x, y, z);
            glVertex3f(x, y, z+bitSize);
            glVertex3f(x+bitSize, y, z+bitSize);
            glVertex3f(x+bitSize, y, z);
            glEnd();
            }
    }
    
    glBindTexture(GL_TEXTURE_2D, texnames[1]);   
    glEnable(GL_TEXTURE_2D);
    float x = -hallWidth/2;
    for (float y = -hallHeight/2; y < hallHeight/2; y+=bitSize) {
            for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
            glNormal3f(1, 0, 0);
            glBegin(GL_POLYGON);
            glTexCoord2fv( t0 );
            glVertex3f(x, y, z);
            glTexCoord2fv( t1 );
            glVertex3f(x, y, z+bitSize);
            glTexCoord2fv( t2 );
            glVertex3f(x, y+bitSize, z+bitSize);
            glTexCoord2fv( t3 );
            glVertex3f(x, y+bitSize, z);
            glEnd();
            }
    }

    x = hallWidth/2;
    for (float y = -hallHeight/2; y < hallHeight/2; y+=bitSize) {
            for (float z = -hallDepth/2; z < hallDepth/2; z+=bitSize) {
            glNormal3f(-1, 0, 0);
            glBegin(GL_POLYGON);
            glTexCoord2fv( t0 );
            glVertex3f(x, y, z);
            glTexCoord2fv( t1 );
            glVertex3f(x, y, z+bitSize);
            glTexCoord2fv( t2 );
            glVertex3f(x, y+bitSize, z+bitSize);
            glTexCoord2fv( t3 );
            glVertex3f(x, y+bitSize, z);
            glEnd();
            }
    }
    glDisable(GL_TEXTURE_2D);
}

GLvoid drawScene(GLvoid) {
    
                
    qcylinder = gluNewQuadric(); //Creazione 
    gluQuadricCallback(qcylinder, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
    gluQuadricDrawStyle(qcylinder, GLU_FILL); 
    gluQuadricOrientation(qcylinder, GLU_OUTSIDE); 
    gluQuadricNormals(qcylinder, GLU_SMOOTH); 
    gluQuadricTexture(qcylinder, GL_TRUE);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 80);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        
        gluLookAt(0, -hallHeight/10, -hallDepth/2, lookX, lookY, lookZ, 0.0, 1.0, 0.0);
        glTranslatef(0, 0, translateZ);

        float y = hallHeight/3;
        float x = -hallWidth/2+1;
        GLint lightId = GL_LIGHT0;
        for (float z = -hallDepth/2+10; z <= hallDepth/2-10; z+=(hallDepth-20)/2) {
            lightId++;
            GLfloat position1 [4] = {x, y, z, 1};
            GLfloat diffuse [4] = {1, 0.9, 0.7, 1};
            glLightfv(lightId, GL_POSITION, position1);
            glLightfv(lightId, GL_DIFFUSE, diffuse);
            glLightfv(lightId, GL_SPECULAR, diffuse);
            glLightf(lightId, GL_CONSTANT_ATTENUATION, 1.0);
            glLightf(lightId, GL_LINEAR_ATTENUATION, 0.05);
            glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.01);
        }
        y = hallHeight/3;
        x = hallWidth/2-1;
        for (float z = -hallDepth/2+10; z <= hallDepth/2-10; z+=(hallDepth-20)/2) {
            lightId++;
            GLfloat position1 [4] = {x, y, z, 1};
            GLfloat diffuse [4] = {1, 0.9, 0.7, 1};
            glLightfv(lightId, GL_POSITION, position1);
            glLightfv(lightId, GL_DIFFUSE, diffuse);
            glLightfv(lightId, GL_SPECULAR, diffuse);
            glLightf(lightId, GL_CONSTANT_ATTENUATION, 1.0);
            glLightf(lightId, GL_LINEAR_ATTENUATION, 0.05);
            glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.01);
        }
        buildHall();
        
        buildAppliques();

    glPopMatrix();
    glutSwapBuffers(); 
}


int main(int argc, char** argv) {
     
    GLsizei width=900, height=900;  
    GLdouble aspect;  
    glutInit(&argc, argv);
    imageFloor = read_texture("bluetile2.rgba", &imageWidth, &imageHeight, &components); 
    imageVelvet = read_texture("velvet.rgba", &imageWidth, &imageHeight, &components); 
    imageWalls = read_texture("wallbricks1.rgba", &imageWidth, &imageHeight, &components); 
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motionFunc);
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glEnable(GL_AUTO_NORMAL);
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); 
    aspect = (GLdouble) width / (GLdouble) height;  
    glGenTextures(3, texnames); 
    initTexture( 0, imageFloor, imageWidth, imageHeight );  
    initTexture( 1, imageWalls, imageWidth, imageHeight );  
    initTexture( 2, imageVelvet, imageWidth, imageHeight );  
    glutMainLoop(); //Ciclo principale
}
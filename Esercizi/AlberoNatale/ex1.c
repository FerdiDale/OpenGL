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
float eyeDistance = 6;
float eyeX = 0, eyeY = 0, eyeZ = 6;

GLfloat defaultDiffuse [4] = {0.8, 0.8, 0.8, 1};
GLfloat diffuseGreenMaterial [4] = {0, 0.4, 0, 1};
GLfloat diffuseBrownMaterial [4] = {0.3, 0.1, 0, 1};
GLfloat silverDiffuseMaterial [4] = {0.50754, 0.50754, 0.50754, 1};
GLfloat silverAmbientMaterial [4] = {0.19225, 0.19225, 0.19225, 1};
GLfloat silverSpecularMaterial [4] = {0.508273, 0.508273, 0.508273, 1};
GLfloat defaultSpecularMaterial [4] = {0, 0, 0, 1};
GLfloat defaultAmbientMaterial [4] = {0.2, 0.2, 0.2, 1};
GLfloat ballColorMaterial [4] = {0, 0, 0, 1};
GLfloat whiteColorMaterial [4] = {1, 1, 1, 1};
GLfloat defaultEmissiveMaterial [4] = {0, 0, 0, 1};
GLfloat lightEmissionMaterial [4] = {0, 0, 0, 1};

GLUquadricObj *qcylinder, *qdisk; 

GLfloat ballColorsMatrix [6][8][3];
GLfloat lightsColorsMatrix [3][2][3];

byte lightsEnabled [7] = {1, 1, 1, 1, 1, 1, 1};

GLfloat randomFloat () {
    return (double)rand() / (double)RAND_MAX ;
}

GLvoid initRandomColors() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            ballColorsMatrix[i][j][0] = randomFloat();
            ballColorsMatrix[i][j][1] = randomFloat();
            ballColorsMatrix[i][j][2] = randomFloat();
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            lightsColorsMatrix[i][j][0] = randomFloat()*3/2;
            lightsColorsMatrix[i][j][1] = randomFloat()*3/2;
            lightsColorsMatrix[i][j][2] = randomFloat()*3/2;
            lightsColorsMatrix[i][j][rand()%3] = 0.66;
        }
    }
}

void timeFunc (int value) {
    int baseLightId = GL_LIGHT1;
    int lightChosen = (rand()%6)+1;
    if (lightsEnabled[lightChosen]) {
            glDisable(baseLightId + lightChosen);
            lightsEnabled[lightChosen] = 0;
        }
    else { 
        glEnable(baseLightId + lightChosen);
        lightsEnabled[lightChosen] = 1;
    }
    glutPostRedisplay();
    glutTimerFunc(2500, timeFunc, 0);
}


void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case ' ':
            initRandomColors();
            glutPostRedisplay();
            break;
            
        case 'q':
            if (lightsEnabled[0]) {
                glDisable(GL_LIGHT1);
                lightsEnabled[0] = 0;
            }
            else { 
                glEnable(GL_LIGHT1);
                lightsEnabled[0] = 1;
            }
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
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

GLvoid errorCallback(GLenum errorCode) { 
    const GLubyte *estring;
    estring = gluErrorString(errorCode);
    fprintf (stderr, "Errore QUADRICHE: %s\n", estring);
    exit (0);
}

GLvoid drawTopper() {
    float currX = 0, currY = 3.65, currZ = 0;
    glPushMatrix();
        glTranslatef(currX, currY, currZ);
        glRotatef(-90, 1, 0, 0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silverDiffuseMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silverAmbientMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silverSpecularMaterial);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.4);
    
        gluCylinder(qcylinder, 0.1, 0.1, 0.1, 50, 50);
        gluDisk(qdisk, 0, 0.1, 50, 50);

    glPopMatrix();

    currY+=0.15;
    
    glPushMatrix();
        glTranslatef(currX, currY, currZ);
        glRotatef(-90, 1, 0, 0);
    
        glutSolidTorus(0.09, 0.15, 20, 20);

    glPopMatrix();
    
    glPushMatrix();

        glTranslatef(currX, currY, currZ);
        glRotatef(-90, 1, 0, 0);
    
        gluCylinder(qcylinder, 0.1, 0, 0.6, 50, 50);
        gluDisk(qdisk, 0, 0.1, 50, 50);

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, defaultDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaultSpecularMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, defaultAmbientMaterial);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

    glPopMatrix();

}

GLvoid drawString() {
    float currX, currY, currZ, currRadius, baseAngle, angle;
    float ballRadius = 0.05;
    currY =  -0.75, currRadius = 2.2;
    int counter = 1;
    while (currY <= 3.75) {

        currX = sin(DEG_TO_RAD*angle)*currRadius;
        currZ = cos(DEG_TO_RAD*angle)*currRadius;
        glPushMatrix();
            glTranslatef(currX, currY-ballRadius, currZ);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColorMaterial);

            glutSolidSphere(ballRadius, 20, 20);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
        glPopMatrix();

        currY += 0.05;

        angle+= 5;
        baseAngle+=25;
        currRadius -= 2.2/90.0;

    }
    
}

GLvoid drawBalls() {
    float currX, currY, currZ, currRadius, baseAngle, angle;
    int totRowBalls;
    float ballRadius = 0.2;
    currY =  -0.75, currRadius = 2, baseAngle = 0, totRowBalls = 8;
    for (int nRows = 0; nRows < 6; nRows++) {

        for (int nBalls = 0; nBalls < totRowBalls; nBalls++) {
            ballColorMaterial[0] = ballColorsMatrix[nRows][nBalls][0];
            ballColorMaterial[1] = ballColorsMatrix[nRows][nBalls][1];
            ballColorMaterial[2] = ballColorsMatrix[nRows][nBalls][2];
            angle = baseAngle + 360*nBalls/totRowBalls;
            currX = sin(DEG_TO_RAD*angle)*currRadius;
            currZ = cos(DEG_TO_RAD*angle)*currRadius;
            glPushMatrix();
                glTranslatef(currX, currY-ballRadius, currZ);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ballColorMaterial);

                glutSolidSphere(ballRadius, 20, 20);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
            glPopMatrix();
        }
        
        baseAngle+=25;
        totRowBalls-=1;
        currY += 0.75;
        currRadius -= 0.25;
            

    }
    
}

GLvoid drawLeaves() {
    glPushMatrix();
        glTranslatef(0, 2.25, 0);
        glRotatef(-90, 1, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseGreenMaterial);

        gluCylinder(qcylinder, 1, 0, 1.5, 50, 50);
        
        glRotatef(180, 1, 0, 0);

        gluDisk(qdisk, 0, 1, 50, 50);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 0.75, 0);
        glRotatef(-90, 1, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseGreenMaterial);
        
        gluCylinder(qcylinder, 1.5, 0.6, 1.5, 50, 50);
        
        glRotatef(180, 1, 0, 0);

        gluDisk(qdisk, 0, 1.5, 50, 50);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, -0.75, 0);
        glRotatef(-90, 1, 0, 0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseGreenMaterial);

        gluCylinder(qcylinder, 2, 1.1, 1.5, 50, 50);
        
        glRotatef(180, 1, 0, 0);

        gluDisk(qdisk, 0, 2, 50, 50);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
    glPopMatrix();
}

GLvoid drawLog() {
        glPushMatrix();
            glTranslatef(0, -2.25, 0);
            glRotatef(-90, 1, 0, 0);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseBrownMaterial);

            gluCylinder(qcylinder, 0.75, 0.75, 1.5, 15, 50);
        
            glRotatef(180, 1, 0, 0);

            gluDisk(qdisk, 0, 0.75, 50, 50);

            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, defaultDiffuse);
        glPopMatrix();
}

GLvoid drawLights() {

    float currX, currY, currZ, currRadius, baseAngle, angle;
    int totRowLights;
    currY =  0.25, currRadius = 1.4, baseAngle = 0, totRowLights = 2;
    int baseLightId = GL_LIGHT1;
    int currLight = 0;
    GLfloat positionLight [4] = {0, 0, 0, 1};
    GLfloat diffuseLight [3] = {0, 0, 0};
    GLfloat specularLight [3] = {0, 0, 0};

    for (int nRows = 0; nRows < 3; nRows++) {

        for (int nLights = 0; nLights < totRowLights; nLights++) {
            currLight++;
            lightEmissionMaterial[0] = lightsColorsMatrix[nRows][nLights][0];
            lightEmissionMaterial[1] = lightsColorsMatrix[nRows][nLights][1];
            lightEmissionMaterial[2] = lightsColorsMatrix[nRows][nLights][2];

            if (lightsEnabled[currLight] == 0) {
                lightEmissionMaterial[0]/=10;
                lightEmissionMaterial[1]/=10;
                lightEmissionMaterial[2]/=10;
            }

            angle = baseAngle + 360*nLights/totRowLights;
            currX = sin(DEG_TO_RAD*angle)*currRadius;
            currZ = cos(DEG_TO_RAD*angle)*currRadius;
            glPushMatrix();

                positionLight[0] = currX;
                positionLight[1] = currY;
                positionLight[2] = currZ;
                glLightfv(baseLightId + currLight, GL_POSITION, positionLight);
                glLightfv(baseLightId + currLight, GL_DIFFUSE, lightEmissionMaterial);

                glTranslatef(currX, currY, currZ);
                glRotatef(angle, 0, 1, 0);
                glRotatef(-25, 1, 0, 0);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lightEmissionMaterial);
                glutSolidCone(0.05, 0.1, 10, 10);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, defaultEmissiveMaterial);
                
            glPopMatrix();
        }
        
        baseAngle+=45;
        currY += 1.5;
        currRadius -= 0.5;
        currRadius -= nRows * 0.1;
            
    }

}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0.0, 1.0, 0.0);

        GLfloat position1 [4] = {1, 5, 1, 1};
        GLfloat diffuse1 [3] = {0.4, 0.4, 0.4};
        GLfloat specular1 [3] = {0.6, 0.6, 0.6};
        GLfloat ambient1 [3] = {0.2, 0.2, 0.2};
        glLightfv(GL_LIGHT1, GL_POSITION, position1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
        
        qcylinder = gluNewQuadric(); //Creazione 
        gluQuadricCallback(qcylinder, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
        gluQuadricDrawStyle(qcylinder, GLU_FILL); 
        gluQuadricOrientation(qcylinder, GLU_OUTSIDE); 
        gluQuadricNormals(qcylinder, GLU_SMOOTH); 

        qdisk = gluNewQuadric(); //Creazione 
        gluQuadricCallback(qdisk, GLU_ERROR, (GLvoid (*))errorCallback); //Gestione errori 
        gluQuadricDrawStyle(qdisk, GLU_FILL); 
        gluQuadricOrientation(qdisk, GLU_OUTSIDE); 
        gluQuadricNormals(qdisk, GLU_SMOOTH); 

        drawLights();
        drawLeaves();
        drawLog();
        drawBalls();
        // drawString();
        drawTopper();

    glPopMatrix();
    glFlush();
}


int main(int argc, char** argv) {
    initRandomColors();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motionFunc);
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    glEnable(GL_LIGHT7);

    glutTimerFunc(10, timeFunc, 0);
    glutMainLoop(); //Ciclo principale
}
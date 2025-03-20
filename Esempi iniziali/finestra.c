#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glut.h> //Inclusione libreria GLU

void init() { }
void redraw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glBegin( GL_POINTS );
    glVertex2f( 0.0, 0.0 );
    glEnd();
    glFlush();
}
void main( int argc, char** argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_RGB );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize ( 1000, 1000 );
    glutCreateWindow ( argv[0] );
    glutDisplayFunc( redraw );
    glutMainLoop ();
}
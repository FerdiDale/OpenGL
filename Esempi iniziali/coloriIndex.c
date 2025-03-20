#include <GL/gl.h>
#include <GL/glut.h>
void redraw( void )
{
    glutSetColor( 0, 0.0, 0.3, 0.0 );
    glutSetColor( 1, 1.0, 0.0, 1.0 );
    glPointSize( 3.2 );
    glClearIndex( 0 );
    glClear( GL_COLOR_BUFFER_BIT );
    glBegin( GL_POINTS );
    glIndexi( 1 );
    glVertex2f( 0.0, 0.0 );
    glEnd();
    glFlush();
}
void main( int argc, char** argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_INDEX );
    glutInitWindowPosition( 300, 100 );
    glutInitWindowSize ( 150, 150 );
    glutCreateWindow ( argv[0] );
    glutDisplayFunc( redraw );
    glutMainLoop ();
}
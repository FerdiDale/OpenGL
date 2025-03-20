#include <GL/gl.h>
#include <GL/glut.h>

void checkError (char *label)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        printf("%s: %s\n", label, gluErrorString(error));
    }
}
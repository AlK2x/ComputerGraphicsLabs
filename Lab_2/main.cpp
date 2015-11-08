#include "gameapplication.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

int main(int argc, char *argv[])
{
    GameApplication a(argc, argv);
    return a.enterGameLoop();
}

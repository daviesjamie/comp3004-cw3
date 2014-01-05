#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Camera.hpp>
#include <Model.hpp>

bool running = true;

static void keyHandler( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( action == GLFW_PRESS )
    {
        switch( key )
        {
            // Quit
            case GLFW_KEY_ESCAPE:
            case GLFW_KEY_Q:
                running = false;
                break;

            // Screenshot location
            case GLFW_KEY_P:
                break;

            // Start Tour
            case GLFW_KEY_T:
                break;

            // End Tour
            case GLFW_KEY_E:
                break;

            // Turn camera left
            case GLFW_KEY_LEFT:
                break;

            // Turn camera right
            case GLFW_KEY_RIGHT:
                break;

            // Raise camera
            case GLFW_KEY_PAGE_UP:
                break;

            // Lower camera
            case GLFW_KEY_PAGE_DOWN:
                break;

            // Speed up camera
            case GLFW_KEY_UP:
                break;

            // Slow down camera
            case GLFW_KEY_DOWN:
                break;

            // Stop camera
            case GLFW_KEY_SPACE:
                break;

            // Display help screen
            case GLFW_KEY_H:
            case GLFW_KEY_SLASH:
                break;
        }
    }
}

static void resizeHandler( GLFWwindow* window, int width, int height )
{
    screen_width = width;
    screen_height = height;
    glViewport( 0, 0, width, height );
}

bool init()
{

}

bool load_models()
{

}

void cleanup()
{

}

int main( int argc, char* argv[] )
{
    init();

    while( running )
    {

    }

    cleanup();
}

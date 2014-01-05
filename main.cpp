#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Camera.hpp"
#include "Model.hpp"
#include "shader.hpp"

bool running = true;
int screen_width = 640;
int screen_height = 480;

GLFWwindow* window;
GLuint shaderProgram;

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
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to start GLFW\n" );
        return false;
    }

    // Create a window and OpenGL context
    window = glfwCreateWindow( screen_width, screen_height, "COMP3004 CW 3 -- Jamie Davies (jagd1g11)", NULL, NULL );
    if( !window )
    {
        fprintf( stderr, "Failed to create a window\n" );
        glfwTerminate();
        return false;
    }

    // Make that context the current one
    glfwMakeContextCurrent( window );

    // Initialise GLEW
    glewExperimental = GL_TRUE;
    int err = glewInit();
    if( err != GLEW_OK )
    {
        fprintf( stderr, "Failed to start GLEW\n" );
        glfwDestroyWindow( window );
        glfwTerminate();
        return false;
    }

    // Set key/resize callback functions
    glfwSetKeyCallback( window, keyHandler() );
    glfwSetWindowSizeCallback( window, resizeHandler() );

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
}

void load_shaders()
{
    // Load the shaders
    GLuint vertexShader = create_shader( "vertex.glsl", GL_VERTEX_SHADER );
    GLuint fragmentShader = create_shader( "fragment.glsl", GL_FRAGMENT_SHADER );

    // Create the shader program
    std::vector<GLint> shaders;
    shaders.push_back( vertexShader );
    shaders.push_back( fragmentShader );
    shaderProgram = link_shaders( shaders );
}

bool load_models()
{

}

void cleanup()
{

}

int main( int argc, char* argv[] )
{
    if( !init() ) exit( EXIT_FAILURE );

    load_shaders();


    while( running )
    {

    }

    cleanup();
}

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "shader.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool running = true;

static void keyHandler( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( action == GLFW_PRESS )
    {
        switch( key )
        {
            case GLFW_KEY_Q:
            case GLFW_KEY_ESCAPE:
                running = false;
                break;
        }
    }
}

GLint linkShaders( const std::vector<GLint> &shaders )
{
    GLuint program = glCreateProgram();
    for( GLuint i = 0; i < shaders.size(); i++ )
        glAttachShader( program, shaders[ i ] );

    glLinkProgram( program );

    return program;
}

int main( int argc, char* argv[] )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to start GLFW\n" );
        exit( EXIT_FAILURE );
    }

    // Create a window and OpenGL context
    GLFWwindow* window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "COMP3004 CW 3 -- Jamie Davies (jagd1g11)", NULL, NULL );
    if( !window )
    {
        fprintf( stderr, "Failed to create a window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
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
        exit( EXIT_FAILURE );
    }

    // Set key callback function
    glfwSetKeyCallback( window, keyHandler );

    // Load the shaders
    GLuint vertex_shader = createShader( "vertex.glsl", GL_VERTEX_SHADER );
    GLuint fragment_shader = createShader( "fragment.glsl", GL_FRAGMENT_SHADER );

    // Create the shader program
    std::vector<GLint> shaders;
    shaders.push_back( vertex_shader );
    shaders.push_back( fragment_shader );
    GLuint shader_program = linkShaders( shaders );

    glEnable( GL_DEPTH_TEST );

    while( running )
    {
        glClearColor( 1.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glfwSwapBuffers( window );
        glfwPollEvents();

        // Exit on window close
        if( glfwWindowShouldClose( window ) )
            running = false;
    }

    // Clean up
    glfwDestroyWindow( window );
    glfwTerminate();
    return 0;
}

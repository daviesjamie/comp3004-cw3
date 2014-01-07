#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Model.hpp"
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

    // Load models
    Model clanger( "models/clanger.obj" );
    clanger.load();

    // Set up uniform variables for GLSL
    glUseProgram( shader_program );

    GLuint mvp_id = glGetUniformLocation( shader_program, "mvp" );
    GLuint enable_shading_id = glGetUniformLocation( shader_program, "enable_shading" );

    float ambient_intensity = 0.2f;
    GLuint ambient_intensity_id = glGetUniformLocation( shader_program, "ambient_intensity" );
    glUniform1f( ambient_intensity_id, ambient_intensity );

    glm::vec3 light_direction = glm::vec3( 0.0f, 0.0f, 10.0f );
    GLuint light_direction_id = glGetUniformLocation( shader_program, "light_direction" );
    glUniform3fv( light_direction_id, 1, &light_direction[ 0 ] );

    glm::vec3 light_color = glm::vec3( 0.5f, 0.5f, 0.5f );
    GLuint light_color_id = glGetUniformLocation( shader_program, "light_color" );
    glUniform3fv( light_color_id, 1, &light_color[ 0 ] );

    glm::vec3 object_color = glm::vec3( 1.0f, 0.9f, 0.9f );
    GLuint object_color_id = glGetUniformLocation( shader_program, "object_color" );
    glUniform3fv( object_color_id, 1, &object_color[ 0 ] );

    // Set up matrices
    glm::mat4 projection = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );
    glm::mat4 view = glm::lookAt( glm::vec3( 10.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
    glm::mat4 mvp;

    glEnable( GL_DEPTH_TEST );

    while( running )
    {
        glClearColor( 1.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Enable lighting
        glUniform1i( enable_shading_id, GL_TRUE );

        // Send mvp matrix to GLSL
        mvp = projection * view * clanger.getModel();
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );

        // Render clanger
        clanger.render();

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

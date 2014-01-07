#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <vector>

#include "Camera.hpp"
#include "Model.hpp"
#include "shader.hpp"

int screen_width = 800;
int screen_height = 600;

bool running = true;

Camera camera = Camera();

const char* HELP_TEXT =
"COMP3004 Coursework 3, by Jamie Davies (jagd1g11)\n\n"
"|-----------|---------------------------------------------------|\n"
"| Key       | Action                                            |\n"
"|-----------|---------------------------------------------------|\n"
"| Q, ESC    | Quit the program                                  |\n"
"| P         | Move camera to location screenshot was taken from |\n"
"| T         | Start the tour                                    |\n"
"| E         | End the tour                                      |\n"
"| LEFT      | Turn camera left                                  |\n"
"| RIGHT     | Turn camera right                                 |\n"
"| W         | Tilt camera up                                    |\n"
"| S         | Tilt camera down                                  |\n"
"| PAGE UP   | Raise camera                                      |\n"
"| PAGE DOWN | Lower camera                                      |\n"
"| UP        | Speed up camera                                   |\n"
"| DOWN      | Slow down camera                                  |\n"
"| SPACE     | Stop camera                                       |\n"
"| BACKSPACE | Reset camera position                             |\n"
"| .         | Print camera position to console                  |\n"
"| H, ?      | Print this help message                           |\n"
"|-----------|---------------------------------------------------|\n";

const glm::vec3 SCREENSHOT_POSITION = glm::vec3( 4.246779, 3.069176, 9.035881 );
const glm::vec3 SCREENSHOT_DIRECTION = glm::vec3( -4.021917, -0.841034, -9.171530 );

static void keyHandler( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( action == GLFW_PRESS )
    {
        switch( key )
        {
            // Quit
            case GLFW_KEY_Q:
            case GLFW_KEY_ESCAPE:
                running = false;
                break;

            // Screenshot location
            case GLFW_KEY_P:
                camera.setPosition( SCREENSHOT_POSITION );
                camera.setDirection( SCREENSHOT_DIRECTION );
                break;

            // Start tour
            case GLFW_KEY_T:
                if( !camera.isTouring() )
                    camera.startTour();
                break;

            // End tour
            case GLFW_KEY_E:
                if( camera.isTouring() )
                    camera.endTour();
                break;

            // Turn camera left
            case GLFW_KEY_LEFT:
                if( !camera.isTouring() )
                    camera.yaw( 2 );
                break;

            // Turn camera right
            case GLFW_KEY_RIGHT:
                if( !camera.isTouring() )
                    camera.yaw( -2 );
                break;

            // Tilt camera up
            case GLFW_KEY_W:
                if( !camera.isTouring() )
                    camera.pitch( 2 );
                break;

            // Tilt camera down
            case GLFW_KEY_S:
                if( !camera.isTouring() )
                    camera.pitch( -2 );
                break;

            // Raise camera
            case GLFW_KEY_PAGE_UP:
                if( !camera.isTouring() )
                    camera.adjustElevation( 0.5 );
                break;

            // Lower camera
            case GLFW_KEY_PAGE_DOWN:
                if( !camera.isTouring() )
                    camera.adjustElevation( -0.5 );
                break;

            // Speed up camera
            case GLFW_KEY_UP:
                if( !camera.isTouring() )
                    camera.adjustSpeed( 0.01 );
                break;

            // Slow down camera
            case GLFW_KEY_DOWN:
                if( !camera.isTouring() )
                    camera.adjustSpeed( -0.01 );
                break;

            // Stop camera
            case GLFW_KEY_SPACE:
                if( !camera.isTouring() )
                    camera.stop();
                break;

            // Reset camera
            case GLFW_KEY_BACKSPACE:
                if( !camera.isTouring() )
                    camera.reset();
                break;

            // Log camera position to console
            case GLFW_KEY_PERIOD:
                camera.status();
                break;

            // Display help on console
            case GLFW_KEY_H:
            case GLFW_KEY_SLASH:
                std::cout << HELP_TEXT << std::endl;
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
    fprintf( stdout, "Initialising GLFW...\n" );
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to start GLFW\n" );
        exit( EXIT_FAILURE );
    }

    // Create a window and OpenGL context
    GLFWwindow* window = glfwCreateWindow( screen_width, screen_height, "COMP3004 CW 3 -- Jamie Davies (jagd1g11)", NULL, NULL );
    if( !window )
    {
        fprintf( stderr, "Failed to create a window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Make that context the current one
    glfwMakeContextCurrent( window );

    // Initialise GLEW
    fprintf( stdout, "Initialising GLEW...\n" );
    glewExperimental = GL_TRUE;
    int err = glewInit();
    if( err != GLEW_OK )
    {
        fprintf( stderr, "Failed to start GLEW\n" );
        glfwDestroyWindow( window );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Set key/resize callback functions
    glfwSetKeyCallback( window, keyHandler );
    glfwSetWindowSizeCallback( window, resizeHandler );

    // Load the shaders
    GLuint vertex_shader = createShader( "vertex.glsl", GL_VERTEX_SHADER );
    GLuint fragment_shader = createShader( "fragment.glsl", GL_FRAGMENT_SHADER );

    // Create the shader program
    std::vector<GLint> shaders;
    shaders.push_back( vertex_shader );
    shaders.push_back( fragment_shader );
    GLuint shader_program = linkShaders( shaders );

    // Load models
    Model terrain( "models/terrain2.obj" );
    terrain.load();
    terrain.scale( glm::vec3( 100.0f, 100.0f, 100.0f ) );

    Model clanger1( "models/clanger.obj" );
    clanger1.load();

    Model clanger2 = clanger1;
    clanger2.translate( glm::vec3( -3.0f, 0.0f, 0.0f ) );

    Model clanger3 = clanger1;
    clanger3.translate( glm::vec3( 3.0f, 0.0f, 0.0f ) );

    Model clanger4 = clanger1;
    clanger4.translate( glm::vec3( -33.1f, -5.0f, 37.6f ) );

    Model asteroid( "models/asteroid.obj" );
    asteroid.load();
    asteroid.translate( glm::vec3( 20.0f, 5.0f, 0.0f ) );

    Model hole1( "models/hole.obj" );
    hole1.load();
    hole1.scale( glm::vec3( 1.5f, 1.5f, 1.5f ) );

    Model hole2 = hole1;
    hole2.translate( glm::vec3( -3.0f, -0.5f, 6.0f ) );

    Model hole3 = hole1;
    hole3.translate( glm::vec3( -22.0f, -0.5f, 25.0f ) );

    hole1.translate( glm::vec3( 0.0f, -0.3f, 0.0f ) );

    Model lid1( "models/dustbinlid.obj" );
    lid1.load();

    Model lid2 = lid1;
    lid2.translate( glm::vec3( -4.5f, 0.3f, 9.0f ) );

    Model lid3 = lid1;
    lid3.translate( glm::vec3( -15.0f, 0.0f, 19.0f ) );

    Model lid4 = lid1;
    lid4.translate( glm::vec3( -27.0f, -0.6f, 12.0f ) );

    Model lid5 = lid1;
    lid5.translate( glm::vec3( -15.0f, -0.3f, -30.0f ) );

    lid1.translate( glm::vec3( -1.0f, -0.5f, -3.5f ) );

    // Set up uniform variables for GLSL
    glUseProgram( shader_program );

    GLuint mvp_id = glGetUniformLocation( shader_program, "mvp" );
    GLuint enable_shading_id = glGetUniformLocation( shader_program, "enable_shading" );

    float ambient_intensity = 0.2f;
    GLuint ambient_intensity_id = glGetUniformLocation( shader_program, "ambient_intensity" );
    glUniform1f( ambient_intensity_id, ambient_intensity );

    glm::vec3 light_direction = glm::vec3( -10.0f, -10.0f, 10.0f );
    GLuint light_direction_id = glGetUniformLocation( shader_program, "light_direction" );
    glUniform3fv( light_direction_id, 1, &light_direction[ 0 ] );

    glm::vec3 light_color;
    GLuint light_color_id = glGetUniformLocation( shader_program, "light_color" );
    light_color = glm::vec3( 0.5f, 0.5f, 0.5f );
    glUniform3fv( light_color_id, 1, &light_color[ 0 ] );

    glm::vec3 object_color;
    GLuint object_color_id = glGetUniformLocation( shader_program, "object_color" );

    glEnable( GL_DEPTH_TEST );

    // Loop variables
    float currentTime = 0;
    float lastTime = 0;
    float timeDiff = 0;

    float clanger_position = -5.0f;
    bool clanger_going_up = true;

    while( running )
    {
        // Calculate time difference between this frame and the last
        currentTime = glfwGetTime();
        timeDiff = currentTime - lastTime;
        lastTime = currentTime;

        ///////////////////////////////////////////////////////////////////////
        // EVENTS

        glfwPollEvents();

        // Exit on window close
        if( glfwWindowShouldClose( window ) )
            running = false;

        ///////////////////////////////////////////////////////////////////////
        // LOGIC

        camera.move();
        camera.animateTour( timeDiff );

        asteroid.translate( glm::vec3( -20.0f, -5.0f, 0.0f ) );
        asteroid.rotate( -timeDiff * 20, glm::vec3( 0.2f, 1.0f, 0.0f ) );
        asteroid.translate( glm::vec3( 20.0f, 5.0f, 0.0f ) );

        if( clanger_going_up )
        {
            clanger_position += timeDiff * 2;
            clanger4.translate( glm::vec3( 0.0f, timeDiff * 2, 0.0f ) );

            if( clanger_position >= 0.5f )
            {
                clanger_going_up = false;
                clanger_position = 0.5f;
            }
        }
        else
        {
            clanger_position -= timeDiff * 2;
            clanger4.translate( glm::vec3( 0.0f, -timeDiff * 2, 0.0f ) );

            if( clanger_position <= -5.0f )
            {
                clanger_going_up = true;
                clanger_position = -5.0f;
            }
        }

        ///////////////////////////////////////////////////////////////////////
        // RENDERING

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Enable lighting
        glUniform1i( enable_shading_id, GL_TRUE );

        // Terrain
        object_color = glm::vec3( 0.8f, 0.8f, 0.9f );
        glUniform3fv( object_color_id, 1, &object_color[ 0 ] );
        glm::mat4 mvp = camera.getMVP( terrain.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        terrain.render();

        // Clanger 1
        object_color = glm::vec3( 1.0f, 0.6f, 0.6f );
        glUniform3fv( object_color_id, 1, &object_color[ 0 ] );
        mvp = camera.getMVP( clanger1.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        clanger1.render();

        // Clanger 2
        mvp = camera.getMVP( clanger2.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        clanger2.render();

        // Clanger 3
        mvp = camera.getMVP( clanger3.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        clanger3.render();

        // Clanger 4
        mvp = camera.getMVP( clanger4.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        clanger4.render();

        // Asteroid
        object_color = glm::vec3( 0.9f, 0.85f, 0.8f );
        glUniform3fv( object_color_id, 1, &object_color[ 0 ] );
        mvp = camera.getMVP( asteroid.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        asteroid.render();

        // Hole 1
        object_color = glm::vec3( 0.6f, 0.6f, 0.6f );
        glUniform3fv( object_color_id, 1, &object_color[ 0 ] );
        mvp = camera.getMVP( hole1.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        hole1.render();

        // Hole 2
        mvp = camera.getMVP( hole2.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        hole2.render();

        // Hole 3
        mvp = camera.getMVP( hole3.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        hole3.render();

        // Lid 1
        mvp = camera.getMVP( lid1.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        lid1.render();

        // Lid 2
        mvp = camera.getMVP( lid2.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        lid2.render();

        // Lid 3
        mvp = camera.getMVP( lid3.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        lid3.render();

        // Lid 4
        mvp = camera.getMVP( lid4.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        lid4.render();

        // Lid 5
        mvp = camera.getMVP( lid5.getModel() );
        glUniformMatrix4fv( mvp_id, 1, GL_FALSE, &mvp[ 0 ][ 0 ] );
        lid5.render();

        glfwSwapBuffers( window );
    }

    // Clean up
    glfwDestroyWindow( window );
    glfwTerminate();
    return 0;
}

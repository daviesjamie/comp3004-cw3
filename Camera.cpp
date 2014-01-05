#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera()
{
    position = glm::vec3( 0.0f, 0.0f, 0.0f );
    direction = glm::vec3( 1.0f, 0.0f, 0.0f );
    speed = 0.0f;

    // perspective( field of view, aspect ratio, near clip, far clip )
    projection = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );

    // lookAt( camera position, target position, up direction )
    view = glm::lookAt( position, position + direction, UP_DIR );
}

void Camera::adjust_elevation( float amount )
{
    position = glm::vec3( position.x, position.y + amount, position.z );
    view = glm::lookAt( position, position + direction, UP_DIR );
}

void Camera::adjust_speed( float amount )
{
    speed += amount;
    if( speed < 0.0f )
        speed = 0.0f;
}

void Camera::move()
{
    if( speed > 0.0f )
    {
        position = position + glm::vec3( direction.x * speed, direction.y * speed, direction.z * speed );
        view = glm::lookAt( position, position + direction, UP_DIR );
    }
}

void Camera::stop()
{
    speed = 0.0f;
}

void Camera::turn( float angle )
{
    direction = glm::rotateY( direction, angle );
    view = glm::lookAt( position, position + direction, UP_DIR );
}

glm::vec3 Camera::get_position()
{
    return position;
}

void Camera::set_position( glm::vec3 pos )
{
    position = pos;
}

glm::vec3 Camera::get_direction()
{
    return direction;
}

void Camera::set_direction( glm::vec3 dir )
{
    direction = dir;
}

glm::mat4 Camera::get_mvp( glm::mat4 model )
{
    return projection * view * model;
}

void Camera::status()
{
    fprintf( stdout, "Position: ( %f, %f, %f )\n", position.x, position.y, position.z );
    fprintf( stdout, "Looking at: ( %f, %f, %f )\n", direction.x, direction.y, direction.z );
}

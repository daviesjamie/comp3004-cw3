#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Camera.hpp"

Camera::Camera()
{
    reset();


}

void Camera::adjustElevation( float amount )
{
    if( position.y + amount >= 0.5 )
    {
        position = glm::vec3( position.x, position.y + amount, position.z );
        view = glm::lookAt( position, position + direction, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    }
    else
    {
        position = glm::vec3( position.x, 0.5, position.z );
        view = glm::lookAt( position, position + direction, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    }
}

void Camera::adjustSpeed( float amount )
{
    speed += amount;
    //if( speed < 0.0f )
    //   speed = 0.0f;
}

void Camera::move()
{
    //if( speed > 0.0f )
    //{
        position = position + glm::vec3( direction.x * speed, direction.y * speed, direction.z * speed );
        view = glm::lookAt( position, position + direction, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    //}
}

void Camera::stop()
{
    speed = 0.0f;
}

void Camera::pitch( float angle )
{
    direction = glm::rotateX( direction, angle );
    view = glm::lookAt( position, position + direction, glm::vec3( 0.0f, 1.0f, 0.0f ) );
}

void Camera::yaw( float angle )
{
    direction = glm::rotateY( direction, angle );
    view = glm::lookAt( position, position + direction, glm::vec3( 0.0f, 1.0f, 0.0f ) );
}

glm::vec3 Camera::getPosition()
{
    return position;
}

void Camera::setPosition( glm::vec3 pos )
{
    position = pos;
}

glm::vec3 Camera::getDirection()
{
    return direction;
}

void Camera::setDirection( glm::vec3 dir )
{
    direction = dir;
}

glm::mat4 Camera::getMVP( glm::mat4 model )
{
    return projection * view * model;
}

void Camera::status()
{
    fprintf( stdout, "Position: ( %f, %f, %f )\n", position.x, position.y, position.z );
    fprintf( stdout, "Looking at: ( %f, %f, %f )\n", direction.x, direction.y, direction.z );
}

void Camera::reset()
{
    position = glm::vec3( 0.0f, 2.0f, 10.0f );
    direction = glm::vec3( 0.0f, 1.0f, -10.0f );
    speed = 0.0f;

    // perspective( field of view, aspect ratio, near clip, far clip )
    projection = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 500.0f );

    // lookAt( camera position, target position, up direction )
    view = glm::lookAt( position, position + direction, glm::vec3( 0.0f, 1.0f, 0.0f ) );
}

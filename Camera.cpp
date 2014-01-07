#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

#include "Camera.hpp"

Camera::Camera()
{
    reset();

    touring = false;
    tour_speed = 10.0f;

    tour_positions.push_back( glm::vec3( -35.948860, 1.680134, 48.638687 ) );
    tour_positions.push_back( glm::vec3( -45.744678, 1.850140, 18.489935 ) );
    tour_positions.push_back( glm::vec3( -31.784830, 1.320140, -17.002737 ) );
    tour_positions.push_back( glm::vec3( 11.015842, 3.190163, -17.267237 ) );
    tour_positions.push_back( glm::vec3( 14.440728, 2.850228, 18.811127 ) );
    tour_positions.push_back( glm::vec3( -8.720228, 3.320233, 15.417183 ) );
    tour_positions.push_back( glm::vec3( -9.623946, 1.860252, 1.451834 ) );
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

void Camera::animateTour( float time_diff )
{
    if( touring ) {
        if( current_frame + 1 < tour_positions.size() )
        {
            glm::vec3 cur = position;
            glm::vec3 next = tour_positions[ current_frame + 1];
            glm::vec3 vdiff = next - cur;
            float total_dist = glm::sqrt( vdiff[ 0 ] * vdiff[ 0 ] + vdiff[ 1 ] * vdiff[ 1 ] + vdiff[ 2 ] * vdiff[ 2 ] );
            float dist_travelled = tour_speed * time_diff;

            if( dist_travelled > total_dist )
            {
                position = tour_positions[ current_frame + 1 ];
                current_frame++;
            }
            else
            {
                vdiff = ( vdiff / total_dist ) * dist_travelled;
                position = position + vdiff;
            }

            view = glm::lookAt( position, glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
        }
        else
        {
            endTour();
        }
    }
}

void Camera::startTour()
{
    touring = true;
    current_frame = 0;
    position = tour_positions[ 0 ];
    view = glm::lookAt( position, glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
}

void Camera::endTour()
{
    touring = false;
    reset();
}

bool Camera::isTouring()
{
    return touring;
}

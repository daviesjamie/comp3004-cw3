#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <glm/glm.hpp>

class Camera
{
    private:
        glm::vec3 position;
        glm::vec3 direction;
        float speed;

        glm::mat4 projection;
        glm::mat4 view;

    public:
        Camera();

        void adjustElevation( float amount );
        void adjustSpeed( float amount );
        void stop();
        void turn( float angle );

        glm::vec3 getPosition();
        void setPosition( glm::vec3 position );

        glm::vec3 getDirection();
        void setDirection( glm::vec3 direction );

        glm::mat4 getMVP( glm::mat4 model );
};

#endif // CAMERA_HPP_INCLUDED

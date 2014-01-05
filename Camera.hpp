#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <glm/glm.hpp>

const glm::vec3 UP_DIR = glm::vec3( 0, 1, 0 );

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

        void adjust_elevation( float amount );
        void adjust_speed( float amount );
        void stop();
        void turn( float angle );

        glm::vec3 get_position();
        void set_position( glm::vec3 pos );

        glm::vec3 get_direction();
        void set_direction( glm::vec3 dir );

        glm::mat4 get_mvp( glm::mat4 model );
};

#endif // CAMERA_HPP_INCLUDED

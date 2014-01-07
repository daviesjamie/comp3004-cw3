#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <glm/glm.hpp>
#include <vector>

class Camera
{
    private:
        glm::vec3 position;
        glm::vec3 direction;
        float speed;

        glm::mat4 projection;
        glm::mat4 view;

        bool touring;
        int current_frame;
        float tour_speed;

        std::vector<glm::vec3> tour_positions;

    public:
        Camera();

        void adjustElevation( float amount );

        void adjustSpeed( float amount );
        void move();
        void stop();

        void pitch( float angle );
        void yaw( float angle );

        glm::vec3 getPosition();
        void setPosition( glm::vec3 pos );

        glm::vec3 getDirection();
        void setDirection( glm::vec3 dir );

        glm::mat4 getMVP( glm::mat4 model );

        void status();

        void reset();

        void tour();
        bool isTouring();
        void startTour();
        void animateTour( float time_diff );
        void endTour();
};

#endif // CAMERA_HPP_INCLUDED

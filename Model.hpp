#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;

class Model
{
    private:
        GLuint vao[ 1 ];
        GLuint vbo[ 2 ];
        string model_path;

        vector<glm::vec3> vertices;
        vector<glm::vec3> normals;

        glm::mat4 model;

    public:
        Model( string file );

        void load();

        void rotate( float amount, glm::vec3 axes );
        void scale( glm::vec3 amounts );
        void translate( glm::vec3 amounts );

        void render();

        glm::mat4 getModel();
};

#endif // MODEL_HPP_INCLUDED

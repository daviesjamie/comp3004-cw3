#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include <string>
#include <vector>

using namespace std;

class Model
{
    private:
        GLuint vao[ 1 ];
        GLuint vbo[ 3 ];
        GLuint textureID[ 1 ];
        string modelPath;

        vector<glm::vec3> vertices;
        vector<glm::vec3> normals;
        vector<glm::vec3> uvs;

        glm::mat4 model;

    public:
        Model( string file );

        void load();
        GLuint load_texture( string texture );

        void rotate( float amount, glm::vec3 axes );
        void translate( glm::vec3 amounts );
        void scale( glm::vec3 amounts );

        void render();

        glm::mat4 get_model();
};

#endif // MODEL_HPP_INCLUDED

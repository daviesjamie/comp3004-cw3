#ifndef OBJLOADER_HPP_INCLUDED
#define OBJLOADER_HPP_INCLUDED

#include <glm/glm.hpp>
#include <vector>

using namespace std;

bool loadObj( string path, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals );

#endif // OBJLOADER_HPP_INCLUDED

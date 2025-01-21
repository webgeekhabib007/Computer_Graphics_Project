#ifndef sphere_h
#define sphere_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

class Sphere {
public:
    // Material properties
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // Texture property
    unsigned int textureMap;

    // Common property
    float shininess;

    // Constructors
    Sphere() {
        setUpSphereVertexDataAndConfigureVertexAttribute();
    }

    Sphere(glm::vec3 amb = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 diff = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f),
        float shiny = 32.0f) {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpSphereVertexDataAndConfigureVertexAttribute();
    }

    Sphere(unsigned int tMap, glm::vec3 amb = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 diff = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f),
        float shiny = 32.0f) {
        this->textureMap = tMap;
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpSphereVertexDataAndConfigureVertexAttribute();
    }

    // Destructor
    ~Sphere() {
        glDeleteVertexArrays(1, &sphereVAO);
        glDeleteBuffers(1, &sphereVBO);
        glDeleteBuffers(1, &sphereEBO);
    }

    void draw(Shader& shader, glm::mat4 model = glm::mat4(1.0f)) {
        shader.use();

        shader.setInt("texUnit", 0);
        shader.setVec3("material.ambient", this->ambient);
        shader.setVec3("material.diffuse", this->diffuse);
        shader.setVec3("material.specular", this->specular);
        shader.setFloat("material.shininess", this->shininess);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->textureMap);

        shader.setMat4("model", model);

        glBindVertexArray(sphereVAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sphereIndices.size()), GL_UNSIGNED_INT, 0);
    }

private:
    unsigned int sphereVAO;
    unsigned int sphereVBO;
    unsigned int sphereEBO;

    vector<float> sphereVertices;
    vector<unsigned int> sphereIndices;

    void setUpSphereVertexDataAndConfigureVertexAttribute() {
        const unsigned int latitudeCount = 40;
        const unsigned int longitudeCount = 40;
        const float radius = 0.5f;

        // Generate vertices
        for (unsigned int lat = 0; lat <= latitudeCount; ++lat) {
            float theta = lat * glm::pi<float>() / latitudeCount;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (unsigned int lon = 0; lon <= longitudeCount; ++lon) {
                float phi = lon * 2.0f * glm::pi<float>() / longitudeCount;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                float x = cosPhi * sinTheta;
                float y = cosTheta;
                float z = sinPhi * sinTheta;
                float u = static_cast<float>(lon) / longitudeCount;
                float v = static_cast<float>(lat) / latitudeCount;

                // Positions, normals, texture coords
                sphereVertices.push_back(radius * x);
                sphereVertices.push_back(radius * y);
                sphereVertices.push_back(radius * z);
                sphereVertices.push_back(x);
                sphereVertices.push_back(y);
                sphereVertices.push_back(z);
                sphereVertices.push_back(u);
                sphereVertices.push_back(v);
            }
        }

        // Generate indices
        for (unsigned int lat = 0; lat < latitudeCount; ++lat) {
            for (unsigned int lon = 0; lon < longitudeCount; ++lon) {
                unsigned int first = (lat * (longitudeCount + 1)) + lon;
                unsigned int second = first + longitudeCount + 1;

                sphereIndices.push_back(first);
                sphereIndices.push_back(second);
                sphereIndices.push_back(first + 1);

                sphereIndices.push_back(second);
                sphereIndices.push_back(second + 1);
                sphereIndices.push_back(first + 1);
            }
        }

        // OpenGL buffers
        glGenVertexArrays(1, &sphereVAO);
        glGenBuffers(1, &sphereVBO);
        glGenBuffers(1, &sphereEBO);

        glBindVertexArray(sphereVAO);

        glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
        glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(unsigned int), sphereIndices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
};

#endif /* sphere_h */

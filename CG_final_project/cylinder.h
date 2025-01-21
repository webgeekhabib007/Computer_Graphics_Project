#ifndef cylinder_h
#define cylinder_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"


#define M_PI 3.1415

using namespace std;

class Cylinder {
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
    Cylinder() {
        setUpCylinderVertexDataAndConfigureVertexAttribute();
    }

    Cylinder(glm::vec3 amb = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 diff = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f),
        float shiny = 32.0f) {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpCylinderVertexDataAndConfigureVertexAttribute();
    }

    Cylinder(unsigned int tMap, glm::vec3 amb = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 diff = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f),
        float shiny = 32.0f) {
        this->textureMap = tMap;
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpCylinderVertexDataAndConfigureVertexAttribute();
    }

    // Destructor
    ~Cylinder() {
        glDeleteVertexArrays(1, &cylinderVAO);
        glDeleteBuffers(1, &cylinderVBO);
        glDeleteBuffers(1, &cylinderEBO);
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

        glBindVertexArray(cylinderVAO);
        glDrawElements(GL_TRIANGLES, cylinderIndices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    unsigned int cylinderVAO;
    unsigned int cylinderVBO;
    unsigned int cylinderEBO;
    vector<unsigned int> cylinderIndices;

    void setUpCylinderVertexDataAndConfigureVertexAttribute() {
        const int segments = 36; // Number of segments (sides of the cylinder)
        const float radius = 0.5f;
        const float height = 1.0f;

        vector<float> cylinderVertices;
        cylinderIndices.clear();

        // Create the vertex data for the cylinder (top and bottom circles and sides)
        for (int i = 0; i < segments; ++i) {
            float angle = (i * 2.0f * M_PI) / segments;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            float nx = x;
            float ny = 0.0f;
            float nz = z;
            // Bottom circle
            cylinderVertices.push_back(x);  // Position
            cylinderVertices.push_back(-height / 2);  // Position
            cylinderVertices.push_back(z);  // Position
            cylinderVertices.push_back(nx);  // Normal
            cylinderVertices.push_back(ny);  // Normal
            cylinderVertices.push_back(nz);  // Normal
            cylinderVertices.push_back(i / float(segments));  // Texture coord
            cylinderVertices.push_back(0.0f);  // Texture coord

            // Top circle
            cylinderVertices.push_back(x);  // Position
            cylinderVertices.push_back(height / 2);  // Position
            cylinderVertices.push_back(z);  // Position
            cylinderVertices.push_back(nx);  // Normal
            cylinderVertices.push_back(ny);  // Normal
            cylinderVertices.push_back(nz);  // Normal
            cylinderVertices.push_back(i / float(segments));  // Texture coord
            cylinderVertices.push_back(1.0f);  // Texture coord
        }

        // Cylinder sides vertices (two triangles per side)
        for (int i = 0; i < segments; ++i) {
            int nextIndex = (i + 1) % segments;

            // Side bottom left
            cylinderVertices.push_back(cos(i * 2.0f * M_PI / segments) * radius);  // Position
            cylinderVertices.push_back(-height / 2);  // Position
            cylinderVertices.push_back(sin(i * 2.0f * M_PI / segments) * radius);  // Position
            cylinderVertices.push_back(cos(i * 2.0f * M_PI / segments));  // Normal
            cylinderVertices.push_back(0.0f);  // Normal
            cylinderVertices.push_back(sin(i * 2.0f * M_PI / segments));  // Normal
            cylinderVertices.push_back(i / float(segments));  // Texture coord
            cylinderVertices.push_back(0.0f);  // Texture coord

            // Side top left
            cylinderVertices.push_back(cos(nextIndex * 2.0f * M_PI / segments) * radius);  // Position
            cylinderVertices.push_back(-height / 2);  // Position
            cylinderVertices.push_back(sin(nextIndex * 2.0f * M_PI / segments) * radius);  // Position
            cylinderVertices.push_back(cos(nextIndex * 2.0f * M_PI / segments));  // Normal
            cylinderVertices.push_back(0.0f);  // Normal
            cylinderVertices.push_back(sin(nextIndex * 2.0f * M_PI / segments));  // Normal
            cylinderVertices.push_back((i + 1) / float(segments));  // Texture coord
            cylinderVertices.push_back(0.0f);  // Texture coord

            // Side top right
            cylinderVertices.push_back(cos(i * 2.0f * M_PI / segments) * radius);  // Position
            cylinderVertices.push_back(height / 2);  // Position
            cylinderVertices.push_back(sin(i * 2.0f * M_PI / segments) * radius);  // Position
            cylinderVertices.push_back(cos(i * 2.0f * M_PI / segments));  // Normal
            cylinderVertices.push_back(0.0f);  // Normal
            cylinderVertices.push_back(sin(i * 2.0f * M_PI / segments));  // Normal
            cylinderVertices.push_back(i / float(segments));  // Texture coord
            cylinderVertices.push_back(1.0f);  // Texture coord
        }

        // Add indices for top and bottom circles
        for (int i = 0; i < segments; ++i) {
            cylinderIndices.push_back(i * 2);  // Bottom circle
            cylinderIndices.push_back(i * 2 + 1);  // Top circle
            cylinderIndices.push_back((i + 1) % segments * 2);  // Bottom circle next
            cylinderIndices.push_back((i + 1) % segments * 2);  // Bottom circle next
            cylinderIndices.push_back(i * 2 + 1);  // Top circle
            cylinderIndices.push_back((i + 1) % segments * 2 + 1);  // Top circle next
        }

        glGenVertexArrays(1, &cylinderVAO);
        glGenBuffers(1, &cylinderVBO);
        glGenBuffers(1, &cylinderEBO);

        glBindVertexArray(cylinderVAO);

        glBindBuffer(GL_ARRAY_BUFFER, cylinderVBO);
        glBufferData(GL_ARRAY_BUFFER, cylinderVertices.size() * sizeof(float), cylinderVertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinderEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinderIndices.size() * sizeof(unsigned int), cylinderIndices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
};

#endif /* cylinder_h */

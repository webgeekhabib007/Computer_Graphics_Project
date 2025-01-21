#ifndef cone_h
#define cone_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"


#define M_PI 3.1415

using namespace std;

class Cone {
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
    Cone() {
        setUpConeVertexDataAndConfigureVertexAttribute();
    }

    Cone(glm::vec3 amb = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 diff = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f),
        float shiny = 32.0f) {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpConeVertexDataAndConfigureVertexAttribute();
    }

    Cone(unsigned int tMap, glm::vec3 amb = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 diff = glm::vec3(1.0f, 0.5f, 0.3f),
        glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f),
        float shiny = 32.0f) {
        this->textureMap = tMap;
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpConeVertexDataAndConfigureVertexAttribute();
    }

    // Destructor
    ~Cone() {
        glDeleteVertexArrays(1, &coneVAO);
        glDeleteBuffers(1, &coneVBO);
        glDeleteBuffers(1, &coneEBO);
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

        glBindVertexArray(coneVAO);
        glDrawElements(GL_TRIANGLES, coneIndices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    unsigned int coneVAO;
    unsigned int coneVBO;
    unsigned int coneEBO;
    vector<unsigned int> coneIndices;

    void setUpConeVertexDataAndConfigureVertexAttribute() {
        // Number of segments to define the cone
        const int segments = 36;
        const float radius = 0.5f;
        const float height = 1.0f;

        vector<float> coneVertices;
        coneIndices.clear();

        // Create the vertex data for the cone (top circle and sides)
        for (int i = 0; i < segments; ++i) {
            float angle = (i * 2.0f * M_PI) / segments;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            float nx = x;
            float ny = 0.0f;
            float nz = z;
            coneVertices.push_back(x);  // Position
            coneVertices.push_back(0.0f);  // Position (base)
            coneVertices.push_back(z);  // Position
            coneVertices.push_back(nx);  // Normal
            coneVertices.push_back(ny);  // Normal
            coneVertices.push_back(nz);  // Normal
            coneVertices.push_back(i / float(segments));  // Texture coord
            coneVertices.push_back(0.0f);  // Texture coord
        }

        // Cone tip
        coneVertices.push_back(0.0f); // Tip position x
        coneVertices.push_back(height); // Tip position y
        coneVertices.push_back(0.0f); // Tip position z
        coneVertices.push_back(0.0f); // Normal
        coneVertices.push_back(1.0f); // Normal
        coneVertices.push_back(0.0f); // Normal
        coneVertices.push_back(0.5f); // Texture coord
        coneVertices.push_back(1.0f); // Texture coord

        // Add indices for base and sides
        for (int i = 0; i < segments; ++i) {
            coneIndices.push_back(i);
            coneIndices.push_back((i + 1) % segments);
            coneIndices.push_back(segments);
        }

        glGenVertexArrays(1, &coneVAO);
        glGenBuffers(1, &coneVBO);
        glGenBuffers(1, &coneEBO);

        glBindVertexArray(coneVAO);

        glBindBuffer(GL_ARRAY_BUFFER, coneVBO);
        glBufferData(GL_ARRAY_BUFFER, coneVertices.size() * sizeof(float), coneVertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, coneEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, coneIndices.size() * sizeof(unsigned int), coneIndices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
};

#endif /* cone_h */

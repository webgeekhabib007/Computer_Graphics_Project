//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "basic_camera.h"

#include "hexagon.h"
#include "cube.h"
#include "sphere.h"
#include "cone.h"
#include "cylinder.h"
#include "bush.h"
#include "stb_image.h"

#include "pointLight.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform var for base
float base_rotateAngle_X = 0.0;
float base_rotateAngle_Y = 0.0;
float base_rotateAngle_Z = 0.0;
float base_rotateAxis_X = 0.0;
float base_rotateAxis_Y = 0.0;
float base_rotateAxis_Z = 1.0;
float base_translate_X = 0.0;
float base_translate_Y = 0.0;
float base_translate_Z = 0.0;
float base_scale_X = 100.0;
float base_scale_Y = 0.01;
float base_scale_Z = 100.0;

// modelling transform var for shops
float shop_rotateAngle_X = 0.0;
float shop_rotateAngle_Y = 0.0;
float shop_rotateAngle_Z = 0.0;
float shop_rotateAxis_X = 0.0;
float shop_rotateAxis_Y = 0.0;
float shop_rotateAxis_Z = 1.0;
float shop_translate_X = 0.0;
float shop_translate_Y = 0.0;
float shop_translate_Z = 0.0;
float shop_scale_X = 20.0f;
float shop_scale_Y = 10.0f;
float shop_scale_Z = 10.0f;


// modelling transform var for shops
float building_rotateAngle_X = 0.0;
float building_rotateAngle_Y = 0.0;
float building_rotateAngle_Z = 0.0;
float building_rotateAxis_X = 0.0;
float building_rotateAxis_Y = 0.0;
float building_rotateAxis_Z = 1.0;
float building_translate_X = 0.0;
float building_translate_Y = 0.0;
float building_translate_Z = 0.0;
float building_scale_X = 15.0f;
float building_scale_Y = 45.0f;
float building_scale_Z = 10.0f;


// modelling transform var for tree
float tree_rotateAngle_X = 0.0;
float tree_rotateAngle_Y = 0.0;
float tree_rotateAngle_Z = 0.0;
float tree_rotateAxis_X = 0.0;
float tree_rotateAxis_Y = 0.0;
float tree_rotateAxis_Z = 1.0;
float tree_translate_X = 0.0;
float tree_translate_Y = 0.0;
float tree_translate_Z = 0.0;
float tree_scale_X = 15.0f;
float tree_scale_Y = 45.0f;
float tree_scale_Z = 10.0f;





// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 20.0, eyeZ = 55.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(1.50f,  1.50f,  0.0f),
    glm::vec3(1.5f,  -1.5f,  0.0f),
    glm::vec3(-1.5f,  1.5f,  0.0f),
    glm::vec3(-1.5f,  -1.5f,  0.0f)
};


PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);



// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


//bezier
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 30;

unsigned int sphereVAO, coneVAO, treeTopVAO, treeMidVAO;

vector <float> cntrlPointsSphere, cntrlPointsCone, cntrlPointsTreeTop, cntrlPointsTreeMid;
vector <float> coordinatesSphere, coordinatesCone, coordinatesTreeTop;
vector <float> normalsSphere, normalsCone, normalsTreeTop;
vector <int> indicesSphere, indicesCone, indicesTreeTop;
vector <float> verticesSphere, verticesCone, verticesTreeTop;


long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector<float>& coordinates, vector<float>& normals, vector<int>& indices, vector<float>& vertices, float div = 1.0)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal

    const float dtheta = (2 * pi / ntheta) / div;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];
    vector<float> textureCoords;

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            // Calculate (x, y, z) coordinates using parametric equations
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = -(x - 0) * lengthInv;
            ny = -(y - y) * lengthInv;
            nz = -(z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            // Texture coordinates (u, v)
            float u = float(j) / float(ntheta); // Around the circle
            float v = t;     // Along the curve
            textureCoords.push_back(u);
            textureCoords.push_back(v);

            // Increment theta for next iteration
            theta += dtheta;
        }
    }

    // Generate index list of triangles
    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // Create two triangles for each segment
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    // Store the vertex data (positions, normals, texture coordinates)
    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);

        // Add texture coordinates
        vertices.push_back(textureCoords[i / 3 * 2]);
        vertices.push_back(textureCoords[i / 3 * 2 + 1]);
    }

    // Create VAO, VBO, and EBO for OpenGL rendering
    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // Create VBO to copy vertex data to GPU
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // For vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // Target
        (unsigned int)vertices.size() * sizeof(float), // Size in bytes
        vertices.data(),   // Pointer to vertex data
        GL_STATIC_DRAW);                   // Usage

    // Create EBO to copy index data to GPU
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // For index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // Target
        (unsigned int)indices.size() * sizeof(unsigned int),             // Size in bytes
        indices.data(),               // Pointer to index data
        GL_STATIC_DRAW);                   // Usage

    // Enable vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Set attribute pointers
    int stride = 32;     // Should be 32 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);            // Vertex position
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3)); // Normal
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float))); // Texture Coord

    // Unbind VAO, VBO, and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}

void read_file(string file_name, vector<float>& vec)
{
    ifstream file(file_name);
    float number;

    while (file >> number)
        vec.push_back(number);

    file.close();
}

bool fanOn = false;
float r = 1.0f;


void drawFan(unsigned int VAO, Shader ourShader, glm::mat4 matrix) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, RotateTranslateMatrix, InvRotateTranslateMatrix;

    if (fanOn) {
        //fan rod
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.15f, 10.0f, 4.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -1.5f, 0.2f));
        model = matrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan middle
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.85f, 8.5f, 4.6f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.4f, 0.0f, -0.4f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.0f, 0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, -0.2f, 0.8f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.85f, 8.5f, 4.8f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.4f, 0.0f, -0.2f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.0f, 0.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1.5f, -0.2f, 0.4f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.65f, 8.5f, 4.8f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.0f, -0.2f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.4f, 0.0f, 0.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, -0.2f, 0.4f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars up
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.05f, 8.5f, 4.6f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.0f, -0.4f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.0f, 0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, -0.2f, -1.5f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars down
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.05f, 8.5f, 5.4f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.0f, 0.4f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.0f, -0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, -0.2f, 1.5f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        r += 0.75f;
    }

    else {
        //fan rod
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.15f, 10.0f, 4.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -1.5f, 0.2f));
        model = matrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan middle
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.85f, 8.5f, 4.6f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, -0.2f, 0.8f));
        model = matrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.85f, 8.5f, 4.8f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1.5f, -0.2f, 0.4f));
        model = matrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.65f, 8.5f, 4.8f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, -0.2f, 0.4f));
        model = matrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars up
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.05f, 8.5f, 4.6f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, -0.2f, -1.5f));
        model = matrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //fan propelars down
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.05f, 8.5f, 5.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, -0.2f, 1.5f));
        model = matrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}


void drawFractalTree(Shader& shader, const glm::mat4& model, int depth, Cylinder& CubeGreen, const glm::mat4& a_translate_mat, Bush& Leaf_Obj, const glm::mat4& model2) {
    if (depth == 0) return;

    // Draw the current cube

    CubeGreen.draw(shader, a_translate_mat * model);
    if (depth == 1)
    {
        Leaf_Obj.drawWithTexture(shader, a_translate_mat * model2);
    }

    // Scaling and translation for the branches
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.75f, 0.5f));

    float deg = 0;
    glm::mat4 rotateY = rotate(glm::mat4(1.0f), glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
    // Left branch 1
    glm::mat4 translateLeft = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.05f));
    glm::mat4 rotateLeft = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 leftBranchModel = translateLeft * rotateY * rotateLeft * scaleMatrix * model;
    glm::mat4 leftBranchforLeaf = translateLeft * rotateY * rotateLeft * model2;
    drawFractalTree(shader, leftBranchModel, depth - 1, CubeGreen, a_translate_mat, Leaf_Obj, leftBranchforLeaf);
    // Right branch 1
    glm::mat4 translateRight = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.05f));
    glm::mat4 rotateRight = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rightBranchModel = translateRight * rotateY * rotateRight * scaleMatrix * model;
    glm::mat4 rightBranchforLeaf = translateRight * rotateY * rotateRight * model2;
    drawFractalTree(shader, rightBranchModel, depth - 1, CubeGreen, a_translate_mat, Leaf_Obj, rightBranchforLeaf);

    deg = 90;
    rotateY = rotate(glm::mat4(1.0f), glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
    // Left branch 2
    translateLeft = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.15f));
    glm::mat4 leftBranchModel2 = translateLeft * rotateY * rotateLeft * scaleMatrix * model;
    glm::mat4 leftBranchforLeaf2 = translateLeft * rotateY * rotateLeft * model2;
    drawFractalTree(shader, leftBranchModel2, depth - 1, CubeGreen, a_translate_mat, Leaf_Obj, leftBranchforLeaf2);
    translateRight = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.15f));
    glm::mat4 rightBranchModel2 = translateRight * rotateY * rotateRight * scaleMatrix * model;
    glm::mat4 rightBranchforLeaf2 = translateRight * rotateY * rotateRight * model2;
    drawFractalTree(shader, rightBranchModel2, depth - 1, CubeGreen, a_translate_mat, Leaf_Obj, rightBranchforLeaf2);

}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------

    Shader lightingShaderWithTexture("vertexShaderWithTexture.vs", "fragmentShaderWithTexture.fs");
    Shader lightingShader("vertexShaderForPhongShading.vs","fragmentShaderForPhongShading.fs");


    shop_translate_X = base_translate_X - shop_scale_X / 2 - 30.0f;
    shop_translate_Z = base_translate_Z - shop_scale_X / 2 - 25.0f;

    building_translate_X = base_translate_X + building_scale_X / 2 + 20.0f;
    building_translate_Z = base_translate_Z + building_scale_Z / 2 - 35.0f;

    // Object declarations
    string base_tex_path = "images/smallrocks.png";
    string road1_tex_path = "images/road1.bmp";
    string road2_tex_path = "images/tunnel_road.jpg";
    string side_wall_path = "images/wall1.jpg";
    string residential_area_path = "images/concrete.jpg";
    string shop1_path = "images/shop1.bmp";
    string shop2_path = "images/shop2.bmp";
    string shop3_path = "images/shop3.bmp";
    string shop4_path = "images/shop4.bmp";
    string roof_path = "images/floor3.bmp";
    string leaf_path = "images/leaf3.bmp";
    string wood_path = "images/wood4.bmp";
    string white_path = "images/white_tex.jpg";
    string board_path = "images/signboard7.bmp";

    string building_path = "images/building5.bmp";

    unsigned int base_tex = loadTexture(base_tex_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int road1_tex = loadTexture(road1_tex_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int road2_tex = loadTexture(road2_tex_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int side_wall_tex = loadTexture(side_wall_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int residential_area_base_tex = loadTexture(residential_area_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int shop1_tex = loadTexture(shop1_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int shop2_tex = loadTexture(shop2_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int shop3_tex = loadTexture(shop3_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int shop4_tex = loadTexture(shop4_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int roof_tex = loadTexture(roof_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int building_tex = loadTexture(building_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int leaf_tex = loadTexture(leaf_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int wood_tex = loadTexture(wood_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int white_tex = loadTexture(white_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    unsigned int signboard_tex = loadTexture(board_path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);


    Cube base = Cube(base_tex);
    Cube road1 = Cube(road1_tex);
    Cube road2 = Cube(road2_tex);
    Cube side_wall = Cube(side_wall_tex);
    Cube residential_base = Cube(residential_area_base_tex);

    Cube shop1 = Cube(shop1_tex);
    Cube roof = Cube(roof_tex);
    Cube building = Cube(building_tex);

    Cone cone = Cone(leaf_tex);
    Cylinder cylinder = Cylinder(wood_tex);

    Cube signboard = Cube(signboard_tex);
    Cube signStand = Cube(wood_tex);

    Cube fan = Cube(white_tex);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Instruction
    printf("1. Press 'W' to move forward\n");
    printf("2. Press 'S' to move backward\n");
    printf("3. Press 'A' to move left\n");
    printf("4. Press 'D' to move right\n");
    printf("\n");
    printf("5. Press 'I' to move the object up\n");
    printf("6. Press 'K' to move the object down\n");
    printf("7. Press 'L' to move the object right\n");
    printf("8. Press 'J' to move the object left\n");
    printf("\n");
    printf("9. Press 'X' to rotate along X-axis\n");
    printf("10. Press 'Y' to rotate along Y-axis\n");
    printf("11. Press 'Z' to rotate along Z-axis\n");


    read_file("bathtub.txt", cntrlPointsSphere);
    sphereVAO = hollowBezier(cntrlPointsSphere.data(), ((unsigned int)cntrlPointsSphere.size() / 3) - 1, coordinatesSphere, normalsSphere, indicesSphere, verticesSphere, 2.0);


    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", basic_camera.eye);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);

        lightingShader.setVec3("diectionalLight.directiaon", 0.0f, 3.0f, 0.0f);
        lightingShader.setVec3("diectionalLight.ambient", .2, .2, .2);
        lightingShader.setVec3("diectionalLight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("diectionalLight.specular", 1.0f, 1.0f, 1.0f);




        lightingShader.setBool("dlighton", true);


        lightingShader.setVec3("spotlight.position", -0.5, 1, -0.5);
        lightingShader.setVec3("spotlight.direction", 0, -1, 0);
        lightingShader.setVec3("spotlight.ambient", .2, .2, .2);
        lightingShader.setVec3("spotlight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotlight.k_c", 1.0f);
        lightingShader.setFloat("spotlight.k_l", 0.09);
        lightingShader.setFloat("spotlight.k_q", 0.032);
        lightingShader.setFloat("cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setBool("spotlighton", true);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", basic_camera.eye);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(basic_camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = basic_camera.createViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);



        // base
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(base_translate_X, base_translate_Y, base_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(base_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(base_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(base_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(base_scale_X, base_scale_Y, base_scale_Z));

        lightingShaderWithTexture.use();

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(modelMatrixForContainer, glm::vec3(-0.0f, -0.4f, -2.8f));
        lightingShaderWithTexture.setFloat("scaleS", 10.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 10.0f);
        base.draw(lightingShaderWithTexture, modelMatrixForContainer * model);

        // road1
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(base_translate_X, base_translate_Y , base_translate_Z+0.99f));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(base_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(base_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(base_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(base_scale_X, base_scale_Y, base_scale_Z/20));
        lightingShaderWithTexture.setFloat("scaleS", 10.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        road1.draw(lightingShaderWithTexture , model);


        // road2
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(base_translate_X, base_translate_Y+0.01f, base_translate_Z + 0.1f));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(base_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(base_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(base_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(base_scale_X/18, base_scale_Y, base_scale_Z));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 20.0f);
        road2.draw(lightingShaderWithTexture, model);


        // base_side wall 1
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(base_translate_X - base_scale_X/2, base_translate_Y + 0.01f, base_translate_Z + 0.1f));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(base_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(base_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(base_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(0.1f, 10.0f, base_scale_Z));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 25.0f);
        side_wall.draw(lightingShaderWithTexture, model);

        // base_side wall 2
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(base_translate_X + base_scale_X / 2, base_translate_Y + 0.01f, base_translate_Z + 0.1f));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(base_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(base_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(base_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(0.1f, 10.0f, base_scale_Z));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 25.0f);
        side_wall.draw(lightingShaderWithTexture, model);

        // base_side wall 3
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(base_translate_X , base_translate_Y, base_translate_Z - base_scale_Z/2));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(base_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(base_rotateAngle_Y + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(base_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(0.1f, 10.0f, base_scale_Z));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 25.0f);
        side_wall.draw(lightingShaderWithTexture, model);


        // residential area base
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(base_translate_X, base_translate_Y, base_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(base_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(base_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(base_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(base_scale_X/2, base_scale_Y, base_scale_Z/2));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 10.0f);
        residential_base.draw(lightingShaderWithTexture, model);


        // shop1- side 1
       
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(shop_translate_X + shop_scale_X/2, shop_translate_Y+ shop_scale_Y/2, shop_translate_Z - shop_scale_X/2));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(shop_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(shop_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(shop_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(shop_scale_X, shop_scale_Y, shop_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        shop1.draw(lightingShaderWithTexture, model);

        // shop1- side 2
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(shop_translate_X + shop_scale_X / 2, shop_translate_Y + shop_scale_Y / 2, shop_translate_Z + shop_scale_X / 2));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(shop_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(shop_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(shop_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(shop_scale_X, shop_scale_Y, shop_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        shop1.draw(lightingShaderWithTexture, model);


        // shop1- side 3
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(shop_translate_X, shop_translate_Y + shop_scale_Y / 2, shop_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(shop_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(shop_rotateAngle_Y + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(shop_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(shop_scale_X, shop_scale_Y, shop_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        shop1.draw(lightingShaderWithTexture, model);

        // shop1- side 4
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(shop_translate_X + shop_scale_X, shop_translate_Y + shop_scale_Y / 2, shop_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(shop_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(shop_rotateAngle_Y + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(shop_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(shop_scale_X, shop_scale_Y, shop_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        shop1.draw(lightingShaderWithTexture, model);

        // roof1
        
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(shop_translate_X + shop_scale_X/2, shop_translate_Y + shop_scale_Y, shop_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(shop_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(shop_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(shop_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(shop_scale_X * 1.01, shop_scale_Y/10, shop_scale_X*1.01));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        roof.draw(lightingShaderWithTexture, model);


        // building1- side 1

        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(building_translate_X + building_scale_X / 2, building_translate_X + building_scale_Y / 2, building_translate_X - building_scale_X / 2));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(building_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(building_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(building_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(building_scale_X, building_scale_Y, building_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        building.draw(lightingShaderWithTexture, model);

        // building1- side 2
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(building_translate_X + building_scale_X / 2, building_translate_Y + building_scale_Y / 2, building_translate_Z + building_scale_X / 2));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(building_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(building_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(building_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(building_scale_X, building_scale_Y, building_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        building.draw(lightingShaderWithTexture, model);


        // building1- side 3
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(building_translate_X, building_translate_Y + building_scale_Y / 2, building_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(building_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(building_rotateAngle_Y + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(building_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(building_scale_X, building_scale_Y, building_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        building.draw(lightingShaderWithTexture, model);

        // building1- side 4
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(building_translate_X + building_scale_X, building_translate_Y + building_scale_Y / 2, building_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(building_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(building_rotateAngle_Y + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(building_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(building_scale_X, building_scale_Y, building_scale_Z * 0.01f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        building.draw(lightingShaderWithTexture, model);

        // roof1

        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(building_translate_X + building_scale_X / 2, building_translate_Y + building_scale_Y, building_translate_Z));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(building_rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(building_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(building_rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(building_scale_X * 1.01, building_scale_X / 100, building_scale_X * 1.01));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        roof.draw(lightingShaderWithTexture, model);


        //tree1 head
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f - 20.0f, 8.0f, -5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f- 20.0f, 9.0f, -5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        // tree1 body
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f- 20.0f, 5.0f, -5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(1.0f, 7.0f, 1.0f));

        cylinder.draw(lightingShaderWithTexture, model);


        //tree2 head
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f - 10.0f, 8.0f, 5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f - 10.0f, 7.0f, 5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        // tree2 body
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f - 10.0f, 5.0f, 5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(1.0f, 10.0f, 1.0f));

        cylinder.draw(lightingShaderWithTexture, model);


        //tree3 head
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f + 10.0f, 10.0f, -5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f + 10.0f, 9.0f, -5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        // tree3 body
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f + 10.0f, 5.0f, -5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(1.0f, 10.0f, 1.0f));

        cylinder.draw(lightingShaderWithTexture, model);


        //tree4 head
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f + 20.0f, 10.0f, +5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f + 20.0f, 9.0f, 5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(5.0f));
        cone.draw(lightingShaderWithTexture, model);
        // tree4 body
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f + 20.0f, 5.0f, 5.0f));  // Move sphere to a position
        model = glm::scale(model, glm::vec3(1.0f, 10.0f, 1.0f));

        cylinder.draw(lightingShaderWithTexture, model);




        //basin using bezier curve
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-35.30f, 12.0f, -25.0f));
        auto scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.8, 2.0, 1.2));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateZMatrix * rotateYMatrix * scaleMatrix;
        lightingShaderWithTexture.setInt("material.diffuse", 0);
        lightingShaderWithTexture.setInt("material.specular", 1);
        lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, white_tex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, white_tex);
        glBindVertexArray(sphereVAO);
        lightingShaderWithTexture.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, (unsigned int)indicesSphere.size(), GL_UNSIGNED_INT, (void*)0);


        // signboard 
        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0f,7.0f,-15.0f));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(5.0f,2.0f,5.0f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        signboard.draw(lightingShaderWithTexture, model);


        identityMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0f, 5.0f, -15.0f));
        rotateXMatrix = glm::rotate(translateMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(rotateXMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(rotateYMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(rotateZMatrix, glm::vec3(0.5f, 5.0f, 0.5f));
        lightingShaderWithTexture.setFloat("scaleS", 1.0f); // Repeat texture 2 times
        lightingShaderWithTexture.setFloat("scaleT", 1.0f);
        signStand.draw(lightingShaderWithTexture, model);


        //drawFan(fan.cubeVAO, lightingShaderWithTexture, model);
        Bush Leaf_Obj1 = Bush(leaf_tex, leaf_tex, 32.0f);

        Cylinder Tree_root1 = Cylinder(wood_tex);
        
        //// Tree
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 4.0f, 0.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0f, 1.25, 3.0));
        glm::mat4 rootModel1 = scaleMatrix * translateMatrix;
        // Draw fractal tree
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 4.0f, 4.0f));

        //glm::mat4 rootModel2 = translate(identityMatrix, glm::vec3(-1.0f, 1.0f,-1.0f))  * scaleMatrix * translateMatrixinit;
        //Leaf_Obj.drawWithTexture(shader, rootModel2);
        //glm::mat4 rootModel2 = translate(identityMatrix, glm::vec3(-0.8f, -0.65f, 0.0f)) * scaleMatrix;
        glm::mat4 rootModel21 = translate(identityMatrix, glm::vec3(0.0f, -0.75f, 0.0f)) * scaleMatrix;
        drawFractalTree(lightingShaderWithTexture, rootModel1, 4, Tree_root1, translateMatrix, Leaf_Obj1, rootModel21); // Change depth as needed

        Bush Leaf_Obj2 = Bush(leaf_tex, leaf_tex, 32.0f);

        Cylinder Tree_root2 = Cylinder(wood_tex);

        //// Tree
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 4.0f, 0.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(9.0f, 1.25, -3.0));
        glm::mat4 rootModel2 = scaleMatrix * translateMatrix;
        // Draw fractal tree
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 4.0f, 4.0f));

        //glm::mat4 rootModel2 = translate(identityMatrix, glm::vec3(-1.0f, 1.0f,-1.0f))  * scaleMatrix * translateMatrixinit;
        //Leaf_Obj.drawWithTexture(shader, rootModel2);
        //glm::mat4 rootModel2 = translate(identityMatrix, glm::vec3(-0.8f, -0.65f, 0.0f)) * scaleMatrix;
        glm::mat4 rootModel22 = translate(identityMatrix, glm::vec3(0.0f, -0.75f, 0.0f)) * scaleMatrix;
        drawFractalTree(lightingShaderWithTexture, rootModel2, 4, Tree_root2, translateMatrix, Leaf_Obj2, rootModel22); // Change depth as needed


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        basic_camera.move(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        basic_camera.move(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        basic_camera.move(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        basic_camera.move(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        /*if (rotateAxis_X) rotateAngle_X -= deltaTime * 50;
        else if (rotateAxis_Y) rotateAngle_Y -= deltaTime * 50;
        else rotateAngle_Z -= deltaTime * 50;*/
    }
    /*if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += deltaTime;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= deltaTime;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += deltaTime;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= deltaTime;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += deltaTime;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= deltaTime;*/

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        /*rotateAngle_X += deltaTime * 50;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;*/
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        /*rotateAngle_Y += deltaTime * 50;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;*/
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        /*rotateAngle_Z += deltaTime * 50;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;*/
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 3.5 * deltaTime;
        basic_camera.eye = glm::vec3(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 3.5 * deltaTime;
        basic_camera.eye = glm::vec3(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 3.5 * deltaTime;
        basic_camera.eye = glm::vec3(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 3.5 * deltaTime;
        basic_camera.eye = glm::vec3(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 3.5 * deltaTime;
        basic_camera.eye = glm::vec3(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 3.5 * deltaTime;
        basic_camera.eye = glm::vec3(eyeX, eyeY, eyeZ);
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Set the OpenGL viewport to match the new window dimensions
    glViewport(0, 0, width, height);
}



// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    basic_camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


void drawTree(Cube& cube, Shader& shader, glm::mat4 model, int depth, float branchLength, float angle)
{
    if (depth <= 0) return;

    // Draw the current branch (cube)
    cube.draw(shader, model);

    // Reduce branch length for the next level
    branchLength *= 0.7f;

    // Recursion depth decreases
    depth--;

    // Transformations for branches
    glm::mat4 branch1 = glm::translate(model, glm::vec3(0.0f, branchLength, 0.0f)); // Upwards
    branch1 = glm::rotate(branch1, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate right
    branch1 = glm::scale(branch1, glm::vec3(0.7f, 0.7f, 0.7f)); // Scale down

    glm::mat4 branch2 = glm::translate(model, glm::vec3(0.0f, branchLength, 0.0f)); // Upwards
    branch2 = glm::rotate(branch2, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate left
    branch2 = glm::scale(branch2, glm::vec3(0.7f, 0.7f, 0.7f)); // Scale down

    // Recursive calls for the branches
    drawTree(cube, shader, branch1, depth, branchLength, angle);
    drawTree(cube, shader, branch2, depth, branchLength, angle);
}

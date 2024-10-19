#ifndef CAMERA_H
#define CAMERA_H

#include "shaderProgram.hpp"
#include <GLFW/glfw3.h>
#include "cameraSettings.hpp"
#include "transform.hpp"

using glm::vec3, glm::mat4;

class Camera
{
private:
    TransformComposite transform; 
    vec3 target;
    vec3 upVector;
    GLFWwindow* window;
    CameraSettings settings;
    float ratio;

public:
    Camera(GLFWwindow* window, CameraSettings settings);
    mat4 getViewMatrix();
    mat4 getProjectionMatrix();
    vec3 getPosition();
    vec3 getForwardVector();
    vec3 getRightVector();

    void move(vector<bool> keys, float deltaTime);
    void changeTarget(float deltaX, float deltaY, float delta);

    TransformComposite getTransform() const;
    void setTransform(const Transform& transform);

    void addPosition(const vec3& newPosition);
    void addRotation(const vec3& rotationVec, const float& angle);


};

#endif
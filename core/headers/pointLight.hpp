#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "transformComposite.hpp"
#include "IGameObject.hpp"
#include "shaderProgram.hpp"

class PointLight : public IGameObject
{
private:
    TransformComposite transform;
    ShaderProgram* shaderProgram;

    float time;

public:
    PointLight(ShaderProgram* shaderProgram);
    ~PointLight() = default;

    void addPosition(const vec3& newPosition);
    mat4 getTransformMatrix();

    void update(float delta) override;

    TransformComposite getTransform() const { return transform;}
    void setTransform(const TransformComposite& transform){ this->transform = transform;}

    void addRotation(const vec3& rotationVec, const float& angle){}
    void addScale(const vec3& newScale){}

};

#endif
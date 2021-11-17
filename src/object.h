#ifndef object_H
#define object_H


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <ppgso/ppgso.h>
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>


class Scene;


class Object {
protected:
    glm::mat4 modelMatrix{1};

    glm::vec3 collisionPoints[2];


    void generateModelMatrix();


public:
    glm::vec3 position = {0, 0, 0};

    glm::vec3 rotation = {0, 0, 0};

    glm::vec3 scale = {1, 1, 1};

    // box collider defined by two points
    glm::vec3 collider[2];  // collider[0] holds smaller x, smaller y and smaller z of box collider
                            // collider[1] holds higher x, higher y and higher z of box collider


    Object() = default;

    Object(const Object&) = default;

    Object(Object&&) = default;

    virtual bool update(Scene &scene, float dTime) = 0;

    virtual void render(Scene &scene) = 0;

    bool collision(glm::vec3 objCollider[2]);

    void updateCollider();
};


#endif
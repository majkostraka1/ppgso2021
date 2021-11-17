#ifndef simpleObject_H
#define simpleObject_H


#include "scene.h"
#include "object.h"


class staticObjects final : public Object {
private:
    uint8_t id;
    const static uint8_t OBJ_COUNT = 12;
    static std::unique_ptr<ppgso::Mesh> mesh[OBJ_COUNT];
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture[OBJ_COUNT];
    static char *textureName[OBJ_COUNT];
    static char *meshName[OBJ_COUNT];


public:
    staticObjects(glm::vec3 p = {0, 0, 0}, glm::vec3 r = {0, 0, 0}, glm::vec3 s = {1, 1, 1}, uint8_t id = 0);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};


#endif
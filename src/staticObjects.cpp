#include "staticObjects.h"


std::unique_ptr<ppgso::Mesh> staticObjects::mesh[OBJ_COUNT];
std::unique_ptr<ppgso::Texture> staticObjects::texture[OBJ_COUNT];
std::unique_ptr<ppgso::Shader> staticObjects::shader;
char *staticObjects::textureName[OBJ_COUNT] = {"tree.bmp", "bear.bmp", "rat.bmp"};
char *staticObjects::meshName[OBJ_COUNT] = {"tree.obj", "bear.obj", "rat.bmp"};


staticObjects::staticObjects(glm::vec3 p, glm::vec3 r, glm::vec3 s, uint8_t id) {
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!texture[id]) texture[id] = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureName[id]));
    if (!mesh[id]) mesh[id] = std::make_unique<ppgso::Mesh>(meshName[id]);

    position = p;
    rotation = r;
    scale = s;

    collisionPoints[0] = collisionPoints[1] = {0,0,0};

    if (id == 0) { // strom
        collisionPoints[0] = {.8, 3, .8};
        collisionPoints[1] = {-.8, -2, -0.8};
    }
    updateCollider();

    this->id = id;
}


bool staticObjects::update(Scene &scene, float dTime) {
    generateModelMatrix();

    return true;
}


void staticObjects::render(Scene &scene) {

    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera.projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera.viewMatrix);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture[id]);
    shader->setUniform("CameraPosition", scene.camera.position);

    mesh[id]->render();

}

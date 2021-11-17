#include "player.h"
#include "scene.h"


std::unique_ptr<ppgso::Mesh> Player::mesh;
std::unique_ptr<ppgso::Texture> Player::texture;
std::unique_ptr<ppgso::Shader> Player::shader;


Player::Player() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("penguin.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("rat.obj");

    scale = {1.5, 1.5, 1.5};
    position.y = 0.01;

}


glm::vec3 Player::handleKeys(bool keys[5], glm::vec3 back, float dTime) {    // pohyb na zaklade natocenia kamery
    glm::vec3 direction = -back;
    direction.y = 0;
    direction = glm::normalize(direction);
    glm::vec3 side = {direction.z, 0, -direction.x};

    const float speed = 5.f * dTime;
    glm::vec3 dPos = {0, 0, 0};

    if (keys[1]) {
        dPos += speed * direction;
    }
    if (keys[2]) {
        dPos -= speed * direction;
    }
    if (keys[3]) {
        dPos += side * speed;
    }
    if (keys[4]) {
        dPos -= side * speed;
    }

    return dPos;
}


bool Player::update(Scene &scene, float dTime) {

    glm::vec3 deltaPosition = handleKeys(scene.keys, scene.camera.back, dTime);

    if (deltaPosition.x != 0 || deltaPosition.z != 0) {
        rotation.y = -scene.cursor.yaw + 90;
    }

    animationTime += dTime;


    if (currKeyframe >= 3 || deltaPosition.x == 0 && deltaPosition.z == 0) {
        animationTime = 0;
        currKeyframe = 0;
    }


    glm::vec3 lastPosition = position;
    position += deltaPosition;
    updateCollider();

    for (auto &obj : scene.objects) {
        if (obj.get() == this) continue;

        if (obj.get()->collision(collider)) {
            position = lastPosition;
            updateCollider();
            break;
        }
    }

    scene.camera.position = position;

    generateModelMatrix();
    
    return true;
}

void Player::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera.projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera.viewMatrix);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("CameraPosition", scene.camera.position);

    mesh->render();
}
#ifndef scene_H
#define scene_H


#include <list>
#include <memory>

#include "camera.h"
#include "staticObjects.h"
#include "object.h"
#include "player.h"


class Scene {
public:
    Camera camera;

    Player player;

    std::list<std::unique_ptr<Object>> objects;

    bool keys[5] = {0};

    Cursor cursor;

    Scene(Camera camera);

    void scene1();

    bool update(float dTime);

    void render();
};


#endif
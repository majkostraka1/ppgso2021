#include "scene.h"


const unsigned int SIZEX = 1920, SIZEY = 1080;


class OriginWindow : public ppgso::Window {
private:
    std::unique_ptr<Scene> scene;
    float time;
    float lastX;
    float lastY;
    bool firstTimeCurs = true;


public:
    OriginWindow() : Window{"task5_3d_origin", SIZEX, SIZEY} {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        auto camera = Camera(90.0f, (float)width/(float)height, 1.0f, 400.0f);
        scene = std::make_unique<Scene>(camera);
    }


    void onCursorPos(double cursorX, double cursorY) override {
        if (firstTimeCurs) {
            lastX = cursorX;
            lastY = cursorY;
            firstTimeCurs = false;
        }

        float xoffset = cursorX - lastX;
        float yoffset = lastY - cursorY; // reverse (y-coordinates are bottom-up)
        lastX = cursorX;
        lastY = cursorY;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        scene->cursor.yaw += xoffset;
        scene->cursor.pitch += yoffset;

        // vertical bounds
        if (scene->cursor.pitch > 89.0f) {
            scene->cursor.pitch = 89.0f;
        }
        if (scene->cursor.pitch < -89.0f) {
            scene->cursor.pitch = -89.0f;
        }
    }


    void onKey(int key, int scanCode, int action, int mods) override {
        // key released == 0, key pressed == 1, key hold == 2
        if (key == GLFW_KEY_F) {    // only once per click
            scene->keys[0] = action == 1;
        }
        else if (key == GLFW_KEY_W) {
            scene->keys[1] = action > 0;
        }
        else if (key == GLFW_KEY_S) {
            scene->keys[2] = action > 0;
        }
        else if (key == GLFW_KEY_A) {
            scene->keys[3] = action > 0;
        }
        else if (key == GLFW_KEY_D) {
            scene->keys[4] = action > 0;
        }
    }


    void onIdle() {
        glClearColor(.33f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float dTime = (float) glfwGetTime() - time;
        time = (float) glfwGetTime();

        if (!scene->update(dTime)) {
            exit(EXIT_SUCCESS);
        }
        scene->render();
    }
};


int main() {
    auto window = OriginWindow{};

    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}

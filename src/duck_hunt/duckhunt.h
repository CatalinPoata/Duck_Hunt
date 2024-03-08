#pragma once

#include "components/simple_scene.h"
#include "duck_hunt/Bird.h"
#include "duck_hunt/Head.h"
#include "extra/basic_text/basic_text.h"


namespace m1
{
    class DH : public gfxc::SimpleScene
    {
     public:
        DH();
        ~DH();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
        float theta;
        float scaling;
        float alpha;
        float currX, currY;
        float factor;
        GLuint width, height;

        glm::vec2 direction;
        glm::vec2 centre;
        Bird bird;
        Head head;
        int speed;
        int count;
        int score;
        int lives;
        int bullets;

        glm::mat3 crosshair;

        std::string word;

        gfxc::TextRenderer* textRenderer;

    };
}   // namespace m1

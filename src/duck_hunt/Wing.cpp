#pragma once
#include "duck_hunt/Wing.h"

Wing::Wing() {
    
}

Wing::Wing(float birdScale, int wingNo, float theta) {
    this->verticesPos.clear();
    this->verticesPos.push_back(std::pair<float, float>(0.0f, 2.0f));
    this->verticesPos.push_back(std::pair<float, float>(-1 * (float)sqrt(3), -1.0f));
    this->verticesPos.push_back(std::pair<float, float>((float)sqrt(3), -1.0f));
    if (wingNo == 1) {
        this->selfTransform = glm::mat3(1);
        this->selfTransform *= transform2D::Rotate(theta - M_PI_2);
        this->selfTransform *= transform2D::Translate(birdScale, birdScale);
        this->selfTransform *= transform2D::Rotate(-M_PI_2);
        this->selfTransform *= transform2D::Scale(birdScale, birdScale);
    }
    else {
        this->selfTransform = glm::mat3(1);
        this->selfTransform *= transform2D::Rotate(theta - M_PI_2);
        this->selfTransform *= transform2D::Translate(-birdScale, birdScale);
        this->selfTransform *= transform2D::Rotate(M_PI_2);
        this->selfTransform *= transform2D::Scale(birdScale, birdScale);
    }
    this->moveTransform = glm::mat3(1);
    this->rotateTransform = glm::mat3(1);
    this->wingNO = wingNO;
    this->flapTransform = glm::mat3(1);
    this->wingAngle = 0;
}

Wing::~Wing() {
}

Mesh* Wing::createWingMesh(const std::string& name, glm::vec3 color) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0.0f, 2.0f, 0.0f), color),
        VertexFormat(glm::vec3(-1 * (float)sqrt(3), -1.0f, 0.0f), color),
        VertexFormat(glm::vec3((float)sqrt(3), -1.0f, 0.0f), color)
    };

    Mesh* wing = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    wing->InitFromData(vertices, indices);
    return wing;
}

glm::mat3 Wing::getTransform() {
    return this->moveTransform * this->rotateTransform * this->flapTransform * this->selfTransform;
}

int Wing::hasHitEdge(int width, int height) {
    glm::mat3 currState = this->moveTransform * this->rotateTransform * this->selfTransform;
    for (int i = 0; i < this->verticesPos.size(); i++) {
        float x = this->verticesPos[i].first;
        float y = this->verticesPos[i].second;
        glm::vec3 interVector = glm::vec3(x, y, 1);
        glm::vec3 resVector = currState * interVector;

        //printf("Punctul %d se afla la: %f %f\n", i, resVector.x, resVector.y);

        if ((resVector.x < 0) || (resVector.x > width)) {
            //printf("Are punct in afara la pozitia: %f %f\n", resVector.x, resVector.y);
            return 1;
        }

        if ((resVector.y < 0) || (resVector.y > height)) {
            //printf("Are punct in afara la pozitia: %f %f\n", resVector.x, resVector.y);
            return -1;
        }
    }

    return 0;
}

void Wing::updateVertices() {
    glm::mat3 currState = this->moveTransform * this->rotateTransform * this->selfTransform;
    for (int i = 0; i < this->verticesPos.size(); i++) {
        float x = this->verticesPos[i].first;
        float y = this->verticesPos[i].second;
        glm::vec3 interVector = glm::vec3(x, y, 1);
        glm::vec3 resVector = currState * interVector;
        this->verticesPos[i].first = resVector.x;
        this->verticesPos[i].second = resVector.x;
    }
}

bool Wing::isMouseOnWing(int mouseX, int mouseY) {
    int i, j;
    int intersections = 0;
    glm::mat3 currState = this->moveTransform * this->rotateTransform * this->selfTransform;
    for (i = 0, j = this->verticesPos.size() - 1; i < this->verticesPos.size(); j = i++) {
        float x1 = this->verticesPos[i].first;
        float y1 = this->verticesPos[i].second;
        float x2 = this->verticesPos[j].first;
        float y2 = this->verticesPos[j].second;
        glm::vec3 interVector1 = glm::vec3(x1, y1, 1);
        glm::vec3 interVector2 = glm::vec3(x2, y2, 1);
        glm::vec3 resVector1 = currState * interVector1;
        glm::vec3 resVector2 = currState * interVector2;

        if ((resVector1.y > (float)mouseY) != (resVector2.y > (float)mouseY) &&
            (float)mouseX < ((resVector2.x - resVector1.x) * ((float)mouseY - resVector1.y) / (resVector2.y - resVector1.y) + resVector1.x)) {
            intersections += 1;
        }
    }

    if (intersections % 2 == 0) {
        return false;
    }
    return true;
}

void Wing::flap(float deltaTimeSeconds) {
    float rotAngle = sin(wingAngle) * M_PI_4 / 4;
    //Aripa dreapta
    if (wingNO == 1) {
        flapTransform = transform2D::Rotate(rotAngle);
    }
    else {
        flapTransform = transform2D::Rotate(-rotAngle);
    }

    wingAngle += 1 / M_1_PI * deltaTimeSeconds;
}
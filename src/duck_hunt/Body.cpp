#pragma once
#include "duck_hunt/Body.h"

Body::Body() {
}

Body::Body(float birdScale, float theta) {
    this->verticesPos.clear();
    this->verticesPos.push_back(std::pair<float, float>(0.0f, 2.0f));
    this->verticesPos.push_back(std::pair<float, float>(-1 * (float)sqrt(3), -1.0f));
    this->verticesPos.push_back(std::pair<float, float>((float)sqrt(3), -1.0f));
    this->selfTransform = glm::mat3(1);
    this->selfTransform *= transform2D::Rotate(theta - M_PI_2);
    this->selfTransform *= transform2D::Scale(birdScale, 2 * birdScale);
    this->moveTransform = glm::mat3(1);
    this->rotateTransform = glm::mat3(1);
}

Body::~Body() {
}

Mesh* Body::createBodyMesh(const std::string& name, glm::vec3 color) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0.0f, 2.0f, -1.0f), color),
        VertexFormat(glm::vec3(-1 * (float)sqrt(3), -1.0f, -1.0f), color),
        VertexFormat(glm::vec3((float)sqrt(3), -1.0f, -1.0f), color)
    };

    Mesh* body = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    body->InitFromData(vertices, indices);
    return body;
}

glm::mat3 Body::getTransform() {
    return this->moveTransform * this->rotateTransform * this->selfTransform;
}

int Body::hasHitEdge(int width, int height) {
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

void Body::updateVertices() {
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

bool Body::isMouseOnBody(int mouseX, int mouseY) {
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
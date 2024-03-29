#pragma once
#include "duck_hunt/Head.h"

Head::Head() {
}

Head::Head(float birdScale, float theta) {
    this->noOfVertices = 64;
    this->verticesPos.clear();
    float angle = 0.0f;
    for (int i = 0; i < this->noOfVertices; i++) {
        this->verticesPos.push_back(std::pair<float, float>(cos(angle), sin(angle)));
        angle += 2 * M_PI / ((float)this->noOfVertices);
    }
    this->selfTransform = glm::mat3(1);
    this->selfTransform *= transform2D::Rotate(theta - M_PI_2);
    this->selfTransform *= transform2D::Translate(0, 4 * birdScale);
    this->selfTransform *= transform2D::Scale(birdScale, birdScale);
    this->moveTransform = glm::mat3(1);
    this->rotateTransform = glm::mat3(1);
}

Head::~Head() {
}

Mesh* Head::createHeadMesh(const std::string& name, glm::vec3 color) {
    float radius = 1;
    std::vector<VertexFormat> vertices;
    float angle = 0.0f;

    for (int i = 0; i < this->noOfVertices; i++) {
        vertices.push_back(VertexFormat(glm::vec3(radius * cos(angle), radius * sin(angle), 0), color));
        angle += 2 * M_PI / ((float)this->noOfVertices);
    }

    Mesh* head = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < this->noOfVertices; i++) {
        indices.push_back(i + 1);
    }
    indices.push_back(0);
    head->SetDrawMode(GL_TRIANGLE_FAN);

    head->InitFromData(vertices, indices);
    return head;
}

glm::mat3 Head::getTransform() {
    return this->moveTransform * this->rotateTransform * this->selfTransform;
}

int Head::hasHitEdge(int width, int height) {
    
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

void Head::updateVertices() {
    glm::mat3 currState = this->moveTransform * this->rotateTransform * this->selfTransform;
    for (int i = 0; i < this->verticesPos.size(); i++) {
        float x = this->verticesPos[i].first;
        float y = this->verticesPos[i].second;
    }
}

bool Head::isMouseOnHead(int mouseX, int mouseY) {
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
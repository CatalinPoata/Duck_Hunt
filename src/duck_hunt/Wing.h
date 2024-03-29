#pragma once
#include "duck_hunt/transform2D.h"
#include "duck_hunt/objects2D.h"
#include <stdlib.h>
#include "components/simple_scene.h"

class Wing
{
public:
	Wing();
	Wing(float bodyScale, int wingNo, float theta);
	~Wing();

	Mesh* createWingMesh(const std::string& name, glm::vec3 color);
	glm::mat3 getTransform();
	int hasHitEdge(int width, int height);
	void updateVertices();
	bool isMouseOnWing(int mouseX, int mouseY);
	void flap(float deltaTimeSeconds);

	std::vector<std::pair<float, float>> verticesPos;
	glm::mat3 selfTransform;
	glm::mat3 moveTransform;
	glm::mat3 rotateTransform;
	glm::mat3 flapTransform;
	int wingNO;
	float wingAngle;
};
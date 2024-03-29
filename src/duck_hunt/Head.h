#pragma once
#include "duck_hunt/transform2D.h"
#include "duck_hunt/objects2D.h"
#include <stdlib.h>
#include "components/simple_scene.h"

class Head
{
public:
	Head();
	Head(float bodyScale, float theta);
	~Head();

	Mesh* createHeadMesh(const std::string& name, glm::vec3 color);
	glm::mat3 getTransform();
	int hasHitEdge(int width, int height);
	void updateVertices();
	bool isMouseOnHead(int mouseX, int mouseY);

	std::vector<std::pair<float, float>> verticesPos;
	int noOfVertices;
	glm::mat3 selfTransform;
	glm::mat3 moveTransform;
	glm::mat3 rotateTransform;
};
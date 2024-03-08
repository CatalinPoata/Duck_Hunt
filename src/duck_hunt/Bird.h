#pragma once
#include "duck_hunt/transform2D.h"
#include "duck_hunt/objects2D.h"
#include <stdlib.h>
#include "components/simple_scene.h"
#include "duck_hunt/Wing.h"
#include "duck_hunt/Body.h"
#include "duck_hunt/Head.h"

class Bird
{
public:

	Bird();
	Bird(float speed, float scale);
	~Bird();

	void move(float deltaTimeSeconds);
	void rotateBird(int c);
	int hasHitEdge(int width, int height);
	void updateVertices();
	bool isMouseOnBird(int mouseX, int mouseY);
	
	int status;
	float scale;
	float speed;
	float theta;
	Wing wing1;
	Wing wing2;
	Head head;
	Body body;
	std::pair<float, float> position;
	std::vector<Mesh*> meshes;
	int collisions;
};
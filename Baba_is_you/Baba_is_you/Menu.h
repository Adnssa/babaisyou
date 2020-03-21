#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Quad.h"
#include "TexturedQuad.h"



#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


class Menu
{
public:
	Menu();
	~Menu();
	void init();
	void update(int deltaTime);
	void render(int state);

private:
	void initShaders();

private:
	enum { STATE_MENU, STATE_PLAYING, STATE_CREDITS };
	Quad* quad;
	Texture texs[3];
	TexturedQuad* texQuad;
	ShaderProgram simpleProgram, texProgram;
	float currentTime;
	glm::mat4 projection;
};

#endif
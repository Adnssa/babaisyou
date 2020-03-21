#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, STAND_UP, STAND_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN
};

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/Baba_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1 / 32.f, 1 / 66.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	FrameCount = 0;

	sprite->setAnimationSpeed(STAND_LEFT, 4);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(10 / 32.f, 0.f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(10 / 32.f, 1 / 66.f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(10 / 32.f, 2 / 66.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 4);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 1 / 66.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 2 / 66.f));

	sprite->setAnimationSpeed(STAND_UP, 4);
	sprite->addKeyframe(STAND_UP, glm::vec2(5 / 32.f, 0.f));
	sprite->addKeyframe(STAND_UP, glm::vec2(5 / 32.f, 1 / 66.f));
	sprite->addKeyframe(STAND_UP, glm::vec2(5 / 32.f, 2 / 66.f));

	sprite->setAnimationSpeed(STAND_DOWN, 4);
	sprite->addKeyframe(STAND_DOWN, glm::vec2(15 / 32.f, 0.f));
	sprite->addKeyframe(STAND_DOWN, glm::vec2(15 / 32.f, 1 / 66.f));
	sprite->addKeyframe(STAND_DOWN, glm::vec2(15 / 32.f, 2 / 66.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 16);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(10 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(11 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(12 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(13 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(14 / 32.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 16);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4 / 32.f, 0.f));


	sprite->setAnimationSpeed(MOVE_UP, 16);
	sprite->addKeyframe(MOVE_UP, glm::vec2(5 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(6 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(7 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(8 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(9 / 32.f, 0.f));

	sprite->setAnimationSpeed(MOVE_DOWN, 16);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(15 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(16 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(17 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(18 / 32.f, 0.f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(19 / 32.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		if (FrameCount == 0) {
			posPlayer.x -= 16;
			FrameCount++;
		}
		else if (FrameCount == 10) FrameCount = 0;
		else FrameCount++;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(24, 24)))
		{
			posPlayer.x += 16;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		if (FrameCount == 0) {
			posPlayer.x += 16;
			FrameCount++;
		}
		else if (FrameCount == 10) FrameCount = 0;
		else FrameCount++;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(24, 24)))
		{
			posPlayer.x -= 16;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		if (FrameCount == 0) {
			posPlayer.y -= 16;
			FrameCount++;
		}
		else if (FrameCount == 10) FrameCount = 0;
		else FrameCount++;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(24, 24), &posPlayer.y))
		{
			posPlayer.y += 16;
			sprite->changeAnimation(STAND_UP);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		if (FrameCount == 0) {
			posPlayer.y += 16;
			FrameCount++;
		}
		else if (FrameCount == 10) FrameCount = 0;
		else FrameCount++;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(24, 24), &posPlayer.y))
		{
			posPlayer.y -= 16;
			sprite->changeAnimation(STAND_DOWN);
		}
	}
	else
	{
		FrameCount = 0;
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		else if (sprite->animation() == MOVE_UP)
			sprite->changeAnimation(STAND_UP);
		else if (sprite->animation() == MOVE_DOWN)
			sprite->changeAnimation(STAND_DOWN);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);
	~TileMap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	/*	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size) const;
		bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size) const;
	*/
private:
	bool loadLevel(const string& levelFile);
	void prepareSheetCoords();
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);

private:
	void Move_block(int pos_ini, int pos_dest);

	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	glm::vec2 sheetCoords[10];
	glm::vec2 MinCoords;
	int* map;
	vector<float> vertices;
	ShaderProgram p;
	int nTiles;

};


#endif // _TILE_MAP_INCLUDE



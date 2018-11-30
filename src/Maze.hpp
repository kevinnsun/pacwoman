/*!
   \file "Maze.hpp"
   \brief "Maze header file"
   \date "28"/"Nov"/"2018"
*/
#ifndef PACWOMAN_MAZE_HPP
#define PACWOMAN_MAZE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

/*!
   \brief "Maze class"
	 \desc "Header to create the map or scene for the game"
*/
class Maze : public sf::Drawable
{
	public:

	Maze(sf::Texture& texture); //maze texture
	void loadLevel(std::string name); //load level

	sf::Vector2i getPacWomanPosition() const; //positon of pacwoman
	std::vector<sf::Vector2i> getGhostPositions() const; //ghostposition based on vector

	inline std::size_t positionToIndex(sf::Vector2i position) const; //position to index for arrry
	inline sf::Vector2i indexToPosition(std::size_t index) const; // index to position

	sf::Vector2i mapPixelToCell(sf::Vector2f pixel) const; //sends png pixel to cell on map
	sf::Vector2f mapCellToPixel(sf::Vector2i cell) const;

	bool isWall(sf::Vector2i position) const; //checks if wall
	bool isDot(sf::Vector2i position) const; //checks if dot
	bool isSuperDot(sf::Vector2i position) const; // checks if superdot
	void pickObject(sf::Vector2i position); //eat dots

	bool isBonus(sf::Vector2i position) const;

	sf::Vector2i getSize() const; //get size

	int getRemainingDots() const; //remaining dots

	private:
	//private variables
	enum CellData
	{
		Empty,
		Wall,
		Dot,
		SuperDot,
		Bonus
	};

/*!
   \brief "Draw header"
   \param "sfml rendering states"
*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2i m_mazeSize; //maze size vector
	std::vector<CellData> m_mazeData; //mazedata
	sf::Vector2i m_pacWomanPosition; //pacwoman position
	std::vector<sf::Vector2i> m_ghostPositions; //ghost positions

	sf::RenderTexture m_renderTexture;
	sf::Texture& m_texture;
};

#endif // PACWOMAN_MAZE_HPP

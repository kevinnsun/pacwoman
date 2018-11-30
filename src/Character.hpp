/*!
   \file "Character.hpp"
   \brief "Parent character class for the ghost and pacwoman"
   \date "28th/November/2018"
*/
#ifndef PACWOMAN_CHARACTER_HPP
#define PACWOMAN_CHARACTER_HPP
#include <array>
#include "Maze.hpp"
#include <SFML/Graphics.hpp>

/*!
   \brief "Character Class"
   \pre "Drawable and Transformable SFML object"
*/
class Character : public sf::Drawable, public sf::Transformable
{
	public:
	/*!
	   \brief "Character Constructor"
	   \desc "Create a character Object"
	*/
	Character();
	/*!
	   \brief "update vitual implementation"
	   \param "delta of Time object"
	*/
	virtual void update(sf::Time delta);
	/*!
	   \brief "set the direction of the chracters"
	   \param "direction object"
	*/
	void setDirection(sf::Vector2i direction);
	/*!
	   \brief "get the direction of character"
	   \return "Vector 2D object"
	*/
	sf::Vector2i getDirection() const;
	/*!
	   \brief "set the maze map"
		 \param "maze object"
		 \desc "create the maze map by assigning maze param to local maze attribute"
	*/
	void setMaze(Maze* maze);

	/*!
	   \brief "set the speed"
	   \param "speed: float type"
	*/
	void setSpeed (float speed);
	/*!
	   \brief "getSpeed"
	   \desc "get the speed of character"
	   \return "float"
	*/
	float getSpeed() const;

	/*!
	   \brief "willmove function"
	   \desc "object will move indicator"
	   \return "boolean"
	*/
	bool willMove() const;

	/*!
	   \brief "getCollisionBox"
	   \desc "get the collision outline of the chracter"
	   \return "rectangle float"
	*/
	sf::FloatRect getCollisionBox() const;

	protected:
	/*!
	   \brief "change direction: virtual implementation"
	   \desc "Change the direction of character function"
	*/
	virtual void changeDirection() {};

	private:
	float m_speed; //speed attribute
	Maze* m_maze; //maze object

	sf::Vector2i m_currentDirection; //2D vector of the current direction
	sf::Vector2i m_nextDirection; //2D vector of the next direction of character

	sf::Vector2i m_previousIntersection; //the previous intersection
	std::array<bool, 4> m_availableDirections; //array of the avaiable directions
};

#endif // PACWOMAN_CHARACTER_HPP

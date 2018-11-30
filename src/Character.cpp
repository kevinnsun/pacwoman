#include "Character.hpp"
#include <cmath>

/*!
   \brief "Character Constructor"
   \desc "Create a character Object"
*/
Character::Character()
:m_maze(nullptr) //set the maze null pointer
,m_speed(25.f) //set the default speed of character
,m_currentDirection(1, 0) //set the current direction to moving right
,m_nextDirection(0, 0)
,m_previousIntersection(0, 0)
{
}
/*!
   \brief "getCollisionBox"
   \desc "get the collision outline of the chracter"
   \return "rectangle float"
*/
sf::FloatRect Character::getCollisionBox() const
{
  sf::FloatRect bounds(3, 3, 34, 34);
    return getTransform().transformRect(bounds);
}
/*!
   \brief "set the maze map"
   \param "maze object"
   \desc "create the maze map by assigning maze param to local maze attribute"
*/
void Character::setMaze(Maze* maze)
{
	m_maze = maze;
}

/*!
   \brief "set the speed"
   \param "speed: float type"
*/
void Character::setSpeed(float speed)
{
	m_speed = speed;
}
/*!
   \brief "getSpeed"
   \desc "get the speed of character"
   \return "float"
*/
float Character::getSpeed() const
{
	return m_speed;
}
/*!
   \brief "set the direction of the chracters"
   \param "direction object"
*/
void Character::setDirection(sf::Vector2i direction)
{
	m_nextDirection = direction;
}
/*!
   \brief "get the direction of character"
   \return "Vector 2D object"
*/
sf::Vector2i Character::getDirection() const
{
	return m_currentDirection;
}
/*!
   \brief "willmove function"
   \desc "object will move indicator"
   \return "boolean"
*/
bool Character::willMove() const
{
	return !m_maze->isWall(m_previousIntersection + m_nextDirection);
}
/*!
   \brief "update vitual implementation"
   \param "delta of Time object"
*/
void Character::update(sf::Time delta)
{
  //get the position of the pixels
	sf::Vector2f pixelPosition = getPosition();
  //get the speed of the pixel that is traveled
	float pixelTraveled = getSpeed() * delta.asSeconds();

	sf::Vector2f nextPixelPosition = pixelPosition + sf::Vector2f(m_currentDirection) * pixelTraveled;
	setPosition(nextPixelPosition);

	sf::Vector2i cellPosition = m_maze->mapPixelToCell(pixelPosition);

	sf::Vector2f offset;
	offset.x = std::fmod(pixelPosition.x, 32) - 16;
	offset.y = std::fmod(pixelPosition.y, 32) - 16;

  //if character heads into wall, then the character will have to change directions
	if (m_maze->isWall(cellPosition + m_currentDirection))
	{
		if ((m_currentDirection.x == 1 &&  offset.x > 0) ||
			(m_currentDirection.x == -1 && offset.x < 0) ||
			(m_currentDirection.y == 1 && offset.y > 0) ||
			(m_currentDirection.y == -1 && offset.y < 0))
		{
			setPosition(m_maze->mapCellToPixel(cellPosition));
		}
	}

	if (!m_maze->isWall(cellPosition + m_nextDirection) && m_currentDirection != m_nextDirection)
	{
		if ((!m_currentDirection.y && (offset.x > -2 && offset.x < 2)) ||
			(!m_currentDirection.x && (offset.y > -2 && offset.y < 2)))
		{
      //set the postion of the character based on maze map
			setPosition(m_maze->mapCellToPixel(cellPosition));
			m_currentDirection = m_nextDirection;

      //get the rotational element depending on the direction characters are going
			if (m_currentDirection == sf::Vector2i(1, 0))
            {
                setRotation(0);
                setScale(-1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(0, 1))
            {
                setRotation(90);
                setScale(-1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(-1, 0))
            {
                setRotation(0);
                setScale(1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(0, -1))
            {
                setRotation(90);
                setScale(1, 1);
            }
		}
	}

  //vector directions
	static sf::Vector2i directions[4] = {
        sf::Vector2i(1, 0),
        sf::Vector2i(0, 1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(0, -1)
        };

    if (cellPosition != m_previousIntersection)
    {
      //at an intersection, character can move in different directions
        if ((!m_currentDirection.y  && (offset.x > -2 && offset.x < 2)) ||
            (!m_currentDirection.x  && (offset.y > -2 && offset.y < 2)))
        {
            std::array<bool, 4> availableDirections;

            int i = 0;
            for (auto direction : directions)
            {
                availableDirections[i] = m_maze->isWall(cellPosition + direction);
                i++;
            }

            if (m_availableDirections != availableDirections)
            {

                m_previousIntersection = cellPosition;
                m_availableDirections = availableDirections;

                changeDirection();
            }
        }
    }
}

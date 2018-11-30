#include "Ghost.hpp"
#include <cmath>

/*!
   \brief "Ghost attributes "
	 \desc "Ghost class with a list of attributes that make it unique"
*/
Ghost::Ghost(sf::Texture& texture, PacWoman* pacWoman)
:m_visual(texture)
,m_isWeak(false)
,m_weaknessDuration(sf::Time::Zero)
,m_pacWoman(pacWoman)

{
	setOrigin(20, 20); //set intial position of ghosts

	//m_strongAnimator.addFrame(sf::IntRect(40, 32, 40, 40));
    m_strongAnimator.addFrame(sf::IntRect(80, 32, 40, 40)); //animations for ghosts using png

    m_weakAnimator.addFrame(sf::IntRect(40, 72, 40, 40)); //animations for ghosts using png
    //m_weakAnimator.addFrame(sf::IntRect(80, 72, 40, 40));

    m_strongAnimator.play(sf::seconds(0.25), true); //how fast the animations are working
    m_weakAnimator.play(sf::seconds(1), true);

}

/*!
   \brief "Set weak state"
   \param "Time duration for sfml"
*/
void Ghost::setWeak(sf::Time duration)
{
	m_isWeak =true;
	m_weaknessDuration = duration;
}

/*!
   \brief "is weak method"
   \return "returns weak state"
*/
bool Ghost::isWeak() const
{
	return m_isWeak;
}

/*!
   \brief "draw ghost"
	 \desc "uses draw mechanic to draw ghost"
*/
void Ghost::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_visual, states);
}
/*!
   \brief "update ghost"
	 \desc "method used to update ghost states an animations"
*/
void Ghost::update(sf::Time delta)
{

	if (m_isWeak)//if weak then change animation for a set duration
    {
        m_weaknessDuration -= delta;

        if (m_weaknessDuration <= sf::Time::Zero)
        {
            m_isWeak = false;
            m_strongAnimator.play(sf::seconds(0.25), true);
        }
    }

    if (!m_isWeak)
    {
        m_strongAnimator.update(delta);
        m_strongAnimator.animate(m_visual);
    }
    else
    {
        m_weakAnimator.update(delta);
        m_weakAnimator.animate(m_visual);
    }

    Character::update(delta);
}

/*!
   \brief "direction change for ghost"
	 \desc "changes animation and sprite according to direction that user inputs"
*/
void Ghost::changeDirection()
{
	//directional movements
	static sf::Vector2i directions[4] = {
        sf::Vector2i(1, 0),
        sf::Vector2i(0, 1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(0, -1)
        };

	std::map<float, sf::Vector2i> directionProb;

	float targetAngle;

	sf::Vector2f distance = m_pacWoman->getPosition() - getPosition();

	targetAngle = std::atan2(distance.x, distance.y) * (180/3.14);

	//change angles according to direction
	for (auto direction : directions)
	{
		float directionAngle = std::atan2(direction.x, direction.y) * (180/3.14);

		//Normalize the angle difference
		float diff = 180 - std::abs(std::abs(directionAngle - targetAngle) - 180);

		directionProb[diff] = direction;
	}
	setDirection(directionProb.begin()->second);

	auto it = directionProb.begin();

	do
	{
		setDirection(it->second);
		it++;
	}
	while(!willMove());
}

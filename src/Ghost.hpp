/*!
   \file "Ghost.hpp"
   \brief "Ghost header file"
   \date "28"/"Nov"/"2018"
*/
#ifndef PACWOMAN_GHOST_HPP
#define PACWOMAN_GHOST_HPP

#include "Animator.hpp"
#include "PacWoman.hpp"
#include "Character.hpp"

/*!
   \brief "Ghost class"
   \desc "Ghost class with public variables, multiple public states"
*/
class Ghost : public Character
{
	public:

	//different ghost states
	enum State
	{
		Strong,
		Weak
	};

	public:
/*!
	   \brief "ghost constructor"
	   \param "sfml texture for PacWoman"
*/
	Ghost(sf::Texture& texture, PacWoman* pacWoman);

	void setWeak(sf::Time duration); //ghost weak condition times
	bool isWeak() const; //ghost weak condition

	void update(sf::Time delta); //update time

	protected:
	void changeDirection(); //direction change

	private:
/*!
   \brief "draw constructor"
   \desc "use to draw differst states for ghosts"
*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isWeak; //boolean for weak state
	sf::Time m_weaknessDuration;// duration of weak state

	sf::Sprite m_visual; //picture for ghost 
	PacWoman* m_pacWoman;

	Animator m_strongAnimator;
	Animator m_weakAnimator;
};
#endif // PACWOMAN_GHOST_HPP

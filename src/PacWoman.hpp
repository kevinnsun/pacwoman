/*!
   \file "PacWoman.hpp"
   \brief "PacWoman header file"
   \date "28"/"Nov"/"2018"
*/
#ifndef PACWOMAN_PACWOMAN_HPP
#define PACWOMAN_PACWOMAN_HPP

#include "Animator.hpp"
#include "Character.hpp"

//PacWoman class
class PacWoman : public Character

{
	public:
/*!
   \brief "Pacwoman public header"
   \param "sfml texture"
*/
	PacWoman(sf::Texture& texture);
	void die(); //pacwoman death

	bool isDying() const; //isdying pacwoman
	bool isDead() const; //isdead pacwoman

	void update(sf::Time delta);  //update time

	void reset();	//reset pacwoman

	private:
/*!
   \brief "draw function"
   \desc "draw pacwoman using rendering states"
*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isDying;
	bool m_isDead;
	sf::Sprite m_visual;

	Animator m_runAnimator;
	Animator m_dieAnimator;
};

#endif // PACWOMAN_PACWOMAN_HPP

#ifndef PACWOMAN_GHOST_HPP
#define PACWOMAN_GHOST_HPP

#include "Animator.hpp"
#include "PacWoman.hpp"
#include "Character.hpp"

class Ghost : public Character
{
	public:

	enum State
	{
		Strong, //when the ghost can kill pacwoman
		Weak //when pacwoman can kill the ghost
	};

	public:
	Ghost(sf::Texture& texture);

	void setWeak(sf::Time duration);
	bool isWeak() const;

	void update(sf::Time delta);


	private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isWeak;
	sf::Time m_weaknessDuration;

	sf::Sprite m_visual;
	PacWoman* m_pacWoman;

	Animator m_strongAnimator;
	Animator m_weakAnimator;
};
#endif // PACWOMAN_GHOST_HPP

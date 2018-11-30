#include "PacWoman.hpp"
#include <iostream>

/*!
   \brief "PacWoman"
   \param "sfml texture"
*/
PacWoman::PacWoman(sf::Texture& texture)
: m_visual(texture)
, m_isDying(false)
, m_isDead(false)
{
	setOrigin(20, 20);

	//runs animations based on the png file pixels
	m_runAnimator.addFrame(sf::IntRect(0, 32, 40, 40));
    m_runAnimator.addFrame(sf::IntRect(0, 72, 40, 40));

    m_dieAnimator.addFrame(sf::IntRect(0, 32, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(0, 72, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(0, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(40, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(80, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(120, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(160, 112, 40, 40));

    m_runAnimator.play(sf::seconds(0.25), true);
}

/*!
   \brief "Pacwoman death"
   \desc " death animation play time for pacwoman"
*/
void PacWoman::die()
{
	if (!m_isDying)
	{
		m_dieAnimator.play(sf::seconds(1), false);
		m_isDying = true;
	}
}
/*!
   \brief "Pacwoman reset"
   \desc " rest animation play time for pacwoman after death"
*/
void PacWoman::reset()
{
	m_isDying = false;
	m_isDead = false;

	m_runAnimator.play(sf::seconds(0.25), true);
	m_runAnimator.animate(m_visual);
}
/*!
   \brief "Pacwoman death"
   \return "dying state for pacwoman"
*/
bool PacWoman::isDying() const
{
	return m_isDying;
}

/*!
   \brief "Pacwoman death"
   \desc " death animation play time for pacwoman"
*/
bool PacWoman::isDead() const
{
	return m_isDead;
}
/*!
   \brief "draw method for pacwoman "
   \desc "visual for pacwoman"
*/
void PacWoman::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (!m_isDead)
	target.draw(m_visual, states);
}

/*!
   \brief "update for pacwoman"
   \param "sf time"
*/
void PacWoman::update(sf::Time delta)
{
    if (!m_isDead && !m_isDying)
    {
        m_runAnimator.update(delta); //animation time
        m_runAnimator.animate(m_visual); //animation visual
    }
    else
    {
        m_dieAnimator.update(delta); 
        m_dieAnimator.animate(m_visual);

        if (!m_dieAnimator.isPlaying())
        {
            m_isDying = false;
            m_isDead = true;
        }
    }
    Character::update(delta);
}

/*!
   \file "Animator.hpp"
   \brief "Animator class - handles game animations"
   \date "28/November/2018"
*/
#ifndef PACWOMAN_ANIMATOR_HPP
#define PACWOMAN_ANIMATOR_HPP

#include <SFML/Graphics.hpp>

/*!
   \brief "Animator Class"
   \desc "times animations for the sprites in the game"
*/
class Animator
{

public: //public methods
    Animator();

    void addFrame(sf::IntRect frame);
    void play(sf::Time duration, bool loop);
    bool isPlaying() const;
    void update(sf::Time delta);
    void animate(sf::Sprite& sprite);


private: //private attributes
    std::vector<sf::IntRect> m_frames;
    bool m_isPlaying;
    sf::Time m_duration;
    bool m_loop;

    unsigned int m_currentFrame;
};

#endif // PACWOMAN_ANIMATOR_HPP

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
    /*!
       \brief "Add a new frame to the animation"
       \param "frame of type IntRect"
    */
    void addFrame(sf::IntRect frame);
    /*!
       \brief "Play animation"
       \param "duration time, and the loop boolean"
    */
    void play(sf::Time duration, bool loop);
    /*!
       \brief "Isplaying function to determin if the game state is in playing mode"
       \return "true or false"
    */
    bool isPlaying() const;
    /*!
       \brief "Update animation based on time"
       \param "dealta of type Time from SFML"
       \pre "User must be in playing mode"
    */
    void update(sf::Time delta);
    /*!
       \brief "animate function to animate the sprite"
       \param "sprite of type Sprite"
       \return "void"
    */
    void animate(sf::Sprite& sprite);


private: //private attributes
    std::vector<sf::IntRect> m_frames; // animation frames
    bool m_isPlaying;
    sf::Time m_duration; //duration of animation
    bool m_loop; //animation loop

    unsigned int m_currentFrame; //curent frame
};

#endif // PACWOMAN_ANIMATOR_HPP

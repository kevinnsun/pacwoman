#include "Animator.hpp"

/*!
   \brief "Animator Constructor"
   \init "set the isplay to false"
   \init "set the current frame to 0"
   \init "set the duration to time zero"
   \init "set the loop to false"
*/
Animator::Animator()
: m_currentFrame(0)
, m_isPlaying(false)
, m_duration(sf::Time::Zero)
, m_loop(false)
{
}

/*!
   \brief "Add a new frame to the animation"
   \param "frame of type IntRect"
*/
void Animator::addFrame(sf::IntRect frame)
{
    m_frames.push_back(frame);
}
/*!
   \brief "Play animation"
   \param "duration time, and the loop boolean"
*/
void Animator::play(sf::Time duration, bool loop)
{
    m_isPlaying = true;
    m_duration = duration;
    m_loop = loop;
}
/*!
   \brief "Isplaying function to determin if the game state is in playing mode"
   \return "true or false"
*/
bool Animator::isPlaying() const
{
    return m_isPlaying;
}

/*!
   \brief "Update animation based on time"
   \param "dealta of type Time from SFML"
   \pre "User must be in playing mode"
*/
void Animator::update(sf::Time delta)
{
    if (!isPlaying())
        return;

    static sf::Time timeBuffer = sf::Time::Zero;
    timeBuffer += delta;

    sf::Time frameDuration = m_duration / static_cast<float>(m_frames.size());

    while (timeBuffer > frameDuration)
    {
        m_currentFrame++;

        if (m_currentFrame == m_frames.size())
        {
            if (!m_loop)
                m_isPlaying = false;

            m_currentFrame = 0;
        }

        timeBuffer -= frameDuration;
    }
}

/*!
   \brief "animate function to animate the sprite"
   \param "sprite of type Sprite"
   \return "void"
*/
void Animator::animate(sf::Sprite& sprite)
{
    sprite.setTextureRect(m_frames[m_currentFrame]);
}

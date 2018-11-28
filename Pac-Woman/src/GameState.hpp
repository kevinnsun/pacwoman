#ifndef PACWOMAN_GAMESTATE_HPP
#define PACWOMAN_GAMESTATE_HPP

#include "PacWoman.hpp"
#include "Ghost.hpp"
#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
  enum State{
    NoCoin,
    GetReady,
    Playing,
    Won,
    Lost,
    Count
  };

  GameState(Game* game);
  Game* getGame() const;

  virtual void insertCoin()=0;
  virtual void pressButton()=0;
  virtual void moveStick(sf::Vector2i direction)=0;
  virtual void update(sf::Time delta)=0;
  virtual void draw(sf::RenderWindow& window)=0;

private:
  Game* m_game;
};

//the no coins state
class NoCoinState : public GameState
{
public:
  NoCoinState(Game* game);

  void insertCoin();
  void pressButton();
  void moveStick(sf::Vector2i direction);
  void update(sf::Time delta);
  void draw(sf::RenderWindow& window);

private:
  sf::Text m_text;
  sf::Sprite m_sprite;

  bool m_displayText;
};

//the get ready state
class GetReadyState : public GameState
{
public:
  GetReadyState(Game* game);

  void insertCoin();
  void pressButton();
  void moveStick(sf::Vector2i direction);
  void update(sf::Time delta);
  void draw(sf::RenderWindow& window);

private:
  sf::Text m_text;
  sf::Sprite m_sprite;
};

class PlayingState : public GameState
{
public:
  PlayingState(Game* game);

  void insertCoin();
  void pressButton();
  void moveStick(sf::Vector2i direction);
  void update(sf::Time delta);
  void draw(sf::RenderWindow& window);

private:
  PacWoman m_pacWoman;
  Ghost m_ghost;
};

class WonState : public GameState
{
public:
  WonState(Game* game);

  void insertCoin();
  void pressButton();
  void moveStick(sf::Vector2i direction);
  void update(sf::Time delta);
  void draw(sf::RenderWindow& window);

private:
  sf::Text m_text;
};

class LostState : public GameState
{
public:
  LostState(Game* game);

  void insertCoin();
  void pressButton();
  void moveStick(sf::Vector2i direction);
  void update(sf::Time delta);
  void draw(sf::RenderWindow& window);

private:
  sf::Text m_text;
  sf::Time m_countdown;
  sf::Text m_countdownText;
};

#endif // PACWOMAN_GAMESTATE_HPP

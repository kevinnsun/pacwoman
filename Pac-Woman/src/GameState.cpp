#include "GameState.hpp"
#include "Game.hpp"

template <typename T>
void centerOrigin(T& drawable){
  sf::FloatRect bound = drawable.getLocalBounds();
  drawable.setOrigin(bound.width/2, bound.height/2);
}

GameState::GameState(Game* game)
:m_game(game)
{
}
//nocoin state constructor
NoCoinState::NoCoinState(Game* game)
:GameState(game)
{
  m_sprite.setTexture(game->getLogo());
  m_sprite.setPosition(20, 50);

  m_text.setFont(game->getFont());
  m_text.setString("Insert Coin");

  centerOrigin(m_text);
  m_text.setPosition(240,150);

  m_displayText = true;
}

GetReadyState::GetReadyState(Game* game)
:GameState(game)
{
  m_sprite.setTexture(game->getLogo());
  m_sprite.setPosition(20, 50);

  m_text.setFont(game->getFont());
  m_text.setString("Press Start(S) when you ready");
  m_text.setCharacterSize(14);

  centerOrigin(m_text);
  m_text.setPosition(240,240);
}

PlayingState::PlayingState(Game* game)
:GameState(game)
{
}

WonState::WonState(Game* game)
:GameState(game)
{
}

LostState::LostState(Game* game)
:GameState(game)
{
}


Game* GameState::getGame() const
{
  return m_game;
}

void NoCoinState::insertCoin(){
  getGame()->changeGameState(GameState::GetReady);
}

void NoCoinState::pressButton(){

}

void NoCoinState::moveStick(sf::Vector2i direction){

}

void NoCoinState::update(sf::Time delta){
  static sf::Time timeBuffer = sf::Time::Zero;
  timeBuffer += delta;

  while(timeBuffer >= sf::seconds(0.5)){
    m_displayText = !m_displayText;
    timeBuffer -= sf::seconds(1);
  }
}

void NoCoinState::draw(sf::RenderWindow& window){
  window.draw(m_sprite);

  if(m_displayText){
    window.draw(m_text);
  }
}

void GetReadyState::insertCoin(){

}

void GetReadyState::pressButton(){
  getGame()->changeGameState(GameState::Playing);
}

void GetReadyState::moveStick(sf::Vector2i direction){

}

void GetReadyState::update(sf::Time delta){

}

void GetReadyState::draw(sf::RenderWindow& window){
  window.draw(m_sprite);
  window.draw(m_text);
}

void PlayingState::insertCoin(){

}

void PlayingState::pressButton(){
  getGame()->changeGameState(GameState::Playing);


}

void PlayingState::moveStick(sf::Vector2i direction){

}

void PlayingState::update(sf::Time delta){

}

void PlayingState::draw(sf::RenderWindow& window){

}

void WonState::insertCoin(){

}

void WonState::pressButton(){

}

void WonState::moveStick(sf::Vector2i direction){

}

void WonState::update(sf::Time delta){

}

void WonState::draw(sf::RenderWindow& window){

}

void LostState::insertCoin(){

}

void LostState::pressButton(){

}

void LostState::moveStick(sf::Vector2i direction){

}

void LostState::update(sf::Time delta){

}

void LostState::draw(sf::RenderWindow& window){

}

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
  m_text.setString("Welcome! Press I to continue");

  centerOrigin(m_text);
  m_text.setPosition(240,150);

  m_displayText = true;
}

//ready state constructor
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
,m_pacWoman(game->getTexture())
,m_ghost(game->getTexture())
{
  m_pacWoman.move(100,100);
  m_ghost.move(200,200);
}

//won state constructor
WonState::WonState(Game* game)
:GameState(game)
{
  //create font for winning page
  m_text.setFont(game->getFont());
  m_text.setString("You Win!");
  m_text.setCharacterSize(40);

  centerOrigin(m_text);
  m_text.setPosition(240,240);
}

//lost state constructor
LostState::LostState(Game* game)
:GameState(game)
{
  m_text.setFont(game->getFont());
  m_text.setString("Game Over.");
  m_text.setCharacterSize(40);

  centerOrigin(m_text);
  m_text.setPosition(240,240);

  m_countdownText.setFont(game->getFont());
  m_countdownText.setCharacterSize(12);

  centerOrigin(m_countdownText);
  m_countdownText.setPosition(240,280);
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
  if(direction.x == -1){
    getGame()->changeGameState(GameState::Lost);
  }
  else if(direction.x == 1){
    getGame()->changeGameState(GameState::Won);
  }
}

void GetReadyState::update(sf::Time delta){

}

void GetReadyState::draw(sf::RenderWindow& window){
  window.draw(m_sprite);
  window.draw(m_text);
}

void PlayingState::insertCoin(){
  m_pacWoman.die();
}

void PlayingState::pressButton(){
  m_ghost.setWeak(sf::seconds(3));
}

void PlayingState::moveStick(sf::Vector2i direction){

}

void PlayingState::update(sf::Time delta){
  m_pacWoman.update(delta);
	m_ghost.update(delta);
}

void PlayingState::draw(sf::RenderWindow& window){
  window.draw(m_pacWoman);
  window.draw(m_ghost);
}

void WonState::insertCoin(){

}

void WonState::pressButton(){

}

void WonState::moveStick(sf::Vector2i direction){

}

void WonState::update(sf::Time delta){
  static sf::Time timeBuffer = sf::Time::Zero;
  timeBuffer += delta;

  if(timeBuffer.asSeconds()>5){
    getGame()->changeGameState(GameState::GetReady);
  }
}

void WonState::draw(sf::RenderWindow& window){
  window.draw(m_text);
}

void LostState::insertCoin(){
  getGame()->changeGameState(GameState::GetReady);
}

void LostState::pressButton(){

}

void LostState::moveStick(sf::Vector2i direction){

}

void LostState::update(sf::Time delta){
    m_countdown += delta;

    if(m_countdown.asSeconds() >= 10){
      getGame()->changeGameState(GameState::NoCoin);
    }

    m_countdownText.setString("Press I to continue: " + std::to_string(10 - static_cast<int>(m_countdown.asSeconds())));
}

void LostState::draw(sf::RenderWindow& window){
  window.draw(m_text);
  window.draw(m_countdownText);
}

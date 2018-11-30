#include "Game.hpp"
#include <iostream>

Game::Game()
:m_window(sf::VideoMode(480, 500), "3307 PacWoman") //set the window size and the window title
{
	// load the font from assets. If error then return runtime error
	if (!m_font.loadFromFile("assets/font.ttf")){
		throw std::runtime_error("Unable to load the font file");
	}
	// load the logo from assets. If error then return runtime error
	if (!m_logo.loadFromFile("assets/logo.png")){
		throw std::runtime_error("Unable to load the logo file");
	}
	// load the texture from assets. If error then return runtime error
	if (!m_texture.loadFromFile("assets/texture.png")){
		throw std::runtime_error("Unable to load the texture file");
	}

	//game state labels: NoCoin, Playing, getReady, Lost, Won
		m_gameStates[GameState::NoCoin] = new NoCoinState(this);
		m_gameStates[GameState::Playing] = new PlayingState(this);
		m_gameStates[GameState::GetReady] = new GetReadyState(this, m_gameStates[GameState::Playing]);
		m_gameStates[GameState::Lost] = new LostState(this, m_gameStates[GameState::Playing]);
		m_gameStates[GameState::Won] = new WonState(this, m_gameStates[GameState::Playing]);
		//init window with nocoin game state
		changeGameState(GameState::NoCoin);
}

/*!
   \brief "Game Constructor"
*/
Game::~Game()
{
	for (GameState* gameState : m_gameStates){
		delete gameState;
	}

}

/*!
   \brief "Game: run"
   \return "void"
*/
void Game::run()
{
	//create a clock variable
	sf::Clock frameClock;
	//open a window to display the game
	while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
					//if the event is a close event the exit program
          if (event.type == sf::Event::Closed)
                m_window.close();

					//event key listener for any KeyPressed
          if (event.type == sf::Event::KeyPressed)
          {
						//I key will call the current states insert coin function
						 if (event.key.code == sf::Keyboard::I)
						 		m_currentState->insertCoin();
						//S key will call the current states pressbutton function
						 if (event.key.code == sf::Keyboard::S)
						 		m_currentState->pressButton();
						//use the arrow keys will call the respective current states movestick function
						 if (event.key.code == sf::Keyboard::Left)
						 		m_currentState->moveStick(sf::Vector2i(-1, 0));
						 if (event.key.code == sf::Keyboard::Right)
						 		m_currentState->moveStick(sf::Vector2i(1, 0));
						 if (event.key.code == sf::Keyboard::Up)
						 		m_currentState->moveStick(sf::Vector2i(0, -1));
						 if (event.key.code == sf::Keyboard::Down)
						 		m_currentState->moveStick(sf::Vector2i(0, 1));
					 }

        }
				//update the current state based on the clock speed
        m_currentState->update(frameClock.restart());
				m_window.clear();
				//draw the elements to the window based on the current state's draw function
				//display the elements
				m_currentState->draw(m_window);
        m_window.display();
    }
}

/*!
   \brief "general gamestate function: Change the game state"
   \param "gamestate of type gamestate"
   \return "void"
*/
void Game::changeGameState(GameState::State gameState)
{
	   m_currentState = m_gameStates[gameState];
}

/*!
   \brief "Get Font"
   \return "Font type"
*/
sf::Font& Game::getFont()
{
	return m_font;
}

/*!
   \brief "Get logo"
   \return "Logo type - png"
*/
sf::Texture& Game::getLogo()
{
	return m_logo;
}

/*!
   \brief "Get texture"
   \return "texture of sf::texture type"
*/
sf::Texture& Game::getTexture()
{
	return m_texture;
}

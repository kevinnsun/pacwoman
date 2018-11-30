/*!
   \file "Game.hpp"
   \brief "Game class"
   \date "28th/November/2018"
*/
#ifndef PACWOMAN_GAME_HPP
#define PACWOMAN_GAME_HPP

#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <array>

/*!
   \brief "Game Class"
   \desc " the entry point to our program; called from main.cpp"
*/
class Game
{
	public:
	/*!
	   \brief "game construtor and destructor"
	*/
	Game();
	~Game();

	/*!
	   \brief "run the game command"
	*/
	void run();

	/*!
	   \brief "getFont"
	   \return "Font Type"
	*/
	sf::Font& getFont();
	/*!
	   \brief "getLogo"
	   \return "Logo Type"
	*/
	sf::Texture& getLogo();
	/*!
	   \brief "getTexture"
	   \return "Texture Type"
	*/
	sf::Texture& getTexture();

	/*!
	   \brief "change the game state"
	   \param "new game state"
	*/
	void changeGameState(GameState::State gameState);

	private:
	sf::RenderWindow m_window; //render window
	GameState* m_currentState; //current state
	std::array<GameState*, GameState::Count> m_gameStates; //array of game states

	sf::Font m_font; //font for the game
	sf::Texture m_logo; //game logo
	sf::Texture m_texture; //game texture
};

#endif //PACWOMAN_GAME_HPP

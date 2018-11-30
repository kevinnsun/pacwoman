/*!
   \file "GameState.hpp"
   \brief "Game state class header"
   \date "28th/November/2018"
*/
#ifndef PACWOMAN_GAMESTATE_HPP
#define PACWOMAN_GAMESTATE_HPP

#include "Maze.hpp"
#include "PacWoman.hpp"
#include "Ghost.hpp"
#include <SFML/Graphics.hpp>
class Game;

/*!
   \brief "Game State class"
   \desc "The game states navigation"
*/
class GameState
{
	public:
	//enumeration of game states
	enum State
	{
		NoCoin,
		GetReady,
		Playing,
		Won,
		Lost,
		Count
	};
	/*!
	   \brief "Game state constructor"
	   \param "Game  object"
	*/
	GameState (Game* game);
	Game* getGame() const;

	/*!
	   \brief "insert coin virtual function"
	*/
	virtual void insertCoin()=0;
	/*!
	   \brief "vitual implementation for press button"
	*/
	virtual void pressButton()=0;
	/*!
	   \brief "vitual implementation for movestick"
	*/
	virtual void moveStick(sf::Vector2i direction)=0;
	/*!
	   \brief "vitual implementation for update"
	*/
	virtual void update(sf::Time delta)=0;
	/*!
	   \brief "vitual implementation for draw"
	*/
	virtual void draw(sf::RenderWindow& window)=0;

	private:
			Game* m_game;
};

/*!
   \brief "Nocoin state Class"
   \param "Param description"
   \pre "Pre-conditions"
   \post "Post-conditions"
   \return "Return of the function"
*/
class NoCoinState : public GameState
{
public:
	/*!
	   \brief "No coin state construtor"
	   \param "Game object"
	   \desc "create the no coin game state"
	*/
	NoCoinState (Game* game);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

	private:
	sf::Text m_text;
	sf::Sprite m_sprite;

	bool m_displayText;
};

class GetReadyState : public GameState
{
public:

	GetReadyState (Game* game, GameState* playingState);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

	private:
	sf::Text m_text;
	GameState* m_playingState;

};

class PlayingState : public GameState
{
public:

	PlayingState (Game* game);
	~PlayingState();

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

	void loadNextLevel();
	void resetToZero();
	void resetCurrentLevel();
	void resetLiveCount();

	void moveCharactersToInitialPosition();
	void updateCameraPosition();

	private:
	PacWoman* m_pacWoman;
	std::vector<Ghost*> m_ghosts;
	//Ghost m_ghost;
	Maze m_maze;

	sf::View m_camera;
	sf::RenderTexture m_scene;

	sf::Text m_scoreText;
	sf::Text m_levelText;
	sf::Text m_remainingDotsText;
	sf::Sprite m_liveSprite[3];

	int m_level;
	int m_liveCount;
	int m_score;
};

class LostState : public GameState
{
public:

	LostState (Game* game, GameState* playingState);

	/*!
	   \brief "Key Commands for all the loststate game state"
	   \desc "These are the functions that are the key commands for the Loststate"
	*/
	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

	private:
	sf::Text m_text;
	sf::Time m_countDown;
	sf::Text m_countDownText;

	PlayingState* m_playingState;
};

class WonState : public GameState
{
public:

	WonState (Game* game, GameState* playingState);

	/*!
	   \brief "Key Commands for all the wonstate game state"
	   \desc "These are the functions that are the key commands for the wonstate"
	*/
	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

	private:
	sf::Text m_text;

	PlayingState* m_playingState;
};

# endif // PACWOMAN_GAMESTATE_HPP

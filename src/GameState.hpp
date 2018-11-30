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
			Game* m_game; // game object
};

/*!
   \brief "Nocoin state Class"
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
	sf::Text m_text; //text
	sf::Sprite m_sprite; //sprite of logo

	bool m_displayText; //display text: true or false, this used to implement flashing text
};

/*!
   \brief "getReady state Class"
*/
class GetReadyState : public GameState
{
public:
	/*!
	   \brief "GetReadyState Constructor"
		 \desc "prompt user to get ready and click S to begin game"
	   \param "game ojbect and playing state"
	*/
	GetReadyState (Game* game, GameState* playingState);
	/*!
	   \brief "Key Commands for all the get ready state game state"
	   \desc "These are the functions that are the key commands for the get ready state"
	*/
	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

	private:
	sf::Text m_text; //the text for the get ready state
	GameState* m_playingState; //next game state to be loaded

};

/*!
   \brief "Playing State Class"
*/
class PlayingState : public GameState
{
public:
	/*!
	   \brief "Playing State construtor and destructor"
	   \param "game object"
	*/
	PlayingState (Game* game);
	~PlayingState();
	/*!
	   \brief "Key Commands for all the playing state game state"
	   \desc "These are the functions that are the key commands for the playing state"
	*/
	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	void update(sf::Time Delta);
	void draw(sf::RenderWindow& window);

	/*!
	   \brief "load the next level"
	   \desc "after user completes level, load the next level"
	*/
	void loadNextLevel();
	/*!
		 \brief "reset to zero"
		 \desc "rest all the stats to zero"
	*/
	void resetToZero();
	/*!
	   \brief "reset the current level"
	   \desc "after user dies, then reset the current level"
	*/
	void resetCurrentLevel();
	/*!
	   \brief "reset lives count"
	   \desc "after the pacwoman dies completely, reset the number of lives back to zero"
	*/
	void resetLiveCount();

	/*!
	   \brief "Move characters back to original position"
	   \desc "once game begins or pacwoman dies, then reset characters to original position"
	*/
	void moveCharactersToInitialPosition();
	/*!
	   \brief "update camera position"
	   \param "As pacwoman moves thru the maze, update the sceen based on her movements"
	*/
	void updateCameraPosition();

	private:
	PacWoman* m_pacWoman; //pacwoman
	std::vector<Ghost*> m_ghosts; //ghosts
	//Ghost m_ghost;
	Maze m_maze; //maze object

	sf::View m_camera; //camera object
	sf::RenderTexture m_scene; //scene object

	sf::Text m_scoreText; //score text
	sf::Text m_levelText; //level text
	sf::Text m_remainingDotsText; //remaining dots
	sf::Sprite m_liveSprite[3]; //lives sprite

	int m_level; // level count
	int m_liveCount; // lives count
	int m_score; //score count
};

/*!
   \brief "Lost State Class"
*/
class LostState : public GameState
{
public:

	/*!
	   \brief "lost state construtor"
	   \param "Game object, playing state object"
	*/
	LostState (Game* game, GameState* playingState);
	/*!
	   \brief "Lost state, insertCoin"
	   \desc "when the user loses, reset the current level and reset the lives count"
	*/
	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	/*!
	   \brief "update on the lost state"
	   \desc "update the lost state"
	*/
	void update(sf::Time Delta);
	/*!
	   \brief "Lost state draw method"
	   \desc "draw the texts "you lost and perform the countdown!""
	*/
	void draw(sf::RenderWindow& window);

	private:
	sf::Text m_text; //text for lost state
	sf::Time m_countDown; //time for countdown
	sf::Text m_countDownText; //text for countdown

	PlayingState* m_playingState;
};

/*!
   \brief "Won State Class"
*/
class WonState : public GameState
{
public:
	/*!
	   \brief "Wonstate construtor"
	   \param "game and playing state object"
	*/
	WonState (Game* game, GameState* playingState);

	void insertCoin();
	void pressButton();
	void moveStick(sf::Vector2i direction);
	/*!
	   \brief "update in the won state"
	   \param "delta of sfml Time"
	*/
	void update(sf::Time Delta);
	/*!
	   \brief "Won state draw function"
		 \param "the window to be drawn to"
	   \desc "draw the texts "you won!""
	*/
	void draw(sf::RenderWindow& window);

	private:
	sf::Text m_text; //text for the won state: "you won"
	PlayingState* m_playingState; //next playing state to be loaded
};

# endif // PACWOMAN_GAMESTATE_HPP

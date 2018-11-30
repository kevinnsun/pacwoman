#include "GameState.hpp"
#include "Game.hpp"
#include <cmath>
#include <iostream>

/*!
   \brief "center Origins: template to center the text"
   \param "drawable object"
*/
template <typename T>
void centerOrigin(T& drawable)
{
	sf::FloatRect bound = drawable.getLocalBounds();
	drawable.setOrigin(bound.width/2, bound.height/2);
}

/*!
   \brief "GameState Constructor"
*/
GameState::GameState(Game* game)
:m_game(game)
{
}

/*!
   \brief "NoCoinState Constructor"
	 \desc "create the logo display and texts for the intialization state"
   \param "Game object"
*/
NoCoinState::NoCoinState(Game* game)
:GameState(game)
{
	// get the the logo from the game object and set the position
	m_sprite.setTexture(game->getLogo());
	m_sprite.setPosition(20, 50);

	//get the front from the game object and create the string
	m_text.setFont(game->getFont());
	m_text.setString("Press I to Begin!");
	//set the position of the string
	centerOrigin(m_text);
	m_text.setPosition(240, 180);
	m_displayText = true;
}

/*!
   \brief "GetReadyState Constructor"
	 \desc "prompt user to get ready and click S to begin game"
   \param "game ojbect and playing state"
*/
GetReadyState::GetReadyState(Game* game, GameState* playingState)
:GameState(game)
,m_playingState(playingState)
{
	//get the font from the game object
	m_text.setFont(game->getFont());
	m_text.setString("Press S when you're ready...");
	m_text.setCharacterSize(14);

	//set the position of the text
	centerOrigin(m_text);
	m_text.setPosition(240, 240);
}

/*!
   \brief "PlayingState Constructor"
   \param "game object"
*/
PlayingState::PlayingState(Game* game)
:GameState(game)
, m_maze(game->getTexture()) //set the texture of the maze
, m_pacWoman(nullptr)
, m_level(0) //set the level to 0
, m_liveCount(3) //set the lives count to 3
, m_score(0) //set the score to 0
{
	//get pacwoman texture, set the maze, and set pacwoman position
	m_pacWoman = new PacWoman(game->getTexture());
	m_pacWoman->setMaze(&m_maze);
	m_pacWoman->setPosition(m_maze.mapCellToPixel(m_maze.getPacWomanPosition()));
	resetToZero();

	//set the camera size to 480x480 pixels and create a scene the size of the camera
	m_camera.setSize(sf::Vector2f(480, 480));
	m_scene.create(480, 480);

	//set the fonts, font size, and font position for the score
	m_scoreText.setFont(game->getFont());
	m_scoreText.setCharacterSize(10);
	m_scoreText.setPosition(10, 480);
	//set the fonts, font size, and font position for the level display
	m_levelText.setFont(game->getFont());
	m_levelText.setCharacterSize(10);
	m_levelText.setPosition(160, 480);
	//set the fonts, font size, and font position for the remaining dots display
	m_remainingDotsText.setFont(game->getFont());
	m_remainingDotsText.setCharacterSize(10);
	m_remainingDotsText.setPosition(280, 480);

	for (auto& liveSprite : m_liveSprite)
	{
		liveSprite.setTexture(game->getTexture());
		liveSprite.setTextureRect(sf::IntRect(122, 0, 20, 20));
	}

	//set the starting positions of all characters
	m_liveSprite[0].setPosition(sf::Vector2f(415, 480));
	m_liveSprite[1].setPosition(sf::Vector2f(435, 480));
	m_liveSprite[2].setPosition(sf::Vector2f(455, 480));
}

/*!
   \brief "Playing state: loading next level"
	 \desc "load the levels and all of it's elements"
   \return "void"
*/
void PlayingState::loadNextLevel()
{
	//load the small level
	m_maze.loadLevel("small");
	m_level++;

	int mapLevel = m_level % 2;
	int speedLevel = std::floor(m_level / 3);

	// Load map level of small and medium
	if (mapLevel == 0)
		m_maze.loadLevel("small");
	else if (mapLevel == 1)
		m_maze.loadLevel("medium");

	// Destroy previous characters
	for (Ghost* ghost : m_ghosts)
			delete ghost;

		m_ghosts.clear();

	// Create new characters
	for (auto ghostPosition : m_maze.getGhostPositions())
	{
		Ghost* ghost = new Ghost(getGame()->getTexture(), m_pacWoman);
		ghost->setMaze(&m_maze);
		//ghost->setPosition(m_maze.mapCellToPixel(ghostPosition));

		m_ghosts.push_back(ghost);
	}

	// Change speed according to the new level
	float speed = 100 + (speedLevel * 50);

	m_pacWoman->setSpeed(speed+25);

	for (auto& ghost : m_ghosts)
			ghost->setSpeed(speed);

	moveCharactersToInitialPosition();

	//Update level text
	m_levelText.setString("level " + std::to_string(speedLevel) + " - " + std::to_string(mapLevel+1));

}

/*!
   \brief "PlayingState - move characters to intial position function"
   \return "void"
*/
void PlayingState::moveCharactersToInitialPosition()
{
	m_pacWoman->setPosition(m_maze.mapCellToPixel(m_maze.getPacWomanPosition()));

    auto ghostPositions = m_maze.getGhostPositions();
    for (unsigned int i = 0; i < m_ghosts.size(); i++)
        m_ghosts[i]->setPosition(m_maze.mapCellToPixel(ghostPositions[i]));

    updateCameraPosition();
}

/*!
   \brief "Update the camera position"
   \return "void"
*/
void PlayingState::updateCameraPosition()
{
	m_camera.setCenter(m_pacWoman->getPosition());

	if (m_camera.getCenter().x < 240)
		m_camera.setCenter(240, m_camera.getCenter().y);
	if (m_camera.getCenter().y < 240)
		m_camera.setCenter(m_camera.getCenter().x, 240);

	if (m_camera.getCenter().x > m_maze.getSize().x *32 - 240)
		m_camera.setCenter(m_maze.getSize().x *32 - 240, m_camera.getCenter().y);

	if (m_camera.getCenter().y > m_maze.getSize().y *32 - 240)
		m_camera.setCenter(m_camera.getCenter().x, m_maze.getSize().y *32 - 240);

}

/*!
   \brief "Playing state constructor"
   \pre "the game was in get ready state and after user presses S, it loads playing state"
*/
PlayingState::~PlayingState()
{
	delete m_pacWoman;
	
	for (Ghost* ghost : m_ghosts)
		delete ghost;
}

/*!
   \brief "WonState constructor"
   \param "Takes in the game object and the playing state"
	 \desc "create the texts and the timer for the won page"
*/
WonState::WonState(Game* game, GameState* playingState) :GameState(game), m_playingState(static_cast<PlayingState*>(playingState))
{
	//set the font and the strong and center the text
	m_text.setFont(game->getFont());
	m_text.setString("You Won!");
	m_text.setCharacterSize(42);

	centerOrigin(m_text);
	m_text.setPosition(240, 120);
}

/*!
   \brief "LostState constructor"
   \param "Game object and playing state"
	 \desc "create the texts and the timer for the lost page"
*/
LostState::LostState(Game* game, GameState* playingState) :GameState(game), m_playingState(static_cast<PlayingState*>(playingState))
{
	//set the font and the strong and center the text
	m_text.setFont(game->getFont());
	m_text.setString("You lost!");
	m_text.setCharacterSize(42);

	centerOrigin(m_text);
	m_text.setPosition(240, 120);

	//set the font for the countdown text and the size
	m_countDownText.setFont(game->getFont());
	m_countDownText.setCharacterSize(12);
	//center the countdown text
	centerOrigin(m_countDownText);
	m_countDownText.setPosition(100, 240);
}
/*!
   \brief "get the game"
   \desc "helper functio to get the game oject"
*/
Game* GameState::getGame() const
{
	return m_game;
}

/*!
   \brief "insert coin"
	 \desc "once the player clicks I in the nocoinstate, then change the game state to get ready"
*/
void NoCoinState::insertCoin()
{
	getGame()->changeGameState(GameState::GetReady);
}
void NoCoinState::pressButton()
{

}
void NoCoinState::moveStick(sf::Vector2i direction)
{

}

/*!
   \brief "Nocoin state update function"
   \param "dealt in type Time"
   \desc "in the initalize state, the text will flash"
   \return "void"
*/
void NoCoinState::update(sf::Time delta)
{
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;

	while (timeBuffer >= sf::seconds(0.5))
	{
		m_displayText = !m_displayText;
		timeBuffer -= sf::seconds(1);
	}
}
/*!
   \brief "Description"
   \param "Param description"
   \pre "Pre-conditions"
   \post "Post-conditions"
   \return "Return of the function"
*/
void NoCoinState::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);

	if (m_displayText)
	window.draw(m_text);
}

void GetReadyState::insertCoin()
{

}
/*!
   \brief "Description"
   \param "Param description"
   \pre "Pre-conditions"
   \post "Post-conditions"
   \return "Return of the function"
*/
void GetReadyState::pressButton()
{
	getGame()->changeGameState(GameState::Playing);
}
/*!
   \brief "Description"
   \param "Param description"
   \pre "Pre-conditions"
   \post "Post-conditions"
   \return "Return of the function"
*/
void GetReadyState::moveStick(sf::Vector2i direction)
{
	if (direction.x == -1)
		getGame()->changeGameState(GameState::Lost);
	else if (direction.x == 1)
		getGame()->changeGameState(GameState::Won);
}
/*!
   \brief "Description"
   \param "Param description"
   \pre "Pre-conditions"
   \post "Post-conditions"
   \return "Return of the function"
*/
void GetReadyState::update(sf::Time delta)
{
	m_playingState->update(delta);
}
/*!
   \brief "Description"
   \param "Param description"
   \pre "Pre-conditions"
   \post "Post-conditions"
   \return "Return of the function"
*/
void GetReadyState::draw(sf::RenderWindow& window)
{
	m_playingState->draw(window);
	window.draw(m_text);
}

void PlayingState::insertCoin()
{
	//m_pacWoman.die();
}
void PlayingState::pressButton()
{
	//m_ghost.setWeak(sf::seconds(3));
}
void PlayingState::moveStick(sf::Vector2i direction)
{
	m_pacWoman->setDirection(direction);
}
/*!
   \brief "reset stats to zero"
*/
void PlayingState::resetToZero()
{
	resetLiveCount();

	m_level = 0;
	resetCurrentLevel();

	m_score = 0;
}
/*!
   \brief "reset the current level"
*/
void PlayingState::resetCurrentLevel()
{
	//decrement level attribute and load the next level
	m_level--;
	loadNextLevel();
}
/*!
   \brief "reset the number of pacwoman lives"
*/
void PlayingState::resetLiveCount()
{
	m_liveCount = 3;
}
/*!
   \brief "Update playing state"
   \desc "update pacwoman's position and ghost positions and coins"
*/
void PlayingState::update(sf::Time delta)
{
	//update pacwoman sprite
	m_pacWoman->update(delta);
	//for all the ghosts update the ghost sprite
	for (Ghost* ghost : m_ghosts)
		ghost->update(delta);

	//get the pacwoman position
	sf::Vector2f pixelPosition = m_pacWoman->getPosition();
	//offset the position
	sf::Vector2f offset(std::fmod(pixelPosition.x, 32), std::fmod(pixelPosition.y, 32));
	offset -= sf::Vector2f(16, 16);

	if (offset.x <= 2 && offset.x >= -2 && offset.y <= 2 && offset.y >= -2)
	{
		sf::Vector2i cellPosition = m_maze.mapPixelToCell(pixelPosition);
		if (m_maze.isDot(cellPosition))
		{
			m_score += 5;
		}
		else if (m_maze.isSuperDot(cellPosition))
		{
			for (Ghost* ghost : m_ghosts)
				ghost->setWeak(sf::seconds(5));

				m_score += 25;
		}

		m_maze.pickObject(cellPosition);
	}

	//for every ghost object, execute ghost logic
	for (Ghost* ghost : m_ghosts)
	{
		//if the ghost collision box hits pacwoman
		if (ghost->getCollisionBox().intersects(m_pacWoman->getCollisionBox()))
		{
			//if the ghost is weak then kill ghost
			if (ghost->isWeak())
			{
				m_ghosts.erase(std::find(m_ghosts.begin(), m_ghosts.end(), ghost));
				//add 100 to the score
				m_score += 100;
			}
			//if the ghost is strong then pacwoman dies
			else
				m_pacWoman->die();
		}
	}

	//if pacwoman is dead the reset pacwoman to her initial position and delete a life
	if (m_pacWoman->isDead())
	{
		m_pacWoman->reset();
		m_liveCount--;

		//if pacwoman runs of out lives then display the game state
		if (m_liveCount < 1)
		    getGame()->changeGameState(GameState::Lost);
		else
			//otherwise move the characters into the inital position
		    moveCharactersToInitialPosition();
	}

	//if there is not remaining dots, player wins
	if (m_maze.getRemainingDots() == 0)
	{
		//change game state
		getGame()->changeGameState(GameState::Won);
	}

	//update the camera position
	updateCameraPosition();

	// Update score text and remaining dots
	m_scoreText.setString(std::to_string(m_score) + " points");
	m_remainingDotsText.setString(std::to_string(m_maze.getRemainingDots()) + "x dots");
}

/*!
   \brief "draw function for playing state"
   \param "intakes the window object"
*/
void PlayingState::draw(sf::RenderWindow& window)
{
	//clear the scene
	m_scene.clear();
	//set the view adjusted to camera
	m_scene.setView(m_camera);
	//draw the loaded maze sprite
	m_scene.draw(m_maze);
	//draw the loaded pacwoman sprite
	m_scene.draw(*m_pacWoman);

	//for every ghost, draw the loaded ghost sprite
	for (Ghost* ghost : m_ghosts)
	m_scene.draw(*ghost);

	m_scene.display();

	//draw the texture of the scene
	window.draw(sf::Sprite(m_scene.getTexture()));

	//draw the score
	window.draw(m_scoreText);
	//draw the level
	window.draw(m_levelText);
	//draw the remaining dots
	window.draw(m_remainingDotsText);

	//draw the number of lives that pacwoman still has
	for (unsigned int i=0; i < m_liveCount; i++)
		window.draw(m_liveSprite[i]);
}

void WonState::insertCoin()
{

}
void WonState::pressButton()
{

}
void WonState::moveStick(sf::Vector2i direction)
{

}

/*!
   \brief "update in the won state"
   \param "delta of sfml Time"
   \return "void"
*/
void WonState::update(sf::Time delta)
{
	//create a timebuffer
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;

	//set the time buffer to be more that 5 seconds
	if (timeBuffer.asSeconds() > 5)
	{
		//after 5 seconds of the won message, load the next level
		m_playingState->loadNextLevel();
		//change the game state to get ready
		getGame()->changeGameState(GameState::GetReady);
	}
}

/*!
   \brief "Won state draw function"
   \desc "draw the texts "you won!""
*/
void WonState::draw(sf::RenderWindow& window)
{
	//display the texts
	window.draw(m_text);
}

/*!
   \brief "Lost state, insertCoin"
   \desc "when the user loses, reset the current level and reset the lives count"
*/
void LostState::insertCoin()
{
	//if user has lost, the reset the current level and reset the lives
	m_playingState->resetCurrentLevel();
	m_playingState->resetLiveCount();
	//change the game state to get ready
	getGame()->changeGameState(GameState::GetReady);
}

void LostState::pressButton()
{

}
void LostState::moveStick(sf::Vector2i direction)
{

}
/*!
   \brief "update on the lost state"
   \desc "update the lost state"
*/
void LostState::update(sf::Time delta)
{
	m_countDown += delta;

	//update the countdown from 10 seconds
	if (m_countDown.asSeconds() >= 10)
	{
		m_playingState->resetToZero();
		//once the countdown hits zero then change the current game state back to get ready state
		getGame()->changeGameState(GameState::GetReady);
	}
	//perform count down method with the continue to play text
	m_countDownText.setString("Insert a coin to continue... " + std::to_string(10- static_cast<int>(m_countDown.asSeconds())));

}
/*!
   \brief "Lost state draw method"
   \desc "draw the texts "you lost and perform the countdown!""
*/
void LostState::draw(sf::RenderWindow& window)
{
	//display the text and the countdown text
	window.draw(m_text);
  window.draw(m_countDownText);
}

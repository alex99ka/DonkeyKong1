#pragma once
#include "Board.h"
#include "Item.h"
#include <vector>
class CGame
{
public: 
	enum MenuDecision { GAME_START, GAME_END, RETURN_TO_MENU };
	MenuDecision Start();
	void PrintGoodbye();
private:
	enum NeighboorType {NONE, BARREL, DONKEYKONG, PRINCESS };
	enum LiveStatus { DEAD, ALIVE, WON };
	enum ScreenType {MAIN_MENU, PAUSE_MENU};
	static constexpr int ESC_KEY = 27; //ASCII code for esc
	static constexpr int MARIO_LIVES = 3;
	static constexpr char AVATAR_MARIO = '@';
	static constexpr char AVATAR_BARREL = 'O';
	static constexpr char AVATAR_DONKEYKONG = '&';
	static constexpr char AVATAR_PRINCESS = '$';
	static constexpr int NUM_OF_BARRELS = 7;
	static constexpr int SLEEP_TIME = 100;

	void PrintMenu(bool IsColored);
	MenuDecision GetMenuDecision();
	void PrintInstructions(ScreenType type); // fix and add cls
	void Init();
	void StartGame();
	void PrintCongratulation();
	MenuDecision Paused();
	void PrintPauseMenu();
	NeighboorType WhoSomeoneNextToMe(CPoint& point);
	MenuDecision PlayLoop();
	LiveStatus PlayerCheckNextCell(CMovingItem& character);
	void FallCharacter(CMovingItem& character);
	void ResetCharacter();
	void EraseCharacter(CMovingItem& character);
	CGame::LiveStatus MovePlayer(CMovingItem& character, CPoint& newPos);
	void GameOverScreen();
	bool m_IsColored = true;
	CMovingItem m_mario;
	CItem m_donkeykong;
	std::vector<CMovingItem> m_barrels;
	CBoard m_board;
};







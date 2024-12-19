#include<iostream>
#include<windows.h> // sleep and other stuff
#include <conio.h> // For _kbhit() and _getch and go to 
#include "game.h"
#include "ColorPoint.h"
#include "utils.h"


CGame::MenuDecision CGame::Start()
{
	PrintMenu(true);
	if (GetMenuDecision() == GAME_END)
		return GAME_END;
	clrscr();
	StartGame();
	return PlayLoop();
}

void CGame::PrintMenu(bool isColored)
{
	clrscr();

	CColoredPrint::prl("Hello, guy!\n");
	CColoredPrint::prl("Welcome to Donkey Kong game\n", CColorPoint::c_color::BLUE, CColorPoint::c_decoration::BOLD);
	CColoredPrint::prl("Please select one of the follwing options : ", CColorPoint::c_color::CYAN, CColorPoint::c_decoration::BOLD);

	CColoredPrint::prl("1 - Start a new game", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	if (isColored)
		CColoredPrint::prl("2 - Turn off color", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	else
		CColoredPrint::prl("2 - Turn on color", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	CColoredPrint::prl("8 - Present instructions and keys", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	CColoredPrint::prl("9 - exit", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
}

CGame::MenuDecision CGame:: GetMenuDecision()
{
	char choice;
	bool color = true;

	while (true)
	{
		if (_kbhit())
		{
		 choice = _getch();
		 switch (choice)
		 {
		 case '1':
			 this->m_IsColored = color;
			 return  CGame::GAME_START;
		 case '2':
			 color = !color; // toggle 
			 PrintMenu(color);
			 break;
		 case '8':
			 PrintInstructions(MAIN_MENU);
			 break;
		 case '9':
			 return CGame::GAME_END;
	
			default:
				cout << "your choice is not legal input"<< endl;
		 }
		}
	}
	return GAME_END;
}

void CGame::PrintInstructions(ScreenType type)
{
	clrscr();
	CColoredPrint::prl("\nGame instructions and keys\n", m_IsColored ? CColoredPrint::c_color::YELLOW : CColoredPrint::c_color::WHITE);
	CColoredPrint::prl("When the game starts, Mario(the hero) is positioned at his start position without any movement.");
	CColoredPrint::prl("Once you selects move direction(using the keys, as listed below)");
	CColoredPrint::prl("Mario will continue to move in this direction even if the user does not press any key");
	CColoredPrint::prl("as long as game board boundaries are not reached and the STAY key is not pressed.");
	CColoredPrint::prl("KEYS :", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, m_IsColored ? CColoredPrint::c_decoration::BLINK : CColoredPrint::c_decoration::NORMAL);
	CColoredPrint::pr("LEFT :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("a or A", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("RIGHT :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("d or D", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("UP / JUMP :		", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("w or W", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("DOWN :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("x or X", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("STAY :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("s or S", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::prl("\nPausing a game:", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::UNDERLINE);
	CColoredPrint::prl("Pressing the ESC key during a game pauses the game.");
	CColoredPrint::prl("When the game is at pause state, pressing ESC again would continue the game");
	CColoredPrint::prl("\nExit a game:", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::UNDERLINE);
	CColoredPrint::prl("You can exit the game via the Pause menu");
	CColoredPrint::prl("\nYou need to defeat Donkey Kong in order to save the Princess",m_IsColored? CColoredPrint::c_color::BLUE : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::UNDERLINE);


	while (true)
	{
		if (_kbhit())
		{
			char clean = _getch(); // trash input to clean the buffer 
			if (type == PAUSE_MENU) // ASCII code for ESC key
			{
				clrscr();
				PrintPauseMenu();
				return;
			}
			else
			{
				clrscr();
				PrintMenu(true);
				return;
			}
		}
	}
}


void CGame::PrintGoodbye()
{
	clrscr();
	CColoredPrint::prl("Goodbye, friend!\n", CColoredPrint::c_color::CYAN);
}

void CGame::StartGame()
{
	Init();
	m_board.Draw(m_IsColored);
}

void CGame::Init()
{
	m_board.Init();
	m_mario = CMovingItem(2, m_board.GetBorderHight() - 2, AVATAR_MARIO, m_IsColored ? CColorPoint::c_color::GREEN : CColorPoint::c_color::WHITE); // reset mario to the bottom 
	m_mario.SetLives(MARIO_LIVES);
	m_donkeykong = CItem(m_board.GetBorderWidth()/2,2, AVATAR_DONKEYKONG, m_IsColored ? CColorPoint::c_color::CYAN : CColorPoint::c_color::WHITE);
	m_DonkeyIsDead = false;
}
void CGame::ResetCharacter()
{
	EraseCharacter(m_mario);
	m_mario.SetX(2);
	m_mario.SetY(m_board.GetBorderHight() - 2);
	m_mario.ReduceLife();
	m_mario.ResetFalls();
	m_mario.SetDirection(CMovingItem::STOP);
	if (m_DonkeyIsDead)
		m_princess.Draw();
}


CGame:: MenuDecision CGame::PlayLoop()
{
	bool Mario(true), Italian(true); // mario will never be israeli, he is not jewish. 
	bool OnLadder(false);
	char input, prevchioce = '\0';
	int curr_lives = 0;

	hideCursor();
	m_mario.Draw();
	m_donkeykong.Draw();
	while (Mario = Italian) // a joke, eqaul to true because mario and italian will never change
	{
		if (_kbhit())
		{ // add an if statment that checks the prev input from player
			input = _getch();
			{
				if (prevchioce != input)
				{
					switch (input)
					{
					case 'a':
					case 'A':
						m_mario.SetDirection(CMovingItem::LEFT);
						break;
					case 'd':
					case 'D':
						m_mario.SetDirection(CMovingItem::RIGHT);
						break;
					case 'w':
					case 'W':
						m_mario.SetDirection(CMovingItem::UP);
						break;
					case 'x':
					case 'X':
						m_mario.SetDirection(CMovingItem::DOWN);
						break;
					case 's':
					case 'S':
						m_mario.SetDirection(CMovingItem::STOP);
						break;
					case ESC_KEY:
					{
						if (Paused() == GAME_END)
							return RETURN_TO_MENU;
						break;
					}
					default:
						// ignore illegal input
						break;
					}
				}
			}
		} 

		switch(PlayerCheckNextCell(m_mario))
		{
		case DEAD:
			ResetCharacter();
			if (m_mario.GetLives() == 0)
			{
				GameOverScreen();
				return RETURN_TO_MENU;
			}
			clrscr();
			m_board.Draw(m_IsColored);
			m_mario.Draw();
			m_donkeykong.Draw();
			DrawHearts();
			break;
		case WON:
			PrintCongratulation();
			return RETURN_TO_MENU;
		case ALIVE:
			break;
		} 

		if (curr_lives != MARIO_LIVES)
			DrawHearts(curr_lives);

		std::cout.flush(); 
		Sleep(SLEEP_TIME);
	}
	return RETURN_TO_MENU; // the game will never reach this line. this line only to remove the error 
}

CGame::MenuDecision CGame::Paused()
{
	bool flag(true);
	char choice, prevchioce= '\0';
	

	clrscr();
	PrintPauseMenu();

	while (flag)
	{
		if (_kbhit())
		{
			choice = _getch();
			if (prevchioce != choice)
			{
				switch (choice)
				{
					case ESC_KEY:
					{
						clrscr();
						m_board.Draw(m_IsColored);
						m_donkeykong.Draw();
						DrawHearts();
						if(m_DonkeyIsDead)
							m_princess.Draw();
						return GAME_START; // just continue the game
					}
					case '1':
					{
						clrscr();
						PrintInstructions(PAUSE_MENU);
						break;
					}
					case '2':
					{
						PrintGoodbye();
						return GAME_END;
					}
				}
			}
		}
	}
	return GAME_START;
}

void CGame::PrintPauseMenu() 
{
	const char* PauseMenu[] = {
		"********************************************************************************",
		"*                                                                              *",
		"*                               GAME PAUSED                                    *",
		"*                                                                              *",
		"********************************************************************************",
		"*                                                                              *",
		"*                            [ESC] Resume Game                                 *",
		"*                                                                              *",
		"*                            [1] Instructions                                  *",
		"*                                                                              *",
		"*                            [2] Quit Game                                     *",
		"*                                                                              *",
		"********************************************************************************",
		"*                                                                              *",
		"*                   Use the indicated keys to make your selection              *",
		"*                                                                              *",
		"********************************************************************************"
	};

	for (const char* line : PauseMenu) {
		std::cout << line << std::endl;
	}
}

void CGame::EraseCharacter(CMovingItem& character)
{
	char symbol;
	CColorPoint::c_color color;

	m_board.GetBoardCh(character, &symbol, &color);
	if (m_IsColored == false)
		color = CColorPoint::WHITE;
	character.SeRestoreSymbol(symbol, color);
	character.Erase();
}

CGame::NeighboorType CGame::WhoSomeoneNextToMe(CPoint& point)
{
	if (m_donkeykong.Compare(point))
		return DONKEYKONG;
	if (m_DonkeyIsDead)
	{
		if (m_princess.Compare(point))
			return PRINCESS;
	}

	for (CMovingItem& barrel : m_barrels) {
		if (barrel.Compare(point))
			return BARREL;
	}
	
	return NONE;
}

CGame::LiveStatus CGame::MovePlayer(CMovingItem& character, CPoint& newPos)
{

	CGame::NeighboorType neigboorType;

	neigboorType = WhoSomeoneNextToMe(newPos);
	switch (neigboorType)
	{
	case NONE:
		if (character.IsStop() == false) {
			EraseCharacter(character);
		}
		break;
	case BARREL:
		return DEAD;
	case DONKEYKONG:
		m_donkeykong.ChangeColor(m_IsColored ? CColorPoint:: RED : CColorPoint::BLACK);
		if (m_DonkeyIsDead == false)
			CreatePrincess();
		m_DonkeyIsDead = true;
		EraseCharacter(character);
		break;
	case PRINCESS:
		return WON;
	}

	m_donkeykong.Draw();
	character.SetX(newPos.GetX());
	character.SetY(newPos.GetY());
	character.Draw();

	return ALIVE;
}

void CGame::FallCharacter(CMovingItem& character)
{
	character.SetDirection(CMovingItem::DOWN); //fall
	character.Falling();
}
// checks what in cell next to the direction of the player
CGame::LiveStatus CGame::PlayerCheckNextCell(CMovingItem& character)
{
	enum CBoard::Board_Place place = m_board.GetBoardPlace(character);
	CMovingItem::Directions direction = character.GetDirection();
	CPoint newPos;

	if (place == CBoard::Board_Place::LADDER && direction == CMovingItem::UP)
		newPos.SetCoord(character.GetX(), character.GetY() - 1);
	else 
		newPos.SetCoord(character.GetX() + character.GetXDirection(), character.GetY() + character.GetYDirection());

	enum CBoard::Board_Place nextPlace  = m_board.GetBoardPlace(newPos);
	
	switch (nextPlace) {
	case CBoard::Board_Place::BOARDER:
	case CBoard::Board_Place::FLOOR:
		if (direction == CMovingItem::UP) {
			newPos.SetCoord(character.GetX(), character.GetY() - 1);
			nextPlace = m_board.GetBoardPlace(newPos);
			if (nextPlace == CBoard::Board_Place::FREE) {
				FallCharacter(character);
				return MovePlayer(character, newPos);
			}
		}
		if (direction == CMovingItem::DOWN)
			character.ResetFalls();
		character.SetDirection(CMovingItem::STOP);
		break;
	case CBoard::Board_Place::LADDER:
		return MovePlayer(character, newPos);
		break;
	case CBoard::Board_Place::FREE:
	{
		if (place == CBoard::Board_Place::LADDER) {
			if (direction == CMovingItem::LEFT || direction == CMovingItem::RIGHT) {
				CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
				enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
				if (downPlace == CBoard::Board_Place::FREE)
					character.SetDirection(CMovingItem::STOP);
				else
					return MovePlayer(character, newPos);
			}
			else if (direction == CMovingItem::UP) {
				MovePlayer(character, newPos);
				character.SetDirection(CMovingItem::STOP);
				break;
			}
			else
				return MovePlayer(character, newPos);
		} // current place is FREE
		else if (direction == CMovingItem::LEFT || direction == CMovingItem::RIGHT) {
			CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
			enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
			if (downPlace == CBoard::Board_Place::FREE) {
				FallCharacter(character);
			}
			return MovePlayer(character, newPos);
		}
		else {
			if (direction == CMovingItem::DOWN) {
				int nFalls = character.GetFallCounter();
				if (nFalls == character.GetMaxFall())
					return DEAD;
				if (nFalls > 0) {
					character.Falling();
					return MovePlayer(character, newPos);
				}
			}
			else if (direction == CMovingItem::UP) { //   JUMPING
				// we should check directions cell
				CPoint UpPos(character.GetX(), character.GetY() - 1);
				CPoint UpUpPos(character.GetX(), character.GetY() - 2);
				enum CBoard::Board_Place UpPlace = m_board.GetBoardPlace(UpPos);
				enum CBoard::Board_Place UpUpPlace = m_board.GetBoardPlace(UpUpPos);
				if (UpPlace == CBoard::Board_Place::FREE && UpUpPlace == CBoard::Board_Place::FREE) {
					if (newPos.Compare(UpUpPos)) { // Jump UP only
						FallCharacter(character);
					}
					else {
						CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
						enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
						if (downPlace == CBoard::Board_Place::FREE) {
							FallCharacter(character);
						}
						else {
							int xDir = character.GetXDirection();
							if (xDir == 1) character.SetDirection(CMovingItem::RIGHT);
							if (xDir == -1) character.SetDirection(CMovingItem::LEFT);
						}
					}
					return MovePlayer(character, newPos);
				}

			}
			character.SetDirection(CMovingItem::STOP);
		}

		break;
	}
	default:
		break;

	}
	return ALIVE;
}

void CGame::PrintCongratulation()
{
	clrscr();
	/*if (m_IsColored)
	{
		CColoredPrint::prl("Congratinatio!!!!", CColoredPrint::c_color::YELLOW, CColoredPrint::c_decoration::BLINK);
		CColoredPrint::prl("You Won !!!", CColoredPrint::c_color::YELLOW, CColoredPrint::c_decoration::BLINK);
	}
	else
	{
		CColoredPrint::prl("Congratinatio!!!!");
		CColoredPrint::prl(" PRESS ANY KEY TO RETURN");
	}
	Sleep(1500);
	CColoredPrint::prl(" PRESS ANY KEY TO RETURN"); */
	

		CColoredPrint::prl("         _                                  _                       ");
		CColoredPrint::prl("__      _(_)_ __  _ __   ___ _ __  __      _(_)_ __  _ __   ___ _ __ ");
		CColoredPrint::prl("\\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__| \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__|");
		CColoredPrint::prl(" \\ V  V /| | | | | | | |  __/ |     \\ V  V /| | | | | | | |  __/ |   ");
		CColoredPrint::prl("  \\_/\\_/ |_|_| |_|_|_|_|\\___|_|      \\_/\\_/_|_|_| |_|_| |_|\\___|_|   ");
		CColoredPrint::prl("   ___| |__ (_) ___| | _____ _ __     __| (_)_ __  _ __   ___ _ __   ");
		CColoredPrint::prl("  / __| '_ \\| |/ __| |/ / _ \\ '_ \\   / _` | | '_ \\| '_ \\ / _ \\ '__|  ");
		CColoredPrint::prl(" | (__| | | | | (__|   <  __/ | | | | (_| | | | | | | | |  __/ |     ");
		CColoredPrint::prl("  \\___|_| |_|_|\\___|_|\\_\\___|_| |_|  \\__,_|_|_| |_|_| |_\\___|_|     ");
		CColoredPrint::prl("                                                                      ");
		CColoredPrint::prl("\n\n PRESS ANY KEY TO RETURN");
		while (true)
		{
			if (_kbhit())
				return;
		}

}

void CGame::GameOverScreen()
{
	// Clear the screen
	clrscr();

	// ASCII art for a gravestone with Mario's name
	const char* art[] = {
		"         _______",
		"      .-'       `-.",
		"     /             \\",
		"    /               \\",
		"   |    RIP MARIO    |",
		"   |                 |",
		"   |    1981-2023    |",
		"   |                 |",
		"    \\               /",
		"     \\_____________/",
		"         ||     ||",
		"         ||     ||",
		"      ###############",
		"      #             #",
		"      ###############",
		"",
		"        GAME OVER!",
		"",
		" PRESS ANY KEY TO RETURN"
	};

	Beep(1200, 300);

	// Print the gravestone
	if (m_IsColored) {
		// Print in color
		int cntLine = 0;
		for (const char* line : art) {
			if (cntLine == 16)
				CColoredPrint::prl(line, CColoredPrint::c_color::RED, CColoredPrint::c_decoration::BOLD); // Game Over
			else if (cntLine == 18)
				CColoredPrint::prl(line, CColoredPrint::c_color::YELLOW, CColoredPrint::c_decoration::ITALIC); // Press any key
			else
				CColoredPrint::prl(line, CColoredPrint::c_color::WHITE); // Base
			cntLine++;
		}
	}
	else {
		// Print in black and white
		for (const char* line : art) {
			CColoredPrint::prl(line); // Default black and white
		}
	}

	while (true)
	{
		if (_kbhit())
			return;
	}
}

void CGame::DrawHearts(int& curr_lives)
{
	int i;
	GoToXY(3, 2);
	curr_lives = m_mario.GetLives();
	for (i = 0; i < curr_lives; i++)
	{
			CColoredPrint::pr("<3", m_IsColored? CColoredPrint::c_color::RED : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	}
}

void CGame::DrawHearts()
{
	int i, lives;
	lives = m_mario.GetLives();
	GoToXY(3, 2);
	for (i = 0; i < lives; i++)
		CColoredPrint::pr("<3", m_IsColored ? CColoredPrint::c_color::RED : CColorPoint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
}

void CGame::CreatePrincess()
{
	int princessY = 3, princessX = 66;
	int PlatforSize = 3;
		m_princess = CItem(princessX, princessY, AVATAR_PRINCESS, m_IsColored ? CColorPoint::c_color::MAGENTA : CColorPoint::c_color::WHITE);
		for (int i = -1; i < PlatforSize - 1; i++)
		{
			m_board.UpdateWorkBoard(princessX + i, princessY + 1, FLOOR_SYMB);
			GoToXY(princessX + i, princessY + 1);
			CColoredPrint::pr(FLOOR_SYMB, m_IsColored ? CColorPoint::c_color::YELLOW : CColorPoint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
		}
		m_princess.Draw();
}



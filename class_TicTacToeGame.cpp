// murtada alamir s171649
#include "class_TicTacToeGame.h"
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <time.h> 
#include <ctime>

using namespace std;

namespace casino
{
	ticTacToeGame::ticTacToeGame()
	{
		// Sets a random starting point.
		srand((unsigned)time(0)); 
	}

	void ticTacToeGame::initializeGrid()
	{
		if(cells == NULL) 
		{
			free(cells);
		}

		// Allocate memory
		cells = (int *) malloc(rowsLength * rowsLength * sizeof(int));

		// Initialize the cells with their positions
		for(int i = 0; i < rowsLength * rowsLength; i++)
		{
			cells[i] = i + 1; 
		} 
	}

	void ticTacToeGame::clearScreen()
	{
#ifdef _WIN32
		// Windows OS
		std::system ( "cls" );
#else
		// Assume POSIX
		std::system ( "clear" );
#endif	
	}

	void ticTacToeGame::start()
	{
		int input;
		char again = 'y';
		bool validChoice;

		while (again != 'n' && again != 'N')
		{	
			clearScreen();
			cout << "\t\tWelcome to Tic Tac Toe! Have fun playing!\n\n";

			// Enter number of fields
			do
			{
				cout << "Enter number of fields (min. 3): ";
				cin >> input;
				if(input >= 3)
				{
					rowsLength = input;
					validChoice = true;
				}
				else
				{
					validChoice = false;
				}
			}
			while(!validChoice);

			// Choose the difficulty level
			do
			{
				cout << endl << "Choose the difficulty level (0 for easy, 1 for difficult): ";
				cin >> input;
				if(input == 0 || input == 1)
				{
					difficultyLevel = input;
					validChoice = true;
				}
				else
				{
					validChoice = false;
				}		
			}
			while(!validChoice);

			playRound();

			cout << endl << endl << "Do you want to play again? (Y/N): ";
			cin  >> again;
		}
	}

	void ticTacToeGame::playRound()
	{
		// Terminal player starts playing
		bool isTerminalPlayer = false; 
		int state, choice;

		clearScreen();

		initializeGrid();

		do
		{
			drawGrid();

			isTerminalPlayer = !isTerminalPlayer;

			if(isTerminalPlayer)
			{
				bool validChoice;
				do
				{
					cout << endl << "Enter a number: ";
					cin >> choice;

					if(choice >= 1 && choice <= rowsLength * rowsLength &&
						cells[choice - 1] == choice)
					{
						validChoice = true;
					}
					else
					{
						cout << "Invalid choice";
						validChoice = false;
					}
				}
				while(!validChoice);
			}
			else
			{
				cout << endl << "Waiting for Computer's Player's choice...";
				choice = getComputerPlayerChoice(choice - 1);
				cout << " " << choice;

				// Let the terminal's player see the choice
				long timeout = clock() + 1000;
				while(clock() < timeout) 
				{
					continue;
				}
			}

			// X is the terminal player's mark
			// O is the computer player's mark
			// X -> 0x58, O -> 0x4F
			cells[choice - 1] = isTerminalPlayer ? 0x58: 0x4F; 

			state = getGameState(); 
		} 
		while(state == 3); // Playing until the play is finished

		drawGrid();

		if(state == 1)
		{
			cout << endl;
			cout << (isTerminalPlayer ? "Congratulation! You won" : "Bummer! Computer's player won!");
		}
		else
		{
			cout << endl << "The game was a draw!";
		}
	}

	int ticTacToeGame::getComputerPlayerChoice(int playerChoice)
	{
		// Simulate taking time to make a choice
		long timeout = clock() + 1000;
		while(clock() < timeout) 
		{
			continue;
		}

		// Celver version: Place the mark in any unoccupied cell next to the mark of the player
		// "next to" means to the left of, to the right of, above or below the player's mark
		if(difficultyLevel)
		{
			int choice = -1;
			int random_integer;

			do
			{
				random_integer = 1 + int(8 * rand() / (RAND_MAX + 1.0)); 

				switch (random_integer)
				{
				case 1:
					// Place mark in upper left corner to player's mark
					if(playerChoice - rowsLength - 1 >= 0 && 
						cells[playerChoice - rowsLength - 1] == playerChoice - rowsLength)
					{
						choice = playerChoice - rowsLength; 
					}
					else
					{
						choice = -1;
					}
					break;

				case 2:
					// Place mark above player's mark
					if(playerChoice - rowsLength >= 0 && 
						cells[playerChoice - rowsLength] == playerChoice - rowsLength + 1)
					{
						choice = playerChoice - rowsLength + 1; 
					}
					else
					{
						choice = -1;
					}
					break;

				case 3:
					// Place mark in upper right corner to player's mark
					if(playerChoice - rowsLength + 1 >= 0 && 
						cells[playerChoice - rowsLength + 1] == playerChoice - rowsLength + 2)
					{
						choice = playerChoice - rowsLength + 2; 
					}
					else
					{
						choice = -1;
					}
					break;

				case 4:
					// Place mark to the right of player's mark
					if(playerChoice + 1 < rowsLength * rowsLength && 
						cells[playerChoice + 1] == playerChoice + 2)
					{
						choice = playerChoice + 2; 
					}
					else
					{
						choice = -1;
					}
					break;

				case 5:
					// Place mark in bottom right corner to player's mark
					if(playerChoice + rowsLength + 1 < rowsLength * rowsLength && 
						cells[playerChoice + rowsLength + 1] == playerChoice + rowsLength + 2)
					{
						choice = playerChoice + rowsLength + 2; 
					}
					else
					{
						choice = -1;
					}
					break;

				case 6:
					// Place mark below player's mark
					if(playerChoice + rowsLength < rowsLength * rowsLength && 
						cells[playerChoice + rowsLength] == playerChoice + rowsLength + 1)
					{
						choice = playerChoice + rowsLength + 1; 
					}
					else
					{
						choice = -1;
					}
					break;

				case 7:
					// Place mark in bottom left corner to player's mark
					if(playerChoice + rowsLength - 1 < rowsLength * rowsLength && 
						cells[playerChoice + rowsLength - 1] == playerChoice + rowsLength)
					{
						choice = playerChoice + rowsLength; 
					}
					else
					{
						choice = -1;
					}
					break;

				case 8:
					// Place mark to the left of player's mark
					if(playerChoice - 1 >= 0 && cells[playerChoice - 1] == playerChoice + 1)
					{
						choice = playerChoice + 1; 
					}
					else
					{
						choice = -1;
					}
					break;
				}
			}
			while(choice == -1);

			return choice;
		}
		// Primitive version: Place the mark in any unoccupied cell beginning from the end
		else
		{
			for(int i = rowsLength * rowsLength - 1; i >= 0; i--)
			{
				if(cells[i] == i + 1)
				{
					return i + 1; 
				}
			}
		}
	}



	int ticTacToeGame::getNumberLength(int number)
	{
		int lengthCount = 0;
		for(; number != 0; number /= 10, lengthCount++);
		return lengthCount;
	}

	void ticTacToeGame::drawGrid()
	{
		clearScreen();
		cout << "\t\tWelcome to Tic Tac Toe! Have fun playing!\n\n";
		cout << "Terminal's Player (X)  -  Computer's Player (O)" << endl << endl;
		cout << endl;

		// Get number length to adjust the cell's width
		int maxNumberLength = getNumberLength(rowsLength * rowsLength);

		stringstream noBorder, bottomBorder;

		noBorder << "  ";
		bottomBorder << "__";

		for(int i = 0; i < maxNumberLength; i++)
		{
			noBorder << " ";
			bottomBorder << "_";
		}

		noBorder << "  ";
		bottomBorder << "__";


		for(int row = 0; row < rowsLength; row++)
		{    
			// Print cell's header
			for(int col = 0; col < rowsLength; col++)
			{
				cout << noBorder.str() << (col + 1 < rowsLength ? "|" : "");
			}   
			cout << endl;

			// Print cell's value
			for(int col = 0; col < rowsLength; col++)
			{
				cout << "  ";

				// The cell isn't occupied. So print its position
				if(cells[col + row * rowsLength] == col + row * rowsLength + 1)
				{
					int numberLength = getNumberLength(col + row * rowsLength + 1);
					for(int i = 0; i < maxNumberLength - numberLength; i++)
					{
						cout << " ";
					}

					cout << cells[col + row * rowsLength];
				}
				else
				{
					int numberLength = getNumberLength(1);
					for(int i = 0; i < maxNumberLength - numberLength; i++)
					{
						cout << " ";
					}

					// Print X or O
					cout << (cells[col + row * rowsLength] == 0x58 ? 'X' : 'O'); 
				}

				cout << "  ";
				cout << (col + 1 < rowsLength ? "|" : " ");
			}   
			cout << endl;

			// print cell's footer
			for(int col = 0; col < rowsLength; col++)
			{
				cout << (row + 1 < rowsLength ? bottomBorder.str() : noBorder.str());
				cout << (col + 1 < rowsLength ? "|" : "");
			}   
			cout << endl;
		}
	}

	int ticTacToeGame::getGameState()
	{
		bool won = false;

		for(int row = 0; row < rowsLength; row++)
		{
			// 1. Check the rows vertically
			for(int col = 0; col < rowsLength - 1; col++)
			{
				if (cells[col + row * rowsLength] == cells[col + row * rowsLength + 1])
				{
					won = true;
				}
				else
				{
					won = false;
					break;
				}
			} 

			if(won)
			{
				// A player won
				return 1;
			}


			// 2. Check the rows horizontally
			for(int col = 0 + row; col < row + rowsLength + 1; col = col + rowsLength)
			{
				if (cells[col] == cells[col + rowsLength])
				{
					won = true;
				}
				else
				{
					won = false;
					break;
				}
			} 

			if(won)
			{
				// A player won
				return 1;
			}
		}

		// 3a. Check the rows diagonally from left to right
		for(int row = 0; row < rowsLength * rowsLength - 1; row = row + rowsLength + 1)
		{
			if (cells[row] == cells[row + rowsLength + 1])
			{
				won = true;
			}
			else
			{
				won = false;
				break;
			}
		}

		if(won)
		{
			// A player won
			return 1;
		}

		// 3b. Check the rows diagonally from right to left
		for(int row = rowsLength - 1; row < rowsLength * rowsLength - rowsLength; row = row + rowsLength - 1)
		{
			if (cells[row] == cells[row + rowsLength - 1])
			{
				won = true;
			}
			else
			{
				won = false;
				break;
			}
		}

		if(won)
		{
			// A player won
			return 1;
		}


		// No player won. The game either is a draw or it's not finished yet
		bool isDraw = false;  
		for(int i = 0; i < rowsLength * rowsLength; i++)
		{
			if (cells[i] != i + 1)
			{
				isDraw = true;
			}
			else 
			{
				isDraw = false;
				break; 
			}
		} 

		if(isDraw)
		{
			// Game was a draw
			return 2;
		}
		else
		{
			// Game is not finished yet 
			return 3;
		}
	}
}

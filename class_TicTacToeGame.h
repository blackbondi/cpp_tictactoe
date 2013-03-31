// murtada alamir s171649
#ifndef CLASS_TICTACTOEGAME_H
#define CLASS_TICTACTOEGAME_H


namespace casino
{  
	class ticTacToeGame 
	{
	private:
		// Number of rows respectively columns
		int rowsLength;

		// Difficulty level
		// 0 for easy, 1 for difficult
		int difficultyLevel;

		// Grids's cells
		int *cells;

		/*
		* Utility function to get the length of number e. g. 123 = 3
		*/
		int getNumberLength(int number);

		/*
		* Utility function to clean the console screen
		*/
		void clearScreen();

		/*
		* Initializes the cells with their positions
		*/
		void initializeGrid();
		
		/* 
		* Draws the grid with current game state
		*/
		void drawGrid();

		/* 
		* Retrievs game's state
		* Return value: 
		*	1: Game is over and a player won
		*	2: Game was a draw
		*	3: Game is not finished yet 
		*/
		int getGameState();

		/*
		* Retrievs the computer player choice
		* Return value: The cell's number in the grid
		*/
		int getComputerPlayerChoice(int playerChoice);

	protected:
		void playRound();

	public:
		ticTacToeGame();
		void start();
	};
}

#endif

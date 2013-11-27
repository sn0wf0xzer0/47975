//Data file structure.
//Author: John Palacios

#ifndef VICTORY_H
#define VICTORY_H

struct Victory
{
	int nameLength;			//The number of characters used in player.
	char player[21];		//The name of the victorious player.
	char board[9];			//The board at time of victory.
};

#endif /* VICTORY_H */
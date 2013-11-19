//Basic information pertinant to the player is stored in this struct.
//Author: John Palacios

#include <string>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
	int nameLength;					//The number of characters in playerName.
	string playerName;				//The Name of player ex, player oh, or of the winner.
	char playerToken;				//This is the character used to mark spaces captured.
};

#endif /* PLAYER */
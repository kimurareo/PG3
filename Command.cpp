#include "Command.h"
#include "Player.h"

Command::~Command() {}

void MoveRightCommand::Execute(Player& player)
{
	player.MoveRight();
}

void MoveLeftCommand::Execute(Player& player)
{
	player.MoveLeft();
}
#include "InputHandler.h"
#include <Novice.h>

Command* InputHandler::HandleInput()
{

	if (Novice::CheckHitKey(DIK_A))
	{
		return pressKeyA_;
	}

	if (Novice::CheckHitKey(DIK_D))
	{
		return pressKeyD_;
	}

	return nullptr;
}

void InputHandler::AssignMoveLeftCommand2PressKeyA()
{
	Command* command = new MoveLeftCommand();
	this->pressKeyA_ = command;
}

void InputHandler::AssignMoveRightCommand2PressKeyD()
{
	Command* command = new MoveRightCommand();
	this->pressKeyD_ = command;
}
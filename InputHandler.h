#pragma once
#include "Command.h"

class InputHandler
{
private:

	Command* pressKeyA_;


	Command* pressKeyD_;

public:

	Command* HandleInput();

	
	void AssignMoveLeftCommand2PressKeyA();

	
	void AssignMoveRightCommand2PressKeyD();
};
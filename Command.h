#pragma once
class Player;

class Command
{
public:
	virtual ~Command();
	virtual void Execute(Player& player) = 0;

};
class MoveRightCommand : public Command
{
public:
	void Execute(Player& player) override;

};

class MoveLeftCommand : public Command
{
public:
	void Execute(Player& player) override;
};


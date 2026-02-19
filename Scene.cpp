#include "Scene.h"

void Scene::Initialize()
{
	inputHandler_ = new InputHandler();

	inputHandler_->AssignMoveLeftCommand2PressKeyA();
	inputHandler_->AssignMoveRightCommand2PressKeyD();

	player_ = new Player();
	player_->Initialize();
}

void Scene::Update()
{

	command_ = inputHandler_->HandleInput();

	if (command_)
	{
		command_->Execute(*player_);
	}

	player_->Update();
}

void Scene::Draw()
{
	player_->Draw();
}
#pragma once
#include "../../KamataEngine/DirectXGame/math/Vector2.h"



class Player
{
private:

	
	Vector2 position_;

	
	float speed_ = 2.0f;

public:

	void Initialize();

	void Update();

	void Draw();

	
	void MoveRight();


	void MoveLeft();
};

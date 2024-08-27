#pragma once
class Vector2;

class Vector2F {

public:

	// �f�t�H���g�R���X�g���N�^
	Vector2F();

	// �R���X�g���N�^
	Vector2F(float vX, float vY);

	// �R���X�g���N�^
	Vector2F(Vector2 value);

	float x, y;

	Vector2F operator+(const Vector2F& value);
	Vector2F operator-(const Vector2F& value);

};
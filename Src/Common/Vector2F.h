#pragma once
class Vector2;

//struct Vector2F {
//
//	// �f�t�H���g�R���X�g���N�^
//	Vector2F(void);
//
//	// �R���X�g���N�^
//	Vector2F(float vX, float vY);
//
//	// �R���X�g���N�^
//	Vector2F(Vector2 value);
//
//	float x, y;
//
//};
//
//	Vector2F operator+(const Vector2F& va, const Vector2F vb);
//	Vector2F operator-(const Vector2F& va, const Vector2F vb);

class Vector2F {

public:

	// �f�t�H���g�R���X�g���N�^
	Vector2F(void);

	// �R���X�g���N�^
	Vector2F(float vX, float vY);

	// �R���X�g���N�^
	Vector2F(Vector2 value);

	float x, y;

	Vector2F operator+(const Vector2F& value);
	Vector2F operator-(const Vector2F& value);

};
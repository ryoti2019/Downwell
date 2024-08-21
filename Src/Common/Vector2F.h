#pragma once
class Vector2;

//struct Vector2F {
//
//	// デフォルトコンストラクタ
//	Vector2F(void);
//
//	// コンストラクタ
//	Vector2F(float vX, float vY);
//
//	// コンストラクタ
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

	// デフォルトコンストラクタ
	Vector2F(void);

	// コンストラクタ
	Vector2F(float vX, float vY);

	// コンストラクタ
	Vector2F(Vector2 value);

	float x, y;

	Vector2F operator+(const Vector2F& value);
	Vector2F operator-(const Vector2F& value);

};
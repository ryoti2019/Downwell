#pragma once
class Vector2;

class Vector2F {

public:

	static Vector2F vectorUp;
	static Vector2F vectorDown;
	static Vector2F vectorLeft;
	static Vector2F vectorRight;

public:

	// デフォルトコンストラクタ
	Vector2F();

	// コンストラクタ
	Vector2F(float vX, float vY);


	// コンストラクタ
	Vector2F(Vector2 value);

	float x, y;

	Vector2F operator+(const Vector2F& value) const;
	Vector2F operator+=(const Vector2F& value);
	Vector2F operator-(const Vector2F& value) const;
	Vector2F operator-=(const Vector2F& value);
	Vector2F operator*(const float value) const;
	Vector2F operator/(const float value) const;

	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

};
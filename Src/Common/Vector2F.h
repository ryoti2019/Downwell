#pragma once
class Vector2;

class Vector2F {

public:

	static Vector2F vectorUp;
	static Vector2F vectorDown;
	static Vector2F vectorLeft;
	static Vector2F vectorRight;

public:

	// �f�t�H���g�R���X�g���N�^
	Vector2F();

	// �R���X�g���N�^
	Vector2F(float vX, float vY);


	// �R���X�g���N�^
	Vector2F(Vector2 value);

	float x, y;

	Vector2F operator+(const Vector2F& value) const;
	Vector2F operator+=(const Vector2F& value);
	Vector2F operator-(const Vector2F& value) const;
	Vector2F operator-=(const Vector2F& value);
	Vector2F operator*(const float value) const;
	Vector2F operator/(const float value) const;

	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

};
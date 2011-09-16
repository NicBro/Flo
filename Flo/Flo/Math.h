#include "pch.h"

using namespace std;

class Vec2
{
};

class Vec3
{
};

class Vec4
{
};

class Mat3
{
};

class Mat4
{
};

class Quaternion
{
};

class Transformable
{
public:
	Vec3 pos;
	Quaternion rot;
	Vec3 scale;
	Mat4 matrix;

};
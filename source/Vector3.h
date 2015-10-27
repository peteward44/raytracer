
#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>


template <class T>
class basic_Vector3
{
public:
	typedef basic_Vector3<T> Type;

	T X, Y, Z;


	inline basic_Vector3(T x = 0, T y = 0, T z = 0)
		: X(x), Y(y), Z(z)
	{}


	static inline T Dot(const Type& first, const Type& second)
	{
		return first.X * second.X + first.Y * second.Y + first.Z * second.Z;
	}


	static inline Type Cross(const Type& first, const Type& second)
	{
		Type result;
		result.X = first.Y * second.Z - second.Y * first.Z;
		result.Y = first.Z * second.X - second.Z * first.X;
		result.Z = first.X * second.Y - second.X * first.Y;
		return result;
	}


	static inline Type Subtract(const Type& vec1, const Type& vec2)
	{
		Type result;
		result.X = vec1.X - vec2.X;
		result.Y = vec1.Y - vec2.Y;
		result.Z = vec1.Z - vec2.Z;
		return result;
	}


	static inline Type Subtract(const Type& vec1, T scalar)
	{
		Type result;
		result.X = vec1.X - scalar;
		result.Y = vec1.Y - scalar;
		result.Z = vec1.Z - scalar;
		return result;
	}


	inline Type operator - (const Type& vec1) const
	{
		return Subtract(*this, vec1);
	}


	inline Type& operator -= (const Type& vec1)
	{
		*this = Subtract(*this, vec1);
		return *this;
	}


	inline Type operator - (T scalar) const
	{
		return Subtract(*this, scalar);
	}


	inline Type& operator -= (T scalar)
	{
		*this = Subtract(*this, scalar);
		return *this;
	}


	static inline Type Add(const Type& vec1, const Type& vec2)
	{
		Type result;
		result.X = vec1.X + vec2.X;
		result.Y = vec1.Y + vec2.Y;
		result.Z = vec1.Z + vec2.Z;
		return result;
	}


	static inline Type Add(const Type& vec1, T scalar)
	{
		Type result;
		result.X = vec1.X + scalar;
		result.Y = vec1.Y + scalar;
		result.Z = vec1.Z + scalar;
		return result;
	}


	inline Type operator + (const Type& vec2) const
	{
		return Add(*this, vec2);
	}


	inline Type& operator += (const Type& vec1)
	{
		*this = Add(*this, vec1);
		return *this;
	}


	inline Type operator + (T scalar) const
	{
		return Add(*this, scalar);
	}


	inline Type& operator += (T scalar)
	{
		*this = Add(*this, scalar);
		return *this;
	}


	static inline Type Multiply(const Type& vec1, const Type& vec2)
	{
		Type result;
		result.X = vec1.X * vec2.X;
		result.Y = vec1.Y * vec2.Y;
		result.Z = vec1.Z * vec2.Z;
		return result;
	}


	static inline Type Multiply(const Type& vec1, T scalar)
	{
		Type result;
		result.X = vec1.X * scalar;
		result.Y = vec1.Y * scalar;
		result.Z = vec1.Z * scalar;
		return result;
	}


	inline Type operator * (const Type& vec1) const
	{
		return Multiply(*this, vec1);
	}


	inline Type& operator *= (const Type& vec1)
	{
		*this = Multiply(*this, vec1);
		return *this;
	}


	inline Type operator * (T scalar) const
	{
		return Multiply(*this, scalar);
	}


	inline Type& operator *= (T scalar)
	{
		*this = Multiply(*this, scalar);
		return *this;
	}


	static inline Type Normalize(const Type& first)
	{
		float a = first.Length();
		Type result;
		result.X = first.X / a;
		result.Y = first.Y / a;
		result.Z = first.Z / a;
		return result;
	}


	inline void Normalize()
	{
		*this = Normalize(*this);
	}


	inline T Length() const
	{
		return (T)sqrt((T)LengthSq());
	}


	inline T LengthSq() const
	{
		return X * X + Y * Y + Z * Z;
	}
};


typedef basic_Vector3< float > Vector3;


#endif


#pragma once
#include "Core/BasicType.h"

#include "Math/Angle.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"
#include "Math/Geometry.h"


#include <limits>
#include <cmath>

template <typename T>
Quaternion<T> QuaternionFromMatrix(Matrix4T<T> const& rotationMatrix)
{
	// see Real-Time Rendering, 3rd. 4.3.2 Quaternion Transforms.
	// code modified from From paper 'Quaternion to Matrix and Back', by ID software, 2005.
	T x, y, z, w;

	// check the diagonal
	if (rotationMatrix(0, 0) + rotationMatrix(1, 1) + rotationMatrix(2, 2) > 0)
	{
		T const t = +rotationMatrix(0, 0) + rotationMatrix(1, 1) + rotationMatrix(2, 2) + T(1);
		T const s = ReciprocalSqrt(t) * T(0.5);
		w = s * t;
		x = (rotationMatrix(2, 1) - rotationMatrix(1, 2)) * s;
		y = (rotationMatrix(0, 2) - rotationMatrix(2, 0)) * s;
		z = (rotationMatrix(1, 0) - rotationMatrix(0, 1)) * s;
	}
	else if (rotationMatrix(0, 0) > rotationMatrix(1, 1) && rotationMatrix(0, 0) > rotationMatrix(2, 2))
	{
		T const t = +rotationMatrix(0, 0) - rotationMatrix(1, 1) - rotationMatrix(2, 2) + T(1);
		T s = ReciprocalSqrt(t) * T(0.5);
		x = s * t;
		y = (rotationMatrix(0, 1) + rotationMatrix(1, 0)) * s;
		z = (rotationMatrix(0, 2) + rotationMatrix(2, 0)) * s;
		w = (rotationMatrix(2, 1) + rotationMatrix(1, 2)) * s;
	}
	else if (rotationMatrix(1, 1) > rotationMatrix(2, 2))
	{
		T const t = -rotationMatrix(0, 0) + rotationMatrix(1, 1) - rotationMatrix(2, 2) + T(1);
		T const s = ReciprocalSqrt(t) * T(0.5);

		y = s * t;
		x = (rotationMatrix(0, 1) + rotationMatrix(1, 0)) * s;
		w = (rotationMatrix(0, 2) - rotationMatrix(2, 0)) * s;
		z = (rotationMatrix(1, 2) + rotationMatrix(2, 1)) * s;
	}
	else
	{
		T const t = -rotationMatrix(0, 0) - rotationMatrix(1, 1) + rotationMatrix(2, 2) + T(1);
		T const s = ReciprocalSqrt(t) * T(0.5);

		z = s * t;
		w = (rotationMatrix(1, 0) - rotationMatrix(0, 1)) * s;
		x = (rotationMatrix(0, 2) + rotationMatrix(2, 0)) * s;
		y = (rotationMatrix(1, 2) + rotationMatrix(2, 1)) * s;
	}

	// return Quaternion<T>(x, y, z, w).Normalize();
	return Quaternion<T>(x, y, z, w);
}
template floatQ QuaternionFromMatrix(floatM44 const& rotationMatrix);


template <typename T>
Matrix4T<T> MatrixFromQuaternion(Quaternion<T> const& quaternion)
{
	// see Real-Time Rendering, 3rd. 4.3.2 Quaternion Transforms
	// or Mathematics for 3D Game Programming and Computer Graphics, 3rd. 4.6.2 Rotations with Quaternions

	T const x2(quaternion.X() + quaternion.X());
	T const y2(quaternion.Y() + quaternion.Y());
	T const z2(quaternion.Z() + quaternion.Z());

	T const xx2(quaternion.X() * x2);
	T const xy2(quaternion.X() * y2);
	T const xz2(quaternion.X() * z2);
	T const yy2(quaternion.Y() * y2);
	T const yz2(quaternion.Y() * z2);
	T const zz2(quaternion.Z() * z2);

	T const wx2(quaternion.W() * x2);
	T const wy2(quaternion.W() * y2);
	T const wz2(quaternion.W() * z2);

	return Matrix4T<T>(
		1 - yy2 - zz2, xy2 + wz2, xz2 - wy2, 0,
		xy2 - wz2, 1 - xx2 - zz2, yz2 + wx2, 0,
		xz2 + wy2, yz2 - wx2, 1 - xx2 - yy2, 0,
		0, 0, 0, 1);
}
template floatM44 MatrixFromQuaternion(floatQ const& quaternion);

template <typename T, uint32 N>
Vector<T, N> Transform(Matrix4T<T> const& matrix, Vector<T, N> const& vector, T const& lastComponent)
{
	Vector<T, N> temp;
	MathHelper::TransformHelper<T, N>::DoTransform(const_cast<T*>(&temp[0]), &matrix[0], &vector[0], lastComponent);
	return temp;
}
template V3F32 Transform(floatM44 const& matrix, V3F32 const& vector, float32 const& lastComponent);
template V4F32 Transform(floatM44 const& matrix, V4F32 const& vector, float32 const& lastComponent);

template <typename T>
Vector<T, 3> RotateByQuaternion(Quaternion<T> const& quaternion, Vector<T, 3> const& vector)
{
	// see Mathematics for 3D Game Programming and Computer Graphics, 3rd. 4.6.2 Rotations with Quaternions

	// result = a * vector + b * quaternion + c * (quaternion.V CROSS vector)
	// where
	//  a = quaternion.W^2 - (quaternion.V DOT quaternion.V)
	//  b = 2 * (quaternion.V DOT vector)
	//  c = 2 * quaternion.W
	T const a(quaternion.W() * quaternion.W() - quaternion.V().LengthSquared());
	T const b(2 * Dot(quaternion.V(), vector));
	T const c(quaternion.W() + quaternion.W());

	Vector<T, 3> crossV(Cross(quaternion.V(), vector)); // quaternion.V CROSS vector

	return a * vector + b * quaternion.V() + c * crossV;
}
template V3F32 RotateByQuaternion(floatQ const& quaternion, V3F32 const& vector);

template <typename T, uint32 N>
Vector<T, N> TransformDirection(Matrix4T<T> const& matrix, Vector<T, N> const& vector)
{
	Vector<T, N> temp;
	MathHelper::TransformHelper<T, N>::DoTransformDirection(const_cast<T*>(&temp[0]), &matrix[0], &vector[0]);
	return temp;
}
template V3F32 TransformDirection(floatM44 const& matrix, V3F32 const& vector);
template V4F32 TransformDirection(floatM44 const& matrix, V4F32 const& vector);


template <typename T>
Matrix4T<T> TranslationMatrix(T const& x, T const& y, T const& z)
{
	return Matrix4T<T>(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1);
}
template floatM44 TranslationMatrix(float32 const& x, float32 const& y, float32 const& z);

template <typename T>
Matrix4T<T> TranslationMatrix(Vector<T, 3> const& v)
{
	return TranslationMatrix(v.X(), v.Y(), v.Z());
}
template floatM44 TranslationMatrix(V3F32 const& v);

template <typename T>
Matrix4T<T> ScalingMatrix(T const& s)
{
	return ScalingMatrix(s, s, s);
}
template floatM44 ScalingMatrix(float32 const& s);

template <typename T>
Matrix4T<T> ScalingMatrix(T const& sx, T const& sy, T const& sz)
{
	return Matrix4T<T>(
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);
}
template floatM44 ScalingMatrix(float32 const& sx, float32 const& sy, float32 const& sz);

template <typename T>
Matrix4T<T> ScalingMatrix(Vector<T, 3> const& s)
{
	return ScalingMatrix(s.X(), s.Y(), s.Z());
}
template floatM44 ScalingMatrix(V3F32 const& s);

template <typename T>
Matrix4T<T> RotationMatrixX(T const& angleX)
{
	float32 sx = std::sin(angleX);
	float32 cx = std::cos(angleX);
	return Matrix4T<T>(
		1, 0, 0, 0,
		0, cx, -sx, 0,
		0, sx, cx, 0,
		0, 0, 0, 1);
}
template floatM44 RotationMatrixX(float32 const& angleX);

template <typename T>
Matrix4T<T> RotationMatrixY(T const& angleY)
{
	float32 sy = std::sin(angleY);
	float32 cy = std::cos(angleY);
	return Matrix4T<T>(
		cy, 0, sy, 0,
		0, 1, 0, 0,
		-sy, 0, cy, 0,
		0, 0, 0, 1);
}
template floatM44 RotationMatrixY(float32 const& angleY);

template <typename T>
Matrix4T<T> RotationMatrixZ(T const& angleZ)
{
	float32 sz = std::sin(angleZ);
	float32 cz = std::cos(angleZ);
	return Matrix4T<T>(
		cz, -sz, 0, 0,
		sz, cz, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
template floatM44 RotationMatrixZ(float32 const& angleZ);

template <typename T>
Matrix4T<T> RotationMatrix(T const& angle, T const& x, T const& y, T const& z)
{
	return RotationMatrix(angle, Vector<T, 3>(x, y, z));
}
template floatM44 RotationMatrix(float32 const& angle, float32 const& x, float32 const& y, float32 const& z);

template <typename T>
Matrix4T<T> RotationMatrix(T const& angle, Vector<T, 3> const& axis)
{
	// 0 vector
	if (axis.LengthSquared() == 0)
	{
		return Matrix4T<T>::Zero;
	}
	Vector<T, 3> naxis = axis.Normalize();
	T ux = naxis.X();
	T uy = naxis.Y();
	T uz = naxis.Z();

	Matrix4T<T> temp;
	T* resultArray = const_cast<T*>(temp.GetArray());

	// Rotation matrix, see http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
	// for details, see 'Mathematics for 3D Game Programming and Computer Graphics, 3rd', 4.3.1
	T sin = std::sin(angle);
	T cos = std::cos(angle);
	T t = 1 - cos;

	resultArray[0] = ux * ux * t + cos;
	resultArray[1] = uy * ux * t + uz * sin;
	resultArray[2] = uz * ux * t - uy * sin;
	resultArray[3] = 0;

	resultArray[4] = ux * uy * t - uz * sin;
	resultArray[5] = uy * uy * t + cos;
	resultArray[6] = uz * uy * t + ux * sin;
	resultArray[7] = 0;

	resultArray[8] = ux * uz * t + uy * sin;
	resultArray[9] = uy * uz * t - ux * sin;
	resultArray[10] = uz * uz * t + cos;
	resultArray[11] = 0;

	resultArray[12] = 0;
	resultArray[13] = 0;
	resultArray[14] = 0;
	resultArray[15] = 1;

	return temp;
}
template floatM44 RotationMatrix(float32 const& angle, V3F32 const& axis);

template <typename T>
Matrix4T<T> RotationMatrixFromTo(Vector<T, 3> const& from, Vector<T, 3> const& to)
{
	// 0 vector
	if (from.LengthSquared() == 0 || to.LengthSquared() == 0)
	{
		return Matrix4T<T>::Zero;
	}
	Vector<T, 3> ufrom = from.Normalize();
	Vector<T, 3> uto = to.Normalize();

	Matrix4T<T> temp;
	T* resultArray = const_cast<T*>(temp.GetArray());

	// Rotation matrix build from two vectors, see 'Real-time Rendering, 3rd', 4.3.2, 'Rotation from One Vector to Another'
	T vx = ufrom.Y() * uto.Z() - ufrom.Z() * uto.Y();
	T vy = ufrom.Z() * uto.X() - ufrom.X() * uto.Z();
	T vz = ufrom.X() * uto.Y() - ufrom.Y() * uto.X();
	T e = ufrom.X() * uto.X() + ufrom.Y() * uto.Y() + ufrom.Z() * uto.Z();
	T h = T(1) / (T(1) + e);

	resultArray[0] = e + h * vx * vx;
	resultArray[1] = h * vx * vy + vz;
	resultArray[2] = h * vx * vz - vy;
	resultArray[3] = 0;

	resultArray[4] = h * vx * vy - vz;
	resultArray[5] = e + h * vy * vy;
	resultArray[6] = h * vy * vz + vx;
	resultArray[7] = 0;

	resultArray[8] = h * vx * vz + vy;
	resultArray[9] = h * vy * vz - vx;
	resultArray[10] = e + h * vz * vz;
	resultArray[11] = 0;

	resultArray[12] = 0;
	resultArray[13] = 0;
	resultArray[14] = 0;
	resultArray[15] = 1;

	return temp;
}
template floatM44 RotationMatrixFromTo(V3F32 const& from, V3F32 const& to);


template <typename T>
Quaternion<T> RotationQuaternion(T const& angle, T const& x, T const& y, T const& z)
{
	return RotationQuaternion(angle, Vector<T, 3>(x, y, z));
}
template floatQ RotationQuaternion(float32 const& angle, float32 const& x, float32 const& y, float32 const& z);

template <typename T>
Quaternion<T> RotationQuaternion(T const& angle, Vector<T, 3> const& axis)
{
	if (Equal<T>(axis.LengthSquared(), 0))
	{
		return Quaternion<T>::Identity;
	}
	T halfAngle = T(0.5) * angle;
	T sha = std::sin(halfAngle);
	T cha = std::cos(halfAngle);
	return Quaternion<T>(sha * axis.Normalize(), cha);
}
template floatQ RotationQuaternion(float32 const& angle, V3F32 const& axis);

template <typename T>
Quaternion<T> RotationQuaternionFromTo(Vector<T, 3> const& from, Vector<T, 3> const& to)
{
	Vector<T, 3> uFrom = from.Normalize();
	Vector<T, 3> uTo = to.Normalize();

	T cos = Dot(uFrom, uTo);
	if (Equal<T>(cos, T(1)))
	{
		return Quaternion<T>::Identity;
	}
	else if (Equal<T>(cos, T(-1)))
	{
		return Quaternion<T>(1, 0, 0, 0);
	}
	Vector<T, 3> axis = Cross(uFrom, uTo);

	// 	sin(A/2)=+-((1-cosA)/2)^(1/2), here only positive
	// 	cos(A/2)=+-((1+cosA)/2)^(1/2), here only positive
	T sha = std::sqrt(T((1 - cos) * 0.5));
	T cha = std::sqrt(T((1 + cos) * 0.5));
	return Quaternion<T>(sha * axis, cha).Normalize();
}
template floatQ RotationQuaternionFromTo(V3F32 const& from, V3F32 const& to);

namespace
{
	template <typename T>
	Matrix4T<T> BaseMatrixByZReferenceY(Vector<T, 3> const& zAxis, Vector<T, 3> const& yAxis, bool transpose = false)
	{
		Vector<T, 3> z = zAxis.Normalize();
		Vector<T, 3> l = Cross(yAxis, z);
		if (l.LengthSquared() == 0)
		{
			return Matrix4T<T>::Zero;
		}
		Vector<T, 3> x = l.Normalize();
		Vector<T, 3> y = Cross(z, x);

		Matrix4T<T> matrix;
		T* resultArray = const_cast<T*>(matrix.GetArray());
		if (transpose)
		{
			resultArray[0] = x.X();
			resultArray[1] = y.X();
			resultArray[2] = z.X();
			resultArray[3] = 0;
			resultArray[4] = x.Y();
			resultArray[5] = y.Y();
			resultArray[6] = z.Y();
			resultArray[7] = 0;
			resultArray[8] = x.Z();
			resultArray[9] = y.Z();
			resultArray[10] = z.Z();
			resultArray[11] = 0;
		}
		else
		{
			resultArray[0] = x.X();
			resultArray[1] = x.Y();
			resultArray[2] = x.Z();
			resultArray[3] = 0;
			resultArray[4] = y.X();
			resultArray[5] = y.Y();
			resultArray[6] = y.Z();
			resultArray[7] = 0;
			resultArray[8] = z.X();
			resultArray[9] = z.Y();
			resultArray[10] = z.Z();
			resultArray[11] = 0;
		}
		resultArray[12] = 0;
		resultArray[13] = 0;
		resultArray[14] = 0;
		resultArray[15] = 1;
		return matrix;
	}

}

template <typename T>
Matrix4T<T> FaceToMatrix(Vector<T, 3> const& to, Vector<T, 3> const& up, Vector<T, 3> const& localFront, Vector<T, 3> const& localUp)
{
	if (to.LengthSquared() == 0)
	{
		return Matrix4T<T>::Zero;
	}
	if (up.LengthSquared() == 0)
	{
		return Matrix4T<T>::Zero;
	}
	if (localFront.LengthSquared() == 0)
	{
		return Matrix4T<T>::Zero;
	}
	if (localUp.LengthSquared() == 0)
	{
		return Matrix4T<T>::Zero;
	}

	// To build a matrix M that M * localX/Y/Z = worldX/Y/Z, so M = world(X,Y,Z) * local(X,Y,Z)^(-1)
	Matrix4T<T> world = BaseMatrixByZReferenceY(to, up, false);
	Matrix4T<T> localInverse = BaseMatrixByZReferenceY(localFront, localUp, true);

	return world * localInverse;
}
template floatM44 FaceToMatrix(V3F32 const& to, V3F32 const& up, V3F32 const& localFront, V3F32 const& localUp);

template <typename T>
Quaternion<T> FaceToQuaternion(Vector<T, 3> const& to, Vector<T, 3> const& up, Vector<T, 3> const& localFront, Vector<T, 3> const& localUp)
{
	if (to.LengthSquared() == 0)
	{
		return Quaternion<T>::Zero;
	}
	if (up.LengthSquared() == 0)
	{
		return Quaternion<T>::Zero;
	}
	if (localFront.LengthSquared() == 0)
	{
		return Quaternion<T>::Zero;
	}
	if (localUp.LengthSquared() == 0)
	{
		return Quaternion<T>::Zero;
	}
	// see FaceToMatrix
	Quaternion<T> world = QuaternionFromMatrix(BaseMatrixByZReferenceY(to, up, false));
	Quaternion<T> localInverse = QuaternionFromMatrix(BaseMatrixByZReferenceY(localFront, localUp, true));
	return world * localInverse;
}
template floatQ FaceToQuaternion(V3F32 const& to, V3F32 const& up, V3F32 const& localFront, V3F32 const& localUp);


template <typename T>
Matrix4T<T> LookToViewMatrix(Vector<T, 3> const& eye, Vector<T, 3> const& to, Vector<T, 3> const& up)
{
	if (to.LengthSquared() == 0)
	{
		return Matrix4T<T>::Identity;
	}

	if (up.LengthSquared() == 0)
	{
		return Matrix4T<T>::Identity;
	}


	Vector<T, 3> zAxis(to.Normalize());
	Vector<T, 3> xAxis(Cross(up, zAxis).Normalize());
	Vector<T, 3> yAxis(Cross(zAxis, xAxis));

	Matrix4T<T> temp;
	T* resultArray = const_cast<T*>(temp.GetArray());

	resultArray[0] = xAxis.X();
	resultArray[1] = yAxis.X();
	resultArray[2] = zAxis.X();
	resultArray[3] = 0;
	resultArray[4] = xAxis.Y();
	resultArray[5] = yAxis.Y();
	resultArray[6] = zAxis.Y();
	resultArray[7] = 0;
	resultArray[8] = xAxis.Z();
	resultArray[9] = yAxis.Z();
	resultArray[10] = zAxis.Z();
	resultArray[11] = 0;
	resultArray[12] = -Dot(xAxis, eye);
	resultArray[13] = -Dot(yAxis, eye);
	resultArray[14] = -Dot(zAxis, eye);
	resultArray[15] = 1;

	return temp;
}
template floatM44 LookToViewMatrix(V3F32 const& eye, V3F32 const& at, V3F32 const& up);

template <typename T>
Matrix4T<T> FrustumProjectionMatrix(T const& fieldOfView, T const& aspectRatio, T const& near, T const& far)
{
	T top = std::tan(fieldOfView * T(0.5)) * near;
	T bottom = -top;
	T r = top * aspectRatio;
	T l = -r;
	return FrustumProjectionMatrix<T>(l, r, bottom, top, near, far);
}
template floatM44 FrustumProjectionMatrix(float32 const& fieldOfView, float32 const& aspectRatio, float32 const& near, float32 const& far);

template <typename T>
Matrix4T<T> FrustumProjectionMatrix(T const& l, T const& r, T const& bottom, T const& top, T const& near, T const& far)
{
	Matrix4T<T> temp;
	T* resultArray = const_cast<T*>(temp.GetArray());

	// for details, see 'Real-time Rendering, 3rd', 4.6.2
	// or 'Mathematics for 3D Game Programming and Computer Graphics, 3rd', 5.5.1
	// the code here is different from the books because there +z is the view direction.
	T rl = (r - l), tb = (top - bottom), fn = (far - near);
	resultArray[0] = -(near * 2) / rl;
	resultArray[1] = 0;
	resultArray[2] = 0;
	resultArray[3] = 0;
	resultArray[4] = 0;
	resultArray[5] = (near * 2) / tb;
	resultArray[6] = 0;
	resultArray[7] = 0;
	resultArray[8] = -(r + l) / rl;
	resultArray[9] = (top + bottom) / tb;
	resultArray[10] = (far + near) / fn;
	resultArray[11] = 1;
	resultArray[12] = 0;
	resultArray[13] = 0;
	resultArray[14] = -(far * near * 2) / fn;
	resultArray[15] = 0;

	return temp;
};
template floatM44 FrustumProjectionMatrix(float32 const& l, float32 const& r, float32 const& bottom, float32 const& top, float32 const& near, float32 const& far);

template <typename T>
Matrix4T<T> OrthogonalProjectionMatrix(T const& width, T const& height, T const& depth)
{
	return OrthogonalProjectionMatrix<T>(-width * T(0.5), width * T(0.5), -height * T(0.5), height * T(0.5), T(0), depth);
}
template floatM44 OrthogonalProjectionMatrix(float32 const& width, float32 const& height, float32 const& depth);

template <typename T>
Matrix4T<T> OrthogonalProjectionMatrix(T const& l, T const& r, T const& bottom, T const& top, T const& near, T const& far)
{
	Matrix4T<T> temp;
	T* resultArray = const_cast<T*>(temp.GetArray());

	// for details, see 'Real-time Rendering, 3rd', 4.6.1
	// or 'Mathematics for 3D Game Programming and Computer Graphics, 3rd', 5.5.2
	// the code here is different from the books because there +z is the view direction.
	T rl = (r - l), tb = (top - bottom), fn = (far - near);
	resultArray[0] = -2 / rl;
	resultArray[1] = 0;
	resultArray[2] = 0;
	resultArray[3] = 0;
	resultArray[4] = 0;
	resultArray[5] = 2 / tb;
	resultArray[6] = 0;
	resultArray[7] = 0;
	resultArray[8] = 0;
	resultArray[9] = 0;
	resultArray[10] = 2 / fn;
	resultArray[11] = 0;
	resultArray[12] = (r + l) / rl;
	resultArray[13] = -(top + bottom) / tb;
	resultArray[14] = -(far + near) / fn;
	resultArray[15] = 1;

	return temp;
}
template floatM44 OrthogonalProjectionMatrix(float32 const& l, float32 const& r, float32 const& bottom, float32 const& top, float32 const& near, float32 const& far);


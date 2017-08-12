#pragma once
#include "Math/BasicMath.h"

#include "Math/Angle.h"


#include <limits>
#include <cmath>

namespace X
{
	struct Math : BasicMath
	{


		/*
		*	@return: angle in [0, PI] in radians.
		*/
		template <typename T, uint32 N>
		Radian<T> Angle(VectorT<T, N> const& from, VectorT<T, N> const& to)
		{
			return std::acos(Dot(from, to) / (from.Length() * to.Length()));
		}

		template <typename T>
		QuaternionT<T> QuaternionFromMatrix(Matrix4T<T> const& rotationMatrix);
		template <typename T>
		Matrix4T<T> MatrixFromQuaternion(QuaternionT<T> const& quaternion);

		/*
		*	for 3 dimension vector, affine division will be done on the result vector.
		*/
		template <typename T, uint32 N>
		VectorT<T, N> Transform(Matrix4T<T> const& matrix, VectorT<T, N> const& vector, T const& lastComponent = T(1));

		template <typename T>
		VectorT<T, 3> RotateByQuaternion(QuaternionT<T> const& quaternion, VectorT<T, 3> const& vector);

		template <typename T, uint32 N>
		VectorT<T, N> TransformDirection(Matrix4T<T> const& matrix, VectorT<T, N> const& vector);

		template <typename T>
		Matrix4T<T> TranslationMatrix(T const& x, T const& y, T const& z);
		template <typename T>
		Matrix4T<T> TranslationMatrix(VectorT<T, 3> const& v);

		template <typename T>
		Matrix4T<T> ScalingMatrix(T const& s);
		template <typename T>
		Matrix4T<T> ScalingMatrix(T const& sx, T const& sy, T const& sz);
		template <typename T>
		Matrix4T<T> ScalingMatrix(VectorT<T, 3> const& s);

		template <typename T>
		Matrix4T<T> RotationMatrixX(T const& angleX);
		template <typename T>
		Matrix4T<T> RotationMatrixY(T const& angleY);
		template <typename T>
		Matrix4T<T> RotationMatrixZ(T const& angleZ);
		template <typename T>
		Matrix4T<T> RotationMatrix(T const& angle, T const& x, T const& y, T const& z);
		template <typename T>
		Matrix4T<T> RotationMatrix(T const& angle, VectorT<T, 3> const& axis);
		template <typename T>
		Matrix4T<T> RotationMatrixFromTo(VectorT<T, 3> const& from, VectorT<T, 3> const& to);

		template <typename T>
		QuaternionT<T> RotationQuaternion(T const& angle, T const& x, T const& y, T const& z);
		template <typename T>
		QuaternionT<T> RotationQuaternion(T const& angle, VectorT<T, 3> const& axis);
		template <typename T>
		QuaternionT<T> RotationQuaternionFromTo(VectorT<T, 3> const& from, VectorT<T, 3> const& to);

		/*
		*	@to: face to direction in world space.
		*	@up: up direction in world space as reference.
		*	@localFront: front direction in local space.
		*	@localUp: up reference direction in local space.
		*	@return: matrix only contains rotation component.
		*/
		template <typename T>
		Matrix4T<T> FaceToMatrix(VectorT<T, 3> const& to, VectorT<T, 3> const& up, VectorT<T, 3> const& localFront, VectorT<T, 3> const& localUp);
		/*
		*	@to: face to direction in world space.
		*	@up: up direction in world space as reference.
		*	@localFront: front direction in local space.
		*	@localUp: up reference direction in local space.
		*/
		template <typename T>
		QuaternionT<T> FaceToQuaternion(VectorT<T, 3> const& to, VectorT<T, 3> const& up, VectorT<T, 3> const& localFront, VectorT<T, 3> const& localUp);

		/*
		*	Create a view matrix of camera. With assumption of camera front is +z.
		*	@eye: eye position.
		*	@to: look to direction.
		*	@up: up direction in world space.
		*	@return: view matrix.
		*/
		template <typename T>
		Matrix4T<T> LookToViewMatrix(VectorT<T, 3> const& eye, VectorT<T, 3> const& to, VectorT<T, 3> const& up);


		template <typename T>
		Matrix4T<T> FrustumProjectionMatrix(T const& fieldOfView, T const& aspectRatio, T const& near, T const& far);
		template <typename T>
		Matrix4T<T> FrustumProjectionMatrix(T const& l, T const& r, T const& bottom, T const& top, T const& near, T const& far);

		/*
		*	Create a orthogonal projection matrix, with camera at the center of near plane.
		*/
		template <typename T>
		Matrix4T<T> OrthogonalProjectionMatrix(T const& width, T const& height, T const& depth);
		template <typename T>
		Matrix4T<T> OrthogonalProjectionMatrix(T const& l, T const& r, T const& bottom, T const& top, T const& near, T const& far);
	};


}


#include "Math/Math.inl"
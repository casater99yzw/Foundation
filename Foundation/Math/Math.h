#pragma once
#include "Math/BasicMath.h"

#include "Math/Angle.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"


#include <limits>
#include <cmath>

namespace X
{
	struct Math : BasicMath
	{


		//	@return: angle in [0, PI].
		template <typename T, uint32 N>
		constexpr static Radian<T> Angle(Vector<T, N> const& from, Vector<T, N> const& to)
		{
			return ACos(Dot(from, to) / (from.Length() * to.Length()));
		}

		template <typename T>
		Quaternion<T> QuaternionFromMatrix(Matrix4T<T> const& rotationMatrix);
		template <typename T>
		Matrix4T<T> MatrixFromQuaternion(Quaternion<T> const& quaternion);

		/*
		*	for 3 dimension vector, affine division will be done on the result vector.
		*/
		template <typename T, uint32 N>
		Vector<T, N> Transform(Matrix4T<T> const& matrix, Vector<T, N> const& vector, T const& lastComponent = T(1));

		template <typename T>
		Vector<T, 3> RotateByQuaternion(Quaternion<T> const& quaternion, Vector<T, 3> const& vector);

		template <typename T, uint32 N>
		Vector<T, N> TransformDirection(Matrix4T<T> const& matrix, Vector<T, N> const& vector);

		template <typename T>
		Matrix4T<T> TranslationMatrix(T const& x, T const& y, T const& z);
		template <typename T>
		Matrix4T<T> TranslationMatrix(Vector<T, 3> const& v);

		template <typename T>
		Matrix4T<T> ScalingMatrix(T const& s);
		template <typename T>
		Matrix4T<T> ScalingMatrix(T const& sx, T const& sy, T const& sz);
		template <typename T>
		Matrix4T<T> ScalingMatrix(Vector<T, 3> const& s);

		template <typename T>
		Matrix4T<T> RotationMatrixX(T const& angleX);
		template <typename T>
		Matrix4T<T> RotationMatrixY(T const& angleY);
		template <typename T>
		Matrix4T<T> RotationMatrixZ(T const& angleZ);
		template <typename T>
		Matrix4T<T> RotationMatrix(T const& angle, T const& x, T const& y, T const& z);
		template <typename T>
		Matrix4T<T> RotationMatrix(T const& angle, Vector<T, 3> const& axis);
		template <typename T>
		Matrix4T<T> RotationMatrixFromTo(Vector<T, 3> const& from, Vector<T, 3> const& to);

		template <typename T>
		Quaternion<T> RotationQuaternion(T const& angle, T const& x, T const& y, T const& z);
		template <typename T>
		Quaternion<T> RotationQuaternion(T const& angle, Vector<T, 3> const& axis);
		template <typename T>
		Quaternion<T> RotationQuaternionFromTo(Vector<T, 3> const& from, Vector<T, 3> const& to);

		/*
		*	@to: face to direction in world space.
		*	@up: up direction in world space as reference.
		*	@localFront: front direction in local space.
		*	@localUp: up reference direction in local space.
		*	@return: matrix only contains rotation component.
		*/
		template <typename T>
		Matrix4T<T> FaceToMatrix(Vector<T, 3> const& to, Vector<T, 3> const& up, Vector<T, 3> const& localFront, Vector<T, 3> const& localUp);
		/*
		*	@to: face to direction in world space.
		*	@up: up direction in world space as reference.
		*	@localFront: front direction in local space.
		*	@localUp: up reference direction in local space.
		*/
		template <typename T>
		Quaternion<T> FaceToQuaternion(Vector<T, 3> const& to, Vector<T, 3> const& up, Vector<T, 3> const& localFront, Vector<T, 3> const& localUp);

		/*
		*	Create a view matrix of camera. With assumption of camera front is +z.
		*	@eye: eye position.
		*	@to: look to direction.
		*	@up: up direction in world space.
		*	@return: view matrix.
		*/
		template <typename T>
		Matrix4T<T> LookToViewMatrix(Vector<T, 3> const& eye, Vector<T, 3> const& to, Vector<T, 3> const& up);


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
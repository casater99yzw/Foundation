#pragma once

#include "Base/Math.h"

namespace X
{

	class Color
	{
	public:
		Color()
		{
		}
		Color(float32 r, float32 g, float32 b, float32 a)
			: value_(r, g, b, a)
		{
		}
		Color(Color const& r)
			: value_(r.value_)
		{
		}
		~Color()
		{
		}

		float32 R() const
		{
			return value_.X();
		}
		float32 G() const
		{
			return value_.Y();
		}
		float32 B() const
		{
			return value_.Z();
		}
		float32 A() const
		{
			return value_.W();
		}

		friend Color operator +(Color const& l, Color const& r)
		{
			Color temp;
			temp.value_ = l.value_ + r.value_;
			return temp;
		}

		friend Color operator -(Color const& l, Color const& r)
		{
			Color temp;
			temp.value_ = l.value_ - r.value_;
			return temp;
		}

		friend Color operator *(Color const& l, Color const& r)
		{
			Color temp;
			temp.value_ = l.value_ * r.value_;
			return temp;
		}

		friend Color operator *(Color const& l, float32 r)
		{
			Color temp;
			temp.value_ = l.value_ * r;
			return temp;
		}
		friend Color operator *(float32 const& l, Color const& r)
		{
			Color temp;
			temp.value_ = l * r.value_;
			return temp;
		}

		friend Color operator /(Color const& l, float32 const& r)
		{
			Color temp;
			temp.value_ = l.value_ / r;
			return temp;
		}

		Color const& operator +() const
		{
			return *this; 
		}
		Color operator -() const
		{
			Color temp;
			temp.value_ = -value_;
			return temp;
		}

		friend bool operator ==(Color const& l, Color const& r)
		{
			return l.value_ == r.value_;
		}

		friend bool operator !=(Color const& l, Color const& r)
		{
			return l.value_ != r.value_;
		}

		float32 const* GetArray() const
		{
			return value_.GetArray();
		}

	private:
		f32V4 value_;
	};

}

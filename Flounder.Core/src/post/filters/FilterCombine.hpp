#pragma once

#include "../../maths/Vector4.hpp"
#include "../IPostFilter.hpp"

namespace Flounder
{
	class FilterCombine :
		public IPostFilter
	{
	private:
		Vector4 *m_slideSpaceValue;
	public:
		FilterCombine();

		~FilterCombine();

		void StoreValues() override;

		Vector4 *GetSlideSpaceValue() const { return m_slideSpaceValue; }

		void SetSlideSpaceValue(const Vector4 &slideSpaceValue) const { m_slideSpaceValue->Set(slideSpaceValue); }

		void SetSlideSpace(const float &x, const float &y, const float &z, const float &w) const { m_slideSpaceValue->Set(x, y, z, w); }
	};
}

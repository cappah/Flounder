#include "filterblurvertical.hpp"

namespace Flounder
{
	filterblurvertical::filterblurvertical(const float &sizeScalar) :
		IPostFilter("filterBlurVertical", "res/shaders/filters/blurvertical.frag.spv", new Fbo(true, sizeScalar)),
		m_heightValue(static_cast<int>(Display::Get()->GetHeight() * sizeScalar)),
		m_scaleValue(2.0f),
		m_fitToDisplay(true),
		m_sizeScalar(sizeScalar)
	{
	}

	filterblurvertical::filterblurvertical(const int &width, const int &height) :
		IPostFilter("filterBlurVertical", "res/shaders/filters/blurvertical.frag.spv", new Fbo(width, height)),
		m_heightValue(height),
		m_scaleValue(2.0f),
		m_fitToDisplay(false),
		m_sizeScalar(-1.0f)
	{
	}

	filterblurvertical::~filterblurvertical()
	{
	}

	void filterblurvertical::StoreValues()
	{
		if (m_fitToDisplay)
		{
			m_heightValue = static_cast<int>(Display::Get()->GetHeight() * m_sizeScalar);
		}
#if 0
		m_shader->loadUniform1f("height", static_cast<float>(m_heightValue));
		m_shader->loadUniform1f("scale", m_scaleValue);
#endif
	}
}

#pragma once

#include "../maths/Matrix4.hpp"
#include "../maths/Vector4.hpp"

namespace Flounder
{
	class UbosTerrains
	{
	public:
		struct UboScene
		{
			Matrix4 projection;
			Matrix4 view;
			Vector4 clip;
		};

		struct UboObject
		{
			Matrix4 transform;
			float shineDamper;
			float reflectivity;
		};
	};
}

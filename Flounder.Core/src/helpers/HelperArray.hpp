#pragma once

namespace Flounder
{
	/// <summary>
	/// A helper for C++ arrays.
	/// </summary>
	class HelperArray
	{
	public:
		/// <summary>
		/// Creates a new rectangular float array.
		/// </summary>
		/// <param name="size1"> The first size. </param>
		/// <param name="size2"> The seconds size. </param>
		/// <returns> The new rectangular float array. </returns>
		static float **FloatArray(const int &size1, const int &size2);
	};
}

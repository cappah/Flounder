#pragma once

#include <vector>
#include "../engine/Engine.hpp"
#include "../noise/NoiseFast.hpp"
#include "Terrain.hpp"

namespace Flounder
{
	/// <summary>
	/// A module used for managing terrains in 3D worlds.
	/// </summary>
	class Terrains :
		public IModule
	{
	private:
		std::vector<Terrain*> *m_terrains;
		NoiseFast m_noiseTerrain;
	public:
		/// <summary>
		/// Gets this engine instance.
		/// </summary>
		/// <returns> The current module instance. </returns>
		static Terrains *Get()
		{
			return static_cast<Terrains*>(Engine::Get()->GetModule("terrains"));
		}

		/// <summary>
		/// Creates a new terrains module.
		/// </summary>
		Terrains();

		/// <summary>
		/// Deconstructor for the terrains module.
		/// </summary>
		~Terrains();

		void Update() override;

		float GetHeight(const float &x, const float &z);

		float GetSlope(const float &x, const float &z);

		Vector3 GetPosition(const float &x, const float &z);

		std::vector<Terrain*> *GetTerrains() const { return m_terrains; }
	};
}

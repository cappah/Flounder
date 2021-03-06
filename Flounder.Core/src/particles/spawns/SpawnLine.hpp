﻿#pragma once

#include "ISpawnParticle.hpp"

namespace Flounder
{
	class SpawnLine :
		public ISpawnParticle
	{
	private:
		float m_length;
		Vector3 *m_axis;
		Vector3 *m_spawnPosition;
	public:
		SpawnLine(const float &length, const Vector3 &axis);

		~SpawnLine();

		Vector3 *GetBaseSpawnPosition() override;

		float GetLength() const { return m_length; }

		void SetLength(const float &length) { m_length = length; }

		Vector3 *GetAxis() const { return m_axis; }

		void SetAxis(const Vector3 &axis) const { m_axis->Set(axis); }

		Vector3 *GetSpawnPosition() const { return m_spawnPosition; }

		void SetSpawnPosition(const Vector3 &spawnPosition) const { m_spawnPosition->Set(spawnPosition); }
	};
}

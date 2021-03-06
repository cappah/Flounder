#pragma once

#include "EntityRender.hpp"

namespace Flounder
{
	class Entity;

	class IComponent
	{
	protected:
		Entity *m_entity;
	public:
		IComponent()
		{
			m_entity = nullptr;
		}

		virtual ~IComponent()
		{
		}

		virtual void Update() = 0;

		virtual void Render(EntityRender *render) = 0;

		Entity *GetEntity() const { return m_entity; }

		void SetEntity(Entity *entity) { m_entity = entity; }
	};
}

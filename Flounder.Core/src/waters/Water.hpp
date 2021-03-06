﻿#pragma once

#include "../maths/Colour.hpp"
#include "../maths/Matrix4.hpp"
#include "../maths/Vector3.hpp"
#include "../models/Model.hpp"
#include "../physics/Aabb.hpp"
#include "../renderer/buffers/UniformBuffer.hpp"
#include "../renderer/pipelines/Pipeline.hpp"
#include "../textures/Texture.hpp"

namespace Flounder
{
	class Water
	{
	private:
		UniformBuffer *m_uniformObject;

		Model *m_model;

		Colour *m_colour;
		Texture *m_textureWater;

		Vector3 *m_position;
		Vector3 *m_rotation;
		Vector3 *m_offset;
		bool m_moved;

		Matrix4 *m_modelMatrix;
		Aabb *m_aabb;
	public:
		static const float SIDE_LENGTH;
		static const float SQUARE_SIZE;
		static const int VERTEX_COUNT;
		static const float TEXTURE_SCALE;

		static const Colour WATER_COLOUR;

		static const float SHINE_DAMPER;
		static const float REFLECTIVITY;

		Water(const Vector3 &position = Vector3(), const Vector3 &rotation = Vector3());

		~Water();

		void Update();

		void CmdRender(const VkCommandBuffer &commandBuffer, const Pipeline &pipeline, const UniformBuffer &uniformScene);
	private:
		void GenerateMesh();

		void StoreQuad(std::vector<uint32_t> &indices, const uint32_t &topLeft, const uint32_t &topRight, const uint32_t &bottomLeft, const uint32_t &bottomRight);
	public:
		Model *GetModel() const { return m_model; }

		Colour *GetColour() const { return m_colour; }

		void SetColour(const Colour &colour) const { m_colour->Set(colour); }

		Vector3 *GetPosition() const { return m_position; }

		void SetPosition(const Vector3 &position);

		Vector3 *GetRotation() const { return m_rotation; }

		void SetRotation(const Vector3 &rotation);

		Vector3 *GetOffset() const { return m_offset; }

		Matrix4 *GetModelMatrix() const { return m_modelMatrix; }

		Aabb *GetAabb() const { return m_aabb; }
	};
}

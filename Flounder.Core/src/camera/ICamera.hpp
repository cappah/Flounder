#pragma once

#include "../maths/Vector3.hpp"
#include "../maths/Matrix4.hpp"
#include "../physics/Frustum.hpp"
#include "../physics/Ray.hpp"
#include "IPlayer.hpp"

namespace Flounder
{
	/// <summary>
	/// This class is used throughout the engine wherever the camera is involved, so that the engine doesn't rely at all on the camera's implementation.
	/// </summary>
	class ICamera
	{
	public:
		/// <summary>
		/// Creates a new camera.
		/// </summary>
		ICamera()
		{
		}

		/// <summary>
		/// Deconstructor for the camera.
		/// </summary>
		virtual ~ICamera()
		{
		}

		/// <summary>
		/// Checks inputs and carries out smooth camera movement. Should be called every frame.
		/// </summary>
		/// <param name="player"> The movement and rotation controller to read from. </param>
		virtual void Update(IPlayer *player) = 0;

		/// <summary>
		/// Prepares the camera for the reflection render pass.
		/// </summary>
		/// <param name="waterHeight"> The height of the water to be reflected on. </param>
		virtual void ReflectView(const float &waterHeight) = 0;

		/// <summary>
		/// Gets the distance of the near pane of the view frustum.
		/// </summary>
		/// <returns> The distance of the near pane of the view frustum. </returns>
		virtual float GetNearPlane() const = 0;

		/// <summary>
		/// Gets the distance of the view frustum's far plane.
		/// </summary>
		/// <returns> The distance of the view frustum's far plane. </returns>
		virtual float GetFarPlane() const = 0;

		/// <summary>
		/// Gets the field of view angle for the view frustum.
		/// </summary>
		/// <returns> The field of view angle for the view frustum. </returns>
		virtual float GetFov() const = 0;

		/// <summary>
		/// Gets the view frustum created by the current camera position and rotation.
		/// </summary>
		/// <returns> The view frustum created by the current camera position and rotation. </returns>
		virtual Frustum *GetViewFrustum() const = 0;

		/// <summary>
		/// Gets the ray that extends from the cameras position though the screen.
		/// </summary>
		/// <returns> The cameras ray. </returns>
		virtual Ray *GetViewRay() const = 0;

		/// <summary>
		/// Gets the view matrix created by the current camera position and rotation.
		/// </summary>
		/// <returns> The view matrix created by the current camera position and rotation. </returns>
		virtual Matrix4 *GetViewMatrix() const = 0;

		/// <summary>
		/// Gets the projection matrix used in the current scene render.
		/// </summary>
		/// <returns> The projection matrix used in the current scene render. </returns>
		virtual Matrix4 *GetProjectionMatrix() const = 0;

		/// <summary>
		/// Gets the cameras 3D position in the world.
		/// </summary>
		/// <returns> The cameras 3D position in the world. </returns>
		virtual Vector3 *GetPosition() const = 0;

		/// <summary>
		/// Gets the cameras 3D velocity in the world.
		/// </summary>
		/// <returns> The cameras 3D velocity in the world. </returns>
		virtual Vector3 *GetVelocity() const = 0;

		/// <summary>
		/// Gets the cameras 3D rotation in the world, where x=pitch, y=yaw, z=roll.
		/// </summary>
		/// <returns> The cameras 3D rotation in the world, where x=pitch, y=yaw, z=roll. </returns>
		virtual Vector3 *GetRotation() const = 0;
	};
}

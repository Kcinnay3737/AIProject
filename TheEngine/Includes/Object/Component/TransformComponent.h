#pragma once

#include "Object/Component/Component.h"

namespace NPEngine
{
	//Component with all transform value for an actor
	class TransformComponent : public Component
	{
	private:
		//Actor position
		Vector2D<float> _Position;
		//Actor size
		Vector2D<float> _Size;
		//Actor angle
		float _Angle = 0.0f;

	public:
		TransformComponent(const std::string& Name);
		virtual ~TransformComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;

		//Ajuste the current angle value between paramaters value
		void AdjustsAngleBetweenValue(float MinAngle, float MaxAngle);

	public:
		//Return the current position
		Vector2D<float> GetPosition();
		//Set the current position
		void SetPosition(const Vector2D<float>& NewPosition);
		//Add position to the current position
		void AddPositionOffset(const Vector2D<float>& PositionOffsetToAdd);
		
		//Return the current size
		Vector2D<float> GetSize();
		//Set the current size
		void SetSize(const Vector2D<float>& NewSize);
		//Add a size to the current size
		void AddSizeOffset(const Vector2D<float>& SizeOffsetToAdd);

		//Return the current position and size in a rectangle
		Rectangle2D<float> GetPositionSizeRectangle();

		//Return the angle
		float GetAngle();
		//Set the current angle
		void SetAngle(const float& NewAngle);
		//Add a angle to the current angle
		void AddAngleOffset(const float& AngleOffsetToAdd);
	};
}
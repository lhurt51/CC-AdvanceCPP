#pragma once

#include <glm/glm.hpp>

namespace GameEngine
{

	/*
	class Transform
	{
	public:

		Transform(const glm::vec3& pos = {0,0,0}, const float rot = 0.0f, const float scale = 1.0f) :
			m_Pos(pos),
			m_Rot(rot),
			m_Scale(scale),
			m_Parent(0),
			m_ParentMat(glm::mat4(1.0f)),
			m_InitializedOldStuff(false)
		{}

		inline glm::vec3& GetPos() { return m_Pos; }
		inline const glm::vec3& GetPos() const { return m_Pos; }
		inline float GetRot() const { return m_Rot; }
		inline float GetScale() const { return m_Scale; }

		inline void SetPos(const glm::vec3& pos) { m_Pos = pos; }
		inline void SetRot(float rot) { m_Rot = rot; }
		inline void SetScale(float scale) { m_Scale = scale; }
		inline void SetParent(Transform* parent) { m_Parent = parent; }

		// inline glm::vec3 GetTransformedPos() const { return glm::vec3(GetParentMatrix().Transform(m_pos)); }
		// float GetTransformedRot() const;

		glm::mat4 GetTransformation() const;

		bool HasChanged();
		void Update();

		// void Rotate(const glm::vec3& axis, float angle);
		// void LookAt(const glm::vec3& point, const glm::vec3& up);

	private:

		const glm::mat4& GetParentMatrix() const;

	private:

		glm::vec3 m_Pos;
		float m_Rot;
		float m_Scale;

		Transform* m_Parent;
		mutable glm::mat4 m_ParentMat;

		mutable glm::vec3 m_OldPos;
		mutable float m_OldRot;
		mutable float m_OldScale;
		mutable bool m_InitializedOldStuff;

	};
	*/

}
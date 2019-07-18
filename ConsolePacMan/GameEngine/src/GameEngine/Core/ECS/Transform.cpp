#include "gepch.h"
#include "Transform.h"

namespace GameEngine
{

	glm::mat4 Transform::GetTransformation() const
	{
		// Not rotation or scaling yet
		return glm::mat4(1.0f);
	}

	bool Transform::HasChanged()
	{
		if (m_Parent != 0 && m_Parent->HasChanged())
			return true;

		if (m_Pos != m_OldPos)
			return true;

		if (m_Rot != m_OldRot)
			return true;

		if (m_Scale != m_OldScale)
			return true;

		return false;
	}

	void Transform::Update()
	{
		if (m_InitializedOldStuff)
		{
			m_OldPos = m_Pos;
			m_OldRot = m_Rot;
			m_OldScale = m_Scale;
		}
		else
		{
			m_OldPos = m_Pos + glm::vec3(1, 1, 1);
			m_OldRot = m_Rot * 0.5f;
			m_OldScale = m_Scale + 1;
			m_InitializedOldStuff = true;
		}
	}

	const glm::mat4& Transform::GetParentMatrix() const
	{
		if (m_Parent != 0 && m_Parent->HasChanged())
			m_ParentMat = m_Parent->GetTransformation();

		return m_ParentMat;
	}

}
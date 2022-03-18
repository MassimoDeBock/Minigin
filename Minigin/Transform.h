#pragma once
namespace dae
{
	class Transform final
	{
	public:
		Transform();
		Transform(float x, float y, float z);
		Transform(glm::vec3 vec3);
		Transform(const Transform& transform);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const Transform& transform);
		Transform operator+(Transform& right);
		Transform operator+(const Transform& right);
		Transform operator-(Transform& right);
		Transform operator-(const Transform& right);
		Transform operator*(Transform& right);

	private:
		glm::vec3 m_Position;
	};
}

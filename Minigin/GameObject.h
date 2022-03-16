#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <unordered_map>

namespace dae
{
	class Texture2D;
	class GameObject final: public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetId(unsigned int id);

		void SetRelativePosition(float x, float y);
		void SetAbsolutePosition(float x, float y);

		void AddComponent(const std::shared_ptr<Component> component);


		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		std::unordered_map<std::type_index, std::shared_ptr<Component>> m_Components;
		Transform GetAbsoluteTransform() const;


	private:

	public:


	private:
		std::weak_ptr<Transform> m_OriginTransform;
		std::shared_ptr<Transform> m_RelativeTransform;



		//templated functions
	public:
		template <typename T> std::weak_ptr<T> getComponent();
	/*	template <typename T> void AddComponent(const std::shared_ptr<T> component);*/
	};

}

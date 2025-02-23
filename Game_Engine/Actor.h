#pragma once
#include <vector>
#include <iostream>
#include "Component.h"
#include "TransformComponent.h"
#include <Matrix.h>

using namespace MATH;

class Actor : public Component {
	Actor(const Actor&) = delete;
	Actor(Actor&&) = delete;
	Actor& operator= (const Actor&) = delete;
	Actor& operator=(Actor&&) = delete;

protected:
	Matrix4 modelMatrix;

public:
	Actor(Component* parent_);
	~Actor();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime);
	virtual void Render() const;

	std::vector<Ref<Component>> components;


	template<typename ComponentTemplate>
	void AddComponent(Ref<ComponentTemplate> component_) {
		if (GetComponent<ComponentTemplate>().get() != nullptr) {
		#ifdef _DEBUG
			std::cerr << "WARNING: Trying to add a component type that is already added - ignored\n";
		#endif
			return;
		}
		components.push_back(component_);
	}

	template<typename ComponentTemplate, typename ... Args>
	void AddComponent(Args&& ... args_) {
		if (GetComponent<ComponentTemplate>().get() != nullptr) {
		#ifdef _DEBUG
			std::cerr << "WARNING: Trying to add a component type that is already added - ignored\n";
		#endif		
			return;
		}
		components.push_back(std::make_shared<ComponentTemplate>(std::forward<Args>(args_)...));
	}

	template <typename ComponentTemplate>
	Ref<ComponentTemplate> GetComponent() const {
		for (auto &component : components) {
			if (dynamic_cast <ComponentTemplate*>(component.get()) != nullptr) {
				return std::dynamic_pointer_cast<ComponentTemplate>(component);
			}
		}
		return Ref<ComponentTemplate>(nullptr);
	}

	template <typename ComponentTemplate>
	void RemoveComponent() {
		for (unsigned int i = 0; i < components.size(); ++i) {
			if (dynamic_cast<ComponentTemplate*>(components[i].get()) != nullptr) {
				components.erase(components.begin() + i);
				break;
			}
		}
	}

	void ListComponents() const;
	void RemoveAllComponents();

	Matrix4 getModelMatrix();
};


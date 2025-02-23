#include "Actor.h"

Actor::Actor(Component* parent_):Component(parent_) {}

Actor::~Actor() {
	OnDestroy();
}

bool Actor::OnCreate() {
	if (isCreated) return true;
	for (auto component : components) {
		if (!component->OnCreate()) {
			isCreated = false;
			return isCreated;
		}
	}
}

void Actor::OnDestroy() {
}

void Actor::Update(const float deltaTime) {
}

void Actor::Render() const {
}

void Actor::ListComponents() const {
	std::cout << typeid(*this).name() << " contain the following components:\n";
	for (auto component : components) {
			std::cout << typeid(*component).name() << std::endl;	
	}
}


void Actor::RemoveAllComponents() {
	components.clear();
}

Matrix4 Actor::getModelMatrix() {
	Ref<TransformComponent> transformComponent = GetComponent<TransformComponent>();
		if (transformComponent != nullptr) {
			return  transformComponent->GetTransformMatrix();
	}
		return modelMatrix;
}

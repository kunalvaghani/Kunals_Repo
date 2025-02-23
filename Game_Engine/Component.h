#pragma once

#include <memory>


template <typename T>
using Ref = std::shared_ptr<T>;


class Component {
public:
	Component(Component* parent_):parent(parent_), isCreated(false) {}
	virtual ~Component() = default;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
protected:
	Component* parent;
	bool isCreated;
};
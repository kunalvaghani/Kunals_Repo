#ifndef SCENE5_H
#define SCENE5_H
#include "Scene.h"
union SDL_Event;
class Scene5 : public Scene {
public:
	explicit Scene5();
	virtual ~Scene5();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
};


#endif // SCENE5_H
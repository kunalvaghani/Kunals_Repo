#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
union SDL_Event;
class Scene1 : public Scene {
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
};


#endif // SCENE1_H
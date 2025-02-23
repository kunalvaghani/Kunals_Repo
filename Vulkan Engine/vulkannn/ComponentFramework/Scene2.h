#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
union SDL_Event;
class Scene2 : public Scene {
public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
};


#endif // SCENE2_H
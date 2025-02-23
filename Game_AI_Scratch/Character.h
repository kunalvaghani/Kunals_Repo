#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "Seek.h"
#include "Scene.h"
#include "KinematicBody.h"
#include "GameManager.h"
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <memory>
#include <windows.h>
#include "Action.h"
#include "PlayerInRange.h"
#include "Node.h"
#include <psapi.h>
#include "Flee.h"
#include "Arrive.h"


using namespace std;

class Character
{

private:
	class KinematicBody* body;
	GameManager* game;
	SteeringOutput* steering;
	DecisionTreeNode* decisionTree;
	float ARRIVAL_THRESHOLD = 2.0f;
	Vec3 Mouseclick;

public:
		Character()
		{
			body = NULL;
			scene = NULL;
			decisionTree = NULL;
		};
		~Character()
		{
			if (body)
			{
				delete body;
			}
			SDL_DestroyTexture(NpcangryTexture);
			SDL_DestroyTexture(NpcNormalTexture);
			SDL_DestroyTexture(NpcExcitedTexture);

		};
		float distance_;
		float MaxDistance = 20.0f;
		string mood;
		SDL_Texture* NpcangryTexture;
		SDL_Texture* NpcNormalTexture;
		SDL_Texture* NpcExcitedTexture;

		float IntialNpcAccelration;
		float IntialNpcSpeed;
		float getMaxSpeed(){ return body->getMaxSpeed(); }
		Vec3 getpos() { return body->getPos(); }
		class Scene* scene;
		float getMaxAcceleration() { return body->getMaxAcceleration(); }
		float getRadius() { return body->getRadius(); }
		Vec3 setVel(Vec3 _Velocity) { body->setVel(_Velocity); return body->getVel(); }
		float setMaxspeed(float _speed) { body->setMaxSpeed(_speed); return body->getMaxSpeed(); }
		float setMaxAcceleration(float _MaxAcceleration) { body->setMaxAcceleration(_MaxAcceleration); return body->getMaxAcceleration(); }
		void setbodyTexture(SDL_Texture* Texture);
		std::vector<Node*> path;
		std::string getMood() const { return mood; }


		std::vector<Node*> setpath(std::vector<Node*>path_) { path = path_; return path; }
		std::vector<Node*> getpath() { return path; };
		Vec3 Targetpos;
		bool scene2 = false;
		Vec3 setTargetPos(Vec3 Targetpos_) { Targetpos = Targetpos_; return Targetpos; }
		bool OnCreate(Scene * scene_);
		bool myNpcCollidesWithWall();
		void OnDestroy() {};
		bool readDecisionTreeFromFile(string file);
		bool setTextureWith(string file);
		void Update(float time);
		Vec3 getMouseclick() { return Mouseclick; }
		void steerToSeekPlayer(SteeringOutput* steering);
		void steerToRandom(SteeringOutput* steering);
		void setMood(std::string mood_);
		float getInitialNpcAcceleration() const;
		float getInitialNpcSpeed() const;
		void HandleEvents(const SDL_Event & event);
		void render(float scale = 1.0f);

	};


#endif


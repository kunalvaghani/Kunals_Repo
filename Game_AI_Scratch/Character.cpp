#include "Character.h"
#include <windows.h>




bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;
	//Targetpos = Vec3(0, 0, 0);
	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 7.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		std::srand(std::time(0));
		int x = rand() % 20 +2;
		int y = rand() % 10 +2;
		body = new KinematicBody(
		  Vec3(x,y,0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
		mood = "Normal";
		IntialNpcAccelration = maxAcceleration;
		IntialNpcSpeed = maxSpeed;
		
	}
	if (!body)
	{
		return false;
	}
	SDL_Surface* angryImage = IMG_Load("angry.png");
	NpcangryTexture = SDL_CreateTextureFromSurface(scene_->game->getRenderer(), angryImage);

	SDL_Surface* excitedImage = IMG_Load("excited.png");
	NpcExcitedTexture = SDL_CreateTextureFromSurface(scene_->game->getRenderer(), excitedImage);

	SDL_Surface* normalImage = IMG_Load("smile.png");
	NpcNormalTexture = SDL_CreateTextureFromSurface(scene_->game->getRenderer(), normalImage);

	return true;
}
bool Character::myNpcCollidesWithWall()
{
	Vec3 pos = body->getPos();

	float radius = body->getRadius();
	if (pos.x < radius)
	{
		body->setVel(Vec3(1, 0, 0));
	}

	if (pos.y < radius)
	{
		body->setVel(Vec3(0, 1, 0));
	}
	if (pos.x > scene->game->getSceneWidth() - radius)
	{
		body->setVel(Vec3(-1, 0, 0));
	}
	if (pos.y > scene->game->getSceneHeight() - radius)
	{
		body->setVel(Vec3(0, -1, 0));
	}
	return false;
}
void Character::steerToSeekPlayer(SteeringOutput* steering)
{
	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	std::vector<SteeringOutput*> steering_outputs;

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algorithm = new Seek(body, scene->game->getPlayer()->getPos());
	// create some more algorithms and push their get steering onto the outputs list

	steering_outputs.push_back(steering_algorithm->getSteering());
	// add together some steering results
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	// clean up memory
	// (delete only those objects created in this function)
	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}
void Character::steerToRandom(SteeringOutput* steering)
{
	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	std::vector<SteeringOutput*> steering_outputs;

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algorithm = new Arrive(body, scene->game->getrandompoint());
	// create some more algorithms and push their get steering onto the outputs list

	steering_outputs.push_back(steering_algorithm->getSteering());
	// add together some steering results
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	// clean up memory
	// (delete only those objects created in this function)
	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}
void Character::setMood(std::string mood_)
{
	mood = mood_;
}

float Character::getInitialNpcAcceleration() const
{
	return IntialNpcAccelration;
}

float Character::getInitialNpcSpeed() const
{
	return IntialNpcSpeed;
}

// Update the existing functions
bool Character::readDecisionTreeFromFile(string file)
{
	// Gail is faking it here, not actually reading a file
	if (file == "seek")
	{
		decisionTree = new Action(ACTION_SET::SEEK);
		return true;
	}
	else if (file == "random")
	{
		decisionTree = new Action(ACTION_SET::RANDOM);
		return true;
	}
	else if (file == "seekIfInRange")
	{
		DecisionTreeNode* trueNode = new Action(ACTION_SET::SEEK);
		DecisionTreeNode* falseNode = new Action(ACTION_SET::RANDOM);
		decisionTree = new PlayerInRange(trueNode, falseNode, this);
		return true;
	}

	return false;
}


bool Character::setTextureWith(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture) 
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	body->setTexture(texture);
}

void Character::setbodyTexture(SDL_Texture* Texture)
{
	body->setTexture(Texture);
}

void Character::Update(float deltaTime)
{
	// create a new overall steering output
	Vec3 fetchPosition;
	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);

	// create a new overall steering output
	SteeringOutput* steering = new SteeringOutput();	// initialized to zero


	//if (true || ( mouseState && SDL_BUTTON(SDL_BUTTON_LEFT))) 
		Vec3 clickPosition(x, y, 0.0f);
		Vec3 WorldCoord = scene->getinverseProjectionMatrix() * clickPosition;
		Mouseclick = WorldCoord;

		if (scene2 == false) {

			if (decisionTree)
			{
				DecisionTreeNode* action = decisionTree->makeDecision();
				SteeringBehaviour* steering_algorithm;
				switch ((static_cast<Action*>(action))->getValue())
				{
				case ACTION_SET::SEEK:
					steerToSeekPlayer(steering);
					break;
				case ACTION_SET::RANDOM:
					steerToRandom(steering);
					break;
				case ACTION_SET::DO_NOTHING:
					break;

				default:
					break;
				}
			}

		}

		else if(scene2 == true){
			if ((mouseState && SDL_BUTTON(SDL_BUTTON_LEFT))) {
				SteeringBehaviour* steering_algorithm = new Arrive(body, Targetpos);
				steering = steering_algorithm->getSteering();
			}
		}
		else {}

	if (!myNpcCollidesWithWall()) { body->Update(deltaTime, steering); }
}


void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render(float scale)
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
}

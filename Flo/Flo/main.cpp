#include "pch.h"
#include "Math.h"
#include <box2d\Box2D.h>

using namespace std;


template<class T>
class Singleton
{
	static T *singleton;
	Singleton(){};
public:
	static T* getSingleton()
	{
		if(!singleton)
			singleton = new T;
		return singleton;
	}
};

class InputManager:public Singleton<InputManager>
{
};

class AudioManager:public Singleton<AudioManager>
{
};



class IRenderable
{
public:
	virtual void render()=0;
};

class IUpdateable
{
	public:
	virtual void update(float dt)=0;
};


class ScreenObject:public IUpdateable,public IRenderable
{
public:
	void init()
	{
	}
	void update(float dt)
	{
	}
	void render()
	{
	}
};

class ScreenManager
{
public:
	vector<ScreenObject *> objects;
};

//simple wrapper for physics
class PhysicsObject:public IUpdateable
{
	//box2d objects
	b2BodyDef *bodyDef;
	b2Shape *shape;

	virtual void update(float dt)
	{
	}
};

class PhysicsManager:public IUpdateable
{
	b2World *world;
	b2Vec2 gravity;
	bool sleep;
public:
	PhysicsManager()
	{
		gravity = b2Vec2(0,-10);
		sleep=true;
	}
	void init()
	{
		world = new b2World(gravity,sleep);
	}
	virtual void update(float dt)
	{
		world->Step(dt,4,4);
	}
};

class AIManager:public IUpdateable
{
public:
	virtual void update(float dt)
	{
	}
};

class SceneNode:public IUpdateable,public IRenderable,public Transformable,public PhysicsObject
{
	SceneManager *scene;

public:
	SceneNode(SceneManager *sceneManager)
	{
		scene = sceneManager;
	}
	virtual void init()
	{
	}
	virtual void update(float dt)
	{
	}
	virtual void render()
	{
	}
};

class SceneManager:public IUpdateable,public IRenderable
{
public:
	//main scene node
	SceneNode *rootNode;

	//physics world
	PhysicsManager *physics;

	//AI world
	AIManager *ai;

	SceneManager()
	{
		//create and initialize components
		rootNode = new SceneNode(this);
		physics = new PhysicsManager();
		ai = new AIManager();
	}
	virtual void update(float dt)
	{
		rootNode->update(dt);
		ai->update(dt);
		physics->update(dt);
	}
	void render()
	{
		rootNode->render();
	}
};



class StateManager
{
};

class State
{
};

class Flo:public Singleton<Flo>
{
	//sdl stuff
	SDL_Surface * screen;

	//game classes
	InputManager *input;
	AudioManager *audio;

	//this determines if the engine is running
	bool running;
public:
	void init()
	{
		//initilize sdl
		SDL_Init(SDL_INIT_EVERYTHING);
		screen = SDL_SetVideoMode(800,600,32,SDL_OPENGL|SDL_DOUBLEBUF|SDL_HWSURFACE);

		input = InputManager::getSingleton();
		audio = AudioManager::getSingleton();

		running = false;
	}
	void run()
	{
		running = true;
		//initialize some stuff

		while(running)
		{

		}
	}
	void quit()
	{
		running = false;
	}
};

int main(int args,char **argv)
{

	Flo *flo = Flo::getSingleton();

	flo->run();
	return 0;
}
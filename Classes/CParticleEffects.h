#ifndef __CPARTICLE_EFFECTS_H__
#define __CPARTICLE_EFFECTS_H__

#include "cocos2d.h"
#include "CParticleSystem.h"

class CParticleEffects
{
private:
	CParticleSystem _Particle;
	CParticleSystem _Particle_2;

	bool FireworkOn;
	bool FireworkEnd;
	int FireType = 3;
	cocos2d::Point FireworkPos;

	bool ElveOn;
	bool ElveEnd;
	bool ElveVisible;
	cocos2d::Point ElvePos;

	bool TornadoOn;
	bool TornadoEnd;
	bool TornadoVisible;

	bool FlowerOn;
	bool FlowerEnd;
	bool FlowerVisible;
	cocos2d::Point FlowerPos;

	bool touch = false;

	int x = 0;
	float speedx;
	float speedy;
	float time;
	bool Particle_Pt = false;
	float GetWind;
	float GetWindDir;
public:
	CParticleEffects();
	~CParticleEffects();
	void init(cocos2d::Layer &inlayer);
	void doStep(float dt);
	void SetFirework(bool bEm, cocos2d::Point loc);
	void SetElve(bool bEm, cocos2d::Point loc);
	void SetTornado(bool bEm, cocos2d::Point loc);
	void SetFlower(bool bEm, cocos2d::Point loc);

	void SetGravity(float gravity);
	void SetSpread(float spread);
	void SetDirection(float direction);
	void SetSpin(float spin);
	void SetOpacity(int opacity);
	void SetParticles(int particles);
	void SetSpeed(float speed);
	void SetLifetime(float lifetime);
	void SetColorR(int R);
	void SetColorG(int G);
	void SetColorB(int B);
	void SetWindDirection(float winddirection);
	void SetWind(float wind);
	void SetType(int type);
};

#endif

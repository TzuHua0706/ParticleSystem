#include "CParticleEffects.h"

#define CR 150

USING_NS_CC;

#define FALLING_TIME 2.5f
#define MAX_HEIGHT 720.0f
#define PIXEL_PERM (2.0f*MAX_HEIGHT/(9.8f*FALLING_TIME*FALLING_TIME))
#define LIFE_NOISE(f) ((f)*(1.0f-(rand()%2001/1000.0f)))

CParticleEffects::CParticleEffects(){
	FireworkOn = false;
	ElveOn = false;
	ElveVisible = false;
	TornadoOn = false;
	TornadoVisible = false;
	FlowerOn = false;
	FlowerVisible = false;
	auto _fElapsedTime = rand() % 100 / 1000.0f / 8;
	auto _fLifeTime = LIFE_NOISE(0.15f);
	auto cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
	auto t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
	speedx = cosf(t)*cost * 5 * PIXEL_PERM /** cosf(dt) * dt*/;
	speedy = sinf(t)*cost * 5 * PIXEL_PERM /** cosf(dt) * dt*/;
}
CParticleEffects::~CParticleEffects() {}
void CParticleEffects::init(cocos2d::Layer &inlayer)
{
	_Particle._cSprite = Sprite_0;
	_Particle.init(inlayer);
	_Particle._fDir = 90.0;
	_Particle._iNumParticles = 100;
	_Particle._iGenParticles = 0;
	_Particle._fSpread = 180.0f;
	_Particle._fVelocity = 2.5;	 // 分子的離開速度
	_Particle._fLifeTime = 3.5f;	 // 分子的存活時間
	_Particle._fGravity = 0;
	_Particle._fSpin = 0;
	_Particle._iOpacity = 255;
	_Particle._iRed = 255;
	_Particle._iGreen = 255;
	_Particle._iBlue = 255;
	_Particle._fWindDirection = 90;
	_Particle._fElpasedTime = 0;

	_Particle_2._cSprite = Sprite_0;
	_Particle_2.init(inlayer);
	_Particle_2._fDir = 90.0;
	_Particle_2._iNumParticles = 100;
	_Particle_2._iGenParticles = 0;
	_Particle_2._fSpread = 180.0f;
	_Particle_2._fVelocity = 2.5;	 // 分子的離開速度
	_Particle_2._fLifeTime = 3.5f;	 // 分子的存活時間
	_Particle_2._fGravity = 0;
	_Particle_2._fSpin = 0;
	_Particle_2._iOpacity = 255;
	_Particle_2._iRed = 255;
	_Particle_2._iGreen = 255;
	_Particle_2._iBlue = 255;
	_Particle_2._fWindDirection = 90;
	_Particle_2._fElpasedTime = 0;
}
void CParticleEffects::doStep(float dt)
{
	_Particle.doStep(dt); 
	_Particle_2.doStep(dt);
	if (FireworkOn) {
		if (Particle_Pt) {
			_Particle._emitterPt.x += GetWind*dt*60*(cosf(GetWindDir / (180 / M_PI)));
		}
		if (_Particle._emitterPt.y < FireworkPos.y + 500) {
			_Particle._cSprite = Sprite_3;
			_Particle._fSize = -0.5f;
			_Particle._fVelocity = 0.5f;
			_Particle._fLifeTime = 0.3f;
			_Particle._emitterPt.y += 1200 * dt;
			FireworkEnd = false;
		}
		else if(!FireworkEnd){
			//_Particle.setEmitter(false);
			_Particle._cSprite = Sprite_0;
			_Particle._fSize = 0.125f;
			_Particle.setType(FireType);
			_Particle.onTouchesBegan(Point(_Particle._emitterPt.x, _Particle._emitterPt.y));
			_Particle._emitterPt = FireworkPos;
			FireworkEnd = true;
		}
	}
	else if (ElveOn) {
		ElveVisible = true;
		if (!ElveEnd) {
			_Particle._fLifeTime = 5.0f;
			_Particle._fVelocity = 0.5f;
			_Particle._fSize = -1.0f;
			if (_Particle._emitterPt.y < ElvePos.y-5) {
				_Particle._emitterPt.y += rand() % 400 * dt;
			}
			else if (_Particle._emitterPt.y > ElvePos.y+5) {
				_Particle._emitterPt.y -= rand() % 400 * dt;
			}
			if (_Particle._emitterPt.x < ElvePos.x-5) {
				_Particle._emitterPt.x += rand() % 400 * dt;
			}
			else  if (_Particle._emitterPt.x > ElvePos.x+5) {
				_Particle._emitterPt.x -= rand() % 400 * dt;
			}
			else if(_Particle._emitterPt.y < ElvePos.y+5 && _Particle._emitterPt.y > ElvePos.y-5)
				ElveEnd = true;
		}
		else {
			//_Particle._cSprite = Sprite_0;
			_Particle._fLifeTime = 3.5f;
			_Particle._fVelocity = 1.5f; 
			//_Particle._fSize = 0.125f;
			if (_Particle._iOpacity > 0)_Particle._iOpacity -= 5 * dt;
		}
	}
	else if (TornadoOn) {
		if (Particle_Pt) {
			_Particle._emitterPt.x += GetWind*(cosf(GetWindDir / (180 / M_PI)));
		}
		if (_Particle._emitterPt.y > 100) {
			_Particle._cSprite = Sprite_1;
			_Particle._fSize = -1.5f;
			_Particle._fVelocity = 0;
			_Particle.setGravity(dt);
			_Particle._iOpacity = 150;
			_Particle._fLifeTime = 1.0f * 120 * dt;
			_Particle._emitterPt.y -= dt * 120;
		}
		else {
			_Particle_2.setEmitter(true);
			_Particle_2._cSprite = Sprite_1;
			_Particle_2._fSize = -1.0f;
			_Particle_2._iOpacity = 255;
			_Particle_2._fLifeTime = 1.0f;
			_Particle_2._fVelocity = 5;
			_Particle_2.setGravity(10);
			time += dt * 60;
			if (time > 8) {
				touch = false;
				_Particle_2.setEmitter(false);
				_Particle._emitterPt = Point(400, 680);
				time = 0;
			}
		}

		/*_Particle._cSprite = Sprite_5;
		_Particle._fVelocity = 0;
		_Particle._fSpread = 0;
		_Particle._fDir += 3000 * dt;
		_Particle._fWindDirection = 0;
		_Particle._fWind = 10;
		_Particle._fSpin = 120;
		_Particle._fLifeTime = 7.0f;*/
		
		//_Particle._cSprite = Sprite_5;
		//_Particle_2._cSprite = Sprite_3;
		//_Particle._fVelocity = 1.0f;
		//_Particle_2._fVelocity = 1.2f;
		//_Particle._fSpread = 0;
		//_Particle_2._fSpread = 100;
		//_Particle._fDir += 1500 * dt;
		//_Particle._fWindDirection = 90;
		//_Particle._fWind = 10;
		///*_Particle_2._fWindDirection = 0;
		//_Particle_2._fWind = 1;*/
		//_Particle._fSpin = 15;
		//_Particle._fLifeTime = 3.5;
		//_Particle_2._fLifeTime = 7;
	}
	else if (FlowerOn) {
		_Particle._fSpread = 0;
		_Particle._fDir += 360 / 9; //花瓣數
		time += dt;
		auto pos = FlowerPos;
		auto dx = (FlowerPos.x - _Particle._emitterPt.x);
		auto dy = (FlowerPos.y - _Particle._emitterPt.y);
		if (dx < 0)dx = dx * -1;
		if (dy < 0)dy = dy * -1;
		if (touch) {
			if (time >= ((dx-250) / speedx)) {
				if (x < 180) {
					_Particle.setFlower(time, x, FlowerPos, speedx);
				}
				x += dt * 60;
				if (x >= 180) {
					touch = false;
				}
			}
		}
	}
	else {
		_Particle.setEmitter(false);
		_Particle_2.setEmitter(false);
		ElveVisible = false;
		TornadoVisible = false;
		FlowerVisible = false;
	}
}
void CParticleEffects::SetFirework(bool bEm, cocos2d::Point loc) {
	_Particle._cSprite = Sprite_3;
	FireworkEnd = false;
	FireworkPos = loc;
	_Particle._emitterPt = loc;
	_Particle.setEmitter(bEm);
	FireworkOn = bEm;
}
void CParticleEffects::SetElve(bool bEm, cocos2d::Point loc) {
	_Particle._cSprite = Sprite_6;
	_Particle._iNumParticles = 50;
	_Particle._iOpacity = 255;
	ElveEnd = false;
	ElvePos = loc;
	if (!ElveVisible) {
		_Particle._emitterPt = Point(640, 360);
		_Particle.setEmitter(bEm);
	}
	ElveOn = bEm;
}
void CParticleEffects::SetTornado(bool bEm, cocos2d::Point loc) {
	TornadoEnd = false;
	if (!TornadoVisible) {
		_Particle._iNumParticles = 50;
		_Particle._emitterPt = Point(400, 680);
		_Particle.setEmitter(bEm);
		_Particle_2._emitterPt = Point(400, 100);
		/*_Particle_2._iNumParticles = 50;
		_Particle_2._emitterPt = Point(950, 360);
		_Particle_2.setEmitter(bEm);*/
		/*_Particle_2._iNumParticles = 35;
		_Particle_2._iOpacity = 150;
		_Particle_2._emitterPt = Point(400, 50);
		_Particle_2.setEmitter(bEm);*/
		TornadoVisible = true;
	}
	else {
		touch = true;
	}
	TornadoOn = bEm;
}
void CParticleEffects::SetFlower(bool bEm, cocos2d::Point loc) {
	FlowerEnd = false;
	if (!FlowerVisible) {
		_Particle._iNumParticles = 65;
		_Particle._emitterPt = Point(400, 360);
		_Particle.setEmitter(bEm);
		FlowerVisible = true;
	}
	else {
		x = 0;
		time = 0;
		FlowerPos = loc;
		_Particle.setType(9);
		_Particle.onTouchesBegan(FlowerPos);
		touch = true;
	}
	FlowerOn = bEm;
}
void CParticleEffects::SetGravity(float gravity) {
	_Particle.setGravity(gravity);
}
void CParticleEffects::SetSpread(float spread) {
	_Particle._fSpread = spread;
}
void CParticleEffects::SetDirection(float direction) {
	_Particle._fDir = direction;
}
void CParticleEffects::SetSpin(float spin) {
	_Particle._fSpin = spin;
}
void CParticleEffects::SetOpacity(int opacity) {
	_Particle._iOpacity = opacity;
}
void CParticleEffects::SetParticles(int particles) {
	_Particle._iNumParticles = particles;
}
void CParticleEffects::SetSpeed(float speed) {
	_Particle._fVelocity = speed;
}
void CParticleEffects::SetLifetime(float lifetime) {
	_Particle._fLifeTime = lifetime;
}
void CParticleEffects::SetColorR(int R) {
	_Particle._iRed = R;
	_Particle_2._iRed = R;
}
void CParticleEffects::SetColorG(int G) {
	_Particle._iGreen = G;
	_Particle_2._iGreen = G;
}
void CParticleEffects::SetColorB(int B) {
	_Particle._iBlue = B;
	_Particle_2._iBlue = B;
}
void CParticleEffects::SetWindDirection(float winddirection) {
	_Particle.setWindDirection(winddirection);
	GetWindDir = winddirection;
}
void CParticleEffects::SetWind(float wind) {
	_Particle.setWind(wind); 
	Particle_Pt = true;
	GetWind = wind;
}
void CParticleEffects::SetType(int type) {
	if (type < 3)FireType = 3;
	else if (type < 6)FireType = type;
	else FireType = 3;
}
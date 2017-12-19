#ifndef __CPARTICLE_H__
#define __CPARTICLE_H__

#define STAY_FOR_TWOSECONDS 0	// �b����ƹL���a�貣�� particle
#define RANDOMS_FALLING     1	// �b����ƹL���a�詹�U���� particle
#define FREE_FLY 2				// �b����ƹL���a����N�V�|�貣�� particle
#define EXPLOSION 3				// �Q�g�X��Ϊ��Ϥ�
#define HEARTSHAPE 4			// �Q�g�X�߫����Ϥ�
#define BUTTERFLYSHAPE	5		// �Q�g�X�����~�����Ϥ�

#define EMITTER_DEFAULT 99
#include "cocos2d.h"

class CParticle
{
private:
	cocos2d::Sprite *_Particle;	// ���l����
	cocos2d::Point  _OldPos;		// ���l�e�@�Ӧ�m
	cocos2d::Point  _Pos;			// ���l�ثe����m
	cocos2d::Point  _Direction;	// ���l�ثe���B�ʤ�V�A���V�q

	float _fVelocity;	// ���l���t��
	float _fLifeTime;	// �ͩR�g��
	float _fIntensity;// ���l��q���̤j�ȡA�q�`�Ω���ܤ��l���C��
	float _fOpacity;	// �ثe���l���z����
	float _fSpin;		// ���l������q
	float _fSize;		// ���l���j�p
	float _fGravity;	// ���l���j�p
	cocos2d::Color3B _color;	// ���l���C��
	// �ɶ�
	float _fElapsedTime; // ���l�q��ܨ�ثe����ɶ�
	float _fDelayTime;	 // ���l��ܫe������ɶ�
	// �欰�Ҧ�
	int _iType;
	// ��ܻP�_
	bool _bVisible;
	
public:
	CParticle();
	void setParticle(const char *pngName, cocos2d::Layer &inlayer);

	bool doStep(float dt);
	void setPosition(const cocos2d::Point &inPos);
	void setColor(cocos2d::Color3B &color) { _color = color;}
	void setBehavior(int iType); // �]�w���l���ͪ��_�l�欰�Ҧ�
	void setVisible();
	void setGravity(const float fGravity);
	void setVelocity(const float v) { _fVelocity = v; }
	void setLifetime(const float lt);
	void setDirection(const cocos2d::Point pt) { _Direction = pt; }
	void setSize(float s) { _fSize = s; _Particle->setScale(_fSize); }
};

#endif
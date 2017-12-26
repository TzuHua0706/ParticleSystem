#ifndef __PARTICLESYSTEM_SCENE_H__
#define __PARTICLESYSTEM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "CParticleEffects.h"
#include "Common/CSwitchButton.h"
#include "Common/CDraggableSprite.h"


class ParticleSystemScene : public cocos2d::Layer
{
private:
	cocos2d::Node * rootNode;
	// ���l���i���㤣�P�Ѽƪ����
	cocos2d::ui::TextBMFont *_GravityBMValue;
	cocos2d::ui::TextBMFont *_SpreadBMValue;
	cocos2d::ui::TextBMFont *_DirectionBMValue;
	cocos2d::ui::TextBMFont *_SpinBMValue;
	cocos2d::ui::TextBMFont *_OpacityBMValue;
	cocos2d::ui::TextBMFont *_ParticlesBMValue;
	cocos2d::ui::TextBMFont *_SpeedBMValue;
	cocos2d::ui::TextBMFont *_LifetimeBMValue;
	cocos2d::ui::TextBMFont *_ColorRBMValue;
	cocos2d::ui::TextBMFont *_ColorGBMValue;
	cocos2d::ui::TextBMFont *_ColorBBMValue;
	cocos2d::ui::TextBMFont *_WindDirectionBMValue;
	cocos2d::ui::TextBMFont *_WindBMValue;

	// ��ܤ��P�����l���A�A�Φb Emitter �S���}�Ҫ����A
	cocos2d::ui::TextBMFont *_TypeBMValue;

	// For Emitter
	CDraggableSprite *_EmitterSprite;
	bool _bEmitterOn;
	CSwitchButton *_emitterSwitchBtn;

	//���l�˦�
	bool _bSpriteOn;
	CSwitchButton *_FlareBtn;
	CSwitchButton *_BubbleBtn;
	CSwitchButton *_CircleBtn;
	CSwitchButton *_CloudBtn;
	CSwitchButton *_CometBtn;
	CSwitchButton *_RaindropBtn;
	CSwitchButton *_SparkBtn;

	//�S��
	bool _bEffectsOn;
	CSwitchButton *_FireworkBtn;
	CParticleEffects _FireworkEffect;
	CSwitchButton *_ElveBtn;
	CParticleEffects _ElveEffect;
	CSwitchButton *_TornadoBtn;
	CParticleEffects _TornadoEffect;
	CSwitchButton *_FlowerBtn;
	CParticleEffects _FlowerEffect;

	cocos2d::Point pos_back;
	cocos2d::Point pos_none;
public:

	CParticleSystem _ParticleControl;

	~ParticleSystemScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void doStep(float dt);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�}�l�ƥ�
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I���ʨƥ�
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�����ƥ� 

	void GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ColorREvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ColorGEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ColorBEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void WindDirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(ParticleSystemScene);
};

#endif // __MAIN_SCENE_H__

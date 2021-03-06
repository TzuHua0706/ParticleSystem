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
	// 分子的可提整不同參數的顯示
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

	// 選擇不同的分子型態，用在 Emitter 沒有開啟的狀態
	cocos2d::ui::TextBMFont *_TypeBMValue;

	// For Emitter
	CDraggableSprite *_EmitterSprite;
	bool _bEmitterOn;
	CSwitchButton *_emitterSwitchBtn;

	//分子樣式
	bool _bSpriteOn;
	CSwitchButton *_FlareBtn;
	CSwitchButton *_BubbleBtn;
	CSwitchButton *_CircleBtn;
	CSwitchButton *_CloudBtn;
	CSwitchButton *_CometBtn;
	CSwitchButton *_RaindropBtn;
	CSwitchButton *_SparkBtn;

	//特效
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

	int iType;

public:

	CParticleSystem _ParticleControl;

	~ParticleSystemScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void doStep(float dt);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

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

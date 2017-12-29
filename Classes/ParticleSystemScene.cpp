#include "ParticleSystemScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

Scene* ParticleSystemScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ParticleSystemScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

ParticleSystemScene::~ParticleSystemScene()
{
	this->removeAllChildren();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

// on "init" you need to initialize your instance
bool ParticleSystemScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);

	rootNode->getChildByName("Slider")->setVisible(false);
	rootNode->getChildByName("Sprite")->setVisible(false);
	_bSpriteOn = false;
	_bEffectsOn = false;
	pos_back = Point(80, 670);
	pos_none = Point(-200, -200);

	//Button
	// For Emitter
	_EmitterSprite = CDraggableSprite::create();
	_EmitterSprite->setSpriteInfo("emittericon.png", Point(-125.0f + visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	_EmitterSprite->setVisible(false);
	_bEmitterOn = false;
	this->rootNode->getChildByName("Emitter")->addChild(_EmitterSprite, 5);
	auto emitterpos = (Sprite *)(rootNode->getChildByName("Emitter")->getChildByName("emitterpos"));
	Point pos_emit = emitterpos->getPosition();
	emitterpos->setVisible(false);
	_emitterSwitchBtn = CSwitchButton::create();
	_emitterSwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", pos_emit);
	this->rootNode->getChildByName("Emitter")->addChild(_emitterSwitchBtn, 2);
	
	//Sprite
	auto flarepos = (Sprite *)(rootNode->getChildByName("Sprite")->getChildByName("Flare"));
	Point pos_flare = flarepos->getPosition();
	flarepos->setVisible(false);
	_FlareBtn = CSwitchButton::create();
	_FlareBtn->setButtonInfo(Sprite_0, Sprite_0, Sprite_0, pos_flare);
	this->rootNode->getChildByName("Sprite")->addChild(_FlareBtn, 2);

	auto bubblepos = (Sprite *)(rootNode->getChildByName("Sprite")->getChildByName("Bubble"));
	Point pos_bubble = bubblepos->getPosition();
	bubblepos->setVisible(false);
	_BubbleBtn = CSwitchButton::create();
	_BubbleBtn->setButtonInfo(Sprite_1, Sprite_1, Sprite_1, pos_bubble);
	this->rootNode->getChildByName("Sprite")->addChild(_BubbleBtn, 2);

	auto circlepos = (Sprite *)(rootNode->getChildByName("Sprite")->getChildByName("Circle"));
	Point pos_circle = circlepos->getPosition();
	circlepos->setVisible(false);
	_CircleBtn = CSwitchButton::create();
	_CircleBtn->setButtonInfo(Sprite_2, Sprite_2, Sprite_2, pos_circle);
	this->rootNode->getChildByName("Sprite")->addChild(_CircleBtn, 2);

	auto cloudpos = (Sprite *)(rootNode->getChildByName("Sprite")->getChildByName("Cloud"));
	Point pos_cloud = cloudpos->getPosition();
	cloudpos->setVisible(false);
	_CloudBtn = CSwitchButton::create();
	_CloudBtn->setButtonInfo(Sprite_3, Sprite_3, Sprite_3, pos_cloud);
	this->rootNode->getChildByName("Sprite")->addChild(_CloudBtn, 2);

	auto cometpos = (Sprite *)(rootNode->getChildByName("Sprite")->getChildByName("Comet"));
	Point pos_comet = cometpos->getPosition();
	cometpos->setVisible(false);
	_CometBtn = CSwitchButton::create();
	_CometBtn->setButtonInfo(Sprite_4, Sprite_4, Sprite_4, pos_comet);
	this->rootNode->getChildByName("Sprite")->addChild(_CometBtn, 2);

	auto raindroppos = (Sprite *)(rootNode->getChildByName("Sprite")->getChildByName("Raindrop"));
	Point pos_raindrop = raindroppos->getPosition();
	raindroppos->setVisible(false);
	_RaindropBtn = CSwitchButton::create();
	_RaindropBtn->setButtonInfo(Sprite_5, Sprite_5, Sprite_5, pos_raindrop);
	this->rootNode->getChildByName("Sprite")->addChild(_RaindropBtn, 2);

	auto sparkpos = (Sprite *)(rootNode->getChildByName("Sprite")->getChildByName("Spark"));
	Point pos_spark  = sparkpos->getPosition();
	sparkpos->setVisible(false);
	_SparkBtn = CSwitchButton::create();
	_SparkBtn->setButtonInfo(Sprite_6, Sprite_6, Sprite_6, pos_spark);
	this->rootNode->getChildByName("Sprite")->addChild(_SparkBtn, 2);

	//特效
	auto firework = (Sprite *)(rootNode->getChildByName("Effects")->getChildByName("Firework"));
	Point pos_fire = firework->getPosition();
	firework->setVisible(false);
	_FireworkBtn = CSwitchButton::create();
	_FireworkBtn->setButtonInfo("firework.png", "back.png", "none.png", pos_fire);
	this->rootNode->getChildByName("Effects")->addChild(_FireworkBtn, 2);

	auto elve = (Sprite *)(rootNode->getChildByName("Effects")->getChildByName("Effect_2"));
	Point pos_elve = elve->getPosition();
	elve->setVisible(false);
	_ElveBtn = CSwitchButton::create();
	_ElveBtn->setButtonInfo("elve.png", "back.png", "none.png", pos_elve);
	this->rootNode->getChildByName("Effects")->addChild(_ElveBtn, 2);

	auto Tornado = (Sprite *)(rootNode->getChildByName("Effects")->getChildByName("Effect_3"));
	Point pos_Tornado = Tornado->getPosition();
	Tornado->setVisible(false);
	_TornadoBtn = CSwitchButton::create();
	_TornadoBtn->setButtonInfo("wind.png", "back.png", "none.png", pos_Tornado);
	this->rootNode->getChildByName("Effects")->addChild(_TornadoBtn, 2);

	auto flower = (Sprite *)(rootNode->getChildByName("Effects")->getChildByName("Effect_4"));
	Point pos_flower = flower->getPosition();
	flower->setVisible(false);
	_FlowerBtn = CSwitchButton::create();
	_FlowerBtn->setButtonInfo("flower.png", "back.png", "none.png", pos_flower);
	this->rootNode->getChildByName("Effects")->addChild(_FlowerBtn, 2);

	_FireworkEffect.init(*this);
	_ElveEffect.init(*this);
	_TornadoEffect.init(*this);
	_FlowerEffect.init(*this);
	
	// Particle Control System
	// 最好的方式是，以下的 Slider 根據這裡的設定值，顯示出正確的數值與位置
	_ParticleControl._cSprite = Sprite_0;
	_ParticleControl.init(*this);
	_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	_ParticleControl._fDir = 90.0;
	_ParticleControl._iNumParticles = 100;
	_ParticleControl._iGenParticles = 0;
	_ParticleControl._fSpread = 180.0f;
	_ParticleControl._fVelocity = 2.5;	 // 分子的離開速度
	_ParticleControl._fLifeTime = 3.5f;	 // 分子的存活時間
	_ParticleControl._fGravity = 0;
	_ParticleControl._fSpin = 0;
	_ParticleControl._iOpacity = 255;
	_ParticleControl._iRed = 255;
	_ParticleControl._iGreen = 255;
	_ParticleControl._iBlue = 255;
	_ParticleControl._fWindDirection = 90;
	_ParticleControl._fElpasedTime = 0;
	_ParticleControl.setType(STAY_FOR_TWOSECONDS); // 分子運動的型態，預設為 0
	_ParticleControl._windDir = Point(0, 0); // 本範例沒有實作此項功能

	// 分子的可調整參數的捲動軸
	// Slider of Gravity
	auto *GravitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Gravity")->getChildByName("Slider_Gravity"));
	GravitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::GravityEvent, this));
	GravitySlider->setMaxPercent(100); 	// 將 0 到 100 對應到 -10 到 10 之間
	_GravityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Gravity")->getChildByName("GravityBMFont");

	// Slider of Spread
	auto *SpreadSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Spread")->getChildByName("Slider_Spread"));
	SpreadSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpreadEvent, this));
	SpreadSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 180 之間
	_SpreadBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Spread")->getChildByName("SpreadBMFont");

	// Slider of Direction
	auto *DirectionSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Direction")->getChildByName("Slider_Direction"));
	DirectionSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::DirectionEvent, this));
	DirectionSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_DirectionBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Direction")->getChildByName("DirectionBMFont");

	// Slider of Spin
	auto *SpinSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Spin")->getChildByName("Slider_Spin"));
	SpinSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpinEvent, this));
	SpinSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 60 之間
	_SpinBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Spin")->getChildByName("SpinBMFont");

	// Slider of Opacity
	auto *OpacitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Opacity")->getChildByName("Slider_Opacity"));
	OpacitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::OpacityEvent, this));
	OpacitySlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 255 之間
	_OpacityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Opacity")->getChildByName("OpacityBMFont");

	// Slider of Particles
	auto *ParticlesSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Particles")->getChildByName("Slider_Particles"));
	ParticlesSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ParticlesEvent, this));
	ParticlesSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 200 之間
	_ParticlesBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Particles")->getChildByName("ParticlesBMFont");

	// Slider of Speed
	auto *SpeedSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Speed")->getChildByName("Slider_Speed"));
	SpeedSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpeedEvent, this));
	SpeedSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 40 之間
	_SpeedBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Speed")->getChildByName("SpeedBMFont");

	// Slider of Lifetime
	auto *LifetimeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Lifetime")->getChildByName("Slider_Lifetime"));
	LifetimeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::LifetimeEvent, this));
	LifetimeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 7 之間
	_LifetimeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Lifetime")->getChildByName("LifetimeBMFont");

	// Slider of Color
	auto *ColorRSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("Slider_Red"));
	ColorRSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorREvent, this));
	ColorRSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 255 之間
	_ColorRBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("RedBMFont");
	auto *ColorGSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("Slider_Green"));
	ColorGSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorGEvent, this));
	ColorGSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 255 之間
	_ColorGBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("GreenBMFont");
	auto *ColorBSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("Slider_Blue"));
	ColorBSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorBEvent, this));
	ColorBSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 255 之間
	_ColorBBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("BlueBMFont");

	// Slider of WindDirection
	auto *WindDirectionSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("Slider_WindDirection"));
	WindDirectionSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::WindDirectionEvent, this));
	WindDirectionSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 -180 到 180 之間
	_WindDirectionBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("WindDirectionBMFont");

	// Slider of Wind
	auto *WindSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("Slider_Wind"));
	WindSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::WindEvent, this));
	WindSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 10 之間
	_WindBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("WindBMFont");

	// Slider of Type
	auto *TypeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Type")->getChildByName("Slider_Type"));
	TypeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::TypeEvent, this));
	TypeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 5 之間
	_TypeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Type")->getChildByName("TypeBMFont");

	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(ParticleSystemScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(ParticleSystemScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(ParticleSystemScene::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器
	this->schedule(CC_SCHEDULE_SELECTOR(ParticleSystemScene::doStep));

    return true;
}

void ParticleSystemScene::doStep(float dt)
{
	_ParticleControl.doStep(dt);
	_FireworkEffect.doStep(dt);
	_ElveEffect.doStep(dt);
	_TornadoEffect.doStep(dt);
	_FlowerEffect.doStep(dt);
}

bool ParticleSystemScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	//顯示 Emitter 時，可拖曳該圖式
	if (_bEmitterOn) {
		_EmitterSprite->touchesBegan(touchLoc);
	}
	else if(iType <= 5){
		_FireworkBtn->touchesBegan(touchLoc);
		_FlowerBtn->touchesBegan(touchLoc);
		_TornadoBtn->touchesBegan(touchLoc);
		_ElveBtn->touchesBegan(touchLoc);
	}
	if (!_bEffectsOn && iType <= 5)_emitterSwitchBtn->touchesBegan(touchLoc);
	if (_bSpriteOn) {
		_SparkBtn->touchesBegan(touchLoc);
		_RaindropBtn->touchesBegan(touchLoc);
		_CometBtn->touchesBegan(touchLoc);
		_CloudBtn->touchesBegan(touchLoc);
		_CircleBtn->touchesBegan(touchLoc);
		_BubbleBtn->touchesBegan(touchLoc);
		_FlareBtn->touchesBegan(touchLoc);
	}
	// 沒有顯示 Emitter，而且沒有按在 Emitter 切換按鈕上，才讓 touch 可以點選顯示分子
	if (!_bEmitterOn && !_bEffectsOn) _ParticleControl.onTouchesBegan(touchLoc);
	return true;
}		 

void  ParticleSystemScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();	
	if (_bEmitterOn) {
		if (_EmitterSprite->touchesMoved(touchLoc)) // 移動並更新 Emitter 的位置
			_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	}
	// 沒有顯示 Emitter，而且沒有按在 Emitter 切換按鈕上，才讓 touch 可以點選顯示分子
	if(!_emitterSwitchBtn->touchesMoved(touchLoc) && !_bEmitterOn && !_bEffectsOn) _ParticleControl.onTouchesMoved(touchLoc);
}

void  ParticleSystemScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	if (_bEmitterOn)
		_EmitterSprite->touchesEnded(touchLoc);
	// 點在 Emitter 切換的圖示上，進行必要的狀態改變
	if (_emitterSwitchBtn->touchesEnded(touchLoc))
	{
		_ParticleControl._emitterPt = _EmitterSprite->getLoc();
		_bEmitterOn = _emitterSwitchBtn->getStatus();
		_bSpriteOn = _bEmitterOn;
		rootNode->getChildByName("Slider")->setVisible(_bEmitterOn);
		rootNode->getChildByName("Sprite")->setVisible(_bEmitterOn);
		rootNode->getChildByName("Effects")->setVisible(!_bEmitterOn);
		rootNode->getChildByName("Type")->setVisible(!_bEmitterOn);
		if (_bEmitterOn) { // 顯示 Emitter 圖示
			_EmitterSprite->setVisible(true);
		}
		else { // 關閉 Emitter 圖示
			_EmitterSprite->setVisible(false);
		}
		_ParticleControl.setEmitter(_bEmitterOn); // 更新控制系統中的 Emitter 狀態
	}

	//Sprite
	if (_bSpriteOn) {
		if (_FlareBtn->touchesEnded(touchLoc)) {
			_ParticleControl.setSprite(Sprite_0);
			_ParticleControl._cSprite = Sprite_0;
		}
		else if (_BubbleBtn->touchesEnded(touchLoc)) {
			_ParticleControl.setSprite(Sprite_1);
			_ParticleControl._cSprite = Sprite_1;
		}
		else if (_CircleBtn->touchesEnded(touchLoc)) {
			_ParticleControl.setSprite(Sprite_2);
			_ParticleControl._cSprite = Sprite_2;
		}
		else if (_CloudBtn->touchesEnded(touchLoc)) {
			_ParticleControl.setSprite(Sprite_3);
			_ParticleControl._cSprite = Sprite_3;
		}
		else if (_CometBtn->touchesEnded(touchLoc)) {
			_ParticleControl.setSprite(Sprite_4);
			_ParticleControl._cSprite = Sprite_4;
		}
		else if (_RaindropBtn->touchesEnded(touchLoc)) {
			_ParticleControl.setSprite(Sprite_5);
			_ParticleControl._cSprite = Sprite_5;
		}
		else if (_SparkBtn->touchesEnded(touchLoc)) {
			_ParticleControl.setSprite(Sprite_6);
			_ParticleControl._cSprite = Sprite_6;
		}
	}

	//特效
	_FireworkEffect.SetFirework(_FireworkBtn->getStatus(), touchLoc);
	_ElveEffect.SetElve(_ElveBtn->getStatus(), touchLoc);
	_TornadoEffect.SetTornado(_TornadoBtn->getStatus(), touchLoc);
	if (!_bEmitterOn) {
		if (_FireworkBtn->touchesEnded(touchLoc)) {
			_bEffectsOn = _FireworkBtn->getStatus();
			rootNode->getChildByName("Slider")->setVisible(_bEffectsOn);
			rootNode->getChildByName("Emitter")->setVisible(!_bEffectsOn);
			rootNode->getChildByName("Type")->setVisible(true);
			if (_bEffectsOn) {
				_FireworkBtn->Newpos(pos_back);
				_ElveBtn->Newpos(pos_none);
				_TornadoBtn->Newpos(pos_none);
				_FlowerBtn->Newpos(pos_none);
			}
			else {
				_FireworkBtn->Newpos(Point(0,0));
				_ElveBtn->Newpos(Point(0, 0));
				_TornadoBtn->Newpos(Point(0, 0));
				_FlowerBtn->Newpos(Point(0, 0));
				_FireworkEffect.SetFirework(_FireworkBtn->getStatus(), touchLoc);
			}
		}
		else if (_ElveBtn->touchesEnded(touchLoc)) {
			_bEffectsOn = _ElveBtn->getStatus();
			rootNode->getChildByName("Slider")->setVisible(_bEffectsOn);
			rootNode->getChildByName("Emitter")->setVisible(!_bEffectsOn);
			rootNode->getChildByName("Type")->setVisible(!_bEffectsOn);
			if (_bEffectsOn) {
				_FireworkBtn->Newpos(pos_none);
				_ElveBtn->Newpos(pos_back);
				_TornadoBtn->Newpos(pos_none);
				_FlowerBtn->Newpos(pos_none);
			}
			else {
				_FireworkBtn->Newpos(Point(0, 0));
				_ElveBtn->Newpos(Point(0, 0));
				_TornadoBtn->Newpos(Point(0, 0));
				_FlowerBtn->Newpos(Point(0, 0));
				_ElveEffect.SetElve(_ElveBtn->getStatus(), touchLoc);
			}
		}
		else if (_TornadoBtn->touchesEnded(touchLoc)) {
			_bEffectsOn = _TornadoBtn->getStatus();
			rootNode->getChildByName("Slider")->setVisible(_bEffectsOn);
			rootNode->getChildByName("Emitter")->setVisible(!_bEffectsOn);
			rootNode->getChildByName("Type")->setVisible(!_bEffectsOn);
			if (_bEffectsOn) {
				_FireworkBtn->Newpos(pos_none);
				_ElveBtn->Newpos(pos_none);
				_TornadoBtn->Newpos(pos_back);
				_FlowerBtn->Newpos(pos_none);
			}
			else {
				_FireworkBtn->Newpos(Point(0, 0));
				_ElveBtn->Newpos(Point(0, 0));
				_TornadoBtn->Newpos(Point(0, 0));
				_FlowerBtn->Newpos(Point(0, 0));
				_TornadoEffect.SetTornado(_TornadoBtn->getStatus(), touchLoc);
			}
		}
		else if (_FlowerBtn->touchesEnded(touchLoc)) {
			_bEffectsOn = _FlowerBtn->getStatus();
			rootNode->getChildByName("Slider")->setVisible(_bEffectsOn);
			rootNode->getChildByName("Emitter")->setVisible(!_bEffectsOn);
			rootNode->getChildByName("Type")->setVisible(!_bEffectsOn);
			if (_bEffectsOn) {
				_FireworkBtn->Newpos(pos_none);
				_ElveBtn->Newpos(pos_none);
				_TornadoBtn->Newpos(pos_none);
				_FlowerBtn->Newpos(pos_back);
			}
			else {
				_FireworkBtn->Newpos(Point(0, 0));
				_ElveBtn->Newpos(Point(0, 0));
				_TornadoBtn->Newpos(Point(0, 0));
				_FlowerBtn->Newpos(Point(0, 0));
				_FlowerEffect.SetFlower(_FlowerBtn->getStatus(), touchLoc);
			}
		}
	}
	_FlowerEffect.SetFlower(_FlowerBtn->getStatus(), touchLoc);
	if (!_bEmitterOn && !_bEffectsOn) _ParticleControl.onTouchesEnded(touchLoc);
}

void ParticleSystemScene::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fGravity = (-50.0f + percent) / 5.0f; // -10 到 10 之間
		_GravityBMValue->setString(StringUtils::format("%2.1f", fGravity));
		_ParticleControl.setGravity(fGravity);
		_ElveEffect.SetGravity(fGravity);
		_FireworkEffect.SetGravity(fGravity);
	}
}

void ParticleSystemScene::SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fSpread = percent*1.8f; // 0 到 180 之間
		_SpreadBMValue->setString(StringUtils::format("%2.1f", fSpread));
		_ParticleControl._fSpread = fSpread;
	}
}

void ParticleSystemScene::DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fDir = percent*3.6f; // 0 到 360 之間
		_DirectionBMValue->setString(StringUtils::format("%2.1f", fDir));
		_ParticleControl._fDir = fDir;
	}
}

void ParticleSystemScene::SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fSpin = percent / 1.6f; // 0 到 60 之間
		_SpinBMValue->setString(StringUtils::format("%2.1f", fSpin));
		_ParticleControl._fSpin = fSpin;
	}
}

void ParticleSystemScene::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iOpacity = percent * 2.55f; // 0 到 255 之間
		_OpacityBMValue->setString(StringUtils::format("%2d", iOpacity));
		_ParticleControl._iOpacity = iOpacity;
	}
}

void ParticleSystemScene::ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iParticles = percent * 2.0f; // 0 到 200 之間
		_ParticlesBMValue->setString(StringUtils::format("%2d", iParticles));
		_ParticleControl._iNumParticles = iParticles;
	}
}

void ParticleSystemScene::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fSpeed = percent / 2.5f; // 0 到 40 之間
		_SpeedBMValue->setString(StringUtils::format("%2.1f", fSpeed));
		_ParticleControl._fVelocity =fSpeed;
	}
}

void ParticleSystemScene::LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fLifetime = percent / 14.2f; // 0 到 7 之間
		_LifetimeBMValue->setString(StringUtils::format("%2.1f", fLifetime));
		_ParticleControl._fLifeTime = fLifetime;
	}
}

void ParticleSystemScene::ColorREvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iColorR = percent * 2.55f; // 0 到 255 之間
		_ColorRBMValue->setString(StringUtils::format("%2d", iColorR));
		_ParticleControl._iRed = iColorR;
		_ElveEffect.SetColorR(iColorR);
		_FlowerEffect.SetColorR(iColorR);
	}
}

void ParticleSystemScene::ColorGEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iColorG = percent * 2.55f; // 0 到 255 之間
		_ColorGBMValue->setString(StringUtils::format("%2d", iColorG));
		_ParticleControl._iGreen = iColorG;
		_ElveEffect.SetColorG(iColorG);
		_FlowerEffect.SetColorG(iColorG);
	}
}

void ParticleSystemScene::ColorBEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iColorB = percent * 2.55f; // 0 到 255 之間
		_ColorBBMValue->setString(StringUtils::format("%2d", iColorB));
		_ParticleControl._iBlue = iColorB;
		_ElveEffect.SetColorB(iColorB);
		_FlowerEffect.SetColorB(iColorB);
	}
}

void ParticleSystemScene::WindDirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fWindDir = -180 + (percent*3.6f); // -180 到 180 之間
		_WindDirectionBMValue->setString(StringUtils::format("%2.1f", fWindDir));
		_ParticleControl.setWindDirection(fWindDir);
		_FireworkEffect.SetWindDirection(fWindDir);
	}
}

void ParticleSystemScene::WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fWind = percent / 10.0f; // 0 到 10 之間
		_WindBMValue->setString(StringUtils::format("%2.1f", fWind));
		_ParticleControl.setWind(fWind);
		_FireworkEffect.SetWind(fWind);
	}
}

void ParticleSystemScene::TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		iType = percent / 12.5f; // 0 到 8 之間
		_TypeBMValue->setString(StringUtils::format("%2d", iType));
		_ParticleControl.setType(iType);
		_FireworkEffect.SetType(iType);
		if (!_bEffectsOn) {
			if (iType > 5) {
				_bSpriteOn = true;
				rootNode->getChildByName("Slider")->setVisible(true);
				rootNode->getChildByName("Sprite")->setVisible(true);
				rootNode->getChildByName("Effects")->setVisible(false);
				rootNode->getChildByName("Emitter")->setVisible(false);
			}
			else {
				_bSpriteOn = false;
				rootNode->getChildByName("Slider")->setVisible(false);
				rootNode->getChildByName("Sprite")->setVisible(false);
				rootNode->getChildByName("Effects")->setVisible(true);
				rootNode->getChildByName("Emitter")->setVisible(true);
			}
		}
	}
}
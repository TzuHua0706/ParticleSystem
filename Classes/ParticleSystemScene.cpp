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

	//�S��
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
	// �̦n���覡�O�A�H�U�� Slider �ھڳo�̪��]�w�ȡA��ܥX���T���ƭȻP��m
	_ParticleControl._cSprite = Sprite_0;
	_ParticleControl.init(*this);
	_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	_ParticleControl._fDir = 90.0;
	_ParticleControl._iNumParticles = 100;
	_ParticleControl._iGenParticles = 0;
	_ParticleControl._fSpread = 180.0f;
	_ParticleControl._fVelocity = 2.5;	 // ���l�����}�t��
	_ParticleControl._fLifeTime = 3.5f;	 // ���l���s���ɶ�
	_ParticleControl._fGravity = 0;
	_ParticleControl._fSpin = 0;
	_ParticleControl._iOpacity = 255;
	_ParticleControl._iRed = 255;
	_ParticleControl._iGreen = 255;
	_ParticleControl._iBlue = 255;
	_ParticleControl._fWindDirection = 90;
	_ParticleControl._fElpasedTime = 0;
	_ParticleControl.setType(STAY_FOR_TWOSECONDS); // ���l�B�ʪ����A�A�w�]�� 0
	_ParticleControl._windDir = Point(0, 0); // ���d�ҨS����@�����\��

	// ���l���i�վ�Ѽƪ����ʶb
	// Slider of Gravity
	auto *GravitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Gravity")->getChildByName("Slider_Gravity"));
	GravitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::GravityEvent, this));
	GravitySlider->setMaxPercent(100); 	// �N 0 �� 100 ������ -10 �� 10 ����
	_GravityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Gravity")->getChildByName("GravityBMFont");

	// Slider of Spread
	auto *SpreadSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Spread")->getChildByName("Slider_Spread"));
	SpreadSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpreadEvent, this));
	SpreadSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 180 ����
	_SpreadBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Spread")->getChildByName("SpreadBMFont");

	// Slider of Direction
	auto *DirectionSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Direction")->getChildByName("Slider_Direction"));
	DirectionSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::DirectionEvent, this));
	DirectionSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
	_DirectionBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Direction")->getChildByName("DirectionBMFont");

	// Slider of Spin
	auto *SpinSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Spin")->getChildByName("Slider_Spin"));
	SpinSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpinEvent, this));
	SpinSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 60 ����
	_SpinBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Spin")->getChildByName("SpinBMFont");

	// Slider of Opacity
	auto *OpacitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Opacity")->getChildByName("Slider_Opacity"));
	OpacitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::OpacityEvent, this));
	OpacitySlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_OpacityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Opacity")->getChildByName("OpacityBMFont");

	// Slider of Particles
	auto *ParticlesSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Particles")->getChildByName("Slider_Particles"));
	ParticlesSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ParticlesEvent, this));
	ParticlesSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 200 ����
	_ParticlesBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Particles")->getChildByName("ParticlesBMFont");

	// Slider of Speed
	auto *SpeedSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Speed")->getChildByName("Slider_Speed"));
	SpeedSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpeedEvent, this));
	SpeedSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 40 ����
	_SpeedBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Speed")->getChildByName("SpeedBMFont");

	// Slider of Lifetime
	auto *LifetimeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Lifetime")->getChildByName("Slider_Lifetime"));
	LifetimeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::LifetimeEvent, this));
	LifetimeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 7 ����
	_LifetimeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Lifetime")->getChildByName("LifetimeBMFont");

	// Slider of Color
	auto *ColorRSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("Slider_Red"));
	ColorRSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorREvent, this));
	ColorRSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_ColorRBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("RedBMFont");
	auto *ColorGSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("Slider_Green"));
	ColorGSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorGEvent, this));
	ColorGSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_ColorGBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("GreenBMFont");
	auto *ColorBSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("Slider_Blue"));
	ColorBSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorBEvent, this));
	ColorBSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_ColorBBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Color")->getChildByName("BlueBMFont");

	// Slider of WindDirection
	auto *WindDirectionSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("Slider_WindDirection"));
	WindDirectionSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::WindDirectionEvent, this));
	WindDirectionSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ -180 �� 180 ����
	_WindDirectionBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("WindDirectionBMFont");

	// Slider of Wind
	auto *WindSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("Slider_Wind"));
	WindSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::WindEvent, this));
	WindSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 10 ����
	_WindBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Slider")->getChildByName("Wind")->getChildByName("WindBMFont");

	// Slider of Type
	auto *TypeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Type")->getChildByName("Slider_Type"));
	TypeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::TypeEvent, this));
	TypeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 5 ����
	_TypeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("Type")->getChildByName("TypeBMFont");

	_listener1 = EventListenerTouchOneByOne::create();	//�Ыؤ@�Ӥ@��@���ƥ��ť��
	_listener1->onTouchBegan = CC_CALLBACK_2(ParticleSystemScene::onTouchBegan, this);		//�[�JĲ�I�}�l�ƥ�
	_listener1->onTouchMoved = CC_CALLBACK_2(ParticleSystemScene::onTouchMoved, this);		//�[�JĲ�I���ʨƥ�
	_listener1->onTouchEnded = CC_CALLBACK_2(ParticleSystemScene::onTouchEnded, this);		//�[�JĲ�I���}�ƥ�

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//�[�J��Ыت��ƥ��ť��
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

bool ParticleSystemScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//Ĳ�I�}�l�ƥ�
{
	Point touchLoc = pTouch->getLocation();
	//��� Emitter �ɡA�i�즲�ӹϦ�
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
	// �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
	if (!_bEmitterOn && !_bEffectsOn) _ParticleControl.onTouchesBegan(touchLoc);
	return true;
}		 

void  ParticleSystemScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I���ʨƥ�
{
	Point touchLoc = pTouch->getLocation();	
	if (_bEmitterOn) {
		if (_EmitterSprite->touchesMoved(touchLoc)) // ���ʨç�s Emitter ����m
			_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	}
	// �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
	if(!_emitterSwitchBtn->touchesMoved(touchLoc) && !_bEmitterOn && !_bEffectsOn) _ParticleControl.onTouchesMoved(touchLoc);
}

void  ParticleSystemScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I�����ƥ� 
{
	Point touchLoc = pTouch->getLocation();
	if (_bEmitterOn)
		_EmitterSprite->touchesEnded(touchLoc);
	// �I�b Emitter �������ϥܤW�A�i�楲�n�����A����
	if (_emitterSwitchBtn->touchesEnded(touchLoc))
	{
		_ParticleControl._emitterPt = _EmitterSprite->getLoc();
		_bEmitterOn = _emitterSwitchBtn->getStatus();
		_bSpriteOn = _bEmitterOn;
		rootNode->getChildByName("Slider")->setVisible(_bEmitterOn);
		rootNode->getChildByName("Sprite")->setVisible(_bEmitterOn);
		rootNode->getChildByName("Effects")->setVisible(!_bEmitterOn);
		rootNode->getChildByName("Type")->setVisible(!_bEmitterOn);
		if (_bEmitterOn) { // ��� Emitter �ϥ�
			_EmitterSprite->setVisible(true);
		}
		else { // ���� Emitter �ϥ�
			_EmitterSprite->setVisible(false);
		}
		_ParticleControl.setEmitter(_bEmitterOn); // ��s����t�Τ��� Emitter ���A
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

	//�S��
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
		float fGravity = (-50.0f + percent) / 5.0f; // -10 �� 10 ����
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
		float fSpread = percent*1.8f; // 0 �� 180 ����
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
		float fDir = percent*3.6f; // 0 �� 360 ����
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
		float fSpin = percent / 1.6f; // 0 �� 60 ����
		_SpinBMValue->setString(StringUtils::format("%2.1f", fSpin));
		_ParticleControl._fSpin = fSpin;
	}
}

void ParticleSystemScene::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iOpacity = percent * 2.55f; // 0 �� 255 ����
		_OpacityBMValue->setString(StringUtils::format("%2d", iOpacity));
		_ParticleControl._iOpacity = iOpacity;
	}
}

void ParticleSystemScene::ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iParticles = percent * 2.0f; // 0 �� 200 ����
		_ParticlesBMValue->setString(StringUtils::format("%2d", iParticles));
		_ParticleControl._iNumParticles = iParticles;
	}
}

void ParticleSystemScene::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fSpeed = percent / 2.5f; // 0 �� 40 ����
		_SpeedBMValue->setString(StringUtils::format("%2.1f", fSpeed));
		_ParticleControl._fVelocity =fSpeed;
	}
}

void ParticleSystemScene::LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fLifetime = percent / 14.2f; // 0 �� 7 ����
		_LifetimeBMValue->setString(StringUtils::format("%2.1f", fLifetime));
		_ParticleControl._fLifeTime = fLifetime;
	}
}

void ParticleSystemScene::ColorREvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int iColorR = percent * 2.55f; // 0 �� 255 ����
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
		int iColorG = percent * 2.55f; // 0 �� 255 ����
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
		int iColorB = percent * 2.55f; // 0 �� 255 ����
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
		float fWindDir = -180 + (percent*3.6f); // -180 �� 180 ����
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
		float fWind = percent / 10.0f; // 0 �� 10 ����
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
		iType = percent / 12.5f; // 0 �� 8 ����
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
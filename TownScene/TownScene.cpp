#include "TalkScene.h"
USING_NS_CC;
Scene* TownScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TownScene::create();
	scene->addChild(layer);
	return scene;
}

bool TownScene::init()
{
	if ( !Layer::init() ){return false;}
	
	count = 0;
	
	bgCangeFlag = false;
	
	static auto view = Director::getInstance()->getOpenGLView();
	static auto size = view->getFrameSize();
	
	static auto bg1 = Sprite::create("TownImg/H2_s.png");
	bg1->setPosition(size/2);
	bg1->setZOrder(1);
	addChild(bg1, 1, 1);

	
	static auto mesWin = Sprite::create("SystemImg/talkWindow.png");
	mesWin->setPosition(Point(size.width / 2, size.height / 8));
	mesWin->setVisible(false);
	addChild(mesWin, 2, 2);
	
	static auto mes = Label::createWithSystemFont("","fonts/mplus-1m-medium.ttf", 90);
	mes->setColor(Color3B::BLACK);
	mes->setPosition(mesWin->getPosition());
	mes->setVisible(false);
	addChild(mes, 3, 3);

	Sprite* tapAreaSpr = Sprite::create();
	
	tapAreaSpr->setContentSize(size);
	
	MenuItemSprite* tapArea = MenuItemSprite::create(tapAreaSpr,tapAreaSpr,[this](Ref*sender){
		switch (count) {
			case 0:
				mes->setVisible(true);
				mesWin->setVisible(true);
				mes->setString("はじめまして！\nあるけみぃの世界へようこそ！"); break;
			case 1:
				mes->setString("私は、H2\n（エイチ・ツー）です。\n物質名は水素です。"); break;
			case 2:
				
				mes->setString("あなたは錬金術士として、\nこの街にやって来ました。"); break;
			case 3:
				mes->setString("これから、\n一緒に街を発展させましょう！");
				break;
			case 4:
				mes->setString("では早速、\n簡単な錬金をしてみましょうか。");
				break;
			case 5:
				mes->setString("水を錬金してみましょう。");
				break;
			case 6:{
				mesWin->setVisible(false);
				mes->setVisible(false);
				
				auto spr = Sprite::create("TownImg/Tutorial01.png");
				spr->setPosition(Point(1536/2,2048/2));
				this->addChild(spr,10000, 100000);
				break;
			}
			case 7:{
				auto nextScene = HomunChooseScene::createScene();
				auto pScene = TransitionFade::create(0.5f, nextScene);
				Director::getInstance()->replaceScene(pScene);
				break;}
			default:break;
		}
		count++;
	});
	tapArea->setPosition(size/2);
	auto tapMenu = Menu::create(tapArea ,NULL);
	tapMenu->setPosition(Point::ZERO);
	this->addChild(tapMenu);

	return true;
}
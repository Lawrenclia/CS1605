#include "graph.h"
#include "slime.h"


//初始化
Graph::Graph(std::vector<Slime*>& playerTeam, std::vector<Slime*>& enemyTeam) {
    easy2d::Window::setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto background = easy2d::gcnew easy2d::Sprite("Res/Background.png");
    
    this->battleScene = new easy2d::Scene();
    this->battleScene->addChild(background);

    // 将控制权退出图形窗口，返回控制台（图形窗口仍存在）
    easy2d::Timer::add([=]() {
        easy2d::Game::quit();  
        },0);

    easy2d::SceneManager::enter(battleScene);
    easy2d::Game::start();
}


//side为false为左边己方图片地址, true为右边敌方图片地址
std::string Graph::GetSlimeIcon(Slime* slime, bool side) {
    std::string imgName = "Res/Slime";
    switch (slime->getProperty()) {
    case Property::Normal:
        imgName += "Normal";
        break;
    case Property::Grass:
        imgName += "Grass";
        break;
    case Property::Fire:
        imgName += "Fire";
        break;
    case Property::Water:
        imgName += "Water";
        break;
    case Property::Electric:
        imgName += "Thunder";
        break;
    default:
        break;
    }

    if (side) {
        imgName += "_r";
    }
    imgName = imgName + ".png";

    return imgName;
}


void Graph::Update(Slime* playSlime0, Slime* playSlime1, 
    std::vector<Slime*>& playerTeam, std::vector<Slime*>& enemyTeam, Weather weather) {

    if (numOfAlive(playerTeam) == 0 || numOfAlive(enemyTeam) == 0) {
		easy2d::Game::quit();  // 如果任一方没有存活的slime，退出游戏
        return;
        
	} 
    
	battleScene->removeAllChildren();   // 清除之前的所有子节点
    easy2d::Window::setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    easy2d::Window::setTitle("Battle of Slimes 2");

    auto background = easy2d::gcnew easy2d::Sprite("Res/Background.png");
    this->battleScene->addChild(background);

    //绘制天气
	DrawWeather(weather);

	// 绘制玩家和敌人的Slime
    float slime_ypos = 80.0f;
    float slime_xpos = 170.0f;

	//绘制玩家Slime
    for (size_t i = 0; i < playerTeam.size(); ++i) {
		Slime* slime = playerTeam[i];
        if (slime != nullptr && slime->isAlive()) {
            if (slime->getType() == playSlime0->getType()) {
                DrawSlime(slime, SLIME_X_PLAYER, SLIME_Y, SLIME_SIZE, false);  //绘制大Slime
				DrawEffect(slime, SLIME_X_PLAYER, SLIME_Y, 30.0f, false);  //绘制大Slime的状态效果
				DrawHPBar(slime, SLIME_X_PLAYER + 50.0f, SLIME_Y + 180.0f, SLIME_SIZE_SMALL, 10.0f); //绘制大Slime的HP条
            } else {
				DrawSlime(slime, SLIME_X_PLAYER - slime_xpos, slime_ypos, SLIME_SIZE_SMALL, false); //绘制小Slime
				DrawEffect(slime, SLIME_X_PLAYER - slime_xpos, slime_ypos, 18.0f, false);  //绘制小Slime的状态效果
				slime_ypos += 70;  //调整y坐标
				slime_xpos += 60;  //调整x坐标
			}
        }
	}

     slime_ypos = 80.0f;
	 slime_xpos = 270.0f;

	 //绘制敌人Slime
     for (size_t i = 0; i < enemyTeam.size(); ++i) {
		 Slime* slime = enemyTeam[i];
         if (slime != nullptr && slime->isAlive()) {
             if (slime->getType() == playSlime1->getType()) {
                 DrawSlime(slime, SLIME_X_ENEMY, SLIME_Y, SLIME_SIZE, true);
                 DrawEffect(slime, SLIME_X_ENEMY, SLIME_Y, 30.0f, true);
                 DrawHPBar(slime, SLIME_X_ENEMY + 50.0f, SLIME_Y + 180.0f, SLIME_SIZE_SMALL, 10.0f);
             } else {
                 DrawSlime(slime, SLIME_X_ENEMY + slime_xpos, slime_ypos, SLIME_SIZE_SMALL, true);
                 DrawEffect(slime, SLIME_X_ENEMY + slime_xpos, slime_ypos, 18.0f, true);
                 slime_ypos += 70;
                 slime_xpos += 60;
             }
         }
     }
     
	 this->battleScene->removeAllListeners(); // 清除之前的所有监听器

	 easy2d::Timer::add([=]() {  // 定时器回调函数
         easy2d::Game::quit();
         }, 0);

	 easy2d::SceneManager::enter(battleScene); // 进入战斗场景

     easy2d::Game::start();
     
}


void Graph::DrawSlime(Slime* slime, float xpos, float ypos, float size, bool side) {

    auto slimeIcon = easy2d::gcnew easy2d::Sprite(GetSlimeIcon(slime, side));
    if (slimeIcon != nullptr) {
        slimeIcon->setPos(xpos, ypos);
        slimeIcon->setSize(size, size);
        this->battleScene->addChild(slimeIcon);
    }
	
}


void Graph::DrawHPBar(Slime* slime, float xpos, float ypos, float width, float height) {
	int hp = slime->getHP();
    int maxHP = slime->getMaxHP();
	float blueWidth = width * hp / maxHP;

	//绘制黑色背景矩形和蓝色HP条
    auto blackRect = easy2d::gcnew easy2d::Shape(easy2d::Shape::Rect, easy2d::Rect(easy2d::Point(), easy2d::Size(width, height)));
	auto blackNode = easy2d::gcnew easy2d::ShapeNode(blackRect);
	blackNode->setPos(xpos, ypos);
    blackNode->setFillColor(easy2d::Color::Black);

    auto blueRect = easy2d::gcnew easy2d::Shape(easy2d::Shape::Rect, easy2d::Rect(easy2d::Point(), easy2d::Size(blueWidth, height)));
    auto blueNode = easy2d::gcnew easy2d::ShapeNode(blueRect);
    blueNode->setPos(xpos, ypos);
    blueNode->setFillColor(easy2d::Color::Blue);
	this->battleScene->addChild(blackNode);
	this->battleScene->addChild(blueNode);

	// 绘制HP文本
    auto hpText = easy2d::gcnew easy2d::Text(std::to_string(hp) + "/" + std::to_string(maxHP));

    easy2d::Font font = easy2d::Font();
    font.size = 20;
    font.weight = easy2d::Font::Weight::Bold;

    easy2d::TextStyle style;
    style.alignment = easy2d::TextAlign::Center;
    style.font = font;

    hpText->setTextStyle(style);
    hpText->setAnchor(0.5, 0.5);
    hpText->setPos(xpos + 75.0f, ypos + 24.0f);
    this->battleScene->addChild(hpText);
}


void Graph::DrawEffect(Slime* slime,float xpos, float ypos, float size, bool side) {
    float effect_ypos = ypos;
	//绘制状态图标isPainted（）
    if (slime->isPainted()) {
        auto effect1 = easy2d::gcnew easy2d::Sprite("Res/IconPaint.png");
        if (side) {
            effect1->setPos(xpos + 6.3f * size, effect_ypos); //right side
        } else {
            effect1->setPos(xpos + size, effect_ypos);  //left side
        }
        effect1->setSize(size, size);
        this->battleScene->addChild(effect1);
        effect_ypos += 1.5 * size ;
    }

	//绘制状态图标isPainted（）
    if (slime->isSleeping()) {
        auto effect2 = easy2d::gcnew easy2d::Sprite("Res/IconSleep.png");
        if (side) {
            effect2->setPos(xpos + 6.3f * size, effect_ypos); //right side
        } else {
			effect2->setPos(xpos + size, effect_ypos);  //left side
        }
        effect2->setSize(size, size);
		this->battleScene->addChild(effect2);
    } 
		   
}


void Graph::DrawWeather(Weather weather) {
	// 绘制天气效果
    if (weather == Weather::SunnyDay) {
        auto weatherIcon = easy2d::gcnew easy2d::Sprite("Res/Sunny.png");
        weatherIcon->setPos(550.0f, 10.0f);
        weatherIcon->setSize(100.0f, 100.0f);
		this->battleScene->addChild(weatherIcon);
    } else if (weather == Weather::RainyDay) {
        auto weatherIcon = easy2d::gcnew easy2d::Sprite("Res/Rainy.png");
        weatherIcon->setPos(550.0f, 10.0f);
        weatherIcon->setSize(100.0f, 100.0f);
        this->battleScene->addChild(weatherIcon);
	}
}


Graph::~Graph() {
    delete this->battleScene;
}
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "slime.h"
#include <easy2d/easy2d.h>
#include <vector>
#include <unordered_map>

// 图形窗口的宽度和高度
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 300

// Slime的初始位置和大小
#define SLIME_X_PLAYER 300.0f
#define SLIME_X_ENEMY 650.0f
#define SLIME_Y 50.0f
#define SLIME_SIZE 250.0f
#define SLIME_SIZE_SMALL 150.0f

class Battle;  // Forward declaration to avoid circular dependency

class Graph {
public:
    //初始化
    Graph(std::vector<Slime*>& playerTeam, std::vector<Slime*>& enemyTeam);
    ~Graph();

	//更新图形
    void Update(Slime* playSlime0, Slime* playSlime1, std::vector<Slime*>& playerTeam, std::vector<Slime*>& enemyTeam, Weather weather);

private:
    easy2d::Scene* battleScene;
    
    //绘制Slime图形
    void DrawSlime(Slime* slime, float xpos, float ypos, float size, bool side);

	//绘制Slime的HP条
	void DrawHPBar(Slime* slime, float xpos, float ypos, float width, float height);

	//绘制Slime的状态效果
    void DrawEffect(Slime* slime, float xpos, float ypos, float size, bool side);

	//绘制天气效果
    void DrawWeather(Weather weather);

	//获取Slime的图标地址
    std::string GetSlimeIcon(Slime* slime, bool side);

};


#endif// GRAPH_H_INCLUDED
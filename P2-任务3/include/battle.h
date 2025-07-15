#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED
#include <vector>
#include "slime.h"
#include "graph.h"



class Battle {
public:
    
    void play(std::istream& is, std::ostream&os);
    std::vector<Slime*> playerTeam;
    std::vector<Slime*> enemyTeam;
	Slime* playSlime0 = nullptr;  //玩家当前使用的slime
    Slime* playSlime1 = nullptr;  //敌人当前使用的slime
    int round;
    Weather weather;  //记录天气状态
    

private:
    std::vector<Slime*> slimes;
    int weatherDuration = 0;
    bool isEnd = false;
    int revivalPotion = 0;  
    int attackPotion = 0;   
    void Init();
    bool PlayerChooseSlime(std::istream& is, std::ostream& os, Slime* &playSlime0);
    bool EnemyChoose(std::ostream& os, Slime* &playSlime0, Slime* &playSlime1, Skill& enemySkill);
    bool UseRevivalPotion(std::ostream& os);
    int GetDamage(Slime* &playSlime0, Slime* &playSlime1, Skill &skill);
    bool Fight(std::istream& is, std::ostream& os, Slime* &slime0, Slime* &slime1, Skill &playSkill, bool side);
    void Assist(std::ostream& os, Slime* &slime0, Slime* &slime1, Skill &playSkill, bool side);
    bool Action(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1, int action, Graph &graph);
    void OneRound(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1, Graph &graph);

};

#endif // BATTLE_H_INCLUDED

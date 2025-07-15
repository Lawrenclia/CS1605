#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED
#include <vector>
#include "slime.h"

enum Weather {NormalDay, SunnyDay, RainyDay};

class BATTLE {
public:
    void play(std::istream& is, std::ostream&os);

private:
    std::vector<Slime*> playerTeam;
    std::vector<Slime*> enemyTeam;
    std::vector<Slime*> slimes;
    int round;
    Weather weather;
    int weatherDuration = 0;
    bool isEnd;
    int revivalPotion;  
    int attackPotion;   
    void Init();
    bool PlayerChooseSlime(std::istream& is, std::ostream& os, Slime* &playSlime0);
    bool EnemyChoose(std::ostream& os, Slime* &playSlime0, Slime* &playSlime1, Skill& enemySkill);
    bool UseRevivalPotion(std::ostream& os);
    int GetDamage(Slime* &playSlime0, Slime* &playSlime1, Skill &skill);
    bool Fight(std::istream& is, std::ostream& os, Slime* &slime0, Slime* &slime1, Skill &playSkill, bool side);
    void Assist(std::ostream& os, Slime* &slime0, Slime* &slime1, Skill &playSkill, bool side);
    bool Action(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1, int action);
    void OneRound(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1);
};

#endif // BATTLE_H_INCLUDED

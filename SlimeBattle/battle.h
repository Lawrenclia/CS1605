#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED
#include <vector>
#include "slime.h"

class BATTLE {
public:
    void play(std::istream& is, std::ostream&os);

private:
    std::vector<Slime*> playerTeam;
    std::vector<Slime*> enemyTeam;
    int round;
    bool isEnd;
    int revivalPotion;  
    int attackPotion;   
    void init();
    bool playerDie(std::istream& is, std::ostream& os, Slime* &playSlime0);
    bool enemyDie(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1);
    bool enemyChooseChange(std::ostream& os, Slime* &playSlime0, Slime* &playSlime1); 
    bool useRevivalPotion(std::ostream& os);
    bool useAttackPotion(std::ostream& os, Slime* &playSlime1, Slime* playSlime0);

    void fight(std::istream& is, std::ostream& os, Slime* &playSlime0, SkillType userSkill, 
        bool userAttack, bool enemyAttack, Slime* &playSlime1, SkillType enemySkill);

    void OneRound(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1);
};

#endif // BATTLE_H_INCLUDED

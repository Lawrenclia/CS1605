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
    void init();
};

#endif // BATTLE_H_INCLUDED

#include <sstream>
#include <vector>
#include <algorithm>
#include "slime.h"
#include "battle.h"

//初始化
void BATTLE::init() {
    playerTeam = {new Slime(SlimeType::Green), new Slime(SlimeType::Red), new Slime(SlimeType::Blue)};
    enemyTeam = {new Slime(SlimeType::Green), new Slime(SlimeType::Red), new Slime(SlimeType::Blue)};
}


// 被动死亡下场,玩家Lose输出true
bool playerDie(std::istream& is, std::ostream& os, Slime* &playSlime0, std::vector<Slime*> &playerTeam) {
    os << "Your " << playSlime0->getName() << " is beaten" << std::endl;
    int choose2;
    std::vector<int> chooses;

    std::vector<std::string> availableOptions;   //玩家可选择的slime
    if (playerTeam[0]->isAlive() && playerTeam[0] != playSlime0) {
        availableOptions.push_back("1 for Green");
        chooses.push_back(1);
    }
    if (playerTeam[1]->isAlive() && playerTeam[1] != playSlime0) {
        availableOptions.push_back("2 for Red");
        chooses.push_back(2);
    }
    if (playerTeam[2]->isAlive() && playerTeam[2] != playSlime0) {
        availableOptions.push_back("3 for Blue");
        chooses.push_back(3);
    }

    if (chooses.empty()) {    //玩家无可选择的slime，输出玩家lose
        os << "You Lose Enemy Win" << std::endl;
        return true;
    }

    while (true) {   //玩家选择可供选择的slime
        os << "Select your next slime (";

        for (size_t i = 0; i < availableOptions.size(); ++i) {
            os << availableOptions[i];
            if (i < availableOptions.size() - 1) {
                os << ", ";
            }
        }
        os << "): ";
        is >> choose2;

        if (std::find(chooses.begin(), chooses.end(), choose2) != chooses.end()) break;
    }

    playSlime0 = playerTeam[choose2 - 1];
    os << "Your sends " << playSlime0->getName()<< std::endl;
    return false;
}


//被动死亡下场，玩家win输出true
bool enemyDie(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1, std::vector<Slime*> &enemyTeam) {
    os << "Enemy's " << playSlime1->getName() << " is beaten" << std::endl;
    std::vector<Slime*> restEnemy;  //剩余活着的敌方slime
    for (auto slime : enemyTeam) {
        if (slime->isAlive()) {
            restEnemy.push_back(slime);
        }
    }

    if (restEnemy.empty()) {   //敌方无活着的slime，输出玩家win
        os << "You Win Enemy Lose" << std::endl;
        return true;
    }

    //按照任务1的逻辑匹配合适的上场slime
    bool haveFound = false;
    bool haveSame = false;
    Slime* sameTypeSlime;

    for (auto slime : restEnemy) {
        if (slime->GetEffectiveness(slime->getSkills()[1], *playSlime0) == 2.0) {
            playSlime1 = slime;
            haveFound = true;
            break;
        } else if (slime->getType() == playSlime0->getType()) {
            sameTypeSlime = slime;
            haveSame = true;
        }

    }

    if (!haveFound) {
        if (haveSame) {
            playSlime1 = sameTypeSlime;
        } else {
            playSlime1 = restEnemy[0];
        }
    }

    os << "Enemy sends " << playSlime1->getName() << std::endl;

    return false;
}


//玩家选择slime的技能
SkillType userChooseSkill(Slime* playSlime0, int choose) {
    if (choose == 1) {
        return playSlime0->getSkills()[0];
    } else {  //choose == 2
        return playSlime0->getSkills()[1];
    }
}


//敌方选择slime的技能（按照任务1的逻辑）
SkillType enemyChooseSkill(Slime* playSlime1, Slime* playSlime0) {
    if (playSlime1->GetEffectiveness(playSlime1->getSkills()[1], *playSlime0) == 2.0) {
        return playSlime1->getSkills()[1];
    } else {
        return playSlime1->getSkills()[0];
    }
}


//进行上场slimes的互相攻击
void fight(std::istream& is, std::ostream& os, Slime* &playSlime0, SkillType userSkill, bool attackAble, Slime* &playSlime1, SkillType enemySkill,
    std::vector<Slime*> &playerTeam, std::vector<Slime*> &enemyTeam, bool& isEnd) {
    int damage0, damage1;

    if (playSlime0->getSpeed() <= playSlime1->getSpeed() || !attackAble) {  //敌方速度更快（大于或等于）或者己方slime无法攻击
        damage1 = playSlime1->Damage(*playSlime0, enemySkill);
        os << "Enemy's " << playSlime1->getName() << " uses " << skillToString(enemySkill) << "! Damage: " << damage1 << std::endl;
        playSlime0->hurtHP(damage1);
        if (playSlime0->isAlive() && attackAble) {
            damage0 = playSlime0->Damage(*playSlime1, userSkill);
            os << "Your " << playSlime0->getName() << " uses " << skillToString(userSkill) << "! Damage: " << damage0 << std::endl;
            playSlime1->hurtHP(damage0);
        } else if (!playSlime0->isAlive()){   //判断己方上场slime是否死亡
            if (playerDie(is, os, playSlime0, playerTeam)) {
                isEnd = true;
            }
        }
        if (!playSlime1->isAlive()) {  //判断敌方slime是否死亡
            if (enemyDie(is, os, playSlime0, playSlime1, enemyTeam)) {
                isEnd = true;
            }
        }
    } else if (attackAble) {  //己方速度更快并且可以攻击
        damage0 = playSlime0->Damage(*playSlime1, userSkill);
        os << "Your " << playSlime0->getName() << " uses " << skillToString(userSkill) << "! Damage: " << damage0 << std::endl;
        playSlime1->hurtHP(damage0);
        if (playSlime1->isAlive()) {
            damage1 = playSlime1->Damage(*playSlime0, enemySkill);
            os << "Enemy's " << playSlime1->getName() << " uses " << skillToString(enemySkill) << "! Damage: " << damage1 << std::endl;
            playSlime0->hurtHP(damage1);
        } else if (!playSlime1->isAlive()) {  //判断敌方slime是否死亡
            if (enemyDie(is, os, playSlime0, playSlime1, enemyTeam)) {
                isEnd = true;
            }
        }
        if (!playSlime0->isAlive()){  //判断己方上场slime是否死亡
            if (playerDie(is, os, playSlime0, playerTeam)) {
                isEnd = true;
            }
        }

    }
}


//一个回合的操作
void OneRound(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1,
    std::vector<Slime*> &playerTeam, std::vector<Slime*> &enemyTeam, bool& isEnd) {
    //玩家选择行动
    int action;
    int num = 0;
    for (auto slime : playerTeam) {
        if (slime->isAlive()) {
            num++;
        }
    }

    if (num > 1) {
        while (true) {
            os << "Select your action (1 for skill, 2 for change): ";
            is >> action;
            if (action == 1 || action == 2) break;
        }
    } else {
        while (true) {
            os << "Select your action (1 for skill): ";
            is >> action;
            if (action == 1) break;
        }
    }

    if (action == 1) {    // 选择技能
        int choose1;
        while (true) {
            os << "Select the skill (1 for " << skillToString(playSlime0->getSkills()[0]) <<
             ", 2 for " << skillToString(playSlime0->getSkills()[1]) << "): ";
            is >> choose1;
            if (choose1 == 1 || choose1 == 2) break;
        }

        SkillType userSkill = userChooseSkill(playSlime0, choose1);
        SkillType enemySkill = enemyChooseSkill(playSlime1, playSlime0);

        fight(is, os, playSlime0, userSkill, true, playSlime1, enemySkill, playerTeam, enemyTeam, isEnd);


    } else if (action == 2) {   // 选择切换
        int choose2;
        std::vector<int> chooses;
        while (true) {

            std::vector<std::string> availableOptions;
            if (playerTeam[0]->isAlive() && playerTeam[0] != playSlime0) {
                availableOptions.push_back("1 for Green");
                chooses.push_back(1);
            }
            if (playerTeam[1]->isAlive() && playerTeam[1] != playSlime0) {
                availableOptions.push_back("2 for Red");
                chooses.push_back(2);
            }
            if (playerTeam[2]->isAlive() && playerTeam[2] != playSlime0) {
                availableOptions.push_back("3 for Blue");
                chooses.push_back(3);
            }

            os << "Select your next slime (";

            for (size_t i = 0; i < availableOptions.size(); ++i) {
                os << availableOptions[i];
                if (i < availableOptions.size() - 1) {
                    os << ", ";
                }
            }
            os << "): ";
            is >> choose2;
           if (std::find(chooses.begin(), chooses.end(), choose2) != chooses.end()) break;
        }

        SkillType userSkill = userChooseSkill(playSlime0, choose2);
        SkillType enemySkill = enemyChooseSkill(playSlime1, playSlime0);

        playSlime0 = playerTeam[choose2 - 1];
        os << "Your sends " << playSlime0->getName() << std::endl;

        fight(is, os, playSlime0, userSkill, false, playSlime1, enemySkill, playerTeam, enemyTeam, isEnd);

    }

    if (!isEnd) {  //若游戏没有结束，输出己方和敌方上场slime的HP
        os << "Your " << playSlime0->getName() << ": HP " << playSlime0->getHP() <<
     " || Enemy's " << playSlime1->getName() << ": HP " << playSlime1->getHP() << std::endl;
    }

    //End
}


//play
void BATTLE::play(std::istream& is, std::ostream&os) {
    round = 1;
    bool isEnd = false;
    init();   //初始化

    os << "Welcome to Battle of Slimes!" << std::endl;
    os << "You have Green, Red and Blue. So does Enemy." << std::endl;

    int choose;
    while (true) {
        os << "Select your starting slime (1 for Green, 2 for Red, 3 for Blue): ";
        is >> choose;
        if (choose == 1) {
            os << "You starts with Green" << std::endl;
            os << "Enemy starts with Red" << std::endl;
            os << "Your Green: HP 110 || Enemy's Red: HP 100" << std::endl;
            break;
        } else if (choose == 2) {
            os << "You starts with Red" << std::endl;
            os << "Enemy starts with Blue" << std::endl;
            os << "Your Red: HP 100 || Enemy's Blue: HP 100" << std::endl;
            break;
        } else if (choose == 3) {
            os << "You starts with Blue" << std::endl;
            os << "Enemy starts with Green" << std::endl;
            os << "Your Blue: HP 100 || Enemy's Green: HP 110" << std::endl;
            break;
        }
    }

    Slime* playSlime0 = playerTeam[choose - 1];
    Slime* playSlime1 = enemyTeam[choose % 3];
    os << "Battle starts!" << std::endl;

    //开始游戏
    while (!isEnd) {
        os << "--------------------------------------------------" << std::endl;
        os << "Round " << round << std::endl;
        OneRound(is, os, playSlime0, playSlime1, playerTeam, enemyTeam, isEnd);
        round++;
        if (round == 101) {
            os << "Draw" << std::endl;
            isEnd = true;
        }
    }

    //删除slimes，释放内存
    for (auto slime : playerTeam) {
        delete slime;
    }
    for (auto slime : enemyTeam) {
        delete slime;
    }

}



#include <sstream>
#include <vector>
#include <algorithm>
#include "slime.h"
#include "battle.h"
#include "skill.h"

//初始化
void BATTLE::Init() {
    playerTeam = {};
    enemyTeam = {new Slime(SlimeType::Pink), new Slime(SlimeType::Green), new Slime(SlimeType::Red)};
    slimes = {new Slime(SlimeType::Green), new Slime(SlimeType::Red), new Slime(SlimeType::Blue), new Slime(SlimeType::Yellow), new Slime(SlimeType::Pink)};
    isEnd = false;
    weather = Weather::NormalDay;
    revivalPotion = 0; 
}

int numOfAlive(const std::vector<Slime*>& team) {
    int num = 0;
    for (auto slime : team) {
        if (slime->isAlive()) {
            num++;
        }
    }
    return num;
}


//任务1中敌方攻击逻辑
Skill BATTLE::EnemyChooseSkill(Slime* playSlime0, Slime* playSlime1) {
   if (playSlime1->getType() == SlimeType::Pink) {
        if (3 * playSlime0->getHP() < playSlime0->getMaxHP()) {
            if (playSlime0->isSleeping() || playSlime0->isPainted()) {
                return playSlime1->getSkills()[0]; // Slap
            }
        }
        if (!playSlime0->isSleeping()) {
            return playSlime1->getSkills()[1]; // Sing
        }
        if (!playSlime0->isPainted()) {
            return playSlime1->getSkills()[2]; // Paint
        }
        return playSlime1->getSkills()[0]; // Slap

    } else if (playSlime1->getType() == SlimeType::Red) {
        if (5 * playSlime0->getHP() < playSlime0->getMaxHP() && (playSlime0->getType() == SlimeType::Blue || playSlime0->getType() == SlimeType::Red)) {
            return playSlime1->getSkills()[0]; // Claw
        }
        if (weather == Weather::SunnyDay) {
            return playSlime1->getSkills()[1]; // Flame
        }
        return playSlime1->getSkills()[2]; // Sunny
    } else if (playSlime1->getType() == SlimeType::Green) {
        if (playSlime1->getHP() >= playSlime1->getMaxHP() / 2 || (playSlime1->getHP() > playSlime0->getHP() && numOfAlive(enemyTeam) == 1)) {
            if (playSlime0->getType() == SlimeType::Blue) {
                return playSlime1->getSkills()[1]; // Leaf
            }
            return playSlime1->getSkills()[0]; // Tackle
        }
        return playSlime1->getSkills()[2]; // Synthesis
    }
    return playSlime1->getSkills()[0];
}


//玩家选择slime的技能
Skill UserChooseSkill(Slime* playSlime0, int choose) {
    if (choose == 1) {
        return playSlime0->getSkills()[0];
    } else if (choose == 2) {  
        return playSlime0->getSkills()[1];
    } else {
        return playSlime0->getSkills()[2];
    }
}


// 被动死亡下场,玩家Lose输出true
bool BATTLE::PlayerChooseSlime(std::istream& is, std::ostream& os, Slime* &playSlime0) { 
    int choose2;
    std::vector<int> chooses;

    std::vector<std::string> availableOptions;   //玩家可选择的slime
    if (playerTeam[0]->isAlive() && playerTeam[0] != playSlime0) {
        std::string first = "1 for " + playerTeam[0]->getName() + "-HP" + std::to_string(playerTeam[0]->getHP());
        availableOptions.push_back(first);
        chooses.push_back(1);
    }
    if (playerTeam[1]->isAlive() && playerTeam[1] != playSlime0) {
        std::string second = "2 for " + playerTeam[1]->getName() + "-HP" + std::to_string(playerTeam[1]->getHP());
        availableOptions.push_back(second);
        chooses.push_back(2);
    }
    if (playerTeam[2]->isAlive() && playerTeam[2] != playSlime0) {
        std::string third = "3 for " + playerTeam[2]->getName() + "-HP" + std::to_string(playerTeam[2]->getHP());
        availableOptions.push_back(third);
        chooses.push_back(3);
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
    os << "You send " << playSlime0->getName() << std::endl;
    return true;
}



bool BATTLE::EnemyChooseSlime(std::ostream& os, Slime* &playSlime0, Slime* &playSlime1) {
    if (playSlime1->getType() == SlimeType::Pink && !playSlime1->isAlive() && enemyTeam[1]->isAlive()) {
        playSlime1 = enemyTeam[1];
        os << "Enemy sends " << playSlime1->getName() << std::endl;
        return true;
    } else if (playSlime1->getType() == SlimeType::Green && enemyTeam[2]->isAlive() && playSlime1->getHP() < playSlime1->getMaxHP() / 2) {
        playSlime1 = enemyTeam[2];
        os << "Enemy sends " << playSlime1->getName() << std::endl;
        return true;
    } else if (playSlime1->getType() == SlimeType::Red && !playSlime1->isAlive() && enemyTeam[1]->isAlive()) {
        playSlime1 = enemyTeam[1];
        os << "Enemy sends " << playSlime1->getName() << std::endl;
        return true;
    } else {
        return false;
    }
}


// // 敌方使用复苏药
// bool BATTLE::useRevivalPotion(std::ostream& os) {
//     if (revivalPotion > 0) {
//         for (auto slime : enemyTeam) {
//             if (!slime->isAlive()) {
//                 slime->setHP(slime->getMaxHP() / 2);  // 恢复最大HP的一半
//                 os << "Enemy uses Revival Potion on " << slime->getName() << std::endl;
//                 revivalPotion--;
//                 return true;
//             }
//         }
//     }
//     return false;
// }


int BATTLE::GetDamage(Slime* &playSlime0, Slime* &playSlime1, Skill &skill) {
    double damage = playSlime0->Damage(*playSlime1, skill);
    if (skill.getProperty() == Property::Fire) {
        if (weather == Weather::SunnyDay) {
            damage *= 1.5;
        } else if (weather == Weather::RainyDay) {
            damage *= 0.5;
        }
    } else if (skill.getProperty() == Property::Water) {
        if (weather == Weather::SunnyDay) {
            damage *= 0.5;
        } else if (weather == Weather::RainyDay) {
            damage *= 1.5;
        }
    } else if (skill.getType() == SkillType::Slap && playSlime1->isSleeping()) {
        damage *= 2.0;
    } 
    return (int)(damage + 0.5);   //四舍五入
}


//slime0攻击,若slime1死亡输出true，side中敌方为1，玩家为0，输出对应内容
bool BATTLE::Fight(std::istream& is, std::ostream& os, Slime* &slime0, Slime* &slime1, Skill &playSkill, bool side) {
    std::string actor, target;
    if (side) {
        actor = "Enemy's ";
        target = "Your ";
    } else {
        actor = "Your ";
        target = "Enemy's ";
    }

    if (slime0->isSleeping()) {
        os << actor << slime0->getName() << " is sleeping!" << std::endl;;
        return false;
    } else {
        int damage = GetDamage(slime0, slime1, playSkill);
        os << actor << slime0->getName() << " uses " << playSkill.getName() << "! ";

        if (playSkill.getType() == SkillType::Thunder && weather != Weather::RainyDay) {
            os << "Failure" << std::endl;
        } else {
            os << "Damage: " << damage << std::endl;
            slime1->hurtHP(damage);
            slime0->setSkillUsed();
        }
        
        if (!slime1->isAlive()) {
            if (side) {
                os << "Your " << slime1->getName() << " is beaten" << std::endl;
                if (numOfAlive(playerTeam) > 0) {
                    PlayerChooseSlime(is, os, slime1);
                } else {
                    os << "You Lose" << std::endl;
                    isEnd = true;
                }
            } else {
                os << "Enemy's " << slime1->getName() << " is beaten" << std::endl;
                if (numOfAlive(enemyTeam) > 0) {
                    EnemyChooseSlime(os, slime0, slime1);
                } else {
                    os << "You Win" << std::endl;
                    isEnd = true;
                }
            }
            return true;
        } else {
            if (slime1->isSleeping()) {
                slime1->wakeUp();
                os << target << slime1->getName() << " wakes up" << std::endl;
            }
        }
        return false;
    }
}


//playSlime0辅助，side中敌方为1，玩家为0，输出对应内容
void BATTLE::Assist(std::ostream& os, Slime* &slime0, Slime* &slime1, Skill &playSkill, bool side) {
    std::string actor, target;
    if (side) {
        actor = "Enemy's ";
        target = "Your ";
    } else {
        actor = "Your ";
        target = "Enemy's ";
    }
    if (slime0->isSleeping()) {
        os << actor << slime0->getName() << " is sleeping!" << std::endl;;
    } else {
        os << actor << slime0->getName() << " uses " << playSkill.getName() << "! ";
        slime0->setSkillUsed();
        if (playSkill.getType() == SkillType::Sing) {
            if (!slime1->isSleeping()) {
                slime1->fallAsleep();
                os << target << slime1->getName() << " falls asleep" << std::endl;
            } else {
                os << "Waste" << std::endl;
            }
        } else if (playSkill.getType() == SkillType::Paint) {
            if (slime1->getSkillUsed()) {
                os << "Failure" << std::endl;
            } else {
                slime1->setPainted();
                os << target << slime1->getName() << " is painted" << std::endl;       
            }
        } else if (playSkill.getType() == SkillType::Synthesis) {
            double recoveryRatio = 0.3;
            if (weather == Weather::SunnyDay) recoveryRatio = 0.4;
            if (weather ==  Weather::RainyDay) recoveryRatio = 0.2;
            int recoverAmount = (int)(slime0->getMaxHP() * recoveryRatio);
            slime0->setHP(std::min(recoverAmount + slime0->getHP(), slime0->getMaxHP()));
            os << "Recovery: " << recoverAmount << std::endl;
        } else if (playSkill.getType() == SkillType::Sunny) {
            weather =  Weather::SunnyDay;
            weatherDuration = 5;
            os << "Weather becomes sunny" << std::endl;
        } else if (playSkill.getType() == SkillType::Rainy) {
            weather =  Weather::RainyDay;
            weatherDuration = 5;
            os << "Weather becomes rainy" << std::endl;
        }
    }
}



//选择back,输出false
bool BATTLE::Action(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1, int action) {
    if (action == 0) {
        os << "You Escape" << std::endl;
        isEnd = true;
        return true;
    } else if (action == 1) {    // 选择技能
        int choose1;   
        while (true) {
            os << "Select the skill (0 for back, 1 for " << playSlime0->getSkills()[0].getName() 
            << ", 2 for " << playSlime0->getSkills()[1].getName() << ", 3 for " << playSlime0->getSkills()[2].getName() << "): ";

            is >> choose1;
            if (choose1 == 0) return false;
            if (choose1 == 1 || choose1 == 2 || choose1 == 3) break;
        }

        Skill userSkill = UserChooseSkill(playSlime0, choose1);

        //敌人选择是否切换slime
        if (EnemyChooseSlime(os, playSlime0, playSlime1)) {
            if (userSkill.getIsAttack()) {
                Fight(is, os, playSlime0, playSlime1, userSkill, false);
            } else {
                Assist(os, playSlime0, playSlime1, userSkill, false);
            }
        } else {
            Skill enemySkill = EnemyChooseSkill(playSlime0, playSlime1);
            bool hasDie = false;
            if (userSkill.getPriority() > enemySkill.getPriority() || (userSkill.getPriority() == enemySkill.getPriority() && playSlime0->getSpeed() > playSlime1->getSpeed())){
                if (userSkill.getIsAttack()) {   //玩家攻击
                    hasDie = Fight(is, os, playSlime0, playSlime1, userSkill, false);
                } else {
                    Assist(os, playSlime0, playSlime1, userSkill, false);
                }
                if (!hasDie) {
                    if (enemySkill.getIsAttack()) {  //敌方攻击
                        Fight(is, os, playSlime1, playSlime0, enemySkill, true);
                    } else {
                        Assist(os, playSlime1, playSlime0, enemySkill, true);
                    }
                }
            } else {
                if (enemySkill.getIsAttack()) {  //敌方攻击
                    hasDie = Fight(is, os, playSlime1, playSlime0, enemySkill, true);
                } else {
                    Assist(os, playSlime1, playSlime0, enemySkill, true);
                }
                if (!hasDie) {
                    if (userSkill.getIsAttack()) {  //玩家攻击
                        Fight(is, os, playSlime0, playSlime1, userSkill, false);
                    } else {
                        Assist(os, playSlime0, playSlime1, userSkill, false);
                    }
                }
            }
        }
        return true;

    } else if (action == 2) {   // 选择切换
        int choose2;
        std::vector<int> chooses = {0};

        std::vector<std::string> availableOptions;   //玩家可选择的slime
        if (playerTeam[0]->isAlive() && playerTeam[0] != playSlime0) {
            std::string first = "1 for " + playerTeam[0]->getName() + "-HP" + std::to_string(playerTeam[0]->getHP());
            availableOptions.push_back(first);
            chooses.push_back(1);
        }
        if (playerTeam[1]->isAlive() && playerTeam[1] != playSlime0) {
            std::string second = "2 for " + playerTeam[1]->getName() + "-HP" + std::to_string(playerTeam[1]->getHP());
            availableOptions.push_back(second);
            chooses.push_back(2);
        }
        if (playerTeam[2]->isAlive() && playerTeam[2] != playSlime0) {
            std::string third = "3 for " + playerTeam[2]->getName() + "-HP" + std::to_string(playerTeam[2]->getHP());
            availableOptions.push_back(third);
            chooses.push_back(3);
        }

        while (true) {   //玩家选择可供选择的slime
            os << "Select your next slime (0 for back, ";

            for (size_t i = 0; i < availableOptions.size(); ++i) {
                os << availableOptions[i];
                if (i < availableOptions.size() - 1) {
                    os << ", ";
                }
            }
            os << "): ";
            is >> choose2;
            if (choose2 == 0) return false;
            if (std::find(chooses.begin(), chooses.end(), choose2) != chooses.end()) break;
        }
        
        //敌人选择是否切换slime
        if (!EnemyChooseSlime(os, playSlime0, playSlime1)) {
            Skill enemySkill = EnemyChooseSkill(playSlime0, playSlime1);
            playSlime0 = playerTeam[choose2 - 1];
            os << "You send " << playSlime0->getName() << std::endl;   
            if (enemySkill.getIsAttack()) {
                Fight(is, os, playSlime1, playSlime0, enemySkill, true);
            } else {
                Assist(os, playSlime1, playSlime0, enemySkill, true);
            } 
        } else {
            playSlime0 = playerTeam[choose2 - 1];
            os << "You send " << playSlime0->getName() << std::endl;   
        }
        return true;
    }
    return true;
}


//一个回合的操作
void BATTLE::OneRound(std::istream& is, std::ostream& os, Slime* &playSlime0, Slime* &playSlime1) {
    os << "--------------------------------------------------" << std::endl;
    // 回合开始前，处理天气和睡眠状态
    if (weatherDuration > 0) {
        weatherDuration--;
        if (weatherDuration == 0 && weather != Weather::NormalDay) {
            os << "Weather becomes normal" << std::endl;
            weather = Weather::NormalDay;
        }
    }

    if (playSlime0->getSleepCounter() == 1) {
        playSlime0->sleepOneTurn();
        os << "Your " << playSlime0->getName() << " wakes up" << std::endl;
    } else if (playSlime0->getSleepCounter() > 1) {
        playSlime0->sleepOneTurn();  // 回合后减一
    }

    if (playSlime1->getSleepCounter() == 1) {
        playSlime1->sleepOneTurn();
        os << "Enemy's " << playSlime1->getName() << " wakes up" << std::endl;
    } else if (playSlime1->getSleepCounter() > 1) {
        playSlime1->sleepOneTurn();
    }

   
    os << "Round " << round << std::endl;

    //玩家选择行动
    int action;

    
    if (numOfAlive(playerTeam) > 1) {
        while (true) {
            os << "Select your action (0 for escape, 1 for skill, 2 for change): ";
            is >> action;
            if ((action == 0 || action == 1 || action == 2) && Action(is, os, playSlime0, playSlime1, action)) {
                break;
            }
        }
    } else if (numOfAlive(playerTeam) == 1) {
        while (true) {
            os << "Select your action (0 for escape, 1 for skill): ";
            is >> action;
            if ((action == 0 || action == 1) && Action(is, os, playSlime0, playSlime1, action)) {
                break;
            }
        }
    }

    if (!isEnd) {  //若游戏没有结束，输出己方和敌方上场slime的HP
        os << "Your " << playSlime0->getName() << ": HP " << playSlime0->getHP() <<
     " || Enemy's " << playSlime1->getName() << ": HP " << playSlime1->getHP() << std::endl;
    }
    playSlime0->resetSkillUsed();
    playSlime1->resetSkillUsed();
    //End
}


//play
void BATTLE::play(std::istream& is, std::ostream&os) {
    round = 1;
    
    Init();   //初始化

    os << "Welcome to Battle of Slimes 2!" << std::endl;
    os << "Enemy has Pink, Green and Red, starting with Pink." << std::endl;
    os << "You can select three from five (1 for Green, 2 for Red, 3 for Blue, 4 for Yellow, 5 for Pink)." << std::endl;
    int slime1, slime2, slime3;
    while (true) {
        os << "Select your 1st slime: ";
        is >> slime1;

        if (slime1 > 0 && slime1 < 6) {
            playerTeam.push_back(slimes[slime1 - 1]);
            while (true) {
                os << "Select your 2nd slime: ";
                is >> slime2;

                if (slime2 > 0 && slime2 < 6 && slime2 != slime1) {
                    playerTeam.push_back(slimes[slime2 - 1]);
                    while (true) {
                        os << "Select your 3rd slime: ";
                        is >> slime3;

                        if (slime3 > 0 && slime3 < 6 && slime3 != slime2 && slime3 != slime1) {
                            playerTeam.push_back(slimes[slime3 - 1]);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

    os << "You have " << playerTeam[0]->getName() <<", " << playerTeam[1]->getName() << " and " 
    << playerTeam[2]->getName() << ", starting with " << playerTeam[0]->getName() << std::endl;

    Slime* playSlime0 = playerTeam[0];
    Slime* playSlime1 = enemyTeam[0];

    os << "Your " << playSlime0->getName() << ": HP " << playSlime0->getHP() 
    << " || Enemy's " << playSlime1->getName() << ": HP " << playSlime1->getHP() << std::endl;

    os << "Battle starts!" << std::endl;


    //开始游戏
    while (!isEnd) {
        OneRound(is, os, playSlime0, playSlime1);
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
    for (auto slime : slimes) {
        delete slime;
    }
    
}



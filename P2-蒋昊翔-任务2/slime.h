#ifndef SLIME_H_INCLUDED
#define SLIME_H_INCLUDED
#include "skill.h"
#include <string>
#include <vector>

enum SlimeType {Green, Red, Blue, Yellow, Pink,};


class Slime {
public:
    Slime(SlimeType type);
    std::string getName();
    SlimeType getType();
    int getHP();
    int getMaxHP();
    void setHP(int hp);  
    void hurtHP(int hp);   //HP减少
    int getAttack();
    int getDefense();
    int getSpeed();
    bool isAlive();
    std::vector<Skill> getSkills();
    Property getProperty();
    double GetEffectiveness(Skill userSkill, Slime target);   //得到属性倍率
    double Damage(Slime target, Skill skill);   //用skill对target造成伤害的值
    void fallAsleep();
    void wakeUp(); 
    void sleepOneTurn(); 
    int getSleepCounter(); 
    bool isSleeping();
    void setPainted(); 
    bool isPainted(); 
    bool getSkillUsed();  //是否成功发动技能
    void setSkillUsed();  //设置为已发动技能
    void resetSkillUsed();  //重置为未发动技能

private:
    std::string name;
    SlimeType type;
    int HP;
    int attack;
    int defense;
    int speed;
    Property property; //属性
    std::vector<Skill> skills;
    int sleepCounter = 0; // 睡眠剩余回合
    bool painted = false; // 是否被涂鸦
    bool skillUsed = false;
};


#endif // SLIME_H_INCLUDED
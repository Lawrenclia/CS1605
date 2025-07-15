#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include <string>

enum Property {Normal, Grass, Fire, Water, Electric};

enum SkillType {Tackle, Claw, Quick, Slap, Sing, Paint, Leaf, Synthesis, Flame, Sunny, Stream, Rainy, Volt, Thunder, NoSkill};

class Skill {
public:
    // Constructor
    Skill(SkillType type);

    // Get name
    std::string getName();

    //Get type
    SkillType getType();

    // Get property
    Property getProperty();

    // Get damage
    double getDamage();

    // Get priority
    int getPriority();

    bool getIsAttack();

private:
    SkillType type;
    bool isAttack; // 是否为攻击技能
    std::string name;
    Property property;
    int priority;
    double damage;
};


#endif //SKILL_H_INCLUDED
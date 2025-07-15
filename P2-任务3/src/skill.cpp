#include "skill.h"
#include <string>

Skill::Skill(SkillType type)
    : type(type)
{
    switch (type) {
        case Tackle:
            name = "Tackle";
            property = Normal;
            damage = 20;
            priority = 0;
            isAttack = true;
            break;
        case Claw:
            name = "Claw";
            property = Normal;
            damage = 15;
            priority = 0;
            isAttack = true;
            break;
        case Quick:
            name = "Quick";
            property = Normal;
            damage = 15;
            priority = 1;
            isAttack = true;
            break;
         case Slap:   // 对睡眠的史莱姆威力翻倍
            name = "Slap";
            property = Normal;
            damage = 15;
            priority = 0;
            isAttack = true;
            break;
         case Sing:  // 使目标陷入睡眠 3 回合
            name = "Sing";
            property = Normal;
            damage = 0;
            priority = 0;
            isAttack = false;
            break;
         case Paint:  //对本回合未发动过技能的目标进行涂鸦
            name = "Paint";
            property = Normal;
            damage = 0;
            priority = 0;
            isAttack = false;
            break;
        case Leaf:
            name = "Leaf";
            property = Grass;
            damage = 20;
            priority = 0;
            isAttack = true;
            break;
        case Synthesis:  //自身 HP 回复最大值的 30%
            name = "Synthesis";
            property = Grass;
            damage = 0;
            priority = 0;
            isAttack = false;
            break;
        case Flame:
            name = "Flame";
            property = Fire;
            damage = 20;
            priority = 0;
            isAttack = true;
            break;
        case Sunny:  //将天气改为晴天 5 回合
            name = "Sunny";
            property = Fire;
            damage = 0;
            priority = 1;
            isAttack = false;
            break;
        case Stream:
            name = "Stream";
            property = Water;
            damage = 20;
            priority = 0;
            isAttack = true;
            break;
        case Rainy:  //将天气改为雨天 5 回合
            name = "Rainy";
            property = Water;
            damage = 0;
            priority = 1;
            isAttack = false;
            break;
        case Volt:
            name = "Volt";
            property = Electric;
            damage = 25;
            priority = 0;
            isAttack = true;
            break;
        case Thunder:  //只能在雨天时成功发动
            name = "Thunder";
            property = Electric;
            damage = 50;
            priority = 0;
            isAttack = true;
            break;
        default:
            break;
    }
}


std::string Skill::getName() {
    return name;
}

SkillType Skill::getType() {
    return type;
}

Property Skill::getProperty() {
    return property;
}

double Skill::getDamage() {
    return damage;
}

int Skill::getPriority() {
    return priority;
}

bool Skill::getIsAttack() {
    return isAttack;
}
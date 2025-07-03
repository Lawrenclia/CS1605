#include <string>
#include <vector>
#include "slime.h"


Slime::Slime(SlimeType type)     //初始化
    : type(type)
{
    switch (type) {
        case Green:
            name = "Green";
            HP = 110;
            attack = 10;
            defense = 10;
            speed = 10;
            skills = {SkillType::Tackle, SkillType::Leaf};
            break;
        case Red:
            name = "Red";
            HP = 100;
            attack = 11;
            defense = 10;
            speed = 11;
            skills = {SkillType::Tackle, SkillType::Flame};
            break;
        case Blue:
            name = "Blue";
            HP = 100;
            attack = 10;
            defense = 11;
            speed = 9;
            skills = {SkillType::Tackle, SkillType::Stream};
            break;
        default:
            break;
    }
}

std::string Slime::getName() {
    return name;
}

SlimeType Slime::getType() {
    return type;
}

int Slime::getHP() {
    return HP;
}

void Slime::hurtHP(int hp) {
    HP -= hp;
}

bool Slime::isAlive() {
    return HP > 0;
}


int Slime::getAttack() {
    return attack;
}

int Slime::getDefense() {
    return defense;
}

int Slime::getSpeed() {
    return speed;
}

std::vector<SkillType> Slime::getSkills() {
    return skills;
}

std::string skillToString(SkillType skill) {
    switch (skill) {
        case Tackle: return "Tackle";
        case Leaf: return "Leaf";
        case Flame: return "Flame";
        case Stream: return "Stream";
        default: return "Unknown";
    }
}
double Slime::GetEffectiveness(SkillType userSkill, Slime target) {
    if (userSkill == SkillType::Leaf) {
        switch (target.getType()) {
            case Green: return 0.5;
            case Red: return 0.5;
            case Blue: return 2.0;
            default: return 1.0;
        }
    } else if (userSkill == SkillType::Flame) {
        switch (target.getType()) {
            case Green: return 2.0;
            case Red: return 0.5;
            case Blue: return 0.5;
            default: return 1.0;
        }
    } else if (userSkill == SkillType::Stream) {
        switch (target.getType()) {
            case Green: return 0.5;
            case Red: return 2.0;
            case Blue: return 0.5;
            default: return 1.0;
        }
    }
    return 1.0;
}

int Slime::Damage(Slime target, SkillType skill) {
    int skillHurt = 0;
    switch (skill) {
        case Tackle:
            skillHurt = 20;
            break;
        case Leaf:
            skillHurt = 20;
            break;
        case Flame:
            skillHurt = 20;
            break;
        case Stream:
            skillHurt = 20;
            break;
        default:
            skillHurt = 20;
    }
    return (int)(skillHurt * attack * GetEffectiveness(skill, target) / target.getDefense());
}



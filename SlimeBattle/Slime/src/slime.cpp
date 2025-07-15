// SlimeBattle/slime.cpp
#include <string>
#include <vector>
#include "slime.h"
#include "skill.h"

Slime::Slime(SlimeType type)     //初始化
    : type(type)
{
    switch (type) {
        case Green:
            name = "Green";
            property = Grass;
            HP = 110;
            attack = 10;
            defense = 10;
            speed = 10;
            skills = {Skill(SkillType::Tackle), Skill(SkillType::Leaf), Skill(SkillType::Synthesis)};
            break;
        case Red:
            name = "Red";
            property = Fire;
            HP = 100;
            attack = 12;
            defense = 10;
            speed = 11;
            skills = {Skill(SkillType::Claw), Skill(SkillType::Flame), Skill(SkillType::Sunny)};
            break;
        case Blue:
            name = "Blue";
            property = Water;
            HP = 100;
            attack = 10;
            defense = 14;
            speed = 9;
            skills = {Skill(SkillType::Tackle), Skill(SkillType::Stream), Skill(SkillType::Rainy)};
            break;
        case Yellow:
            name = "Yellow";
            property = Electric;
            HP = 90;
            attack = 10;
            defense = 10;
            speed = 12;
            skills = {Skill(SkillType::Quick), Skill(SkillType::Volt), Skill(SkillType::Thunder)};
            break;
        case Pink:
            name = "Pink";
            property = Normal;
            HP = 120;
            attack = 9;
            defense = 8;
            speed = 7;
            skills = {Skill(SkillType::Slap), Skill(SkillType::Sing), Skill(SkillType::Paint)};
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

int Slime::getMaxHP() {
    switch (type) {
        case Green:
            return 110;
        case Red:
            return 100;
        case Blue:
            return 100;
        case Yellow:
            return 90;
        case Pink:
            return 120;
        default:
            return 100;
    }
}

void Slime::setHP(int hp) {
    HP = hp;
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

std::vector<Skill> Slime::getSkills() {
    return skills;
}

Property Slime::getProperty() {
    return property;
}

double Slime::GetEffectiveness(Skill userSkill, Slime target) {
    if (userSkill.getProperty() == Grass) {
        switch (target.getProperty()) {
            case Grass: return 0.5;
            case Fire: return 0.5;
            case Water: return 2.0;
            default: return 1.0;
        }
    } else if (userSkill.getProperty() == Fire) {
        switch (target.getProperty()) {
            case Grass: return 2.0;
            case Fire: return 0.5;
            case Water: return 0.5;
            default: return 1.0;
        }
    } else if (userSkill.getProperty() == Water) {
        switch (target.getProperty()) {
            case Grass: return 0.5;
            case Fire: return 2.0;
            case Water: return 0.5;
            default: return 1.0;
        }
    } else if (userSkill.getProperty() == Electric) {
        switch (target.getProperty()) {
            case Grass: return 0.5;
            case Water: return 2.0;
            case Electric: return 0.5;
            default: return 1;
        }
    }
    return 1.0;
}

double Slime::Damage(Slime target, Skill skill) {
    return skill.getDamage() * attack * GetEffectiveness(skill.getType(), target) / target.getDefense();
}


void Slime::fallAsleep() { 
    sleepCounter = 3; 
}
    
void Slime::wakeUp() { 
    sleepCounter = 0; 
}
    
void Slime::sleepOneTurn() { 
    if (sleepCounter > 0) {
        sleepCounter--; 
    }
}

bool Slime::isSleeping() {
    return sleepCounter > 0;
}
int Slime::getSleepCounter() { 
    return sleepCounter; 
}

void Slime::setPainted() { 
    painted = true; 
    switch (type) {
        case Green:
            defense = 5;
            break;
        case Red:
            defense = 5;
            break;
        case Blue:
            defense = 7;
            break;
        case Yellow:
            defense = 5;
            break;
        case Pink:
            defense = 4;
            break;
        default:
            break;
    }
}
    
bool Slime::isPainted() { 
    return painted; 
}

bool Slime::getSkillUsed() {
    return skillUsed;
}

void Slime::setSkillUsed() {
    skillUsed = true;
}

void Slime::resetSkillUsed() {
    skillUsed = false;
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
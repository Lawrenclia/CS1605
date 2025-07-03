#ifndef SLIME_H_INCLUDED
#define SLIME_H_INCLUDED
#include <string>
#include <vector>

enum SlimeType {Green, Red, Blue};
enum SkillType {Tackle, Leaf, Flame, Stream};

class Slime {
public:
    Slime(SlimeType type);
    std::string getName();
    SlimeType getType();
    int getHP();
    void setHP(int hp);  
    void hurtHP(int hp);   //HP减少
    int getAttack();
    void setAttack(int atk);
    int getDefense();
    int getSpeed();
    bool isAlive();
    std::vector<SkillType> getSkills();
    double GetEffectiveness(SkillType userSkill, Slime target);   //得到属性倍率
    int Damage(Slime target, SkillType skill);   //用skill对target造成伤害的值
    bool getHasAttackPotion();
    void resetHasAttackPotion();


private:
    std::string name;
    SlimeType type;
    int HP;
    int attack;
    int defense;
    int speed;
    std::vector<SkillType> skills;
    bool hasAttackPotion; //是否已使用强攻药
};

std::string skillToString(SkillType skill);

#endif // SLIME_H_INCLUDED

#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <map>

class Enemy {
public:
    std::string name;
    int hp;
    int attack; // 공격력 (주사위 값에 따라 매번 달라짐)
    bool isWeak; // 약점 상태 여부
    std::map<std::string, int> rewards; // 적이 주는 보상 아이템

    Enemy(std::string enemyName, int enemyHP);

    virtual void displayStats();
    virtual int rollAttack(); // 공격력을 주사위 값으로 설정
    void addReward(const std::string& itemName, int count); // 보상 추가
};

class Papyrus : public Enemy {
public:
    Papyrus(); // 파피루 생성자
    int rollAttack() override; // 데미지의 1.2배 적용
};
class WanderingKnight : public Enemy {
public:
    WanderingKnight(); // 떠돌이 기사 생성자
    int rollAttack() override; // 공격력 계산
};

class MTE : public Enemy {
public:
    MTE(); // 던전의 왕 MTE 생성자
    int rollAttack() override; // 공격력 계산
};



#endif


#include "Enemy.h"
#include "DiceRoller.h"
#include <iostream>

Enemy::Enemy(std::string enemyName, int enemyHP)
    : name(enemyName), hp(enemyHP), attack(0), isWeak(false) {}

void Enemy::displayStats() {
    std::cout << "=== 적 정보 ===" << std::endl;
    std::cout << "이름: " << name << std::endl;
    std::cout << "체력: " << hp << std::endl;
    std::cout << "공격력: " << attack << " (이번 턴의 주사위 값)" << std::endl;
    std::cout << "상태: " << (isWeak ? "취약" : "정상") << std::endl;
    if (!rewards.empty()) {
        std::cout << "쓰러트리면 보상: ";
        for (const auto& reward : rewards) {
            std::cout << reward.first << " x" << reward.second << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "=================" << std::endl;
}

int Enemy::rollAttack() {
    attack = DiceRoller::rollD20();
    return attack;
}

void Enemy::addReward(const std::string& itemName, int count) {
    rewards[itemName] += count;
}

// Papyrus 클래스 구현
Papyrus::Papyrus() : Enemy("Papyrus", 80) {}

int Papyrus::rollAttack() {
    int baseAttack = DiceRoller::rollD20();
    attack = static_cast<int>(baseAttack * 1.2); // 1.2배 데미지
    return attack;
}

// 떠돌이 기사 생성자
WanderingKnight::WanderingKnight() : Enemy("떠돌이 기사", 90) {}

// 떠돌이 기사 공격 메서드 (특수 공격)
int WanderingKnight::rollAttack() {
    int baseAttack = DiceRoller::rollD20();
    attack = static_cast<int>(baseAttack * 1.5); // 공격력이 1.5배
    std::cout << "떠돌이 기사가 강력한 공격을 준비합니다! (공격력: " << attack << ")" << std::endl;
    return attack;
}

#include "Enemy.h"
#include "DiceRoller.h"
#include <iostream>

// 던전의 왕 MTE 생성자
MTE::MTE() : Enemy("던전의 왕 MTE", 150) {}

// 던전의 왕 MTE 공격 메서드 (주사위 값의 1.5배)
int MTE::rollAttack() {
    int baseAttack = DiceRoller::rollD20();
    attack = static_cast<int>(baseAttack * 1.5); // 공격력이 1.5배
    std::cout << "던전의 왕 MTE가 강력한 공격을 준비합니다! (공격력: " << attack << ")" << std::endl;
    return attack;
}

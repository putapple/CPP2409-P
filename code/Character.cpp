#include "Character.h"
#include <iostream>
#include <algorithm> // std::clamp

Character::Character(std::string charName, int charHP, int charAttack, int charWillpower)
    : name(charName), hp(charHP), attack(charAttack), willpower(charWillpower) {
    // 기본 소지 아이템 초기화
    items["투척 단검"] = 5;
    items["회복용 물약"] = 5;
    items["행운의 동전"] = 1;
}

void Character::displayStats() {
    std::cout << "=== 캐릭터 정보 ===" << std::endl;
    std::cout << "이름: " << name << std::endl;
    std::cout << "직업: " << job << std::endl;
    std::cout << "체력: " << hp << std::endl;
    std::cout << "공격력: " << attack << std::endl;
    std::cout << "정신력: " << willpower << std::endl;
    std::cout << "===================" << std::endl;
}

void Character::adjustHp(int amount) {
    hp = std::clamp(hp + amount, 0, 100); // 체력 조정 (0 ~ 100 범위)
}

void Character::adjustWillpower(int amount) {
    willpower = std::clamp(willpower + amount, 0, 90); // 정신력 조정 (0 ~ 90 범위)
}

void Character::displayItems() {
    std::cout << "\n=== 소지 아이템 ===" << std::endl;
    for (const auto& item : items) {
        std::cout << item.first << ": " << item.second << "개" << std::endl;
    }
    std::cout << "===================" << std::endl;
}

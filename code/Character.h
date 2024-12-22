#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <map>

class Character {
public:
    std::string name;
    std::string job = "모험가";
    int hp;
    int attack;
    int willpower; // 정신력 (0 ~ 90)

    std::map<std::string, int> items; // 소지 아이템과 개수

    Character(std::string charName, int charHP, int charAttack, int charWillpower = 45);

    void displayStats();
    void adjustHp(int amount);         // 체력 조정
    void adjustWillpower(int amount); // 정신력 조정
    void displayItems();              // 소지 아이템 출력
};

#endif

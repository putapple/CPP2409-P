#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <string>
#include <utility>

class DiceRoller {
public:
    static int rollD20(); // D20 주사위를 굴림
    static std::pair<int, std::string> rollD20WithStatus(); // D20 값과 상태를 반환
};

#endif

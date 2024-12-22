#include "DiceRoller.h"
#include <cstdlib>

int DiceRoller::rollD20() {
    return rand() % 20 + 1; // 1부터 20 사이의 값 반환
}

std::pair<int, std::string> DiceRoller::rollD20WithStatus() {
    int roll = rollD20();
    std::string status;

    if (roll == 1) {
        status = "매우 나쁨";
    } else if (roll >= 2 && roll <= 7) {
        status = "나쁨";
    } else if (roll >= 8 && roll <= 13) {
        status = "보통";
    } else if (roll >= 14 && roll <= 19) {
        status = "좋음";
    } else if (roll == 20) {
        status = "매우 좋음";
    }

    return std::make_pair(roll, status);
}

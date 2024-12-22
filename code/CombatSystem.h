#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "Character.h"
#include "Enemy.h"

class CombatSystem {
public:
    static void startCombat(Character& player, Enemy& enemy);

private:
    static void playerTurn(Character& player, Enemy& enemy);
    static void enemyTurn(Character& player, Enemy& enemy);
    static void explorationEvent(Character& player); // 탐색 이벤트 추가
};

#endif

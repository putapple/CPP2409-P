#include "Character.h"
#include "Enemy.h"
#include "CombatSystem.h"
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(0))); // 랜덤 시드 설정

    // 플레이어 이름 입력받기
    std::cout << "캐릭터 이름을 입력하세요: ";
    std::string playerName;
    std::getline(std::cin, playerName);

    // 플레이어 캐릭터 생성
    Character player(playerName, 100, 15, 45);
    player.displayStats();
    player.displayItems();

    // 첫 번째 적: 고블린
    Enemy goblin("Goblin", 50);
    goblin.displayStats();
    CombatSystem::startCombat(player, goblin);

    // 두 번째 적: 마노
    Enemy mano("Mano", 75);
    mano.addReward("회복용 물약", 3); // 쓰러트리면 회복용 물약 3개 보상
    mano.displayStats();
    CombatSystem::startCombat(player, mano);

    // 세 번째 적: 파피루
    Papyrus papyrus;
    papyrus.displayStats();
    CombatSystem::startCombat(player, papyrus);

    // 네 번째 적: 떠돌이 기사
    WanderingKnight wanderingKnight;
    wanderingKnight.displayStats();
    CombatSystem::startCombat(player, wanderingKnight);

    // 다섯 번째 적: 던전의 왕 MTE
    MTE dungeonKing;
    dungeonKing.displayStats();
    CombatSystem::startCombat(player, dungeonKing);

    return 0;
}

#ifndef EXPLORATION_H
#define EXPLORATION_H

#include <string>

// === D20 주사위 === //
// D20 주사위 굴리기 함수
int rollD20();

// === 탐색 이벤트 === //
// 탐색 이벤트 처리 함수
void explorationEvent(int result, const std::string& eventType);

// === 전투 이벤트 === //
// 전투 이벤트 처리 함수
void battleEvent(int result, int& playerHP, int& enemyHP);

#endif // EXPLORATION_H

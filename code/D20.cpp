#include "exploration.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    // 난수 시드 설정 (시간 기반으로 변경)
    srand(static_cast<unsigned int>(time(0)));

    // 이벤트 선택
    int eventChoice;
    cout << "이벤트를 선택하세요 (1: 탐색 이벤트, 2: 전투 이벤트): ";
    cin >> eventChoice;

    if (eventChoice == 1) {
        // 탐색 이벤트 선택
        int explorationChoice;
        cout << "탐색 이벤트를 선택하세요 (1: 동굴 탐험, 2: 숲 탐색, 3: 폐허 조사): ";
        cin >> explorationChoice;

        string eventType;
        // 탐색 유형 결정
        switch (explorationChoice) {
            case 1:
                eventType = "동굴 탐험";
                break;
            case 2:
                eventType = "숲 탐색";
                break;
            case 3:
                eventType = "폐허 조사";
                break;
            default:
                cout << "잘못된 선택입니다. 프로그램을 종료합니다." << endl;
                return 0;
        }

        // D20 주사위 굴리기
        int result = rollD20();
        cout << "주사위 값: " << result << endl;

        // 탐색 이벤트 실행
        explorationEvent(result, eventType);

    } else if (eventChoice == 2) {
        // 전투 이벤트 실행
        int playerHP = 100; // 플레이어 초기 체력
        int enemyHP = 100;  // 적 초기 체력

        while (playerHP > 0 && enemyHP > 0) {
            int result = rollD20();
            cout << "주사위 값: " << result << endl;

            // 전투 이벤트 실행
            battleEvent(result, playerHP, enemyHP);

            // 종료 조건 체크
            if (playerHP <= 0) {
                cout << "플레이어가 쓰러졌습니다! 전투 종료." << endl;
                break;
            } else if (enemyHP <= 0) {
                cout << "적이 쓰러졌습니다! 전투 승리!" << endl;
                break;
            }
        }
    } else {
        cout << "잘못된 선택입니다. 프로그램을 종료합니다." << endl;
    }

    return 0;
}

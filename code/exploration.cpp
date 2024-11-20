#include "exploration.h"
#include <iostream>
#include <cstdlib> // 난수 생성을 위한 rand() 함수
#include <ctime>   // 시간 기반 시드 설정

using namespace std;

// D20 주사위 굴리기 함수 구현
int rollD20() {
    return (rand() % 20) + 1; // 1 ~ 20 사이의 난수 생성
}

// 탐색 이벤트 처리 함수 구현
void explorationEvent(int result, const string& eventType) {
    cout << "탐색 이벤트: " << eventType << endl;

    // 주사위 결과에 따른 탐색 이벤트 처리
    if (result == 1) {
        cout << "결과: 1 - 대실패! 함정을 밟았습니다. 탐색 실패!" << endl;
    } else if (result >= 2 && result <= 7) {
        cout << "결과: 2~7 - 탐색 실패! 아무것도 찾지 못했습니다." << endl;
    } else if (result >= 8 && result <= 13) {
        // 환경에 따라 다른 결과 출력
        if (eventType == "동굴 탐험") {
            cout << "결과: 8~13 - 동굴에서 '작은 보석'을 발견했습니다." << endl;
        } else if (eventType == "숲 탐색") {
            cout << "결과: 8~13 - 숲에서 '약초'를 발견했습니다." << endl;
        } else if (eventType == "폐허 조사") {
            cout << "결과: 8~13 - 폐허에서 '낡은 두루마리'를 발견했습니다." << endl;
        }
    } else if (result >= 14 && result <= 19) {
        // 환경에 따라 다른 결과 출력
        if (eventType == "동굴 탐험") {
            cout << "결과: 14~19 - 동굴 깊은 곳에서 '희귀 보석'을 발견했습니다!" << endl;
        } else if (eventType == "숲 탐색") {
            cout << "결과: 14~19 - 숲에서 '강력한 약초'를 발견했습니다!" << endl;
        } else if (eventType == "폐허 조사") {
            cout << "결과: 14~19 - 폐허에서 '고대의 지도'를 발견했습니다!" << endl;
        }
    } else if (result == 20) {
        // 환경에 따라 다른 결과 출력
        if (eventType == "동굴 탐험") {
            cout << "결과: 20 - 대성공! 동굴에서 '전설의 보석'을 발견했습니다!" << endl;
        } else if (eventType == "숲 탐색") {
            cout << "결과: 20 - 대성공! 숲에서 '전설의 약초'를 발견했습니다!" << endl;
        } else if (eventType == "폐허 조사") {
            cout << "결과: 20 - 대성공! 폐허에서 '고대의 유물'을 발견했습니다!" << endl;
        }
    }
}

// 전투 이벤트 처리 함수 구현
void battleEvent(int result, int& playerHP, int& enemyHP) {
    cout << "전투 이벤트 실행!" << endl;

    // 주사위 결과에 따른 전투 이벤트 처리
    if (result == 1) {
        // 플레이어 체력이 30%로 줄어듦
        playerHP = static_cast<int>(playerHP * 0.3);
        cout << "주사위 값: 1 - 대실패! 플레이어의 체력이 30%로 줄어듭니다." << endl;
    } else if (result >= 2 && result <= 7) {
        // 플레이어가 주사위 값만큼 데미지를 받음
        int damage = (14 - result) * 2;
        playerHP -= damage;
        cout << "주사위 값: " << result << " - 플레이어가 " << damage << "의 데미지를 받습니다." << endl;
    } else if (result >= 8 && result <= 13) {
        // 적이 주사위 값만큼 데미지를 받음
        int damage = result * 2;
        enemyHP -= damage ;
        cout << "주사위 값: " << result << " - 적이 " << damage << "의 데미지를 받습니다." << endl;
    } else if (result >= 14 && result <= 19) {
        // 적이 주사위 값만큼 데미지를 받음
        int damage = result * 2.5;
        enemyHP -= damage;
        cout << "주사위 값: " << result << " - 적이 " << damage << "의 데미지를 받습니다!" << endl;
    } else if (result == 20) {
        // 플레이어 체력을 20% 회복하고, 적에게 전체 체력의 60% 데미지
        playerHP += static_cast<int>(playerHP * 0.2);
        int damage = static_cast<int>(enemyHP * 0.6);
        enemyHP -= damage;
        cout << "주사위 값: 20 - 대성공! 플레이어가 체력을 20% 회복하고, 적에게 " << damage << "의 데미지를 입힙니다!" << endl;
    }

    // 현재 체력 상태 출력
    cout << "플레이어 체력: " << playerHP << ", 적 체력: " << enemyHP << endl;
}

// 전투 이벤트 루프 구현
void battleLoop() {
    int playerHP = 100; // 플레이어 초기 체력
    int enemyHP = 100;  // 적 초기 체력
    bool continueBattle = true;

    while (continueBattle && playerHP > 0 && enemyHP > 0) {
        int result = rollD20();

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


        // 전투 계속 여부 묻기
        int choice;
        cout << "전투를 더 지속하시겠습니까? (1: 예, 2: 아니오): ";
        cin >> choice;
        if (choice == 2) {
            continueBattle = false;
            cout << "전투를 종료하고 이벤트 선택으로 돌아갑니다." << endl;
        }
    }
}

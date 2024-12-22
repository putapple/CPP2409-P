#include "CombatSystem.h"
#include "DiceRoller.h"
#include <iostream>
#include <vector>

void CombatSystem::startCombat(Character& player, Enemy& enemy) {
    std::cout << "전투가 시작되었습니다! 상대: " << enemy.name << std::endl;

    while (player.hp > 0 && enemy.hp > 0) {
        playerTurn(player, enemy);
        if (enemy.hp <= 0) {
            std::cout << enemy.name << "을(를) 처치했습니다!" << std::endl;

            // 플레이어 체력 및 정신력 회복
            player.adjustHp(10);
            player.adjustWillpower(10);
            std::cout << player.name << "의 체력과 정신력이 각각 10 회복되었습니다!" << std::endl;
            std::cout << "현재 체력: " << player.hp << ", 현재 정신력: " << player.willpower << std::endl;

            // 보상 처리
            if (!enemy.rewards.empty()) {
                std::cout << enemy.name << "을(를) 쓰러트리고 다음 보상을 얻었습니다:" << std::endl;
                for (const auto& reward : enemy.rewards) {
                    player.items[reward.first] += reward.second;
                    std::cout << reward.first << " x" << reward.second << std::endl;
                }
            }

            // 특별 처리: 던전의 왕 MTE 처치 시
            if (enemy.name == "던전의 왕 MTE") {
                std::cout << "\n축하합니다! 던전의 왕 MTE를 처치하고 게임을 클리어했습니다!\n" << std::endl;
                std::cout << "모든 적을 물리치고 영웅의 전설을 남겼습니다. 게임을 종료합니다." << std::endl;
                return; // 게임 종료
            }

            // 탐색 이벤트 호출
            explorationEvent(player);
            break;
        }

        enemyTurn(player, enemy);
        if (player.hp <= 0) {
            std::cout << player.name << "이(가) 쓰러졌습니다..." << std::endl;
            break;
        }
    }
}



void CombatSystem::playerTurn(Character& player, Enemy& enemy) {
    std::cout << "\n=== 플레이어 턴 ===" << std::endl;
    std::cout << "1. 공격\n2. 기술\n3. 아이템\n";
    std::cout << "행동을 선택하세요: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: { // 공격
        std::cout << player.name << "이(가) " << enemy.name << "을(를) 공격합니다!" << std::endl;

        auto [roll, status] = DiceRoller::rollD20WithStatus();
        std::cout << "주사위 값: " << roll << " (" << status << ")" << std::endl;

        int damage = 0;
        if (status == "매우 나쁨") {
            std::cout << "공격이 빗나갔습니다!" << std::endl;
        } else if (status == "나쁨") {
            damage = roll;
        } else if (status == "보통") {
            damage = static_cast<int>(roll * 1.2);
        } else if (status == "좋음") {
            damage = static_cast<int>(roll * 1.2);
            player.adjustWillpower(5);
        } else if (status == "매우 좋음") {
            damage = static_cast<int>(roll * 2);
            player.adjustWillpower(10);
        }

        if (enemy.isWeak) {
            damage = static_cast<int>(damage * 1.5); // 약점 상태 시 추가 피해
            std::cout << enemy.name << "이(가) 약점으로 인해 추가 피해를 입었습니다!" << std::endl;
        }

        if (damage > 0) {
            enemy.hp -= damage;
            std::cout << enemy.name << "에게 " << damage << "의 피해를 입혔습니다. 남은 체력: " << enemy.hp << std::endl;
        }
        break;
    }
    case 2: { // 기술
        std::cout << "\n=== 기술 목록 ===" << std::endl;
        std::cout << "1. 신속한 타격 (정신력 5 소모)\n";
        std::cout << "2. 약점 분석 (정신력 7 소모)\n";
        std::cout << "3. 연타 (정신력 10 소모)\n";
        std::cout << "4. 목숨을 건 난투 (정신력 15 소모)\n";
        std::cout << "기술을 선택하세요: ";
        int skillChoice;
        std::cin >> skillChoice;

        switch (skillChoice) {
        case 1: { // 신속한 타격
            if (player.willpower < 5) {
                std::cout << "정신력이 부족하여 기술을 사용할 수 없습니다!" << std::endl;
            } else {
                player.adjustWillpower(-5);
                enemy.hp -= 20;
                std::cout << player.name << "이(가) 신속한 타격을 사용했습니다! "
                          << enemy.name << "에게 20의 피해를 입혔습니다." << std::endl;
            }
            break;
        }
        case 2: { // 약점 분석
            if (player.willpower < 7) {
                std::cout << "정신력이 부족하여 기술을 사용할 수 없습니다!" << std::endl;
            } else {
                player.adjustWillpower(-7);
                enemy.isWeak = true;
                std::cout << player.name << "이(가) 약점 분석을 사용했습니다! "
                          << enemy.name << "이(가) 취약 상태가 되었습니다." << std::endl;
            }
            break;
        }
        case 3: { // 연타
            if (player.willpower < 10) {
                std::cout << "정신력이 부족하여 기술을 사용할 수 없습니다!" << std::endl;
            } else {
                player.adjustWillpower(-10);
                std::cout << player.name << "이(가) 연타를 사용합니다!" << std::endl;

                int totalDamage = 0;
                for (int i = 0; i < 4; ++i) {
                    int roll = DiceRoller::rollD20();
                    std::cout << "주사위 값: " << roll << std::endl;
                    totalDamage += roll;
                }
                enemy.hp -= totalDamage;
                std::cout << enemy.name << "에게 총 " << totalDamage << "의 피해를 입혔습니다." << std::endl;
            }
            break;
        }
        case 4: { // 목숨을 건 난투
            if (player.willpower < 15) {
                std::cout << "정신력이 부족하여 기술을 사용할 수 없습니다!" << std::endl;
            } else {
                player.adjustWillpower(-15);
                std::cout << player.name << "이(가) 목숨을 건 난투를 사용합니다!" << std::endl;

                std::vector<int> customRolls = {1, 5, 10, 15, 20};
                int roll = customRolls[DiceRoller::rollD20() % 5];
                std::cout << "주사위 값: " << roll << std::endl;

                switch (roll) {
                case 1:
                    player.adjustWillpower(-10);
                    player.hp -= 20;
                    std::cout << "정신력이 10 감소하고, 체력이 20 감소했습니다!" << std::endl;
                    break;
                case 5:
                    enemy.hp -= 5;
                    player.hp -= 5;
                    std::cout << enemy.name << "의 체력이 5 감소하고, 당신의 체력이 5 감소했습니다!" << std::endl;
                    break;
                case 10:
                    enemy.hp -= 12;
                    std::cout << enemy.name << "의 체력이 12 감소했습니다!" << std::endl;
                    break;
                case 15:
                    player.adjustWillpower(5);
                    enemy.hp -= 24;
                    std::cout << "정신력이 5 회복되고, " << enemy.name << "의 체력이 24 감소했습니다!" << std::endl;
                    break;
                case 20:
                    player.adjustWillpower(30);
                    player.hp += 5;
                    enemy.hp -= 60;
                    std::cout << "정신력이 30 회복되고, 체력이 5 회복되었습니다!" << std::endl;
                    std::cout << enemy.name << "에게 60의 피해를 입혔습니다!" << std::endl;
                    break;
                }
            }

            break;
        }
        default:
            std::cout << "잘못된 선택입니다. 기술 사용이 취소됩니다." << std::endl;
            break;
        }

        break;
    }
    case 3: { // 아이템
    std::cout << "\n=== 아이템 목록 ===" << std::endl;

    // 아이템 목록 출력
    std::vector<std::string> itemNames;
    int index = 1;
    for (const auto& item : player.items) {
        std::cout << index << ". " << item.first << " (x" << item.second << ")" << std::endl;
        itemNames.push_back(item.first); // 아이템 이름 저장
        index++;
    }

    std::cout << "사용할 아이템의 번호를 입력하세요: ";
    int itemIndex;
    std::cin >> itemIndex;

    // 번호 유효성 검사
    if (itemIndex < 1 || itemIndex > static_cast<int>(itemNames.size())) {
        std::cout << "잘못된 선택입니다. 아이템 사용이 취소됩니다." << std::endl;
        break;
    }

    // 선택한 아이템 이름 가져오기
    std::string selectedItem = itemNames[itemIndex - 1];

    // 선택한 아이템 사용
    if (player.items[selectedItem] > 0) {
        if (selectedItem == "회복용 물약") {
            player.adjustHp(30); // 체력 30 회복
            player.items[selectedItem]--;
            std::cout << "회복용 물약을 사용하여 체력을 30 회복했습니다. 남은 물약: " << player.items[selectedItem] << std::endl;
        } else if (selectedItem == "투척 단검") {
            int damage = DiceRoller::rollD20();
            enemy.hp -= damage;
            player.items[selectedItem]--;
            std::cout << "투척 단검을 사용하여 " << enemy.name << "에게 " << damage << "의 피해를 입혔습니다. 남은 단검: " << player.items[selectedItem] << std::endl;
        } else if (selectedItem == "안티오크의 성스러운 수류탄") {
            enemy.hp -= 100; // 강력한 데미지
            player.items[selectedItem]--;
            std::cout << "안티오크의 성스러운 수류탄을 사용하여 " << enemy.name << "에게 100의 피해를 입혔습니다. 남은 수류탄: " << player.items[selectedItem] << std::endl;
        } else if (selectedItem == "행운의 동전") {
            player.adjustWillpower(10);
            player.items[selectedItem]--;
            std::cout << "행운의 동전을 사용하여 정신력을 10 회복했습니다. 남은 동전: " << player.items[selectedItem] << std::endl;
        } else {
            std::cout << "이 아이템은 사용할 수 없습니다." << std::endl;
        }
    } else {
        std::cout << "선택한 아이템이 부족합니다." << std::endl;
    }
    break;
}



    default:
        std::cout << "잘못된 선택입니다." << std::endl;
        break;
    }
}

void CombatSystem::enemyTurn(Character& player, Enemy& enemy) {
    std::cout << "\n=== 적 턴 ===" << std::endl;
    std::cout << "1. 반격\n2. 회피\n3. 방어\n";
    std::cout << "행동을 선택하세요: ";
    int choice;
    std::cin >> choice;

    // 적의 공격력 설정
    int attackValue = enemy.rollAttack();
    std::cout << enemy.name << "의 주사위 값: " << attackValue << std::endl;

    switch (choice) {
    case 1: { // 반격
        std::cout << player.name << "이(가) 반격을 시도합니다!" << std::endl;

        // 플레이어가 공격받음
        player.hp -= attackValue;
        std::cout << player.name << "의 체력이 " << attackValue << " 감소했습니다. 현재 체력: " << player.hp << std::endl;

        // 플레이어가 반격
        if (player.hp > 0) {
            int retaliationDamage = DiceRoller::rollD20();
            enemy.hp -= retaliationDamage;
            std::cout << player.name << "이(가) 반격하여 " << retaliationDamage << "의 피해를 입혔습니다!" << std::endl;
            std::cout << enemy.name << "의 남은 체력: " << enemy.hp << std::endl;
        } else {
            std::cout << player.name << "이(가) 쓰러져 반격할 수 없습니다." << std::endl;
        }
        break;
    }
    case 2: { // 회피
        std::cout << player.name << "이(가) 회피를 시도합니다!" << std::endl;

        // 플레이어와 적의 주사위 굴림
        int playerRoll = DiceRoller::rollD20();
        std::cout << player.name << "의 주사위 값: " << playerRoll << std::endl;

        if (playerRoll > attackValue) {
            // 회피 성공
            int willpowerGain = playerRoll - attackValue;
            player.adjustWillpower(willpowerGain);
            std::cout << player.name << "이(가) 회피에 성공했습니다! 정신력이 " << willpowerGain << " 회복되었습니다." << std::endl;
        } else {
            // 회피 실패
            player.hp -= attackValue;
            std::cout << player.name << "이(가) 회피에 실패하여 " << attackValue << "의 피해를 입었습니다. 현재 체력: " << player.hp << std::endl;
        }
        break;
    }
    case 3: { // 방어
        std::cout << player.name << "이(가) 방어를 시도합니다!" << std::endl;

        // 플레이어와 적의 주사위 굴림
        int playerRoll = DiceRoller::rollD20();
        std::cout << player.name << "의 주사위 값: " << playerRoll << std::endl;

        // 피해 계산
        int damage = attackValue - playerRoll;
        if (damage <= 0) {
            damage = 1; // 최소 피해는 1
        }
        player.hp -= damage;
        std::cout << player.name << "이(가) 방어하여 " << damage << "의 피해를 입었습니다. 현재 체력: " << player.hp << std::endl;
        break;
    }
    default:
        std::cout << "잘못된 선택입니다. 적의 공격이 성공합니다!" << std::endl;
        player.hp -= attackValue;
        std::cout << player.name << "의 체력이 " << attackValue << " 감소했습니다. 현재 체력: " << player.hp << std::endl;
        break;
    }
}

void CombatSystem::explorationEvent(Character& player) {
    std::cout << "\n=== 탐색 이벤트 ===" << std::endl;
    std::cout << "다음 장소 중 하나를 탐색하세요:\n";
    std::cout << "1. 낡은 모험가 텐트 (생존자 텐트)\n";
    std::cout << "2. 먼지가 쌓인 상자\n";
    std::cout << "3. 무너진 교회\n";
    std::cout << "선택: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: { // 생존자 텐트
        auto [roll, status] = DiceRoller::rollD20WithStatus();
        std::cout << "주사위 값: " << roll << " (" << status << ")" << std::endl;

        if (roll == 1) {
            player.adjustHp(-10); // 피해 10
            std::cout << "텐트가 함정이었습니다! 체력이 10 감소합니다!" << std::endl;
        } else if (roll == 20) {
            player.adjustHp(100 - player.hp); // 체력 최대로 회복
            std::cout << "텐트에서 생존자를 발견했습니다! 체력이 최대치로 회복되었습니다!" << std::endl;
        } else {
            double multiplier = (status == "나쁨") ? 1.0 : (status == "보통") ? 1.2 : 1.5;
            int healthGain = static_cast<int>(roll * multiplier);
            player.adjustHp(healthGain);
            std::cout << "텐트에서 휴식을 취했습니다. 상태(" << status << ")에 따라 체력이 " << healthGain << " 회복되었습니다!" << std::endl;
        }
        break;
    }
    case 2: { // 먼지가 쌓인 상자
        auto [roll, status] = DiceRoller::rollD20WithStatus();
        std::cout << "주사위 값: " << roll << " (" << status << ")" << std::endl;

        if (roll == 1) {
            std::cout << "상자가 비어 있었습니다. 아무 것도 얻지 못했습니다..." << std::endl;
        } else if (roll == 20) {
            player.adjustHp(10);
            player.adjustWillpower(10);
            player.items["투척 단검"] += 5;
            player.items["회복용 물약"] += 5;
            player.items["행운의 동전"] += 5;
            std::cout << "상자에서 엄청난 보상을 찾았습니다! 체력 10 회복, 정신력 10 회복, 단검 5개, 물약 5개, 동전 5개를 얻었습니다!" << std::endl;
        } else {
            int itemCount = (status == "나쁨") ? 1 : (status == "보통") ? 2 : 3;
            std::map<std::string, int> items = {{"투척 단검", 0}, {"회복용 물약", 0}, {"행운의 동전", 0}};

            for (auto& [item, count] : items) {
                count = itemCount; // 모든 아이템에 상태별 개수 추가
                player.items[item] += count;
            }

            std::cout << "상자에서 다음 보상을 찾았습니다:" << std::endl;
            for (const auto& [item, count] : items) {
                std::cout << item << " x" << count << std::endl;
            }
        }
        break;
    }
    case 3: { // 무너진 교회
        auto [roll, status] = DiceRoller::rollD20WithStatus();
        std::cout << "주사위 값: " << roll << " (" << status << ")" << std::endl;

        if (roll == 20) {
            player.items["안티오크의 성스러운 수류탄"] += 3;
            std::cout << "그대는 안티오크의 성스러운 수류탄을 그대의 적에게 던지어, 나의 눈에 불경한 자들은 뒈질 것이니라.\n";
            std::cout << "안티오크의 성스러운 수류탄 x3을 얻었습니다!" << std::endl;
        } else {
            std::cout << "교회를 탐색했지만 아무 것도 얻지 못했습니다..." << std::endl;
        }
        break;
    }
    default:
        std::cout << "잘못된 선택입니다. 탐색 이벤트를 스킵합니다." << std::endl;
        break;
    }

    std::cout << "\n탐색 이벤트가 끝났습니다. 다음 전투로 진행합니다.\n" << std::endl;
}

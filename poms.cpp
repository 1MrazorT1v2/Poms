#include <iostream>
#include <array>
#include <string>
#include <limits>

struct Team {
    std::string color;
};

int main() {
    const int PLAYER_COUNT = 4;
    const int START_APPLES = 5;
    std::array<Team, PLAYER_COUNT> teams{Team{"Red"}, Team{"Blue"}, Team{"Green"}, Team{"Yellow"}};

    int zone[PLAYER_COUNT][PLAYER_COUNT] = {};
    for (int i = 0; i < PLAYER_COUNT; ++i) {
        zone[i][i] = START_APPLES;
    }

    int turn = 0;
    while (true) {
        int player = turn % PLAYER_COUNT;
        if (zone[player][player] == 0) {
            std::cout << "Team " << teams[player].color << " has already moved all apples and wins!\n";
            break;
        }

        std::cout << "\nBoard status (rows are zones, cols are teams' apples):\n";
        for (int i = 0; i < PLAYER_COUNT; ++i) {
            std::cout << "Zone " << (i + 1) << " (Team " << teams[i].color << "):";
            for (int j = 0; j < PLAYER_COUNT; ++j) {
                std::cout << ' ' << zone[i][j];
            }
            std::cout << '\n';
        }

        std::cout << "Team " << teams[player].color << ", choose a zone to drop an apple (1-" << PLAYER_COUNT << ", not your own): ";
        int target;
        if (!(std::cin >> target)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }
        target -= 1;
        if (target < 0 || target >= PLAYER_COUNT || target == player) {
            std::cout << "Invalid zone. Try again.\n";
            continue;
        }

        zone[player][player] -= 1;
        zone[target][player] += 1;

        if (zone[player][player] == 0) {
            std::cout << "Team " << teams[player].color << " has moved all apples and wins!\n";
            break;
        }

        ++turn;
    }

    std::cout << "\nFinal board:\n";
    for (int i = 0; i < PLAYER_COUNT; ++i) {
        std::cout << "Zone " << (i + 1) << ":";
        for (int j = 0; j < PLAYER_COUNT; ++j) {
            std::cout << ' ' << zone[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}


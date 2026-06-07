#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>

// ───────────────────────────────
// Event (for logging only)
// ───────────────────────────────
struct Event {
    std::string who;
    int move;
};

// ───────────────────────────────
// Game state (single authority)
// ───────────────────────────────
class Game {
public:
    static constexpr int MIN = 1;
    static constexpr int MAX = 10;
    static constexpr int TARGET = 100;

    int curVal = 0;
    bool done = false;

    enum class Turn {
        HUMAN,
        COMPUTER
    };

    Turn turn = Turn::HUMAN;

    std::queue<Event> log;

    Game() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    int randomMove() {
        return MIN + (std::rand() % (MAX - MIN + 1));
    }

    void pushLog(const std::string& who, int move) {
        log.push({who, move});
    }

    void printLog() {
        while (!log.empty()) {
            auto e = log.front();
            log.pop();
            std::cout << e.who << " played " << e.move
                      << " | curVal = " << curVal << "\n";
        }
    }
};

// ───────────────────────────────
// HUMAN INPUT (blocking)
// ───────────────────────────────
int humanMove() {
    int move;

    while (true) {
        std::cout << "\nEnter move (1-10): ";
        std::cin >> move;

        if (move >= Game::MIN && move <= Game::MAX)
            return move;

        std::cout << "Invalid input. Try again.\n";
    }
}

// ───────────────────────────────
// COMPUTER AI
// ───────────────────────────────

#if 0
int computerMove(Game& g) {
    // simple random AI (you can replace with keys[] logic later)
    return g.randomMove();
}
#endif

int computerMove(Game& g) {

    int keys[9] = {1,12,23,34,45,56,67,78,89};

    int cur = g.curVal;

    // 1. If we are exactly on a key → break opponent pattern
    for (int i = 0; i < 9; i++) {
        if (cur == keys[i]) {
            return g.randomMove();  // disrupt user control
        }
    }

    // 2. Try to reach next key position
    for (int i = 0; i < 9; i++) {
        if (cur < keys[i]) {
            int move = keys[i] - cur;

            if (move >= Game::MIN && move <= Game::MAX)
                return move;
        }
    }

    // 3. If close to win → finish it
    int remaining = Game::TARGET - cur;
    if (remaining >= Game::MIN && remaining <= Game::MAX)
        return remaining;

    // 4. fallback (should rarely happen)
    return g.randomMove();
}

// ───────────────────────────────
// MAIN ENGINE LOOP
// ───────────────────────────────
void gameLoop(Game& game) {

    while (!game.done) {

        int move = 0;
        std::string who;

        // ───── TURN DISPATCH ─────
        if (game.turn == Game::Turn::HUMAN) {
            move = humanMove();
            who = "Human";
            game.turn = Game::Turn::COMPUTER;
        }
        else {
            move = computerMove(game);
            who = "Computer";
            game.turn = Game::Turn::HUMAN;
        }

        // ───── APPLY STATE ─────
        game.curVal += move;
        game.pushLog(who, move);

        // ───── OUTPUT ─────
        game.printLog();

        // ───── WIN CHECK ─────
        if (game.curVal >= Game::TARGET) {
            std::cout << "\n🎉 " << who << " wins at "
                      << game.curVal << "!\n";
            game.done = true;
        }
    }
}

// ───────────────────────────────
// MAIN
// ───────────────────────────────
int main() {

    Game game;
    gameLoop(game);

    return 0;
}

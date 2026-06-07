#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <cstdlib>
#include <ctime>

// ───────────────────────────────
// GAME LOGIC
// ───────────────────────────────
class Game {
public:
    static constexpr int MIN = 1;
    static constexpr int MAX = 10;
    static constexpr int TARGET = 100;

    int curVal = 0;
    bool done = false;

    int lastComputerMove = 0;

    enum class Turn { HUMAN, COMPUTER };
    Turn turn = Turn::HUMAN;

    enum class Result {
        NONE,
        HUMAN_WON,
        COMPUTER_WON
    };

    Result lastResult = Result::NONE;

    Game() {
        std::srand(std::time(nullptr));
    }

    int randomMove() {
        return MIN + (std::rand() % (MAX - MIN + 1));
    }

#if 0
    int computerMove() {
        int remaining = TARGET - curVal;
        if (remaining >= MIN && remaining <= MAX)
            return remaining;

        return randomMove();
    }
#endif

int computerMove()
{
    int keys[9] = {1, 12, 23, 34, 45, 56, 67, 78, 89};

    int cur = curVal;

    // 1. If on a key → random disruption
    for (int i = 0; i < 9; i++) {
        if (cur == keys[i]) {
            return randomMove();
        }
    }

    // 2. Try to reach next key
    for (int i = 0; i < 9; i++) {
        if (cur < keys[i]) {
            int move = keys[i] - cur;

            if (move >= MIN && move <= MAX)
                return move;
        }
    }

    // 3. Try to win directly
    int remaining = TARGET - cur;
    if (remaining >= MIN && remaining <= MAX)
        return remaining;

    // 4. fallback
    return randomMove();
}

    void step(int humanMove)
    {
        if (done) return;

        lastResult = Result::NONE;

        // ───── HUMAN TURN ─────
        if (turn == Turn::HUMAN) {

            curVal += humanMove;
            turn = Turn::COMPUTER;

            if (curVal >= TARGET) {
                done = true;
                lastResult = Result::HUMAN_WON;
                return;
            }
        }

        // ───── COMPUTER TURN ─────
        if (turn == Turn::COMPUTER && !done) {

            lastComputerMove = computerMove();
            curVal += lastComputerMove;
            turn = Turn::HUMAN;

            if (curVal >= TARGET) {
                done = true;
                lastResult = Result::COMPUTER_WON;
                return;
            }
        }
    }
};

// ───────────────────────────────
// QT WIDGET
// ───────────────────────────────
class GameWidget : public QWidget {
public:
    GameWidget()
    {
        game = new Game();

        auto *layout = new QVBoxLayout(this);

        status = new QLabel("Reach 100 first to win!");
        status->setStyleSheet("font-size: 16px; font-weight: bold;");
        layout->addWidget(status);

        scoreLabel = new QLabel("Score: 0");
        layout->addWidget(scoreLabel);

        auto *grid = new QGridLayout();

        // keypad 1–10
        for (int i = 1; i <= 10; i++) {

            QPushButton *btn = new QPushButton(QString::number(i));

            int row = (i - 1) / 5;
            int col = (i - 1) % 5;

            grid->addWidget(btn, row, col);

            connect(btn, &QPushButton::clicked, [this, i]() {
                onHumanMove(i);
            });
        }

        layout->addLayout(grid);
    }

private:
    Game *game;
    QLabel *status;
    QLabel *scoreLabel;

    void onHumanMove(int move)
    {
        if (game->done) return;

        game->step(move);

        QString msg;

        msg += "You chose: " + QString::number(move) + "\n";
        msg += "Computer chose: " + QString::number(game->lastComputerMove) + "\n";
        msg += "Total: " + QString::number(game->curVal);

        scoreLabel->setText(msg);

        if (game->done) {

            if (game->lastResult == Game::Result::HUMAN_WON)
                status->setText("You won 🎉");

            else if (game->lastResult == Game::Result::COMPUTER_WON)
                status->setText("You lost 💀");
        }
    }
};

// ───────────────────────────────
// MAIN
// ───────────────────────────────
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameWidget w;
    w.resize(320, 200);
    w.show();

    return app.exec();
}

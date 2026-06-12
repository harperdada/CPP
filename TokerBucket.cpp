#include <iostream>
#include <thread>

using namespace std;
class TokenBucket {
private:
    double tokens;
    double max_tokens;
    double refill_rate;   // tokens per second

    std::chrono::steady_clock::time_point last_refill;

    void refill();

public:
    TokenBucket(double capacity, double rate);

    bool consume(double amount);

    double availableTokens() const;
};

TokenBucket::TokenBucket(double capacity, double rate)
{
    tokens = capacity;
    max_tokens = capacity;
    refill_rate = rate;
    last_refill = std::chrono::steady_clock::now();
}

void TokenBucket::refill()
{
    auto now = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(now - last_refill).count();

    tokens += elapsed * refill_rate;

    if (tokens > max_tokens)
        tokens = max_tokens;

    last_refill = now;
}

bool TokenBucket::consume(double amount)
{
    refill();

    if (tokens >= amount)
    {
        tokens -= amount;
        return true;
    }

    return false;
}

int main()
{
    TokenBucket bucket(1000, 20); // capacity=1000, refill=20 tokens/sec

    for (;;) {
         std::this_thread::sleep_for(std::chrono::milliseconds(200));
         if (bucket.consume(50))
             std::cout << "Packet sent\n";
         else
             std::cout << "Rate limited\n";
    }
}


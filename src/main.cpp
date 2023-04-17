#include <iostream>
#include <stack>
#include <utility>

#include "Game.h"
#include <chrono> // for std::chrono functions

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset()
	{
		m_beg = Clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
	}
};

int main()

{
    //Timer t;

    Game this_game {};

    int turn_number;

    turn_number = this_game.run_game();

    //std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

    return turn_number;
}

#include <iostream>
#include <stack>
#include <utility>
//define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch_all.hpp>

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

/*
std::uint64_t Fibonacci(std::uint64_t number) {
    //return 5;
    return number < 2 ? 1 : Fibonacci(number - 1) + Fibonacci(number - 2);
}



TEST_CASE("Fibonacci") {
    CHECK(Fibonacci(0) == 1);
    // some more asserts..
    CHECK(Fibonacci(5) == 8);
    // some more asserts..

    // now let's benchmark:
    BENCHMARK("Fibonacci 20") {
        return Fibonacci(20);
    };

    BENCHMARK("Fibonacci 25") {
        return Fibonacci(25);
    };

    BENCHMARK("Fibonacci 30") {
        return Fibonacci(30);
    };

    BENCHMARK("Fibonacci 35") {
        return Fibonacci(35);
    };
}
*/
/*
int foo (int integer){

	int new_integer = integer + 5;

	return new_integer;
}

*/
int main()

{
    Timer t;

    //std::cout << "main is running" << std::endl;

    Game this_game {};

    this_game.run_game();

    /*
    Catch::Session session; // There must be exactly one instance
    int numFailed = session.run();
    */


    /*int returnCode = session.applyCommandLine( argc, argv );
  	if( returnCode != 0 ) // Indicates a command line error
       //return 0;

    int result = Catch::Session().run();
    */

    std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

    return 0;
}

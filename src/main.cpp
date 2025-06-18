#include "game.hpp"
#include <print>
int main() {
    Game game("Snake");
    if (!game.run()) {
        std::println("Failure");
        return EXIT_FAILURE;
    }
    std::println("Sucess!!");
    return EXIT_SUCCESS;
}

#include "commands.hpp"

void MoveUpCommand::execute(Snake &snake) { snake.setDirection(0.0f, -1.0f); }
void MoveDownCommand::execute(Snake &snake) { snake.setDirection(0.0f, 1.0f); }
void MoveRightCommand::execute(Snake &snake) { snake.setDirection(1.0f, 0.0f); }
void MoveLeftCommand::execute(Snake &snake) { snake.setDirection(-1.0f, 0.0f); }

MoveUpCommand::~MoveUpCommand() {}
MoveDownCommand::~MoveDownCommand() {}
MoveLeftCommand::~MoveLeftCommand() {}
MoveRightCommand::~MoveRightCommand() {}

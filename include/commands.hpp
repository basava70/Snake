#pragma once
#include "snake.hpp"

class Command {
public:
  virtual ~Command() = default;
  virtual void execute(Snake &) = 0;
};

class MoveUpCommand : public Command {
public:
  void execute(Snake &) override;
  ~MoveUpCommand() override;
};

class MoveRightCommand : public Command {
public:
  void execute(Snake &) override;
  ~MoveRightCommand() override;
};

class MoveDownCommand : public Command {
public:
  void execute(Snake &) override;
  ~MoveDownCommand() override;
};

class MoveLeftCommand : public Command {
public:
  void execute(Snake &) override;
  ~MoveLeftCommand() override;
};

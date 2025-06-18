#pragma once

class Command {
public:
  virtual ~Command() = default;
  virtual void execute() = 0;
};

class MoveUpCommand : public Command {
public:
  void execute() override;
  ~MoveUpCommand() override;
};

class MoveRightCommand : public Command {
public:
  void execute() override;
  ~MoveRightCommand() override;
};

class MoveDownCommand : public Command {
public:
  void execute() override;
  ~MoveDownCommand() override;
};

class MoveLeftCommand : public Command {
public:
  void execute() override;
  ~MoveLeftCommand() override;
};

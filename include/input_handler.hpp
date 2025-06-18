#pragma once
#include "commands.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class InputEvents {
  Quit,
  WindowResize,
  Pause,
};

class InputHandler {
private:
  std::unordered_set<SDL_Keycode> mJustPressedKeys;

  std::unordered_map<SDL_Keycode, std::shared_ptr<Command>> mCommandBindings;
  std::unordered_map<SDL_Keycode, InputEvents> mEventBindings;

  std::unordered_set<InputEvents> mTriggeredEvents;
  std::vector<std::shared_ptr<Command>> mTriggeredCommands;

  SDL_Event mEvent;

public:
  InputHandler();
  const std::unordered_set<InputEvents> &triggeredEvents() const;
  const std::vector<std::shared_ptr<Command>> &triggeredCommands() const;
  void run();
};

#include "input_handler.hpp"
#include <memory>

InputHandler::InputHandler() {
  mEventBindings[SDLK_Q] = InputEvents::Quit;
  mEventBindings[SDLK_ESCAPE] = InputEvents::Quit;
  mCommandBindings[SDLK_UP] = std::make_shared<MoveUpCommand>();
  mCommandBindings[SDLK_K] = std::make_shared<MoveUpCommand>();
  mCommandBindings[SDLK_DOWN] = std::make_shared<MoveDownCommand>();
  mCommandBindings[SDLK_J] = std::make_shared<MoveDownCommand>();
  mCommandBindings[SDLK_RIGHT] = std::make_shared<MoveRightCommand>();
  mCommandBindings[SDLK_L] = std::make_shared<MoveRightCommand>();
  mCommandBindings[SDLK_LEFT] = std::make_shared<MoveLeftCommand>();
  mCommandBindings[SDLK_H] = std::make_shared<MoveLeftCommand>();
}

void InputHandler::run() {
  while (SDL_PollEvent(&mEvent)) {
    if (mEvent.type == SDL_EVENT_QUIT)
      mTriggeredEvents.emplace(InputEvents::Quit);

    if (mEvent.type == SDL_EVENT_KEY_DOWN && !mEvent.key.repeat) {
      SDL_Keycode key = mEvent.key.key;

      auto eventIt = mEventBindings.find(key);
      if (eventIt != mEventBindings.end())
        mTriggeredEvents.emplace(eventIt->second);

      auto commandIt = mCommandBindings.find(key);
      if (commandIt != mCommandBindings.end())
        mTriggeredCommands.emplace_back(commandIt->second);
    }
  }
}

const std::unordered_set<InputEvents> &InputHandler::triggeredEvents() const {
  return mTriggeredEvents;
};

const std::vector<std::shared_ptr<Command>> &
InputHandler::triggeredCommands() const {
  return mTriggeredCommands;
};

#include <iostream>
#include <ncurses.h>
#include "core/input_manager.h"

using namespace kuratko::core;

void kuratko::core::InputManager::add(Handler h) {
  handlers_.push_back(h);
}

void kuratko::core::InputManager::handle(int c) {
  core::InputAction action = InputAction::NOP;

  switch (c) {
    case 'a':
    case KEY_LEFT:
    case 'h':
      action = InputAction::Left;
      break;
    case 'w':
    case KEY_UP:
    case 'k':
      action = InputAction::Up;
      break;
    case 's':
    case KEY_DOWN:
    case 'j':
      action = InputAction::Down;
      break;
    case 'd':
    case KEY_RIGHT:
    case 'l':
      action = InputAction::Right;
      break;
    case 'q':
      action = InputAction::Quit;
      break;

    default:
      // TODO - better logging
      std::cerr << "Unrecognized input character '" << c << "'" << std::endl;
  }

  if (action == InputAction::NOP) return;

  for (auto h : handlers_) {
    h(action);
  }
}

std::ostream& operator<<(std::ostream& os, InputAction action) {
  switch (action) {
    case InputAction::Up:
      return os << "Up";
    case InputAction::Down:
      return os << "Down";
    case InputAction::Left:
      return os << "Left";
    case InputAction::Right:
      return os << "Right";
    case InputAction::NOP:
      return os << "NOP";
    case InputAction::Quit:
      return os << "Quit";
    default:
      throw invalid_input_action{};
  }
}


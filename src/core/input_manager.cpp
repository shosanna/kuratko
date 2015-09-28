#include "core/input_manager.h"

void kuratko::core::InputManager::add(Handler h) {
  handlers_.push_back(h);
}

void kuratko::core::InputManager::handle(int c) {
  for (auto h : handlers_) {
    h(c);
  }
}

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <vector>
#include <functional>
#include <ostream>

namespace kuratko {
namespace core {

struct invalid_input_action {};

enum class InputAction { Up, Down, Left, Right, Quit, NOP };

std::ostream& operator<<(std::ostream& os, InputAction action);

class InputManager {
 public:
  using Handler = std::function<void(InputAction)>;

  void add(Handler h);
  void handle(int c);

 private:
  std::vector<Handler> handlers_;
};
}
}

#endif /* INPUT_MANAGER_H */

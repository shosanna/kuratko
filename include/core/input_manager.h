#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <vector>
#include <functional>

namespace kuratko {
namespace core {
class InputManager {
 public:
  using Handler = std::function<void(int)>;

  void add(Handler h);
  void handle(int c);

 private:
  std::vector<Handler> handlers_;
};
}
}

#endif /* INPUT_MANAGER_H */

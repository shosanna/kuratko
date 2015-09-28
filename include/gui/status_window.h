#ifndef STATUS_WINDOW_H
#define STATUS_WINDOW_H

#include <ncurses.h>
#include <string>
#include <functional>
#include <map>

#include "gui/window.h"

namespace kuratko {
namespace gui {
class StatusWindow : public Window {
 public:
  std::map<std::string, int> hladiky;

  using Window::Window;

  virtual void refresh() override;
};
}
}

#endif /* STATUS_WINDOW_H */

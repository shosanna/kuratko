#include <string>
#include <fstream>
#include "utils.h"

static std::string error__;

void clear_error() {
  set_error("                  ");
}

std::string get_error() {
  return error__;
}

void set_error(std::string s) {
  std::ofstream os("log.txt", std::ofstream::out | std::ofstream::app);
  os << s << std::endl;
  error__ = s;
}

#ifndef APP_HPP
#define APP_HPP

#include "../lib/queue.hpp"

#include <string>

int app_init(int *, char ***);

int start_app(queue<std::string>);

#endif
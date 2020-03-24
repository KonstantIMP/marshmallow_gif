#ifndef APP_HPP
#define APP_HPP

#include "../lib/queue.hpp"

#include <string>

int gtk_app_init(int *, char ***);

int gtk_start_app(queue<std::string>);

#endif

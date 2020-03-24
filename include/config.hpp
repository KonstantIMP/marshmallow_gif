#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#define STANDART "std"

#define THEME 0
#define LANG 1
#define EGGS 2
#define LAST 3
#define LOTS 4
#define UPDATE 5
#define GUI 6

bool search_cfg();

bool delete_cfg();

void create_cfg(std::string,
                std::string,
                std::string,
                std::string,
                std::string,
                std::string,
                std::string);

std::string get_param(char);

#endif

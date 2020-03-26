#include <string>
#include "../include/init.hpp"

#include "../lib/queue.hpp"

using namespace std;

int main(int argc, char *argv[]){
    if(app_init(&argc, &argv) == 2){
        //It will be message
    }

    std::string files;

    if(argc < 2) files = "";
    else files = argv[argc - 1];

    start_app(files, &argc, &argv);

    return 0;
}

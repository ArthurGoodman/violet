#include "engine.h"

int main(int argc, char **argv) {
    Engine::init(argc - 1, argv + 1);
    Engine::run();
    Engine::release();

    return 0;
}

#include <memory>
#include <basicini/basicini.h>
#include "yuzu_sdl_config/main_window.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<BasicIni> ini = std::make_unique<BasicIni>("test.ini");
    YuzuSdlConfig::Start(&argc, &argv, std::move(ini));
    return 0;
}

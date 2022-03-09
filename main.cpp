#include <chrono>
#include "src/Graphic.hpp"
#include "src/Inputs.hpp"
#include "src/Raycasting.hpp"
#include "src/Map.hpp"

#define tnow() (std::chrono::high_resolution_clock::now())

int main(int ac, char **av) {
    auto graphic = Graphic::get();
    auto player = std::make_shared<Player>();
    auto input = std::make_shared<Inputs>(graphic, player);
    auto map = std::make_shared<Map>();

    int fps = 0;
    auto start = tnow();
    while (!graphic->update(player)){
        if (std::chrono::duration_cast<std::chrono::milliseconds>(tnow() - start).count() > 500) {
            std::cout << "\rFps: " << fps * 2 << "" << std::flush;
            start = tnow();
            fps = 0;
        }
        fps++;
        input->update(graphic, player);
//        Raycasting::drawMap(graphic, player, map);
    }
}

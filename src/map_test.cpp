#include <mapping/map.h>
#include <mapping/map_builder.h>

int main(void) {
    controllers::map real;
    real = map_builder::build_real_pman_map();
    real.print();
    // controllers::map config;
    return 1;
}
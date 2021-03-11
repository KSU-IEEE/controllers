#include <mapping/map.h>
#include <mapping/map_builder.h>

int main(void) {
    controllers::map real;
    controllers::map config;

    real = map_builder::build_real_pman_map();
    config = map_builder::build_config_space_map(real);
    
    real.print();
    config.print();
    
    return 1;
}
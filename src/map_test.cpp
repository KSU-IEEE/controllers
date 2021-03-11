#include <mapping/map.h>
#include <mapping/map_builder.h>

int main(void) {
    controllers::map real;
<<<<<<< HEAD
    controllers::map config;

    real = map_builder::build_real_pman_map();
    config = map_builder::build_config_space_map(real);
    
    real.print();
    config.print();
    
=======
    real = map_builder::build_real_pman_map();
    real.print();
    // controllers::map config;
>>>>>>> c6b1f231f740e4fe752c1b22b17d10617b9d32e1
    return 1;
}
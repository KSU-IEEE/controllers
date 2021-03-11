#include <mapping/map.h>
#include <mapping/map_builder.h>
#include <iostream>

int main(void) {
    std::cout<<"Creating Maps"<<std::endl;
    controllers::map real;
    controllers::map config;

    std::cout<<"Maps Made, generating pman"<<std::endl;

    real = map_builder::build_real_pman_map();

    std::cout<<"pman made, making config"<<std::endl;

   // config = map_builder::build_config_space_map(real);
    
    real.print();
    //config.print();
    
    return 1;
}
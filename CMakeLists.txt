cmake_minimum_required(VERSION 3.10)
project(controllers)

#############################
## ADD Targets for install ##
#############################

include_directories(include)

# add cpp files here
set(SRCS 
  src/map.cpp 
  src/map_builder.cpp
)
if ( NOT ("${SRCS}" STREQUAL "") )
    set(LIBS)
    message(STATUS "${PROJECT_NAME} library compiling: ${SRCS}")
    message(STATUS "BINARY DIR: ${PROJECT_BINARY_DIR}")
    add_library(controllers ${SRCS})
    target_link_libraries(controllers 
        PUBLIC
        ${LIBS})

    #############
    ## Install ##
    #############
    install(TARGETS controllers
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}
    ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}
    )

    ## Mark cpp header files for installation
    install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${PROJECT_BINARY_DIR}
    FILES_MATCHING PATTERN "*.h"
    )
endif()
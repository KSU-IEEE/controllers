cmake_minimum_required(VERSION 3.10)
project(controllers)

#############################
## ADD Targets for install ##
#############################

include_directories(include)

# add cpp files here
set(SRCS
)
set(BUILDER 
  src/map.cpp
  src/map_builder.cpp
)
set(A_STAR
  src/node.cpp
  src/A_Star_Logic.cpp
)

# for builder tests 
if ( NOT ("${BUILDER}" STREQUAL "") )
    set(LIBS)
    message(STATUS "${PROJECT_NAME} library compiling: ${BUILDER}")
    message(STATUS "BINARY DIR: ${PROJECT_BINARY_DIR}")
    add_library(builder ${BUILDER})
    target_link_libraries(builder 
        PUBLIC
        ${LIBS})

    #############
    ## Install ##
    #############
    install(TARGETS builder
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}
    ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/archive
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}
    )

    ## Mark cpp header files for installation
    install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${PROJECT_BINARY_DIR}
    FILES_MATCHING PATTERN "*.h"
    )

    add_executable(map_builder ${BUILDER})
endif()
if ( NOT ("${A_STAR}" STREQUAL "") )
    set(LIBS)
    message(STATUS "${PROJECT_NAME} library compiling: ${A_STAR}")
    message(STATUS "BINARY DIR: ${PROJECT_BINARY_DIR}")
    add_library(a_star ${A_STAR})
    target_link_libraries(a_star 
        PUBLIC
        ${LIBS})

    #############
    ## Install ##
    #############
    install(TARGETS a_star
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}
    ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/archive
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}
    )

    ## Mark cpp header files for installation
    install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${PROJECT_BINARY_DIR}
    FILES_MATCHING PATTERN "*.h"
    )

    add_executable(a_star_logic ${A_STAR})
endif()

# for final code
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
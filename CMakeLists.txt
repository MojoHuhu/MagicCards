cmake_minimum_required(VERSION 3.13)  # CMake version check


project(simple VERSION 0.0.1)               # Create project "simple_example"


add_subdirectory(libs/third-party/lua)
add_subdirectory(libs/third-party/jsoncpp)


# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME}  main.cpp 
                                libs/card/card.cpp 
                                libs/player/player.cpp 
                                libs/database/database.cpp 
                                )


target_link_libraries(${PROJECT_NAME} lua_static)
target_link_libraries(${PROJECT_NAME} jsoncpp_static)
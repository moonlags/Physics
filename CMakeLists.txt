cmake_minimum_required(VERSION 3.25)
project(Physics VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Physics main.cpp Game.cpp Game.h window.h window.cpp)

target_include_directories(Physics PRIVATE C:/SDL2/include)
target_link_directories(Physics PRIVATE C:/SDL2/lib)
target_link_libraries(Physics PRIVATE -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image)
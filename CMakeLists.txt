cmake_minimum_required(VERSION 3.12)
project(Project C)

set(CMAKE_C_STANDARD 99)

add_executable(Project main.c command.c command.h parser.c parser.h history.h history.c structs.c structs.h help.c bg.c bg.h help.h portaudio.h variables.h variables.c kilo.h kilo.c)

target_link_libraries(Project readline)
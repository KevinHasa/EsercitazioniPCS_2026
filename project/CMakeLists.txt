cmake_minimum_required(VERSION 3.20)

project(circuiti)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

include_directories(/usr/include/eigen3)

add_executable(risolvi_circuito 
    main.cpp
    read_netlist.cpp
    dfs_cicli.cpp
    de_pina.cpp
    costruttore_matrix.cpp
    gradiente_coniugato.cpp
)

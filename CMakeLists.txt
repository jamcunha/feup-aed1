cmake_minimum_required(VERSION 3.22)
project(feup_aed1)

set(CMAKE_CXX_STANDARD 14)

add_executable(feup_aed1 src/main.cpp src/UCTurma.cpp src/Estudante.cpp src/Aula.cpp src/TurmaH.cpp src/Gestor.cpp)

include_directories(feup_aed1 /include)

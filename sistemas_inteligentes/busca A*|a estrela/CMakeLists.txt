cmake_minimum_required(VERSION 3.14)
project(c__)

set(CMAKE_CXX_STANDARD 17)

add_executable(c__ main.cpp comuns/PontosCardeais.hpp comuns/Labirinto.cpp comuns/Labirinto.hpp Ambiente/Model.cpp Ambiente/Model.hpp Ambiente/View.cpp Ambiente/View.hpp problema/Estado.cpp problema/Estado.hpp problema/Problema.cpp problema/Problema.hpp Agente.cpp Agente.hpp arvore/TreeNode.cpp arvore/TreeNode.hpp)

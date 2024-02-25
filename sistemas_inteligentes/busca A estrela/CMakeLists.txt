cmake_minimum_required(VERSION 3.14)
project(c__)

set(CMAKE_CXX_STANDARD 17)

add_executable(c__ main.cpp 
              comuns/PontosCardeais.hpp comuns/Labirinto.o comuns/Labirinto.hpp 
              Ambiente/Model.o Ambiente/Model.hpp Ambiente/View.o Ambiente/View.hpp
              problema/Estado.o problema/Estado.hpp problema/Problema.o problema/Problema.hpp 
              Agente.cpp Agente.hpp 
              arvore/TreeNode.cpp arvore/TreeNode.hpp)

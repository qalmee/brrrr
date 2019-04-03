cmake_minimum_required(VERSION 3.12)
project(untitled2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

add_executable(${PROJECT_NAME} main.cpp codes/CodeItem.h codes/Huffman.cpp codes/Huffman.h codes/Fano.cpp codes/Fano.h codes/ShannonInterface.cpp codes/ShannonInterface.h codes/CodeItem.cpp codes/HilbertMoore.cpp codes/HilbertMoore.h codes/ShannonImpl.cpp codes/ShannonImpl.h codes/TernaryHuffman.cpp codes/TernaryHuffman.h service/Service.cpp service/Service.h service/ArchiveManager.cpp service/ArchiveManager.h codes/BlockCode.cpp codes/BlockCode.h)
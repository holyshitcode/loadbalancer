cmake_minimum_required(VERSION 3.29)
project(loadbalancer C)

set(CMAKE_C_STANDARD 99)

add_executable(loadbalancer main.c
        processor.c
        task.c
        balance.c)

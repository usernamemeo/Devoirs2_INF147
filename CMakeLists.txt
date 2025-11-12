cmake_minimum_required(VERSION 4.0)
project(Devoirs2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Devoirs2 test_m_opbits_char.c
        m_opbits_char.c
        m_opbits_int.c)

cmake_minimum_required(VERSION 4.0)
project(Devoirs2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Devoirs2
        #test_m_opbits_char.c
        m_opbits_char.c
        m_opbits_int.c
        m_gen_gosmique_N.c
        m_gen_gosmique_N.h
        m_gen_gosmique_B.c
        m_gen_gosmique_B.h
        main.c
        m_alea00.c
        affich_informatrice_log.c
        affich_informatrice_log.h
)

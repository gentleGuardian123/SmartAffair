find_package(SEAL 4.1 REQUIRED)

add_library(wt_pir pir_util.hpp pir_util.cpp pir_client.hpp pir_client.cpp pir_server.hpp pir_server.cpp)
target_link_libraries(wt_pir SEAL::seal)

add_executable(main main.cpp)
target_link_libraries(main wt_pir)

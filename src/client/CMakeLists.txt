add_library(client_core STATIC
    tcp_client.cc
)

target_include_directories(client_core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(client_core
    PRIVATE common
)
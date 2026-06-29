add_executable(server server_main.cc)
add_executable(client client_main.cc)

target_link_libraries(server
    PRIVATE server_core
    PRIVATE common
)
target_link_libraries(client
    PRIVATE client_core
    PRIVATE common
)
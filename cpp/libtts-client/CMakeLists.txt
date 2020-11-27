project(libtts_client)

set (CMAKE_CXX_FLAGS -fPIC)

add_library(${PROJECT_NAME}
        techmo_tts.grpc.pb.cc techmo_tts.grpc.pb.h
        techmo_tts.pb.cc techmo_tts.pb.h
        Client.cpp Client.h
        VERSION.h
        )

# Depend on a library that we defined in the top-level file
target_link_libraries(${PROJECT_NAME}
        grpc_pkg
        )

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

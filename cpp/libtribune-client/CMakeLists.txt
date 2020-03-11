project(libtribune_client)

set (CMAKE_CXX_FLAGS -fPIC)

add_library(${PROJECT_NAME}
        tribune_tts.grpc.pb.cc tribune_tts.grpc.pb.h
        tribune_tts.pb.cc tribune_tts.pb.h
        tribune_client.cpp tribune_client.h
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

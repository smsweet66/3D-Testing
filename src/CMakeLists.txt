add_executable(${PROJECT_NAME} camera.cpp main.cpp shader.cpp texture.cpp vertexArray.cpp vertexBuffer.cpp mesh.cpp)

target_link_libraries(${PROJECT_NAME} glfw glad tinyobjloader)
target_precompile_headers(${PROJECT_NAME} PUBLIC pch.hpp)
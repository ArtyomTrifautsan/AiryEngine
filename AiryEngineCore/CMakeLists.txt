cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME AiryEngineCore)

set(ENGINE_PUBLIC_INCLUDES
includes/AiryEngineCore/Rendering/OpenGL/Model3D.hpp
    includes/AiryEngineCore/Application.hpp
    includes/AiryEngineCore/Camera.hpp
    includes/AiryEngineCore/Event.hpp
    includes/AiryEngineCore/Log.hpp
    includes/AiryEngineCore/Keys.hpp
    includes/AiryEngineCore/Input.hpp
    includes/AiryEngineCore/Renderer.hpp
    includes/AiryEngineCore/ResourceManager.hpp

    includes/AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp
    includes/AiryEngineCore/Physics/CollidingObjects/SphereCollidingObject.hpp
    includes/AiryEngineCore/Physics/CollisionDetector.hpp
)

set(ENGINE_PRIVATE_INCLUDES
    src/AiryEngineCore/Window.hpp
    src/AiryEngineCore/stb_image.h

    src/AiryEngineCore/Modules/UIModule.hpp

    src/AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp
    src/AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp
    src/AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp
    src/AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp
    src/AiryEngineCore/Rendering/OpenGL/VertexArray.hpp
    src/AiryEngineCore/Rendering/OpenGL/Mesh.hpp
    src/AiryEngineCore/Rendering/OpenGL/Texture2D.hpp
)

set(ENGINE_PRIVATE_SOURCES
    src/AiryEngineCore/Application.cpp
    src/AiryEngineCore/Camera.cpp
    src/AiryEngineCore/Window.cpp
    src/AiryEngineCore/Input.cpp
    src/AiryEngineCore/Renderer.cpp
    src/AiryEngineCore/ResourceManager.cpp

    src/AiryEngineCore/Modules/UIModule.cpp

    src/AiryEngineCore/Rendering/OpenGL/Model3D.cpp
    src/AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.cpp
    src/AiryEngineCore/Rendering/OpenGL/ShaderProgram.cpp
    src/AiryEngineCore/Rendering/OpenGL/VertexBuffer.cpp
    src/AiryEngineCore/Rendering/OpenGL/IndexBuffer.cpp
    src/AiryEngineCore/Rendering/OpenGL/VertexArray.cpp
    src/AiryEngineCore/Rendering/OpenGL/Texture2D.cpp
    src/AiryEngineCore/Rendering/OpenGL/Mesh.cpp

    src/AiryEngineCore/Physics/CollisionDetector.cpp
    src/AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.cpp
    src/AiryEngineCore/Physics/CollidingObjects/SphereCollidingObject.cpp
)

set(ENGINE_ALL_SOURCES
    ${ENGINE_PUBLIC_INCLUDES}
    ${ENGINE_PRIVATE_INCLUDES}
    ${ENGINE_PRIVATE_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
    ${ENGINE_ALL_SOURCES}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glm)



set(IMGUI_INCLUDES
    ../external/imgui/imgui.h
    ../external/imgui/backends/imgui_impl_glfw.h
    ../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
    ../external/imgui/imgui.cpp
    ../external/imgui/backends/imgui_impl_glfw.cpp
    ../external/imgui/backends/imgui_impl_opengl3.cpp
    ../external/imgui/imgui_draw.cpp
    ../external/imgui/imgui_tables.cpp
    ../external/imgui/imgui_widgets.cpp
    ../external/imgui/imgui_demo.cpp
)

add_library(ImGui STATIC
    ${IMGUI_INCLUDES}
    ${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)

target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)

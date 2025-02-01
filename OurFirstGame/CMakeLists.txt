cmake_minimum_required(VERSION 3.12)

set(GAME_PROJECT_NAME OurFirstGame)

set(GAME_INCLUDES
    src/game_application.hpp
    src/game_round.hpp
)

set(GAME_SOURCES
    src/game_application.cpp
    src/game_round.cpp
)

add_executable(${GAME_PROJECT_NAME}
    src/main.cpp
    ${GAME_INCLUDES}
    ${GAME_SOURCES}
)

target_link_libraries(${GAME_PROJECT_NAME} AiryEngineCore ImGui glm)
target_compile_features(${GAME_PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${GAME_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${GAME_PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>/Resources)
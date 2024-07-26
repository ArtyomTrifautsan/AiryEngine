cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME 3DgameCpp)

add_subdirectory(AiryEngineCore)
add_subdirectory(OurFirstGame)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OurFirstGame)
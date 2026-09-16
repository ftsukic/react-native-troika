cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

set(rnoh_keyboard_insets_generated_dir "${CMAKE_CURRENT_SOURCE_DIR}/RNOH/generated")
file(GLOB_RECURSE rnoh_keyboard_insets_generated_SRC
    "${rnoh_keyboard_insets_generated_dir}/**/*.cpp")
file(GLOB rnoh_keyboard_insets_SRC CONFIGURE_DEPENDS *.cpp)
add_library(rnoh_keyboard_insets SHARED
    ${rnoh_keyboard_insets_SRC}
    ${rnoh_keyboard_insets_generated_SRC})
target_include_directories(rnoh_keyboard_insets PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${rnoh_keyboard_insets_generated_dir})
target_link_libraries(rnoh_keyboard_insets PUBLIC rnoh)

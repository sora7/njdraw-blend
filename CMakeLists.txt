project(njdraw-blend)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
#add_definitions(-Wall -O2 -municode)

set(APP_DIR "${CMAKE_CURRENT_LIST_DIR}")


set(BLEND2D_DIR "${APP_DIR}/lib/blend2d")
set(BLEND2D_STATIC TRUE)
include("${BLEND2D_DIR}/CMakeLists.txt")


set(ASMJIT_DIR "${APP_DIR}/lib/asmjit")
include("${ASMJIT_DIR}/CMakeLists.txt")


set(SDL_DIR "${APP_DIR}/lib/SDL2-2.0.10")
set( SDL_STATIC OFF CACHE BOOL "" FORCE )
set( SDL_SHARED ON CACHE BOOL "" FORCE )

add_subdirectory("${SDL_DIR}" EXCLUDE_FROM_ALL)

aux_source_directory("${APP_DIR}/src" SRC_LIST)

add_executable(
    njdraw-blend
    ${SRC_LIST}
    )

target_link_libraries(
    njdraw-blend
    mingw32
    Blend2D::Blend2D
    SDL2main
    SDL2
    )











#target_link_libraries(
#    njdraw-blend

#    mingw32

#    ${BLEND2D_LIB}/libblend2d.a

##    ${SDL_LIB}/libSDL2main.a
##    ${SDL_LIB}/libSDL2.dll.a
##    ${SDL_LIB}/libSDL2.a
#    )

##install(TARGETS ${PROJECT_NAME} DESTINATION bin)

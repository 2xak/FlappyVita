cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE STRING "Vita toolchain file")
    else()
        message(FATAL_ERROR "VITASDK environment variable not set and CMAKE_TOOLCHAIN_FILE not defined.")
    endif()
endif()

project(flappy_vita)

include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "FlappyVita")
set(VITA_TITLEID "FLAPV0001")
set(VITA_VERSION "01.00")

add_executable(${PROJECT_NAME} 
src/main.cpp
src/Timer.h
src/Bird.h
src/Input.h
src/Level.h)

target_link_libraries(${PROJECT_NAME} 
vita2d
SceCtrl_stub
SceDisplay_stub
SceGxm_stub
SceSysmodule_stub
SceAppMgr_stub
SceCommonDialog_stub
ScePgf_stub
SceTouch_stub
m
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})

vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
    FILE sce_sys/icon0.png sce_sys/icon0.png
)

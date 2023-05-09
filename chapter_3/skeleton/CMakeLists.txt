cmake_minimum_required(VERSION 3.0.0)
project(skeleton VERSION 0.1.0)

#########################################################################################
# WHAT IS THIS FOR ?

include(CTest)
enable_testing()

#########################################################################################
# COMPILE FLAGS : COMPILER OPTIONS

# Just in case we wanna move to mingw
if (MSVC)
    add_compile_options(/W4)
endif()

#########################################################################################
# COMPILE FLAGS : SOURCES
file(GLOB MY_SOURCES "*.cpp")
file(GLOB MY_HEADERS "*.hpp")


add_executable(skeleton ${MY_SOURCES} ${MY_HEADERS} skeleton.rc)


#########################################################################################
# LINKER FLAGS
# Add linker flag to instruct cmake to set the linker to use WinMainCRTStartup as the entry point for your Windows application.
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:WinMainCRTStartup")


#########################################################################################
# WHAT IS THIS ?
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

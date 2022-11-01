cmake_minimum_required(VERSION 3.22)
message("Using toolchain file ${CMAKE_TOOLCHAIN_FILE}.")

project(
	DtryKeyUtil
	VERSION 0.0.2
	DESCRIPTION "A munted update to CommonLibSSE-NG"
	LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

######
# File definitions (Could be nicer but I just want it all in one file right now)
######
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
	@ONLY
)

set(headers
	#src/PCH.h
)

set(sources
	src/main.cpp
	src/PCH.h
	src/hasher.hpp
	src/hooks.cpp
	src/hooks.h
	src/inputEventHandler.cpp
	src/inputEventHandler.h
	src/settings.cpp
	src/settings.h
	src/utils.h
	src/lib/SimpleIni.h
	src/inputHandler/inputTracer.h
	src/inputHandler/inputTracer.cpp
	src/inputHandler/inputTrigger.h
	src/inputHandler/inputTrigger.cpp
	src/inputHandler/movementInputTracer.h
	src/inputHandler/movementInputTracer.cpp
	src/inputHandler/animEvent.cpp
	src/inputHandler/animEvent.h

	${CMAKE_CURRENT_BINARY_DIR}/version.rc
)

source_group(
        TREE ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        ${headers}
        ${sources})

######
# Library inclusions and target config
######
find_package(CommonLibSSE CONFIG REQUIRED)
find_package(xbyak REQUIRED CONFIG)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${headers} ${sources})
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
        $<INSTALL_INTERFACE:src>
)

set(SKSE_SUPPORT_XBYAK ON)
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		xbyak::xbyak
)

target_precompile_headers(
	${PROJECT_NAME}
    PRIVATE
        src/PCH.h
)


install(TARGETS ${PROJECT_NAME}
        DESTINATION "${CMAKE_INSTALL_LIBDIR}")



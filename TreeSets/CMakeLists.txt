################
# CMAKE RULES! #
################

# Need feature in 3.8 or better
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

# Name and Version of the project
project(TreeSets LANGUAGES CXX)

# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Be nice and export compile commands by default
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
	if(CMAKE_CL_64)
        set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
    endif()
endif()

# Helpful option enable build profiling to identify slowly compiling files
#option(MEASURE_ALL "When enabled all commands will be passed through time command" OFF)
#if(MEASURE_ALL)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "time")
#endif()

# Setting the project to cxx_std_11
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_BUILD_TYPE STREQUAL "")
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up differentiation between debug and releaase builds
	set(CMAKE_BUILD_TYPE
				"Debug"
		CACHE STRING
				"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
)
endif (CMAKE_BUILD_TYPE STREQUAL "")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -02")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else ()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /02")
endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

# Lets LOAD app our headers!
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS
		${TreeSets_SOURCE_DIR}/src/*.hpp
		${TreeSets_SOURCE_DIR}/src/*.h
)

# Lets LOAD app our sources!
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
		${TreeSets_SOURCE_DIR}/src/*.cpp
		${TreeSets_SOURCE_DIR}/src/*.c
)

# Only adding the test subdirectory if the build type is debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_subdirectory(tests EXCLUDE_FROM_ALL)
endif()

# Define the executable
add_executable(TreeSets ${HDRS} ${SRCS})

# We need a CMake_Dir with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${TreeSets_SOURCE_DIR}/cmake)

#######################################
# LOOK for the packages that we need! #
#######################################

# No Packages required

# Define the include DIRs
include_directories(
		${TreeSets_SOURCE_DIR}/headers
		${TreeSets_SOURCE_DIR}/sources
		${TreeSets_SOURCE_DIR}/src
)

# Define the link libraries
# target_link_libraries(TreeSets )

if (WIN32)
	string(REPLACE "/" "\\" source_path_windows "${TreeSets_SOURCE_DIR}/res")
	string(REPLACE "/" "\\" build_path_windows "${TreeSets_BINARY_DIR}/res")
	execute_process(COMMAND cmd.exe /c mklink /J "${build_path_windows}" "${source_path_windows}" RESULT_VARIABLE exitcode)
else()
	execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${TreeSets_SOURCE_DIR}/res ${TreeSets_BINARY_DIR}/res RESULT_VARIABLE exitcode)
endif()

if(NOT ${exitcode} EQUAL 0)
	message("SYMLINKING FAILED: ${exitcode}")
	message("FAILED BACK TO COPYING")
endif()

# Copy only if the build folder contains outdated res folder. Only if symlink failed.
file(GLOB_RECURSE RES RELATIVE ${TreeSets_SOURCE_DIR}/res/ ${TreeSets_SOURCE_DIR}/res/*.*)
foreach(file IN LISTS RES)
	configure_file(${TreeSets_SOURCE_DIR}/res/${file} ${TreeSets_BINARY_DIR}/res/${file} COPYONLY)
endforeach()

#Creating virt folders for VS
if(MSVC_IDE)
	foreach(source IN LISTS SRCS HDRS)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${TreeSets_SOURCE_DIR}" "" relative_source_path "${source_paths}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()

install(TARGETS TreeSets DESTINATION ${TreeSets_SOURCE_DIR}/bin)

# Wrap up of settings printed on build
message(STATUS "")
message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} ${VERSION_TYPE} @ ${VERSION_HOST}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  possible options: Debug Release RelWithDebInfo MinSizeRel")
message(STATUS "  set with ` cmake -DCMAKE_BUILD_TYPE=Debug .. `")
message(STATUS "")
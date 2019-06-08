# Tests

add_definitions(-DTESTCODE)

include_directories(
		${3DRenderingEngine_SOURCE_DIR}/headers
		${3DRenderingEngine_SOURCE_DIR}/sources
		${3DRenderingEngine_SOURCE_DIR}/src
		${OPENGL_INCLUDE_DIRS}
		${GLEW_INCLUDE_DIRS}
		${SDL2_INCLUDE_DIRS}
		${ASSIMP_INCLUDE_DIRS}
)

add_executable(3DRendingEngineTest ${SRCS} ${HDRS})

target_link_libraries(3DRendingEngineTest
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES}
		${SDL2_LIBRARIES}
		${ASSIMP_LIBRARIES}
)
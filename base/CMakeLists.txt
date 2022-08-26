aux_source_directory(. SRC_FILES)

add_library(mynetbase ${SRC_FILES})
target_link_libraries(mynetbase pthread rt)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION base)

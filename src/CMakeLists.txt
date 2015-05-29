include_directories(${ASPACEOPERA_SOURCE_DIR}/src/
			#${ASPACEOPERA_SOURCE_DIR}/deps/vmmlib/include/
			)

#include_directories(${ProtobufIncludePath})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

set(ASPACEOPERA_CLIENT_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/client/ASpaceOpera.cpp
  )

set(ASPACEOPERA_CLIENT_HEADERS)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#add_subdirectory(messages)
add_subdirectory(client)
add_subdirectory(db)
add_subdirectory(interfaces)
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(graphics)
add_subdirectory(util)
add_subdirectory(widgets)

#set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES GENERATED TRUE)

add_executable(ASpaceOpera ${ASPACEOPERA_CLIENT_SOURCE} ${ASPACEOPERA_CLIENT_HEADERS} interfaces/chatnotebook.cpp interfaces/chatnotebook.h)

target_link_libraries(ASpaceOpera ${wxWidgets_LIBRARIES})

#SET_TARGET_PROPERTIES(ASpaceOpera PROPERTIES  LINK_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncursesw -lprotobuf")
#if(UNIX AND NOT APPLE)
#        set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncurses -lprotobuf -lrt")
#endif()


find_package(Boost COMPONENTS json)

add_library(server ./server/Server.cpp
                   ./server/Session.cpp)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(server ${CONAN_LIBS_BOOST})

add_library(http ./http/Body.cpp
                 ./http/Header.cpp
                 ./http/Context.cpp)
target_include_directories(http PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(app main.cpp)
target_link_libraries(app PUBLIC server  ${CONAN_LIBS_BOOST})

#find_package(Boost COMPONENTS )

add_library(server ./server/Server.cpp
                   ./server/Session.cpp)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(server ${CONAN_LIBS_BOOST})

add_executable(app main.cpp)
target_link_libraries(app PUBLIC server)
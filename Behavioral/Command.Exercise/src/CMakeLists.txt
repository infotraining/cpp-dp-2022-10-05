set(PROJECT_LIB "${PROJECT_ID}_lib")
set(PROJECT_LIB "${PROJECT_ID}_lib" PARENT_SCOPE)
message(STATUS "PROJECT_LIB is: " ${PROJECT_LIB})

project(${PROJECT_LIB} CXX)

file(GLOB SRC_FILES *.cpp *.c *.cxx)
file(GLOB SRC_HEADERS *.h *.hpp *.hxx)

find_package(Boost COMPONENTS serialization REQUIRED)

add_library(${PROJECT_LIB} STATIC ${SRC_FILES} ${SRC_HEADERS})
target_include_directories(${PROJECT_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_LIB} PUBLIC ${Boost_LIBRARIES})
target_compile_features(${PROJECT_LIB} PUBLIC cxx_std_17)
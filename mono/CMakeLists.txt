cmake_minimum_required(VERSION 3.1)

set(project_name apod-mono) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_executable(${project_name}-exe app.cpp)


set(API_DIR ${CMAKE_CURRENT_LIST_DIR}/../apod-api/build)
set(PAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/../apod-page/build)
set(FACADE_DIR ${CMAKE_CURRENT_LIST_DIR}/../apod-facade/build)

FIND_LIBRARY(USER_LIBRARY
        NAMES api-lib
        HINTS ${API_DIR}
)

FIND_LIBRARY(BOOK_LIBRARY
        NAMES book-service-lib
        HINTS ${PAGE_DIR}
)

FIND_LIBRARY(FACADE_LIBRARY
        NAMES facade-lib
        HINTS ${FACADE_DIR}
)

target_include_directories(${project_name}-exe
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../apod-api/src
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../apod-page/src
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../apod-facade/src
)

target_link_libraries(${project_name}-exe
        PUBLIC ${API_DIR}
        PUBLIC ${PAGE_DIR}
        PUBLIC ${FACADE_DIR}
)

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)

## define path to swagger-ui res folder
add_definitions(-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")

target_link_libraries(${project_name}-exe
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)
cmake_minimum_required(VERSION 3.1)

set(project_name apod-page)

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_library(${project_name}-lib
        src/app_component.hpp
        src/swagger_component.hpp
        src/controller/api_controller.hpp
        src/dto/api_dto.hpp
        src/runner.cpp
        src/runner.hpp
)

## include directories

target_include_directories(${project_name}-lib PUBLIC src)


## link libs

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)

## define path to swagger-ui res folder

add_definitions(-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")


## add executables

add_executable(${project_name}-exe src/app.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(project-tests ${project_name}-test)
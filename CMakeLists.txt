cmake_minimum_required(VERSION 3.2)

set(APP_NAME ip_filter)
set(APP_LIB filter)
set(APP_TEST filter_test)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${APP_NAME} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${APP_NAME} VERSION 0.0.1)
endif()

find_package(GTest REQUIRED)

configure_file(config/version.h.in config/version.h)

add_executable(${APP_NAME} ip_filter.cpp)
add_library(${APP_LIB} lib/lib.cpp)
add_executable(${APP_TEST} test/test.cpp)

set_target_properties(${APP_NAME} ${APP_LIB} ${APP_TEST} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${APP_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)

target_include_directories(${APP_LIB}
    PRIVATE
        "${CMAKE_BINARY_DIR}"
)

set_target_properties(${APP_TEST} PROPERTIES
    INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS}"
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)

target_link_libraries(${APP_NAME} PRIVATE
    ${APP_LIB}
)
target_link_libraries(${APP_TEST}
    ${GTEST_BOTH_LIBRARIES}
    pthread
    ${APP_LIB}
)

if (MSVC)
    target_compile_options(${APP_NAME} PRIVATE
        /W4
    )
    target_compile_options(${APP_LIB} PRIVATE
        /W4
    )
    target_compile_options(${APP_TEST} PRIVATE
        /W4
    )
else ()
    target_compile_options(${APP_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${APP_LIB} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${APP_TEST} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ${APP_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT scfocus@yandex.ru)

include(CPack)

enable_testing()

add_test(${APP_TEST} ${APP_TEST})

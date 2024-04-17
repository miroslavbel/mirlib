enable_testing()


add_library(unity
    STATIC
        deps/Unity/src/unity.c
)
set_target_properties(unity PROPERTIES
    PREFIX  "__lib"
)
target_include_directories(unity
    PUBLIC
        deps/Unity/src/
)


add_executable(libmirtestdriver
        src/test.c
        src/testinfo.c
        src/common.c
)
target_include_directories(libmirtestdriver
    PUBLIC
        include/
        ../include
)
target_link_libraries(libmirtestdriver
    unity
    mir
)


include(tests.cmake)

# ------------------------------
# Test Common
# ------------------------------

add_library(brvc_test_common STATIC)

target_sources(brvc_test_common
    PRIVATE
        framework/brvc_test.cpp
)

target_include_directories(brvc_test_common
    PUBLIC
        ${PROJECT_SOURCE_DIR}/test/include/framework
)

target_link_libraries(brvc_test_common
    PUBLIC
        brvc_common
)

# ------------------------------
# ROM
# ------------------------------

add_library(brvc_rom_test STATIC)

target_sources(brvc_rom_test
    PRIVATE
        rom/brvc_rom_test.cpp
)

target_include_directories(brvc_rom_test
    PUBLIC
        ${PROJECT_SOURCE_DIR}/test/include/rom
)

target_link_libraries(brvc_rom_test
    PUBLIC
        brvc_common
        brvc_test_common
        brvc_rom
)

# ------------------------------
# Tests
# ------------------------------

add_executable(brvc_tests
    brvc_test_main.cpp
)

# target_include_directories(brvc_test_common
#     PUBLIC
#         ${PROJECT_SOURCE_DIR}/test/include/framework
# )

target_link_libraries(brvc_tests
    PRIVATE
        brvc_test_common
        brvc_rom_test
)
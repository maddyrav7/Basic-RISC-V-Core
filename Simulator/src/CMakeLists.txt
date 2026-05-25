# ------------------------------
# Common
# ------------------------------

add_library(brvc_common INTERFACE)

target_include_directories(brvc_common
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/arch
        ${PROJECT_SOURCE_DIR}/include/utils
)

# ------------------------------
# ROM
# ------------------------------

add_library(brvc_rom STATIC)

target_sources(brvc_rom
    PRIVATE
        rom/brvc_rom.cpp
)

target_include_directories(brvc_rom
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/rom
)

target_link_libraries(brvc_rom
    PUBLIC
        brvc_common
)

# ------------------------------
# RAM
# ------------------------------

add_library(brvc_ram STATIC)

target_sources(brvc_ram
    PRIVATE
        ram/brvc_ram.cpp
)

target_include_directories(brvc_ram
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/ram
)

target_link_libraries(brvc_ram
    PUBLIC
        brvc_common
)

# ------------------------------
# CPU
# ------------------------------

add_library(brvc_cpu STATIC)

target_sources(brvc_cpu
    PRIVATE
        cpu/brvc_cpu.cpp
)

target_include_directories(brvc_cpu
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/cpu
)

target_link_libraries(brvc_cpu
    PUBLIC
        brvc_common
        brvc_rom
        brvc_ram
)

# ------------------------------
# System
# ------------------------------

add_library(brvc_system STATIC)

target_sources(brvc_system
    PRIVATE
        system/brvc_system.cpp
)

target_include_directories(brvc_system
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/system
)

target_link_libraries(brvc_system
    PUBLIC
        brvc_common
        brvc_rom
        brvc_ram
        brvc_cpu
)

# ------------------------------
# Simulator
# ------------------------------

add_executable(brvc_simulator
    brvc_simulator.cpp
)

target_link_libraries(brvc_simulator
    PRIVATE
        brvc_system
)
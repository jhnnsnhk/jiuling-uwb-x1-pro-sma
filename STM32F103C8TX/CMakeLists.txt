add_executable(${CMAKE_PROJECT_NAME})
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
include(${CMAKE_SOURCE_DIR}/.cmake/stm32.cmake)
include(${CMAKE_SOURCE_DIR}/.cmake/headersandsources.cmake)
target_compile_definitions(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    DEBUG
    STM32F103xB
    USE_FULL_LL_DRIVER
    USE_HAL_DRIVER
)
set(ARM_COMPILER_FLAGS -mcpu=cortex-m3 -mfloat-abi=soft -mthumb)
set(MCU_LINKER_SCRIPT STM32F103C8TX_FLASH.ld)
target_compile_options(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:
    ${ARM_COMPILER_FLAGS}
    $<$<CONFIG:Debug>:-g3;-O0>
    $<$<CONFIG:Release>:-g3;-Ofast>
    -c
    -x assembler-with-cpp
    --specs=nano.specs
    >
    $<$<COMPILE_LANGUAGE:C>:
    ${ARM_COMPILER_FLAGS}
    $<$<CONFIG:Debug>:-g3;-O0>
    $<$<CONFIG:Release>:-g3;-Ofast>
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -fdata-sections
    -ffunction-sections
    -fstack-usage
    -fcyclomatic-complexity
    --specs=nano.specs
    >
)
target_link_options(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    ${ARM_COMPILER_FLAGS}
    -T${CMAKE_CURRENT_SOURCE_DIR}/${MCU_LINKER_SCRIPT}
    --specs=nosys.specs
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--gc-sections
    -static
    --specs=nano.specs
    -Wl,--start-group -lc -lm -Wl,--end-group
    -Wl,--print-memory-usage
)
add_executable(platformchannel_test
    platformchannel_test.c
)

target_link_libraries(
    platformchannel_test
    flutterpi_module
    Unity
)

add_test(platformchannel_test platformchannel_test)

add_executable(flutterpi_test
    flutterpi_test.c
)

target_link_libraries(
    flutterpi_test
    flutterpi_module
    Unity
)

add_test(flutterpi_test flutterpi_test)

# dpms_test includes modesetting.c/window.c to exercise their private state with
# mock DRM ioctls; compile the remaining module sources with the same settings.
get_target_property(dpms_sources flutterpi_module SOURCES)
list(FILTER dpms_sources EXCLUDE REGEX "src/(modesetting|window)\\.c$")
list(TRANSFORM dpms_sources PREPEND "${PROJECT_SOURCE_DIR}/")
add_executable(dpms_test dpms_test.c ${dpms_sources})
target_include_directories(dpms_test PRIVATE $<TARGET_PROPERTY:flutterpi_module,INCLUDE_DIRECTORIES>)
target_compile_options(dpms_test PRIVATE $<TARGET_PROPERTY:flutterpi_module,COMPILE_OPTIONS>)
target_compile_definitions(dpms_test PRIVATE $<TARGET_PROPERTY:flutterpi_module,COMPILE_DEFINITIONS>)
target_link_libraries(dpms_test PRIVATE $<TARGET_PROPERTY:flutterpi_module,LINK_LIBRARIES> Unity)
target_link_options(dpms_test PRIVATE
    $<TARGET_PROPERTY:flutterpi_module,LINK_OPTIONS>
    -Wl,--wrap=drmModeMoveCursor
    -Wl,--wrap=drmAuthMagic
    -Wl,--wrap=drmModeAtomicAddProperty
    -Wl,--wrap=drmModeAtomicCommit
    -Wl,--wrap=drmModeConnectorSetProperty
    -Wl,--wrap=drmHandleEvent
)
add_test(dpms_test dpms_test)

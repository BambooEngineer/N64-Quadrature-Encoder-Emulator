add_executable(n64c
n64c.c
        )

target_link_libraries(n64c pico_stdlib hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(n64c)

pico_enable_stdio_usb(n64c 1)
pico_enable_stdio_uart(n64c 0)

# add url via pico_set_program_url
example_auto_set_url(n64c)
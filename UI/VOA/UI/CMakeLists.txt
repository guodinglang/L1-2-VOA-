SET(SOURCES screens/ui_main00.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    fonts/ui_font_Font128.c
    fonts/ui_font_Font32.c)

add_library(ui ${SOURCES})

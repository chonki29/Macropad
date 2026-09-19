#include QMK_KEYBOARD_H

static uint8_t volume_level = 50;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LGUI(KC_D), LGUI(KC_L), KC_NO,
        KC_MPRV,    KC_MPLY,    KC_MNXT
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);

            if (volume_level < 100)
                volume_level += 2;
        } else {
            tap_code(KC_VOLD);

            if (volume_level > 0)
                volume_level -= 2;
        }
    }

    return false;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    char buf[16];

    oled_write_P(PSTR("Macropad Active\n"), false);

    snprintf(buf, sizeof(buf), "Volume: %d%%\n", volume_level);
    oled_write(buf, false);

    return false;
}
#endif

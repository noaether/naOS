#include "keyboard.h"
#include "keyboard_map.h"

#include <stdbool.h>
#include <stddef.h>

#include <utils/io.h>

#include <naOS/string.h>

#include <utils/log.h>
#include <drivers/framebuffer.h> // since_enter

bool shift_pressed = false; // Global flag to track Shift key state
bool alt_pressed = false;   // Global flag to track Alt key state
bool ctrl_pressed = false;  // Global flag to track Ctrl key state

void kb_init()
{
    // do nothing
}

void handle_key_release(int keycode) {
    char keycode_str[10];
    citoa(keycode, keycode_str, 10);

    char logup[] = "KBD | UP ";
    strcat(logup, keycode_str);
    log(logup, LOG_DEBUG);

    if (keycode == -86 || keycode == -74) {
        shift_pressed = false;
    }
    else if (keycode == -72) {
        alt_pressed = false;
    }
    else if (keycode == -99) {
        ctrl_pressed = false;
    }
}

void handle_key_press(int keycode) {
    char keycode_str[10];
    citoa(keycode, keycode_str, 10);

    char logdown[] = "KBD | DOWN ";
    strcat(logdown, keycode_str);
    log(logdown, LOG_DEBUG);

    if (keycode == 42 || keycode == 54) {
        shift_pressed = true;
    }
    else if (keycode == 56) {
        alt_pressed = true;
    }
    else if (keycode == 58) {
        shift_pressed = !shift_pressed;
    }
    else if (keycode == 29) {
        ctrl_pressed = true;
    }
}

void handle_special_keys(int keycode) {
    char ascii[2];

    if (alt_pressed) {
        ascii[0] = keyboard_map3[keycode];
    }
    else if (shift_pressed) {
        ascii[0] = keyboard_map2[keycode];
    }
    else if (ctrl_pressed) {
        ascii[0] = keyboard_map[keycode];
        ctrlkey_handler(keycode);
        return;
    } else if (keycode == 72 || keycode == 80 || keycode == 75 || keycode == 77) {
        arrow_key_handler(keycode);
        return;
    }
    else {
        ascii[0] = keyboard_map[keycode];
    }

    if (ascii[0] < 0) {
        return;
    }

    ascii[1] = '\0';
    if (ascii[0] == 0) {
        special_key_handler(keycode);
        return;
    }
    log(ascii, LOG_DEBUG);
    fb_print_after(ascii, 1);

    since_enter++;
}

void handle_keyboard_interrupt() {
    ioport_out(0x20, 0x20);

    unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        int keycode = ioport_in(KEYBOARD_DATA_PORT);

        if (keycode < 0) {
            handle_key_release(keycode);
            return;
        }
        else {
            handle_key_press(keycode);
        }

        if (!(keycode & 0x80)) {
            handle_special_keys(keycode);
        }
    }
    else {
        log("KBD | No data", LOG_DEBUG);
    }
}



void special_key_handler(int keycode)
{

    char keycode_str[10];
    citoa(keycode, keycode_str, 10);
    if ((57 - keycode) == 0)
    {

        char ascii[2];
        ascii[0] = ' ';
        ascii[1] = '\0';
        log(ascii, LOG_ERROR);
        fb_print_after(ascii, 1);
    }
    else if ((14 - keycode) == 0)
    {
        fb_backspace();
    }
    else if /* enter key */ ((28 - keycode) == 0)
    {
        char enter[] = "\n";
        fb_write(enter, -1);

        fb_print_after("naOS> ", 6);
    }
    else
    {
        log(keycode_str, LOG_DEBUG);
    }
}

void ctrlkey_handler(int keycode)
{
    if (keycode == 46)
    {
        //play_array();
        fb_write("\n", -1);
        fb_print_after("naOS> ", 6);
    }
}

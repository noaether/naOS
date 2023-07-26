#ifndef __KEYBOARD_MAP_H
#define __KEYBOARD_MAP_H

int keyboard_map[128] = {
    // -------- 0 to 9 --------
    0,
    0, // 1: escape key
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    // -------- 10 to 19 --------
    '9',
    '0',
    '-',
    '=',
    0, // Backspace
    0, // Tab
    'q',
    'w',
    'e',
    'r',
    // -------- 20 to 29 --------
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    0, // Enter
    0, // left Ctrl
    // -------- 30 to 39 --------
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    // -------- 40 to 49 --------
    '{',
    '`',
    -2, // left Shift 42 to -86; should not be interpreted by special characters function
    0,
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    // -------- 50 to 59 --------
    'm',
    ',',
    '.',
    '/', // slash, or numpad slash if preceded by keycode 224
    -2, // right Shift
    '*', // numpad asterisk
    -2, // left Alt
    ' ', // Spacebar
    0,
    0, // F1
    // -------- 60 to 69 --------
    0, // F2
    0, // F3
    0, // F4
    0, // F5
    0, // F6
    0, // F7
    0, // F8
    0, // F9
    0, // F10
    0,
    // -------- 70 to 79 --------
    0, // scroll lock
    '7', // numpad 7, HOME key if preceded by keycode 224
    '8', // numpad 8, up arrow if preceded by keycode 224
    '9', // numpad 9, PAGE UP key if preceded by keycode 224
    '-', // numpad hyphen
    '4', // numpad 4, left arrow if preceded by keycode 224
    '5', // numpad 5
    '6', // numpad 6, right arrow if preceded by keycode 224
    0,
    '1', // numpad 1, END key if preceded by keycode 224
    // -------- 80 to 89 --------
    '2', // numpad 2, down arrow if preceded by keycode 224
    '3', // numpad 3, PAGE DOWN key if preceded by keycode 224
    '0', // numpad 0, INSERT key if preceded by keycode 224
    '.', // numpad dot, DELETE key if preceded by keycode 224
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 90 to 99 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 100 to 109 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 110 to 119 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 120-127 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

int keyboard_map2[128] = {
    // -------- 0 to 9 --------
    0,
    0, // 1: escape key
    '!', // Shift + 1
    '@', // Shift + 2
    '#', // Shift + 3
    '$', // Shift + 4
    '%', // Shift + 5
    '^', // Shift + 6
    '&', // Shift + 7
    '*', // Shift + 8
    // -------- 10 to 19 --------
    '(', // Shift + 9
    ')', // Shift + 0
    '_', // Shift + Minus
    '+', // Shift + Equals
    0, // Backspace
    0, // Tab
    'Q', // Shift + q
    'W', // Shift + w
    'E', // Shift + e
    'R', // Shift + r
    // -------- 20 to 29 --------
    'T', // Shift + t
    'Y', // Shift + y
    'U', // Shift + u
    'I', // Shift + i
    'O', // Shift + o
    'P', // Shift + p
    '{', // Shift + Left square bracket
    '}', // Shift + Right square bracket
    0, // Enter
    0, // left Ctrl
    // -------- 30 to 39 --------
    'A', // Shift + a
    'S', // Shift + s
    'D', // Shift + d
    'F', // Shift + f
    'G', // Shift + g
    'H', // Shift + h
    'J', // Shift + j
    'K', // Shift + k
    'L', // Shift + l
    ':', // Shift + Semicolon
    // -------- 40 to 49 --------
    '"', // Shift + Apostrophe
    '~', // Shift + Backtick
    -2, // left Shift
    0, // Backslash (Depends on the keyboard)
    'Z', // Shift + z
    'X', // Shift + x
    'C', // Shift + c
    'V', // Shift + v
    'B', // Shift + b
    'N', // Shift + n
    // -------- 50 to 59 --------
    'M', // Shift + m
    '\'', // Shift + Comma
    '"', // Shift + Period
    '?', // Shift + Forward slash
    -2, // right Shift
    '*', // numpad asterisk
    -2, // left Alt
    ' ', // Spacebar
    0,
    0, // F1
    // -------- 60 to 69 --------
    0, // F2
    0, // F3
    0, // F4
    0, // F5
    0, // F6
    0, // F7
    0, // F8
    0, // F9
    0, // F10
    0,
    // -------- 70 to 79 --------
    0, // scroll lock
    '7', // numpad 7, HOME key if preceded by keycode 224
    '8', // numpad 8, up arrow if preceded by keycode 224
    '9', // numpad 9, PAGE UP key if preceded by keycode 224
    '-', // numpad hyphen
    '4', // numpad 4, left arrow if preceded by keycode 224
    '5', // numpad 5
    '6', // numpad 6, right arrow if preceded by keycode 224
    0,
    '1', // numpad 1, END key if preceded by keycode 224
    // -------- 80 to 89 --------
    '2', // numpad 2, down arrow if preceded by keycode 224
    '3', // numpad 3, PAGE DOWN key if preceded by keycode 224
    '0', // numpad 0, INSERT key if preceded by keycode 224
    '.', // numpad dot, DELETE key if preceded by keycode 224
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 90 to 99 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 100 to 109 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 110 to 119 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 120-127 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

int keyboard_map3[128] = { // -1 indicate multicharacter constants, will work on this later
    // -------- 0 to 9 --------
    0,
    0, // 1: escape key
    '|', // left alt + 1
    '@', // left alt + 2
    '#', // left alt + 3
    '$', // left alt + 4
    -1, // left alt + 5
    '{', // left alt + 6
    '[', // left alt + 7
    ']', // left alt + 8
    // -------- 10 to 19 --------
    '}', // left alt + 9
    -1, // left alt + 0
    '-', // left alt + Minus
    '+', // left alt + Equals
    0, // Backspace
    0, // Tab
    -1, // left alt + q
    -1, // left alt + w
    -1, // left alt + e
    -1, // left alt + r
    // -------- 20 to 29 --------
    -1, // left alt + t
    -1, // left alt + y
    -1, // left alt + u
    -1, // left alt + i
    -1, // left alt + o
    -1, // left alt + p
    ';', // left alt + Left square bracket
    ':', // left alt + Right square bracket
    0, // Enter
    0, // left Ctrl
    // -------- 30 to 39 --------
    -1, // left alt + a
    -1, // left alt + s
    -1, // left alt + d
    -1, // left alt + f
    -1, // left alt + g
    -1, // left alt + h
    -1, // left alt + j
    -1, // left alt + k
    -1, // left alt + l
    '#', // left alt + Semicolon
    // -------- 40 to 49 --------
    '{', // left alt + Apostrophe
    '`', // left alt + Backtick
    -2, // left Shift
    0, // Backslash (Depends on the keyboard)
    -1, // left alt + z
    -1, // left alt + x
    -1, // left alt + c
    -1, // left alt + v
    -1, // left alt + b
    -1, // left alt + n
    // -------- 50 to 59 --------
    -1, // left alt + m
    -1, // left alt + Comma
    -1, // left alt + Period
    -1, // left alt + Forward slash
    -2, // right Shift
    '*', // numpad asterisk
    -2, // left Alt
    0, // Spacebar
    0,
    0, // F1
    // -------- 60 to 69 --------
    0, // F2
    0, // F3
    0, // F4
    0, // F5
    0, // F6
    0, // F7
    0, // F8
    0, // F9
    0, // F10
    0,
    // -------- 70 to 79 --------
    0, // scroll lock
    '7', // numpad 7, HOME key if preceded by keycode 224
    '8', // numpad 8, up arrow if preceded by keycode 224
    '9', // numpad 9, PAGE UP key if preceded by keycode 224
    '-', // numpad hyphen
    '4', // numpad 4, left arrow if preceded by keycode 224
    '5', // numpad 5
    '6', // numpad 6, right arrow if preceded by keycode 224
    0,
    '1', // numpad 1, END key if preceded by keycode 224
    // -------- 80 to 89 --------
    '2', // numpad 2, down arrow if preceded by keycode 224
    '3', // numpad 3, PAGE DOWN key if preceded by keycode 224
    '0', // numpad 0, INSERT key if preceded by keycode 224
    '.', // numpad dot, DELETE key if preceded by keycode 224
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 90 to 99 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 100 to 109 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 110 to 119 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // -------- 120-127 --------
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

#endif
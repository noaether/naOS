#ifndef STRUCTS_H
#define STRUCTS_H

struct logConfigStruct {
    unsigned char level; // debug 0, info 1, warning 2, error 3
    unsigned char output; // serial 0, framebuffer 1
}__attribute__((packed));

#endif  // STRUCTS_H

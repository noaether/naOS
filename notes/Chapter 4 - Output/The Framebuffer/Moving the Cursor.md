- done via two different i/o ports
	- 0x3D4 describes data, 0x3D5 is for data
- position determined with a 16 bits integer (counting the cells from 0, left to right, top to bottom)
	- since `out` assembly code is only 8 bits, information is sent in two turns

- to set cursor at row 1, column 0 (position 80 = 0x0050)
```
    out 0x3D4, 14      ; 14 tells the framebuffer to expect the highest 8 bits of the position
    out 0x3D5, 0x00    ; sending the highest 8 bits of 0x0050
    out 0x3D4, 15      ; 15 tells the framebuffer to expect the lowest 8 bits of the position
    out 0x3D5, 0x50    ; sending the lowest 8 bits of 0x0050
```

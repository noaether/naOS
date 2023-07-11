- writing is done with [[Interacting with the Hardware#^e3e39e|memory mapped]] i/o ports
	- starting address for framebuffer is 0x000B8000
	- memory is divided into 16bit cells, where each of the bits determine character (8 bit ASCII), foreground colour, background colour, blink (Nk) following these [[Configuration Bytes]]
```
Bit:     | 15 | 14 13 12 | 11 10 9 8 | 7 6 5 4 3 2 1 0 |
Content: | Nk | BG       | FG        | ASCII           |
```

| Color        | Value | Color         | Value | Color        | Value | Color           | Value |
|--------------|-------|---------------|-------|--------------|-------|-----------------|-------|
| Black        | 0     | Red           | 4     | Dark grey    | 8     | Light red       | 12    |
| Blue         | 1     | Magenta       | 5     | Light blue   | 9     | Light magenta   | 13    |
| Green        | 2     | Brown         | 6     | Light green  | 10    | Light brown     | 14    |
| Cyan         | 3     | Light grey    | 7     | Light cyan   | 11    | White           | 15    |

^739c43
**THESE ARE IN DECIMAL AND NEED TO BE CONVERTED TO HEX**
- first cell is (0;0), A in ASCII = 65, green foreground = 2, red background = 4
	- `mov word [0x000B8000], 0x4241` will therefore print a green A on a red background
- second cell is (0;1), address is therefore `0x000B8000` + 2 = `0x000B8002`

- writing to framebuffer can (and probably should) be done with [[Chapter 3 - Getting to C|C]] by treating the address `0x000B8000` as a char pointer
```C
char *fb = (char *) 0x000B8000 /* declare char pointer */
fb[0] = 'A' /* push A */
fb[1] = 0x82 /* push colour info */
/* since fb is mem-mapped, will update automatically */
```
- this process can be wrapped into this function 
```C
    /** fb_write_cell:
     *  Writes a character with the given foreground and background to position i
     *  in the framebuffer.
     *
     *  @param i  The location in the framebuffer
     *  @param c  The character
     *  @param fg The foreground color
     *  @param bg The background color
     */
	void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
	{
		fb[i] = c;
		fb[i + 1] = ((bg & 0x0F) << 4 | (fg & 0x0F));
	}
```

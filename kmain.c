/* colors */
#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_LIGHT_BLUE 9
#define FB_LIGHT_GREEN 10
#define FB_LIGHT_CYAN 11
#define FB_LIGHT_RED 12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN 14
#define FB_WHITE 15

/* framebuffer mm io */
char *fb = (char *)0x000B8000;

/**
 * display character c on the position i with color fg and bg.
 *
 * @param i the position, 0 for the first line, first col. 16 for the second line.
 * @param c the displayed character
 * @param fg foreground color
 * @param bg background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
  fb[i] = c;
  fb[i + 1] = ((bg & 0x0F) << 4 | (fg & 0x0F));
}

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
  return arg1 + arg2 + arg3;
}

int main()
{
  /* char array */
  char hello[] = "Hello Noa";

  /* print hello */
  int i = 0;
  while (hello[i] != '\0')
  {
    fb_write_cell(i * 2, hello[i], FB_WHITE, FB_BLACK);
    i++;
  }
}

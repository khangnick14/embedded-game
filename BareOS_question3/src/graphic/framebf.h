// ----------------------------------- framebf.h -------------------------------------

#define VIRTUAL_SCREEN_WIDTH 1024
#define VIRTUAL_SCREEN_HEIGHT 768
#define SIZE_64 64
#define SIZE_24 24

void framebf_init();
void drawPixelARGB32(int x, int y, unsigned int attr);
void clearScreen();
void drawBackground();
void erease64x64(int x, int y);
void erease24x24(int x, int y);
void eraseBySize(int x, int y, int width, int height);
void drawline();

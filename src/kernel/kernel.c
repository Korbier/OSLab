#define VIDEO_MEMORY_ADDR 0xB8000

void _start(void) {

  unsigned char * vram = ( unsigned char * ) VIDEO_MEMORY_ADDR;// + ( y * 80 + x );

  *(vram++) = 'H';
  *(vram++) = 0x57;
  *(vram++) = 'E';
  *(vram++) = 0x0A;
  *(vram++) = 'L';
  *(vram++) = 0x4E;
  *(vram++) = 'L';
  *(vram++) = 0x62;
  *(vram++) = 'O';
  *(vram++) = 0x0E;

  while(1);

}

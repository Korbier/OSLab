#define RAMSCREEN 0xB8000       /* début de la mémoire vidéo */

void _start(void) {

  char * video_memory = ( char * ) RAMSCREEN;
  * video_memory = 'X';

  while(1);

}

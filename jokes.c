#include "jokes.h"
#include "malloc.h"

void *oc(size_t size) {

  int i,j;
  char meme[HEIGHT][WIDTH] = {
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▄▄▄░░░░░",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░███▀█░░░░",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░███░██░░░",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░███░░██░░░",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░▄██░░░░██░░",
"░░░░░░░░░░░░░░░░▄▄█▀▀▀▀█▄▄▄▄███▄░░░██░░",
"░░░░░░░░░░░░░▄█▀░░░░░░░░░▀▀▀▀█░▀█░░██░░",
"░░░░░░░░░░░░█▀░░░░░░░░░░░░░░░▀█▄█▀▀▀░░░",
"░░░░░░░░░░░▄▀░░░░░░░░░░░░░░░░▀█▄░░░░░░░",
"░░░░░░░░░░░▀█▄░█░░▄▀░░░░░░░▄▄█░░░░░░░░░",
"░░░░░░░░▄▄▄▄█▀▀▀██▄▄░░░░░░▄▀░░░░░░░░░░░",
"░░░░▄▄██▄▀▀░░░░░█▀░░░░░░▄██▄░░░░░░░░░░░",
"░░▄██▀▀░░░░░░░░▄█░░░░░▄█▀▄█░▀▀█▄▄▄▄▄▄▄▄",
"░██▀░░░░░░░░▄██░░░░░░▄▀▄▄▀░░░░░░░░░░░░░",
"█▀▀░░░░░░▄█▀▄░▀▄▄▄▄██▀▀▀░░░░░█░░░░░░░░░",
"█░░░░░▄▄▀░░░░█░░░░░░░░░░░░░░░▀░░░░░░░░░",
"░▀▀▀▀▀▀░░░░░░░█░░░░░░░░░░░░░░░▀▀█▀▀▀▀▀▀",
"░░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░█▀░░░░░░",
"░░░░░░░░░░░░░░█░░░░░░░░░░░░░░░▄█░░░░░░░"
  };

  for ( i=0; i < HEIGHT; i++ ) {
    for ( j=0; j < WIDTH; j++ ) {
      printf("%c",meme[i][j]);
    }
    printf("\n");
  }

}
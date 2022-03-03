#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

char **LoadMapFromFile(char *mapName, size_t *width, size_t *height) {
  char *mapsPath = "./assets/maps/";
  char *filePath = malloc(strlen(mapsPath) + strlen(mapName) + 1);
  assert(filePath != NULL);
  strcpy(filePath, mapsPath);
  strcat(filePath, mapName);
  char *lineBuf = NULL;
  size_t lineBufSize = 0;
  size_t lineCount = 0;
  int lineSize;

  char **map = malloc(sizeof(char *) * 1);
  assert(map != NULL);

  FILE *fp = fopen(filePath, "r");
  if (!fp) {
    fprintf(stderr, "Error opening file '%s'\n", filePath);
    return NULL;
  }
  lineSize = getline(&lineBuf, &lineBufSize, fp);
  *width = lineSize;
  while (lineSize >= 0) {
    // printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s",
    // lineCount,
    //        lineSize, lineBufSize, lineBuf);
    assert((size_t)lineSize == *width);
    *width = lineSize;
    char *newline = malloc(lineSize);
    assert(newline != NULL);
    memcpy(newline, lineBuf, lineSize - 1);

    map = realloc(map, sizeof(char *) * (lineCount + 1));
    assert(map != NULL);
    map[lineCount] = newline;
    lineCount++;

    lineSize = getline(&lineBuf, &lineBufSize, fp);
  }
  *height = lineCount;
  free(lineBuf);
  free(filePath);
  fclose(fp);
  printf("[+] - Successfully Loaded map file %s\n", mapName);
  return map;
}

char **CreateRandomMap(int size, int seed) {
  srand(seed);
  char **map = malloc(size * sizeof(char *));
  assert(map != NULL);
  for (int i = 0; i < size; ++i) {
    map[i] = malloc(size * sizeof(char));
    assert(map[i] != NULL);
    memset(map[i], ' ', size * sizeof(char));
  }

  for (int y = 0; y < size; ++y) {
    for (int x = 0; x < size; ++x) {
      if (x == 0 || y == 0 || x == size - 1 || y == size - 1) {
        map[x][y] = 'W';
      } else {
        map[x][y] = (rand() % 15 == 4 ? 65 + rand() % 25 : ' ');
      }
    }
  }
  return map;
}

void printMap(char **map, size_t height) {
  for (size_t y = 0; y < height; y++)
    printf("%d/%d = %s\n", y, height, map[y]);
}

void freeMap(char **map, size_t height) {
  for (size_t y = 0; y < height; y++)
    free(map[y]);
  free(map);
}

size_t max(size_t a, size_t b) {
  if (a >= b)
    return a;
  return b;
}

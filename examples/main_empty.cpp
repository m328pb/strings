#include "strings.h"

int main() {
  char p[1];
  str_find(p,p);
  str_find(p,p,0);
  str_cut(p,p,0,0);
  str_set(p,0,p[0]);
  mem_set((uint8_t *)p,0,p[0]);
  mem_set((uint16_t *)p,0,(uint16_t)p);
  str_len(p);
  str_compare(p,p);
  str_add(p,0,p);
  str_copy(p,0,p);
  mem_copy((uint8_t *)p, 0, (const uint8_t *)p);
  ftos(0, p, 0, 0);
  stoi(p);
  btos(0, p);
  str_concat(p, 5, "");
}

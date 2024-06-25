#include "cpu.h"
#include "art.h"

int main(void) {
  CPU cpu;
  cpu.flags.S = 1;

  int8_t a = 10;
  int8_t b = 20;
  int8_t result = overflow_detected(a,b);
  printf("%d\n", result);

  


}

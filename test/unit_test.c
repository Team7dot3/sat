#include "units.h"

int main(int argc, char *argv[]) {
  LOG("Let's run some unit tests...", 2);

  test_check_args();
  test_input_parser();
  test_solver();

  LOG("Testing complete.", 2);
  return 0;
}

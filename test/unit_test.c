#include "units.h"

int main(int argc, char *argv[]) {
  int fails = 0;

  LOG("\nRUNNING UNIT TESTS...\n", 2);

  fails += test_check_args();
  fails += test_input_parser();
  fails += test_solver();

  if (fails) {
    printf(KRED "%s%d tests FAILED! %s", DELIM, fails, DELIM);
  } else {
    printf(KGRN "%sAll tests PASSED! %s" RESET, DELIM, DELIM);
  }

  LOG("\nTESTING COMPLETE.\n", 2);
  return 0;
}

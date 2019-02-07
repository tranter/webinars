#include <iostream>
#include "hello.h"
#include "config.h"
#include "mysqrt.h"

int main()
{
  std::cout << "Demo2 version " << Demo2_VERSION_MAJOR << "." << Demo2_VERSION_MINOR << std::endl;

  hello();

  for (double n = 1; n <= 10; n++) {
      std::cout << "mysqrt(" << n << ") = " << mysqrt(n) << std::endl;
  }

  return 0;
}

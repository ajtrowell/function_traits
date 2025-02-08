// #include <iostream>
// #include <type_traits>

#include "glaze/glaze.hpp"
#include "ruak/param_pack.hpp"
#include "ruak/utilities.hpp"

int main()
{
   using namespace ruak;

   test_packs();

   test_function_traits();
}

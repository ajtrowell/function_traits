#include <iostream>

#include "ruak/param_pack.hpp"
#include "ruak/utilities.hpp"

// Test function for function_traits
double foo(int, float) { return 0.0; }

int main()
{
   using namespace ruak;
   print("Test");
   print(1);
   print(3.14);
   ruak::hello();
   std::cout << "The sum is: " << add(1, 2, 3) << "\n";

   using foo_traits = ruak::function_traits<decltype(&foo)>;
   static_assert(foo_traits::arity == 2, "foo should have 2 parameters");
   std::cout << "Foo arity is : " << foo_traits::arity << "\n";
}

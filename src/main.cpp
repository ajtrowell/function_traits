#include <iostream>

#include "ruak/param_pack.hpp"

template <typename T>
void print(const T& t)
{
   std::cout << t << '\n';
}

int main()
{
   print("Test");
   print(1);
   print(3.14);
   ruak::hello();
   std::cout << "The sum is: " << ruak::add(1, 2, 3) << "\n";
}

#include <iostream>

template<typename T>
void print(const T& t)
{
  std::cout << t << '\n';
}

int main()
{
  print("Test");
  print(1);
  print(3.14);
}

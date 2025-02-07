#include <iostream>
#include <type_traits>

// #include "glaze/glaze.hpp"
#include "ruak/param_pack.hpp"
#include "ruak/utilities.hpp"

// Test function for function_traits
double foo(int, float) { return 0.0; }
void bar(int, float) {}

struct fubar
{
   void operator()(int, double, double) {}
};

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
   static_assert(std::is_same_v<double, foo_traits::return_type>, "Foo return type should be double");
   static_assert(std::is_same_v<int, foo_traits::argument<0>>, "Foo arg 0 should be int");

   using bar_traits = ruak::function_traits<decltype(&bar)>;
   static_assert(std::is_same_v<bar_traits::return_type, void>, "bar should return void but failed to.\n");

   using fubar_trait = function_traits<fubar>;
   // using weird_trait = function_traits<decltype(&fubar::operator())>;
   static_assert(fubar_trait::arity == 3, "3 arguments in fubar functor.\n");

   std::function<float()> myLambda = []() { return 3.14; };
   using lambda_trait = function_traits<decltype(myLambda)>;
   static_assert(lambda_trait::arity == 0, "0 arguments in myLambda\n");
   static_assert(std::is_same_v<lambda_trait::return_type, float>, "myLambda should return float but failed to.\n");
}

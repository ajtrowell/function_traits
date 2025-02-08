#pragma once

#include <cstddef>
#include <functional>
#include <iostream> // TODO: Remove from this header. (Move to test)
#include <tuple>

namespace ruak
{

   // Primary function_traits template.
   template <typename T>
   struct function_traits : public function_traits<decltype(&T::operator())>
   {};

   // Specialization for function pointers.
   template <typename R, typename... Args>
   struct function_traits<R (*)(Args...)>
   {
      using return_type = R;
      static constexpr std::size_t arity = sizeof...(Args);
      using args_tuple = std::tuple<Args...>;

      template <std::size_t N>
      using argument = typename std::tuple_element<N, std::tuple<Args...>>::type;
   };

   // Specialization for function references.
   template <typename R, typename... Args>
   struct function_traits<R (&)(Args...)>
   {
      using return_type = R;
      static constexpr std::size_t arity = sizeof...(Args);
      using args_tuple = std::tuple<Args...>;

      template <std::size_t N>
      using argument = typename std::tuple_element<N, std::tuple<Args...>>::type;
   };

   // Specialization for non-const member function pointers.
   template <typename R, typename T, typename... Args>
   struct function_traits<R (T::*)(Args...)>
   {
      using return_type = R;
      static constexpr std::size_t arity = sizeof...(Args);
      using args_tuple = std::tuple<Args...>;

      template <std::size_t N>
      using argument = typename std::tuple_element<N, std::tuple<Args...>>::type;
   };

   // Specialization for const member function pointers.
   template <typename R, typename T, typename... Args>
   struct function_traits<R (T::*)(Args...) const>
   {
      using return_type = R;
      static constexpr std::size_t arity = sizeof...(Args);
      using args_tuple = std::tuple<Args...>;

      template <std::size_t N>
      using argument = typename std::tuple_element<N, std::tuple<Args...>>::type;
   };

   // Specialization for std::function
   template <typename R, typename... Args>
   struct function_traits<std::function<R(Args...)>>
   {
      using return_type = R;
      static constexpr std::size_t arity = sizeof...(Args);
      using args_tuple = std::tuple<Args...>;

      template <std::size_t N>
      using argument = typename std::tuple_element<N, std::tuple<Args...>>::type;
   };

   // Test function for function_traits
   inline double foo(int, float) { return 0.0; }
   inline void bar(int, float) {}

   struct fubar
   {
      void operator()(int, double, double) {}
   };

   struct fubar_const
   {
      void operator()(int, double, double) const {}
   };

   inline void test_function_traits()
   {
      using foo_traits = ruak::function_traits<decltype(&foo)>;
      static_assert(foo_traits::arity == 2, "foo should have 2 parameters");
      std::cout << "Foo arity is : " << foo_traits::arity << "\n";
      static_assert(std::is_same_v<double, foo_traits::return_type>, "Foo return type should be double");
      static_assert(std::is_same_v<int, foo_traits::argument<0>>, "Foo arg 0 should be int");

      using bar_traits = ruak::function_traits<decltype(&bar)>;
      static_assert(std::is_same_v<bar_traits::return_type, void>, "bar should return void but failed to.\n");

      // Test for non-const member function pointer (functor)
      using fubar_const_trait = function_traits<fubar_const>;
      // using weird_trait = function_traits<decltype(&fubar::operator())>;
      static_assert(fubar_const_trait::arity == 3, "3 arguments in fubar functor.\n");

      // Test for const member function pointer (functor)
      using fubar_trait = function_traits<fubar>;
      // using weird_trait = function_traits<decltype(&fubar::operator())>;
      static_assert(fubar_trait::arity == 3, "3 arguments in fubar functor.\n");

      std::function<float()> myLambda = []() { return 3.14; };
      using lambda_trait = function_traits<decltype(myLambda)>;
      static_assert(lambda_trait::arity == 0, "0 arguments in myLambda\n");
      static_assert(std::is_same_v<lambda_trait::return_type, float>, "myLambda should return float but failed to.\n");

      // Test with function reference
      auto& foo_ref = foo;
      using foo_ref_traits = function_traits<decltype(foo_ref)>;
      static_assert(foo_ref_traits::arity == 2, "foo should have 2 parameters");
      static_assert(std::is_same_v<double, foo_ref_traits::return_type>, "Foo return type should be double");
      static_assert(std::is_same_v<int, foo_ref_traits::argument<0>>, "Foo arg 0 should be int");
   }

}

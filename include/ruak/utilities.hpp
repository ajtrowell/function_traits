#pragma once

#include <cstddef>
#include <functional>
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

   // Specialization for member function pointers.
   template <typename R, typename T, typename... Args>
   struct function_traits<R (T::*)(Args...)>
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

}

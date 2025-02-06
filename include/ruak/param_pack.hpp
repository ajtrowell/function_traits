#pragma once

#include <iostream>

namespace ruak
{

   inline void hello() { std::cout << "Hello world. This is a test.\n"; }

   template <class... T>
   auto add(T... args)
   {
      return (args + ...);
   }

}

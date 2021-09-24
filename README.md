# exec_time
A simple C++ header for prints function execution time with RAII, macros and chrono

## Usage

```C++
#include <exec_time>

int main()
{
  auto et = exec_time_ms;
  std::cout << "exec_time_example" << std::endl;
  exec_time_elapsed(et);  // main from line 11 to 13 executed in 80.765 ms
  return 0;
} // main from line 11 to end executed in 90.036 ms
```
### Macros for construct exec_time_impl object
```C++
  exec_time_ns;
  exec_time_us;
  exec_time_ms;
  exec_time_s;
  exec_time_m;
  exec_time_h;
```

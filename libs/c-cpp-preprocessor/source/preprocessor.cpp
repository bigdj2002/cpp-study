#include "preprocessor.h"

static void predefined_macros()
{
  printf("%s\n", __FUNCTION__);
  printf("%s\n", __FILE__);
  printf("%d\n", __LINE__);
  printf("%d\n", __STDC__);
  printf("%d\n", __STDC_HOSTED__);
  // printf("%d\t", __STDC_NO_ATOMICS__);
  // printf("%d\t", __STDC_NO_COMPLEX__);
  // printf("%d\n", __STDC_NO_THREADS__ );
  // printf("%d\n", __STDC_NO_VLA__  );
  // printf("%d\n", __STDC_VERSION__  );
  // printf("%d\n", __STDCPP_DEFAULT_NEW_ALIGNMENT__);
  // printf("%d\n", __STDCPP_THREADS__);
  printf("%s\n", __TIME__);
}

static int sum(int num_args, ...)
{
  va_list ap;
  va_start(ap, num_args); // #define va_start(ap, v) (ap) = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v)
  int arg = 0, result = 0;
  for (int i = 0; i < num_args; i++)
  {
    arg = va_arg(ap, int); // #define va_arg(ap, t) (*(t*))((ap ++ _INTSIZEOF(t)) - _INTSIZEOF(T))
    result += arg;
  }
  va_end(ap); // #define va_end(ap) ap = (va_list)0
  return result;
}

static double avg(double value, ...)
{
  double sum = 0;
  int num = 0;
  va_list ap;
  va_start(ap, value);
  while (value <= __DBL_MAX__ && value >= __DBL_MIN__)
  {
    sum += value;
    num++;
    value = va_arg(ap, double);
  }
  va_end(ap);
  return (sum / num);
}

static void printlog1_(const char* filename, const char* funcname, const int linenum, const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  std::cout << "FILENAME: " << filename << " FUNCNAME: " << funcname << " LINENUM: " << linenum << std::endl;
  vprintf(fmt, ap);
  va_end(ap);
}

static void printlog2_(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
}

int preprocessor_example()
{
  /**
   * \brief: Variadic(variable + -adic) macros
   */
  CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");
  CHECK1(1, "here %s %s %s", "are", "some", "varargs1(2)\n"); // won't print
  CHECK2(0, "here %s %s %s", "are", "some", "varargs2(3)\n"); // won't print
  CHECK2(1, "here %s %s %s", "are", "some", "varargs2(4)\n");
  CHECK3("here %s %s %s", "are", "some", "varargs3(5)\n"); // always invokes printf in the macro
  std::cout << std::endl;

  int arr0[] = {0, 1, 2, 3, 4};
  double arr1[] = {2.3, 122, 30.12, 32.444, 0.23};
  std::cout << sum(5, arr0[0], arr0[1], arr0[2], arr0[3], arr0[4]) << std::endl;
  std::cout << avg(arr1[0], arr1[1], arr1[2], arr1[3], arr1[4]) << std::endl;
  std::cout << std::endl;

  int num = 3;
  printlog1("num: %d\n", num);
  printlog2("FILENAME: %s FUNCNAME: %s LINENUM: %d\nnum: %d\n", __FILE__, __FUNCTION__, __LINE__, num);
  std::cout << std::endl;

  /**
   * \brief: Predefined macros
   */
  predefined_macros();
  std::cout << std::endl;

  return 0;
}
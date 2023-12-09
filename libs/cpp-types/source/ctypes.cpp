#include "ctypes.h"

typename std::enable_if<!std::numeric_limits<float>::is_integer, bool>::type
almost_equal(float x, float y, int ulp)
{
  // the machine epsilon has to be scaled to the magnitude of the values used
  // and multiplied by the desired precision in ULPs (units in the last place)
  return std::fabs(x - y) <= std::numeric_limits<float>::epsilon() * std::fabs(x + y) * ulp
         // unless the result is subnormal
         || std::fabs(x - y) < std::numeric_limits<float>::min();
}

// answer, prefer enum class
std::pair<int, int> divide1(int a, int b)
{
  if (b == 0)
    return std::make_pair<int, int>(0, -1);
  return std::make_pair<int, int>(a / b, 0);
}

std::optional<int> divide2(int a, int b)
{
  if (b == 0)
    return std::nullopt;
  return a / b;
}

std::tuple<double, char, std::string> get_student(int id)
{
  switch (id)
  {
  case 0:
    return std::make_tuple(3.8, 'A', "Lisa Simpson");
  case 1:
    return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
  case 2:
    return std::make_tuple(1.7, 'D', "Ralph Wiggum");
  case 3:
    return std::make_tuple(0.6, 'F', "Bart Simpson");
  }

  throw std::invalid_argument("id");
}

enum class clothing_size
{
  small,
  medium,
  large
};
enum class clothing_color
{
  red,
  blue,
  yellow
};

clothing_size &operator++(clothing_size &s)
{
  if (s == clothing_size::large)
    return s;
  s = static_cast<clothing_size>(static_cast<int>(s) + 1);
  return s;
}

void buyShirt(clothing_color color, clothing_size size)
{
  ++size;

  if (size == clothing_size::small)
    std::cout << "New size: small" << std::endl;
  else if (size == clothing_size::medium)
    std::cout << "New size: medium" << std::endl;
  else if (size == clothing_size::large)
    std::cout << "New size: large" << std::endl;
}

bool is_negative(float x, int method)
{
  if (method == 0)
  {
    union
    {
      unsigned int ui;
      float d;
    } my_union;
    my_union.d = x;
    return my_union.ui & 0x80000000; // Undefined behavior
  }
  else if (method == 1)
  {
    // Object representation
    // pointer type punning is only allowed → unsigned char *, char *, std::byte *
    unsigned int *ui = reinterpret_cast<unsigned int *>(&x); // Undefined behavior
    return *ui & 0x80000000;
  }
  else if (method == 2)
  {
    unsigned int tmp;
    std::memcpy(&tmp, &x, sizeof(x)); // Might not be done memcpy process depend on compiler
    return tmp & 0x80000000;
  }
  else if (method == 3)
  {
    // Since c++20, refer to std::bit_cast
    // return std::bit_cast<uint32_t>(x) & 0x80000000;
  }

  return false;
}

void types_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] Floating number
   */

  const float num1 = 0.3f; // ≒ 0.300000011920928955078125
  const float num2 = 0.4f; // ≒ 0.4000000059604644775390625
  const float num3 = 0.7f; // ≒ 0.699999988079071044921875
  const float sum = num1 + num2;

  if (sum == num3)
    std::cout << "sum is 0.7f" << std::endl;
  else
    std::cout << "sum is not 0.7f" << std::endl;

  std::cout << std::setprecision(100) << num1 << std::endl;
  std::cout << std::setprecision(100) << num2 << std::endl;
  std::cout << std::setprecision(100) << num3 << std::endl;
  std::cout << std::setprecision(100) << sum << std::endl;

  std::cout << "------------------------------------- [↑ Example 1-1 ↑] -------------------------------------" << std::endl;

  if (almost_equal(sum, num3, 1))
    std::cout << "sum is 0.7f" << std::endl;
  else
    std::cout << "sum is not 0.7f" << std::endl;

  std::cout << "------------------------------------- [↑ Example 1-2 ↑] -------------------------------------" << std::endl;

  float num = 10000000000;
  for (std::size_t count = 0; count < 10000000; count++)
  {
    num += 1.0;
  }
  // Expected 10010000000, But..
  std::cout << std::setprecision(100) << num << std::endl;

  std::cout << "------------------------------------- [↑ Example 1-3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] pair, tuple
   *    - tuple: It is a generalization of std::pair
   */

  /** \example: #1 */

  std::pair<int, std::string> numStr{1, "dongjae"};
  std::cout << numStr.first << std::endl;
  std::cout << numStr.second << std::endl;

  std::pair<int, int> answer1 = divide1(10, 0);
  if (answer1.second != 0)
  {
    std::cout << "No answer" << std::endl;
  }

  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  /** \example: #2 std::tuple in cppreference.com */

  const auto student0 = get_student(0);
  std::cout << "ID: 0, "
            << "GPA: " << std::fixed << std::setprecision(1) << std::get<0>(student0) << ", "
            << "grade: " << std::get<1>(student0) << ", "
            << "name: " << std::get<2>(student0) << '\n';

  const auto student1 = get_student(1);
  std::cout << "ID: 1, "
            << "GPA: " << std::fixed << std::setprecision(1) << std::get<double>(student1) << ", "
            << "grade: " << std::get<char>(student1) << ", "
            << "name: " << std::get<std::string>(student1) << '\n';

  double gpa2;
  char grade2;
  std::string name2;
  std::tie(gpa2, grade2, name2) = get_student(2);
  std::cout << "ID: 2, "
            << "GPA: " << std::fixed << std::setprecision(1) << gpa2 << ", "
            << "grade: " << grade2 << ", "
            << "name: " << name2 << '\n';

  // C++17 structured binding:
  const auto [gpa3, grade3, name3] = get_student(3);
  std::cout << "ID: 3, "
            << "GPA: " << std::fixed << std::setprecision(1) << gpa3 << ", "
            << "grade: " << grade3 << ", "
            << "name: " << name3 << '\n';

  auto student2 = get_student(3);
  std::cout << "ID: 3, "
            << "GPA: " << std::fixed << std::setprecision(1) << std::get<double>(student2) << ", "
            << "grade: " << std::get<char>(student2) << ", "
            << "name: " << std::get<std::string>(student2) << '\n';

  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] std::optional
   *    - Good alternative for pair
   */

  const auto answer2 = divide2(10, 0);
  if (answer2)
  {
    std::cout << answer2.value() << std::endl;
  }
  else
  {
    std::cout << answer2.value_or(0) << std::endl;
  }

  std::optional<catType> kitty1{catType()}; // Tmp cat -> std::move (Very unefficient)
  std::optional<catType> kitty2{std::in_place};
  if (!kitty1)
    std::cout << "No cat yet" << std::endl;
  else
    kitty1->print();

  if (!kitty2)
    std::cout << "No cat yet" << std::endl;
  else
    kitty2->print();

  [[maybe_unused]] int numOp1 = 10;
  std::optional<int> numOp2{20}; // allocated addtional memory to check variable validity

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] enum class
   */

  clothing_color color = clothing_color::red;
  clothing_size size = clothing_size::small;
  buyShirt(color, size);

  std::cout << "------------------------------------- [↑ Example 4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [5] union
   *    - For saving memory! But very dangerous
   */

  std::cout << sizeof(sType1) << std::endl;
  std::cout << sizeof(uType1) << std::endl;
  std::cout << sizeof(uType2) << std::endl;

  uType1 u1;
  u1.i = 10;
  std::cout << u1.i << std::endl;
  u1.d = 0.3;
  std::cout << u1.d << std::endl;
  std::cout << u1.i << std::endl; // Undefined behavior!! (Trash value)

  std::cout << "------------------------------------- [↑ Example 5-1 ↑] -------------------------------------" << std::endl;

  uType2 s = {"Hello, world"};
  // at this point, reading from s.vec is undefined behavior
  std::cout << "s.str = " << s.str << '\n';
  s.str.~basic_string();
  new (&s.vec) std::vector<int>;
  // now, s.vec is the active member of the union
  s.vec.push_back(10);
  std::cout << s.vec.size() << '\n';
  s.vec.~vector();

  std::cout << "------------------------------------- [↑ Example 5-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [6] std::variant
   *    - Usage: To manage error code
   */

  std::variant<int, double, float> var;
  std::cout << "sType2: " << sizeof(sType2) << std::endl;
  std::cout << "uType3: " << sizeof(uType3) << std::endl;
  std::cout << "std::variant: " << sizeof(var) << std::endl;

  std::cout << "------------------------------------- [↑ Example 6-1 ↑] -------------------------------------" << std::endl;

  uType3 u2;
  u2.i = 10;
  std::cout << u2.d << std::endl; // Undefined behavior!

  var = 10;
  // std::cout << std::get<double>(var) << std::endl; // Exceotion!!
  if (auto pVal = std::get_if<double>(&var))
    std::cout << *pVal << std::endl;
  else
    std::cout << "var is not type double" << std::endl;

  std::variant<std::string, std::vector<int>> svar;
  svar = std::string("abcde");
  std::cout << std::get<std::string>(svar) << std::endl;

  // Doesn't need to call constructor or destructor

  svar = std::vector{1, 2, 3};
  const auto &vec = std::get<std::vector<int>>(svar);
  for (const auto &item : vec)
    std::cout << item << ' ';
  std::cout << std::endl;

  std::cout << "------------------------------------- [↑ Example 6-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [7] std::any
   */

  std::cout << std::boolalpha;

  // any type
  std::any a = 1;
  std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
  a = 3.14;
  std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
  a = true;
  std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';

  // bad cast
  try
  {
    a = 1;
    std::cout << std::any_cast<float>(a) << '\n';
  }
  catch (const std::bad_any_cast &e)
  {
    std::cout << e.what() << '\n';
  }

  // has value
  a = 2;
  if (a.has_value())
  {
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
  }

  // reset
  a.reset();
  if (!a.has_value())
  {
    std::cout << "no value\n";
  }

  // pointer to contained data
  a = 3;
  int *i = std::any_cast<int>(&a);
  std::cout << *i << "\n";

  std::cout << "------------------------------------- [↑ Example 7 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [8] type punning
   */

  std::cout << is_negative(-1.0f, 0) << std::endl;
  std::cout << is_negative(1.0f, 1) << std::endl;
  std::cout << is_negative(-1.0f, 2) << std::endl;

  std::cout << "------------------------------------- [↑ Example 8 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
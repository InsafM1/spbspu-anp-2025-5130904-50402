#include <iostream>
#include <iomanip>
#include <cctype>

namespace muhamadiarov
{
  bool checkOnRepeat(char *line, char symbol, size_t size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      if (line[i] == symbol)
      {
        return true;
      }
    }
    return false;
  }
  char *getline(std::istream &in, size_t &size, size_t &countNumbers);
  char *latRmv(char *res, char *str, size_t size);
  char *latTwo(char *line1, size_t size1, const char *line2, size_t size2, char *res2, size_t &size);
}


int main()
{
  namespace muh = muhamadiarov;
  char *str = nullptr;
  size_t countNumbers = 0;
  size_t size = 0;
  try
  {
    str = muh::getline(std::cin, size, countNumbers);
  }
  catch (std::bad_alloc &e)
  {
    std::cerr << "Error creating dinamic memmory\n";
    return 1;
  }
  catch (std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  char *res1 = nullptr;
  try
  {
    char *tmp = new char[countNumbers + 1];
    res1 = muh::latRmv(tmp, str, size);
  }
  catch (...)
  {
    std::cerr << "Error creating dinamic memmory\n";
    delete[] str;
    return 1;
  }
  const char *line2 = "def ghk";
  size_t size2 = 7;
  char *res2 = nullptr;
  size_t sizeForLatTwo = 0;
  try
  {
    char *tmp = new char[size2 + size - countNumbers + 1];
    res2 = muh::latTwo(str, size, line2, size2, tmp, sizeForLatTwo);
  }
  catch (...)
  {
    std::cerr << "Error creating dinamic memmory\n";
    delete[] res1;
    delete[] str;
    return 1;
  }
  for (size_t i = 0; i < countNumbers; ++i)
  {
    std::cout << res1[i] << ' ';
  }
  std::cout << '\n';
  for (size_t i = 0; i < sizeForLatTwo; ++i)
  {
    std::cout << res2[i];
  }
  std::cout << '\n';
  delete[] str;
  delete[] res1;
  delete[] res2;
  return 0;
}

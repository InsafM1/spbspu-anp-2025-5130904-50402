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
  char *getline(std::istream &in, size_t &size, size_t &countNumbers)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      in >> std::noskipws;
    }
    char *str = new char[20];
    size_t comp = 20;
    char ch = ' ';
    while (in >> ch && ch != '\n')
    {
      try
      {
        if (size == comp - 1)
        {
          char *tmp = new char[comp * 2];
          comp *= 2;
          for (size_t i = 0; i < size; ++i)
          {
            tmp[i] = str[i];
          }
          delete[] str;
          str = tmp;
        }
      }
      catch (...)
      {
        delete[] str;
        throw std::bad_alloc();
      }
      str[size] = ch;
      if (std::isdigit(str[size]))
      {
        ++countNumbers;
      }
      ++size;
    }
    if (in.fail())
    {
      delete[] str;
      throw std::logic_error("Error input\n");
    }
    str[size] = '\0';
    try
    {
      if (size < comp)
      {
        char *tmp = new char[size];
        for (size_t i = 0; i < size; ++i)
        {
          tmp[i] = str[i];
        }
        delete[] str;
        str = tmp;
      }
    }
    catch (...)
    {
      delete[] str;
      throw std::bad_alloc();
    }
    if (is_skipws)
    {
      in >> std::skipws;
    }
    return str;
  }
  char *latRmv(char *res, char *str, size_t size)
  {
    size_t i = 0;
    size_t count = 0;
    for (; i < size; ++i)
    {
      if (std::isdigit(str[i]))
      {
        res[count++] = str[i];
      }
    }
    res[count] = '\0';
    return res;
  }
  char *latTwo(char *line1, size_t size1, const char *line2, const size_t size2, char *res2, size_t &size)
  {
    for (size_t i = 0; i < size1; ++i)
    {
      bool ch = checkOnRepeat(res2, line1[i], size);
      if (ch)
      {
        continue;
      }
      if (!std::isdigit(line1[i]) && line1[i] != ' ')
      {
        res2[size] = line1[i];
        ++size;
      }
    }
    for (size_t i = 0; i < size2; ++i)
    {
      bool ch = checkOnRepeat(res2, line2[i], size);
      if (ch)
      {
        continue;
      }
      if (line2[i] != ' ')
      {
        res2[size] = line2[i];
        ++size;
      }
    }
    char tch = ' ';
    for (size_t i = 0; i < size; ++i)
    {
      for (size_t j = 0; j < size - i - 1; ++j)
      {
        if (res2[j] > res2[j + 1])
        {
          tch = res2[j];
          res2[j] = res2[j + 1];
          res2[j + 1] = tch;
        }
      }
    }
    res2[size] = '\0';
    return res2;
  }
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
  const size_t size2 = 7;
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

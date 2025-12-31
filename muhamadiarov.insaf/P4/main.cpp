#include <iostream>
#include <iomanip>
#include <cctype>

namespace muhamadiarov
{
  bool checkOnRepeat(const char *line, char symbol, size_t size)
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
  char *getline(std::istream &in, size_t &size, size_t &countNotLetters)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      in >> std::noskipws;
    }
    const size_t beginSize = 20; 
    char *str = new char[beginSize];
    size_t comp = beginSize;
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
      catch (const std::bad_alloc&)
      {
        if (is_skipws)
        {
          in >> std::skipws;
        }
        delete[] str;
        throw std::bad_alloc();
      }
      str[size] = ch;
      if (!std::isalpha(str[size]))
      {
        ++countNotLetters;
      }
      ++size;
    }
    if (in.fail())
    {
      if (is_skipws)
      {
        in >> std::skipws;
      }
      delete[] str;
      throw std::logic_error("Error input\n");
    }
    str[size] = '\0';
    try
    {
      if (size + 1 < comp)
      {
        char *tmp = new char[size + 1];
        for (size_t i = 0; i < size + 1; ++i)
        {
          tmp[i] = str[i];
        }
        delete[] str;
        str = tmp;
      }
    }
    catch (const std::bad_alloc&)
    {
      if (is_skipws)
      {
        in >> std::skipws;
      }
      delete[] str;
      throw std::bad_alloc();
    }
    if (is_skipws)
    {
      in >> std::skipws;
    }

    return str;
  }
  char *latRmv(char *res, const char *str)
  {
    size_t i = 0;
    size_t count = 0;
    while (str[i] != '\0')
    {
      if (!std::isalpha(str[i]))
      {
        res[count++] = str[i];
      }
      ++i;
    }
    res[count] = '\0';
    return res;
  }
  char *toAssociatStrings(const char *str1, const char *res, size_t &size)
  {   
    size_t i = 0;
    while (str1[i] != '\0')
    {
      bool ch = checkOnRepeat(res, str1[i], size);
      if (!std::isdigit(str1[i]) && str1[i] != ' ')
      {
        res[size] = str1[i];
        ++size;
      }
      ++i;
    }
    return res;
  }
  char *latTwo(const char *line1, const char *line2, char *res2, size_t &size)
  {
    res = toAssociatStrings(line1, res2, size);
    res = toAssociatStrings(line2, res2, size); 
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
  size_t countNotLetters = 0;
  size_t size = 0;
  try
  {
    str = muh::getline(std::cin, size, countNumbers);
  }
  catch (std::bad_alloc&)
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
    char *tmp = new char[countNotLetters + 1];
    tmp[countNotLetters] = '\0';
    res1 = muh::latRmv(tmp, str);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error creating dinamic memmory\n";
    delete[] str;
    return 1;
  }
  const char *line2 = "def ghk";
  char *res2 = nullptr;
  size_t sizeForLatTwo = 0;
  try
  {
    char *tmp = new char[size2 + size - countNotLetters + 1];
    res2 = muh::latTwo(str, line2, tmp, sizeForLatTwo);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error creating dinamic memmory\n";
    delete[] res1;
    delete[] str;
    return 1;
  }
  for (size_t i = 0; i < countNotLetters; ++i)
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

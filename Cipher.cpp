#include "Cipher.h"
#include <regex>
//--------------------------------------------------------------------------------------
namespace
{
const char l_beginOfAlphabet   = 65; // A
const char l_endOfAlphabet     = 90; // Z

std::string toUpper(const std::string & data)
{
  std::string result;
  for (char c : data)
    result += std::toupper(c);
  return result;
};

std::string readUntilAndTrim(std::string & str, char symbol)
{
  std::string result;
  size_t pos = str.find(symbol);
  if (pos != std::string::npos)
  {
    result = str.substr(0, pos);
    str = str.substr(pos + 1, str.length() - 1);
  }

  if (result.empty())
  {
    result = str;
    str.clear();
  }
  return result;
}
}
//--------------------------------------------------------------------------------------
Cipher::Cipher()
{
}
//--------------------------------------------------------------------------------------
std::string Cipher::encodeVigenere(const std::string & data, const std::string & key) const
{
  auto upperedData = toUpper(data);
  auto upperedKey = toUpper(key);

  std::string result;

  std::string dataFilledWithKey = fillDataWithKey(upperedData, upperedKey);
  std::vector<int> shiftForEveryLetter = convertTextToDecimalWithAlphabet(dataFilledWithKey);

  result = shiftDataInAlphabet(upperedData, shiftForEveryLetter);

  return result;
}
//--------------------------------------------------------------------------------------
std::string Cipher::decodeVigenere(const std::string & data, const std::string & key) const
{
  auto upperedData = toUpper(data);
  auto upperedKey = toUpper(key);
  upperedKey = std::regex_replace(upperedKey, std::regex(" "), "");

  std::string result;

  std::string dataFilledWithKey = fillDataWithKey(upperedData, upperedKey);

  std::vector<int> shiftForEveryLetter = convertTextToDecimalWithAlphabet(dataFilledWithKey);

  result = shiftBackDataInAlphabet(upperedData, shiftForEveryLetter);

  return result;
}
//--------------------------------------------------------------------------------------
std::string Cipher::decodeAtbash(const std::string & data) const
{
  auto upperedData = toUpper(data);
  std::string result;

  for (const char c : upperedData)
  {
    if (isSymbolOutOfAlphabet(c) || c == 'N') // middle of alphabet
    {
      result += c;
      continue;
    }

    int posInAlphabet = static_cast<int> (c);
    int posAfterReverse = l_endOfAlphabet - (posInAlphabet - l_beginOfAlphabet);

    result += static_cast<char> (posAfterReverse);
  }

  return result;
}
//--------------------------------------------------------------------------------------
std::string Cipher::decodeA1Z26(const std::string & data) const
{
  auto upperedData = toUpper(data);
  std::string result;

  std::vector<std::vector<int>> decodedData;
  fromA1Z26StringToVector(data, decodedData);

  for (const auto & word : decodedData)
  {
    for (const auto & num : word)
    {
      result += (char)num;
    }

    if (word != decodedData.back())
      result += ' ';
  }

  return result;
}
//--------------------------------------------------------------------------------------
std::string Cipher::decodeCaesar(const std::string & data, const int shift) const
{
  auto upperedData = toUpper(data);
  std::string result;

  for (char c : data)
  {
    if (isSymbolOutOfAlphabet(c))
    {
      result += c;
      continue;
    }
    int pos = static_cast<int> (c);
    result += shiftBackWithRest(pos, shift);
  }

  return result;
}
//--------------------------------------------------------------------------------------
std::string Cipher::fillDataWithKey(const std::string & data, const std::string & key) const
{
  std::string filledData;
  size_t posOfKey = 0;

  for (const auto & i : data)
  {
    if (isSymbolOutOfAlphabet(i))
    {
      filledData += i;
      continue;
    }

    filledData += key.at(posOfKey);
    ++posOfKey;

    if (posOfKey >= key.length())
      posOfKey = 0;
  }
  return filledData;
}
//--------------------------------------------------------------------------------------
std::vector<int> Cipher::convertTextToDecimalWithAlphabet(const std::string & data) const
{
  std::vector<int> text;
  for (const auto & i : data)
  {
    if (isSymbolOutOfAlphabet(i))
      continue;
    int numInAlphabet = static_cast<int> (i) - l_beginOfAlphabet;
    text.push_back(numInAlphabet);
  }
  return text;
}
//--------------------------------------------------------------------------------------
char Cipher::shiftWithRest(int posOfLetterInAlphabet, int shiftOnThisRound) const
{
  char result;
  if (posOfLetterInAlphabet + shiftOnThisRound <= l_endOfAlphabet)
  {
    result = static_cast<char> (posOfLetterInAlphabet + shiftOnThisRound);
  }
  else
  {
    shiftOnThisRound = shiftOnThisRound - (l_endOfAlphabet - posOfLetterInAlphabet) - 1;
    posOfLetterInAlphabet = l_beginOfAlphabet;
    result = shiftWithRest(posOfLetterInAlphabet, shiftOnThisRound);
  }
  return result;
}
//--------------------------------------------------------------------------------------
char Cipher::shiftBackWithRest(int posOfLetterInAlphabet, int shiftOnThisRound) const
{
  char result;
  if (posOfLetterInAlphabet - shiftOnThisRound >= l_beginOfAlphabet)
  {
    result = static_cast<char> (posOfLetterInAlphabet - shiftOnThisRound);
  }
  else
  {
    shiftOnThisRound = shiftOnThisRound - (posOfLetterInAlphabet - l_beginOfAlphabet) - 1;
    posOfLetterInAlphabet = l_endOfAlphabet;
    result = shiftBackWithRest(posOfLetterInAlphabet, shiftOnThisRound);
  }
  return result;
}
//--------------------------------------------------------------------------------------
std::string Cipher::shiftDataInAlphabet(const std::string & data, const std::vector<int> & shifts) const
{
  size_t posOfShifts = 0;
  std::string result;

  for (const auto & c : data)
  {
    if (isSymbolOutOfAlphabet(c))
    {
      result += c;
      continue;
    }
    int posOfLetterInAlphabet = static_cast<int> (c);
    const int & shiftOnThisRound = shifts.at(posOfShifts);

    result += shiftWithRest(posOfLetterInAlphabet, shiftOnThisRound);
    posOfShifts++;
  }
  return result;
}
//--------------------------------------------------------------------------------------
std::string Cipher::shiftBackDataInAlphabet(const std::string & data, const std::vector<int> & shifts) const
{
  size_t posOfShifts = 0;
  std::string result;

  for (const auto & c : data)
  {
    if (isSymbolOutOfAlphabet(c))
    {
      result += c;
      continue;
    }
    int posOfLetterInAlphabet = static_cast<int> (c);
    const int & shiftOnThisRound = shifts.at(posOfShifts);

    result += shiftBackWithRest(posOfLetterInAlphabet, shiftOnThisRound);
    posOfShifts++;
  }
  return result;
}
//--------------------------------------------------------------------------------------
bool Cipher::isSymbolOutOfAlphabet(char c) const
{
  return c < l_beginOfAlphabet || c > l_endOfAlphabet;
}
//--------------------------------------------------------------------------------------
void Cipher::fromA1Z26StringToVector(std::string data, std::vector<std::vector<int>> & result) const
{
  while (data.empty() != true)
  {
    std::vector<int> a1z26Word;
    std::string word = readUntilAndTrim(data, ' ');

    while (word.empty() == false)
    {
      auto number = readUntilAndTrim(word, '-');
      a1z26Word.push_back(std::stoi(number) + l_beginOfAlphabet - 1);
    }
    result.push_back(a1z26Word);
  }
}
//--------------------------------------------------------------------------------------

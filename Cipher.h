#ifndef CIPHER_H
#define CIPHER_H
//--------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
//--------------------------------------------------------------------------------------
class Cipher
{
public:
  Cipher();
  std::string encodeVigenere(const std::string & data, const std::string & key) const;
  std::string decodeVigenere(const std::string & data, const std::string & key) const;

  std::string decodeAtbash(const std::string & data) const;

  std::string decodeA1Z26(const std::string & data) const;

  std::string decodeCaesar(const std::string & data, const int shift) const;
private:
  std::string fillDataWithKey(const std::string & data, const std::string & key) const;

  std::vector<int> convertTextToDecimalWithAlphabet(const std::string & data) const;

  char shiftWithRest(int posOfLetterInAlphabet, int shiftOnThisRound) const;
  char shiftBackWithRest(int posOfLetterInAlphabet, int shiftOnThisRound) const;

  std::string shiftDataInAlphabet(const std::string & data, const std::vector<int> & shifts) const;
  std::string shiftBackDataInAlphabet(const std::string & data, const std::vector<int> & shifts) const;

  bool isSymbolOutOfAlphabet(char c) const;

  void fromA1Z26StringToVector(std::string data, std::vector<std::vector<int>> & result) const;

};
//--------------------------------------------------------------------------------------
#endif // CIPHER_H
//--------------------------------------------------------------------------------------

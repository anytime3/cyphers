#include "Cipher.h"
//--------------------------------------------------------------------------------------
namespace
{
auto print = [](const auto remark, const auto& v)
{
    std::cout << remark;
    for (auto n : v)
      std::cout << n << ' ';
    std::cout << '\n';
};
}
//--------------------------------------------------------------------------------------
int main()
{
  Cipher cipher;

  // std::string line("smofzqa jdfv"), key("widdle");
  std::string line, key;

  std::cout << "Введите строку: ";
  std::getline(std::cin, line);
  std::cout << "Введите ключ: ";
  std::getline(std::cin, key);

  std::string result;
  try
  {
    // result = cipher.encodeVigenere(line, key);
    result = cipher.decodeVigenere(line, key);
  } catch (const std::exception & err)
  {
    std::cout << "Exception: " << err.what() << std::endl;
    return 1;
  }

  std::cout << "Виженер говорит: " << result << std::endl;

  // auto resultDecode = cipher.decodeVigenere(result, key);
  // std:: cout << "Дешифровка ключом дала результат " << resultDecode << std::endl;


  /*
  auto atbashResult = cipher.decodeAtbash(line);
  std::cout << "Расшифрованный Атбаш: " << atbashResult << std::endl;
  */

  /*
  auto a1z26Result = cipher.decodeA1Z26(line);
  std::cout << "Расшифрованный A1Z26: " << a1z26Result << std::endl;
  */

  // auto caesarResult = cipher.decodeCaesar(line, 3);
  // std::cout << "Расшифрованный Цезарь: " << caesarResult << std::endl;

}

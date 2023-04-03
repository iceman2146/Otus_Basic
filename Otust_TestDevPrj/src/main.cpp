#include <iostream>

#include "SequenceContainer.h"
#include "OneWayList.h"
#include "TwoWayList.h"

template <typename T>
void print_seq(T &container)
{
  std::cout << "array: ";
  for (size_t i = 0; i < container.size(); ++i)
  {
    std::cout << container[i] << ' ';
  }
  std::cout << std::endl;

  std::cout << "Size: " << container.size() << std::endl;
  std::cout << std::endl
            << std::endl;
}
template <typename T>
void test_seq(T &container, int razmer)
{

  
  std::cout << "Sozdaem container" << std::endl;
  if (!container.is_empty())
  {
    for (auto iter = container.begin(); iter != container.end();
         ++iter)
    {
      std::cout << iter.get() << ' ';
    }
  }

  for (int i = 0; i < razmer; i++)
  {
    container.push_back(i);
  }
  std::cout << "Zabivaem ot 0 do 9" << std::endl;
  print_seq(container);

  container.erase(7);
  container.erase(5);
  container.erase(3);
  std::cout << "Ubrali 3, 5 i 7 element" << std::endl;
  print_seq(container);

  container.insert(0, 10);
  std::cout << "dobavili 10 v nachalo" << std::endl;

  print_seq(container);

  std::cout << "dobavili 20 v seredinu" << std::endl;
  container.insert(container.size() / 2, 20);

  print_seq(container);

  container.push_back(30);

  for (auto iterator = container.begin(); iterator != container.end(); ++iterator)
  {
    std::cout << *iterator << ' ';
  }

  std::cout << std::endl;

  print_seq(container);
  
}

int main()
{
  size_t Kol_vo_elementov = 10;
  SequenceContainer<int> SequenceContainer_int;
  test_seq(SequenceContainer_int, Kol_vo_elementov);
  
  OneWayContainer<int> OneWayContainer_int;
  test_seq(OneWayContainer_int, Kol_vo_elementov);
  

  TwoWayContainer<int> TwoWayContainer_int;
  test_seq(TwoWayContainer_int, Kol_vo_elementov);

  return 0;
}
#include "System.h"
int main()
{
	setlocale(LC_ALL, "rus");
	int amount;
	std::string name_;
	int bt, at;
	int q;
	do
	{
		std::cout << "ведите количество процессов: ";
		std::cin >> amount;
	} while (amount <= 0);
	do
	{
		std::cout << "ведите время кванта: ";
		std::cin >> q;
	} while (q <= 0);
	System a(q);
	for (int i = 0; i < amount; ++i)
	{
		std::cout << "Введите имя " << i + 1 << "-го процесса :";
		std::cin >> name_;
		do
		{
			std::cout << "Введите время выполнения " << i + 1 << "-го процесса :";
			std::cin >> bt;
			std::cout << "Введите время появления " << i + 1 << "-го процесса :";
			std::cin >> at;

		} while (bt <= 0);
		a.add_process(name_, bt, at);
	}
	a.start_round_robin();
	a.show_system();
	system("pause");
	return 0;
}
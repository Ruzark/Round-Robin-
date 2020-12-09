#include "System.h"

void System::add_process(std::string _name, int bt, int at)
{
	if (pHead == nullptr)
	{
		pHead = new Process(_name, bt, at);
		amount_of_processes++;
	}
	else
	{
		Process* current = pHead;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Process(_name, bt, at);
		amount_of_processes++;
	}
	sort();
}

void System::delete_process()
{
	Process* temp = pHead;
	if (pHead == nullptr)
	{
		std::cout << "В системе ещё нет никаких процессов, удалять нечего" << std::endl;
		std::cout << std::endl;
		return;
	}
	else
	{
		pHead = pHead->pNext;
		delete temp;
		amount_of_processes--;
	}
}

void System::clear_system()
{
	while (amount_of_processes)
	{
		delete_process();
	}
}

void System::show_system()
{
	Process* temp = pHead;
	if (temp == nullptr)
	{
		std::cout << "В системе ещё нет процессов " << std::endl;
		return;
	}
	std::cout << std::endl;
	std::cout << "====================SYSTEM====================" << std::endl;
	std::cout << std::endl;
	std::cout << "Quantum = " << time_quant << std::endl;
	std::cout << std::endl;
	std::cout << "\t|ArT|\t|BuT|\t|MiT|\t|PeR|\t|ReR|\t|TiS|" << std::endl;
	std::cout << "=====================================================" << std::endl;
	do
	{
		std::cout << "|P-" << temp->name << "|\t |" << temp->Arrival_t << "|\t |"<< temp->Burst_t << "|\t |";
		std::cout << temp->Lost_time << "|\t |" << temp->Reactivity_ratio << "|\t |";
		std::cout << temp->Reactivity_ratio << "|\t |" << temp->Total_sys_time << "|"<< std::endl;
		std::cout << "=====================================================" << std::endl;
		temp = temp->pNext;
	} while (temp != nullptr);
	average_characteristics();
}

void System::start_round_robin()
{

	bool check = true;
	Process* temp = pHead;
	if (temp == nullptr)
	{
		std::cout << "Планировать нечего :( " << std::endl;
		return;
	}
	std::cout << "Очередь выполнения процессов :" << std::endl;
	std::cout << std::endl;
	do
	{
		temp = pHead;
		bool flag = false;
		do
		{
			if (temp->Copy_Arrival_t == 0)
			{
				if (temp->Copy_Burst_t == 0)
				{
					temp = temp->pNext;
				}
				else
				{
					flag = true;
					int copyq = 0;
					for (int i = 0; i < time_quant; ++i)
					{
						if (temp->Copy_Burst_t == 0)
						{
							break;
						}
						temp->Copy_Burst_t--;
						temp->Total_sys_time++;
						std::cout << "(P-" << temp->name << ")" << " ";
						copyq++;
					}
					Process* temp1 = pHead;
					do
					{
						if (temp1 != temp)
						{
							for (int i = 0; i < copyq; ++i)
							{
								if (temp1->Copy_Arrival_t == 0)
								{
									if (temp1->Copy_Burst_t == 0)
									{
										break;
									}
									else
									{
										temp1->Total_sys_time++;
									}
								}
								else
								{
									temp1->Copy_Arrival_t--;
								}
							}
							temp1 = temp1->pNext;
						}
						else
						{
							temp1 = temp1->pNext;
						}
					} while (temp1 != nullptr);
					temp = temp->pNext;
				}
			}
			else
			{
				temp = temp->pNext;
			}

		} while (temp != nullptr);
		if (flag == false)
		{
			Process* tmp = pHead;
			do
			{
				for (int i = 0; i < 1; ++i)
				{
					if (tmp->Copy_Arrival_t == 0)
					{
						break;
					}
					else
					{
						tmp->Copy_Arrival_t--;
					}
					
				}
				tmp = tmp->pNext;
			} while (tmp != nullptr);
		}
		else
		{
			Process* ccheck = pHead;
			do
			{
				if (ccheck->Copy_Burst_t == 0)
				{
					check = false;
					ccheck = ccheck->pNext;
				}
				else
				{
					check = true;
					break;
				}

			} while (ccheck != nullptr);
		}
	} while (check);
	std::cout << std::endl;
	calculation_of_characteristics();
}

void System::calculation_of_characteristics()
{
	Process* temp = pHead;
	do
	{
		temp->Lost_time = temp->Total_sys_time - temp->Burst_t;
		temp->Reactivity_ratio = temp->Burst_t / temp->Total_sys_time;
		temp->Penalty_ratio = temp->Total_sys_time / temp->Burst_t;
		temp->Lost_time = floor(temp->Lost_time * 100) / 100;
		temp->Reactivity_ratio = floor(temp->Reactivity_ratio * 100) / 100;
		temp->Penalty_ratio = floor(temp->Penalty_ratio * 100) / 100;
		temp = temp->pNext;

	} while (temp != nullptr);
}

void System::average_characteristics()
{
	Process* temp = pHead;
	do
	{
		avg_lost += temp->Lost_time / amount_of_processes;
		avg_pen += temp->Penalty_ratio / amount_of_processes;
		avg_react += temp->Reactivity_ratio / amount_of_processes;
		avg_tis += temp->Total_sys_time / amount_of_processes;
		temp = temp->pNext;
	} while (temp != nullptr);
	avg_lost = floor(avg_lost * 100) / 100;
	avg_pen = floor(avg_pen * 100) / 100;
	avg_react = floor(avg_react * 100) / 100;
	avg_tis = floor(avg_tis * 100) / 100;
	std::cout << "Среднее значение потерянного времени равно: " << avg_lost << std::endl;
	std::cout << "Среднее значение штрафного отношения равно: " << avg_pen << std::endl;
	std::cout << "Среднее значение отношения реактивности равно: " << avg_react << std::endl;
	std::cout << "Среднее значение общего времени в системе равно: " << avg_tis << std::endl;
	std::cout << std::endl;
}

void System::sort()
{
	Process* temp = pHead;
	if (temp == nullptr)
	{
		return;
	}
	for (int i = 0; i < 2; ++i)
	{
		temp = pHead;
		do
		{
			if (temp->pNext == nullptr)
			{
				break;
			}
			else
			{
				if (temp->Arrival_t > temp->pNext->Arrival_t)
				{
					int tmp = temp->pNext->Arrival_t;
					temp->pNext->Arrival_t = temp->Arrival_t;
					temp->Arrival_t = tmp;

					int tmp1 = temp->pNext->Copy_Arrival_t;
					temp->pNext->Copy_Arrival_t = temp->Copy_Arrival_t;
					temp->Copy_Arrival_t = tmp1;

					int tmp2 = temp->pNext->Burst_t;
					temp->pNext->Burst_t = temp->Burst_t;
					temp->Burst_t = tmp2;

					int tmp3 = temp->pNext->Copy_Burst_t;
					temp->pNext->Copy_Burst_t = temp->Copy_Burst_t;
					temp->Copy_Burst_t = tmp3;

					std::string tname = temp->pNext->name;
					temp->pNext->name = temp->name;
					temp->name = tname;

					double tmp4 = temp->pNext->Lost_time;
					temp->pNext->Lost_time = temp->Lost_time;
					temp->Lost_time = tmp4;

					double tmp5 = temp->pNext->Reactivity_ratio;
					temp->pNext->Reactivity_ratio = temp->Reactivity_ratio;
					temp->Reactivity_ratio = tmp5;

					double tmp6 = temp->pNext->Penalty_ratio;
					temp->pNext->Penalty_ratio = temp->Penalty_ratio;
					temp->Penalty_ratio = tmp6;

					double tmp7 = temp->pNext->Total_sys_time;
					temp->pNext->Total_sys_time = temp->Total_sys_time;
					temp->Total_sys_time = tmp7;
				}
				temp = temp->pNext;
			}
		} while (temp != nullptr);
	}
	
}



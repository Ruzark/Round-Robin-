#pragma once
#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <iostream>
#include <string>
#include <locale>
class System
{
public:
	System(int q)
	{
		amount_of_processes = 0;
		time_quant = q;
		pHead = nullptr;
		avg_lost = 0;
		avg_pen = 0;
		avg_react = 0;
		avg_tis = 0;
	}
	System()
	{
		amount_of_processes = 0;
		time_quant = 1;
		pHead = nullptr;
		avg_lost = 0;
		avg_pen = 0;
		avg_react = 0;
		avg_tis = 0;
	}
	~System()
	{
		clear_system();
	}
	void add_process(std::string, int, int); // Добавляет процесс (имя,время выполнения);
	void delete_process(); // Удаляет процесс 
	void clear_system(); // Полностью очищает систему от процессов
	void show_system(); // Показывает процессы в системе
	void start_round_robin(); // Метод начинает выполнять планирование алгоритмом RR
	void calculation_of_characteristics(); // Вычисляет основные характеристики процессов
	void average_characteristics(); // Вычисляет среднее значение основных характеристик процесса 
private:
	class Process
	{
	public:
		Process* pNext;
		int Burst_t; // Время выполнения 
		int Arrival_t; // Время появления
		int Copy_Arrival_t; // Время появления (для вычислений)
		int Copy_Burst_t; // Время выполнения (для вычислений)
		double Total_sys_time; // Общее время в системе 
		double Lost_time; // Потерянное время 
		double Reactivity_ratio; // Отношение реактивности
		double Penalty_ratio; // Штрафное отношение
		std::string name; // Имя процесса
		Process(std::string _name, int burst, int arrival ,Process* next = nullptr)
		{
			Burst_t = burst;
			Arrival_t = arrival;
			Copy_Burst_t = Burst_t;
			Copy_Arrival_t = Arrival_t;
			Total_sys_time = 0;
			Lost_time = 0;
			Reactivity_ratio = 0;
			Penalty_ratio = 0;
			pNext = next;
			name = _name;
		}
	};
	Process* pHead;
	int amount_of_processes; // Количество процессов
	int time_quant; // Время кванта 
	double avg_tis; // Cреднее значение общего времени в системе всех процессов
	double avg_pen; // Cреднее значение штрафного отношения всех процессов
	double avg_react; // Среднее значение отношения реактивности всех процессов  
	double avg_lost; // Cреднее значение потерянного времени всех процессов
	void sort();
};
#endif

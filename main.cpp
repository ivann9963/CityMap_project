#pragma once
#include <iostream>
#include<locale.h>
#include<windows.h>
#include "System.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Bulgarian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	Base* startSystem = new System(cin, cout);
	try
	{
		startSystem->start();
	}
	catch (...)
	{
		cout << endl << "Something went wrong! Terminating...";
	}
	delete startSystem;
	return 0;
	system("pause");

}

/*
	command to open files
	open ../data/0.txt
	open ../data/1.txt
	open ../data/1-2.txt
	open ../data/EulerCycle.txt
	print
	open ../data/jidc.txt
	print

*/
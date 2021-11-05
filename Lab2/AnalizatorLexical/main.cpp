// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "AnalizatorLexical.h"


using namespace std;


int main()
{
	
	AnalizatorLexical analizator = AnalizatorLexical();
	analizator.analiza("input2.txt", "code.txt", "fip.txt", "ts_const.txt", "ts_id.txt");

}
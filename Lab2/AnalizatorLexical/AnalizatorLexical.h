#pragma once
#include <string>
#include "List.h"
#include "Codare.h"
#include "StateMachine.h"
using namespace std;
class AnalizatorLexical
{

public:
	AnalizatorLexical();
	~AnalizatorLexical();
	void analiza(string input, string codeFile, string outputFip, string outputTsConst, string outputTsId);
	void analizaLinie(string input, string codeFile, string outputFip, string outputTsConst, string outputTsId);

private:
	StateMachine automatConstInt = StateMachine("inputINT.txt");
	StateMachine automatConstString = StateMachine("inputSTRING.txt");
	StateMachine automatID = StateMachine("inputID.txt");
	List listConst = List();
	List listId = List();
	List listCode = List();
	void generareFip(int cod, int codTs, string outputFile);
	void clearFile(string fileName);
	void writeListInFile(List* list, string fileName);
	void codificare(string fileName);
	int pozitie(string atom, List* list);
	int adaugaInList(string atom, List* list);
};


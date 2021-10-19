#pragma once
#include <string>
#include "List.h"
#include "Codare.h"
using namespace std;
class AnalizatorLexical
{

public:
	AnalizatorLexical();
	~AnalizatorLexical();
	void analiza(string input, string codeFile, string outputFip, string outputTsConst, string outputTsId);

private:
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


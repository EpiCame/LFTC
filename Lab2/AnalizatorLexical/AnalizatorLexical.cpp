#include "AnalizatorLexical.h"
#include "Utils.h"
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

void AnalizatorLexical::generareFip(int cod, int codTs, string outputFile)
{
	std::ofstream outfile;

	outfile.open(outputFile, std::ios_base::app);
	outfile << cod << " " << codTs << endl;
}

void AnalizatorLexical::clearFile(string fileName)
{
	std::ofstream outfile;
	outfile.open(fileName, std::ofstream::out | std::ofstream::trunc);
	outfile.close();
}

void AnalizatorLexical::writeListInFile(List* list, string fileName)
{
	ofstream myfile;
	myfile.open(fileName);

	list->display(myfile);
	myfile.close();
}

void AnalizatorLexical::codificare(string fileName)
{
	vector<string> lines = Utils::getStringsLine(fileName);
	vector<string> keys;
	for (unsigned i = 0; i < lines.size(); i++) {
		keys = Utils::split(lines[i]);
		Codare codare = Codare();

		if (keys.size() == 2) {
			codare.dataCod = keys[0];
			codare.cod = atoi(keys[1].c_str());
		}
		else {
			codare.dataCod = lines[i][0];
			string restul = lines[i].substr(2);
			codare.cod = atoi(restul.c_str());
		}
		listCode.add(codare);
	}
}

int AnalizatorLexical::pozitie(string atom, List* list)
{
	return list->find(atom);
}

int AnalizatorLexical::adaugaInList(string atom, List* list)
{
	return list->insert(atom);
}

AnalizatorLexical::AnalizatorLexical()
{
}


AnalizatorLexical::~AnalizatorLexical()
{
}

void AnalizatorLexical::analiza(string input, string codeFile, string outputFip, string outputTsConst, string outputTsId)
{
	vector<string> operators = Utils::getStringsLine("operators.txt");
	vector<string> separators = Utils::getStringsLine("separators.txt");
	vector<string> keywords = Utils::getStringsLine("keywords.txt");

	/*regex naturell_rx("[1-9][0/*-9]*");
	regex naturellpoz_rx("(?:0)|[1-9][0-9]*");
	regex identificator_rx("[a-zA-Z_][a-zA-Z1-9_]{0,7}");
	regex string_const_rx("[\"].*[\"]");*/

	AnalizatorLexical::codificare(codeFile);
	AnalizatorLexical::clearFile(outputFip);

	vector<string> lines = Utils::getStringsLine(input);
	vector<string> words;
	string atom;

	for (unsigned i = 0; i < lines.size(); i++) {
		words = Utils::split(lines[i]);
		for (unsigned j = 0; j < words.size(); j++) {
			atom = words[j];

			if (find(operators.begin(), operators.end(), atom) != operators.end() ||
				find(separators.begin(), separators.end(), atom) != separators.end() ||
				find(keywords.begin(), keywords.end(), atom) != keywords.end()) {

				int cod = AnalizatorLexical::pozitie(atom, &listCode);
				AnalizatorLexical::generareFip(cod, 0, outputFip);
			}
			else
				if (automatID.checkSequence(atom)) {
					int codTs = AnalizatorLexical::pozitie(atom, &listId);
					if (codTs == 0) {
						codTs = AnalizatorLexical::adaugaInList(atom, &listId);
					}
					AnalizatorLexical::generareFip(1, codTs, outputFip);
				}
				else
					if (automatConstInt.checkSequence(atom) || automatConstString.checkSequence(atom)) {
						int codTs = AnalizatorLexical::pozitie(atom, &listConst);
						if (codTs == 0) {
							codTs = AnalizatorLexical::adaugaInList(atom, &listConst);
						}
						AnalizatorLexical::generareFip(2, codTs, outputFip);
					}
					else {
						cout << "Eroare lexicala la linia " << i << " la atomul: " << atom << endl;
					}
		}
	}
			

	AnalizatorLexical::writeListInFile(&listId, outputTsId);
	AnalizatorLexical::writeListInFile(&listConst, outputTsConst);
}

void AnalizatorLexical::analizaLinie(string input, string codeFile, string outputFip, string outputTsConst, string outputTsId)
{
	vector<string> operators = Utils::getStringsLine("operators.txt");
	vector<string> separators = Utils::getStringsLine("separators.txt");
	vector<string> keywords = Utils::getStringsLine("keywords.txt");

	AnalizatorLexical::codificare(codeFile);
	AnalizatorLexical::clearFile(outputFip);

	vector<string> lines = Utils::getStringsLine(input);
	string line;
	string atom = "";
	string atomExtended = "";

	for (unsigned i = 0; i < lines.size(); i++) {
		line = lines[i];

		while (line.size() > 0) {
			if ((atom = automatID.findPrefix(line)) != "") {
				if (find(keywords.begin(), keywords.end(), atom) != keywords.end()) {
					cout << atom << " e cuvant rezervat" << endl;

					// scriere in fip
					int cod = AnalizatorLexical::pozitie(atom, &listCode);
					AnalizatorLexical::generareFip(cod, 0, outputFip);
				}
				else {
					cout << atom << " e identificator" << endl;

					// scriere in tabela identificator (cod 1)
					int codTs = AnalizatorLexical::pozitie(atom, &listId);
					if (codTs == 0) {
						codTs = AnalizatorLexical::adaugaInList(atom, &listId);
					}

					// scriere in fip
					AnalizatorLexical::generareFip(1, codTs, outputFip);
				}
			}
			else if ((atom = automatConstString.findPrefix(line)) != "") {
				cout << atom << " e constanta string" << endl;


				// scriere in tabela constante (cod 2)
				int codTs = AnalizatorLexical::pozitie(atom, &listConst);
				if (codTs == 0) {
					codTs = AnalizatorLexical::adaugaInList(atom, &listConst);
				}
				// scriere in fip
				AnalizatorLexical::generareFip(2, codTs, outputFip);

			}
			else if ((atom = automatConstInt.findPrefix(line)) != "") {
				cout << atom << " e constanta intreaga" << endl;


				// scriere in tabela constante (cod 2)
				int codTs = AnalizatorLexical::pozitie(atom, &listConst);
				if (codTs == 0) {
					codTs = AnalizatorLexical::adaugaInList(atom, &listConst);
				}
				// scriere in fip
				AnalizatorLexical::generareFip(2, codTs, outputFip);
			}
			else {
				atom = line[0];

				if (find(separators.begin(), separators.end(), atom) != separators.end()) {
					cout << atom << " e separator" << endl;

					// scriere in fip
					int cod = AnalizatorLexical::pozitie(atom, &listCode);
					AnalizatorLexical::generareFip(cod, 0, outputFip);
				}

				else {
					int index = 1;
					atomExtended = atom;

					bool isOperator = false;

					while (find(operators.begin(), operators.end(), atomExtended) != operators.end()) {
						atom = atomExtended;
						atomExtended += line[index];
						index++;
						isOperator = true;
					}

					if (isOperator) {
						cout << atom << " e operator" << endl;

						// scriere in fip
						int cod = AnalizatorLexical::pozitie(atom, &listCode);
						AnalizatorLexical::generareFip(cod, 0, outputFip);
					}
					else {
						cout << "Eroare lexicala la linia " << i << " caracter " << atom << endl;
					}
				}
			}
			line = line.substr(atom.size());
		}
	}

	AnalizatorLexical::writeListInFile(&listId, outputTsId);
	AnalizatorLexical::writeListInFile(&listConst, outputTsConst);
}
// CppProject_FinanceTracker.cpp : Defines the entry point for the console application.
//
/* Program to track personal finances.
* Keeps track of financial situation
* by storing incomes and expenses.
*/

#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#pragma warning(disable:4996)
using namespace std;

string removeSpaces(string);

int main()
{
	//choice for menu
	int selection;

	//input types:
	char transactionType;
	float money = 0;	//to be referenced in error checking
	string description;
	string date;

	char input;

	//reading types:
	char readTransactionType;
	float readMoney;
	string readDescription;
	string readDate;
	
	//text file with inputs
	fstream inputFile("Finances.txt");
	inputFile.close();

	do {		
		cout << "Available operations:" << endl << endl;
		cout << "1) Enter input" << endl;
		cout << "2) Read file" << endl;
		cout << "3) Empty File" << endl;
		cout << "4) Print summary report" << endl;
		cout << "5) Quit" << endl << endl;
		cout << "please select operation:" << endl;

		//get input
		cin >> selection;
		cout << endl;

		switch (selection) {
		//enter inputs:
			case 1: {
				//enter type : i, e, I, or E
				cout << "Income or expense (i/e):" << endl;
				cin >> transactionType;

				while ((transactionType != 'i') && (transactionType != 'e') && (transactionType != 'I') && (transactionType != 'E')) {
					cout << "Error - enter i/e: ";
					cin >> transactionType;
				}

				//enter amount: positive number, only inputs first (nothing after a space)
				cout << "Enter amount:" << endl;
				while ((!(cin >> money)) || money <= 0) {
					cout << "Error - enter a positive number: " << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}

				//enter description: spaces removed, empty input converted
				cout << "Enter description word:" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				getline(cin, description);

				if (description.length() == 0) {
					description = "-";
				}
				else {
					description = removeSpaces(description);
				}

				//enter date: only inputs first word
				cout << "Enter date:" << endl;
				cin >> date;

				cout << endl;
				cin.clear();
				cin.ignore(100, '\n');

			//save to file
				cout << "Do you want to save to file? (y/n):" << endl;
				cin >> input;
				//input option: y or Y (added to file), n or N
				while ((input != 'y') && (input != 'n') && (input != 'Y') && (input != 'N')) {
					cout << "Error - enter y/n: ";
					cin >> input;
				}
				if (input == 'y' || input == 'Y') {
					inputFile.open("Finances.txt", ofstream::out | ofstream::app);
					string fileLine;
					if ((inputFile.good())) {
						inputFile << transactionType << " " << money << " " << description << " " << date << "\n";
						inputFile.close();
					}
					else {
						cout << "Error" << endl;
					}
				}
				else{}
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

		//read file:
			case 2: {
				//read file line by line, if not empty
				string fileLineNew;
				inputFile.open("Finances.txt");
				inputFile.clear();
				if (inputFile.is_open()) {
					if (inputFile.peek() == ifstream::traits_type::eof()) {
						cout << "File is empty" << endl;
					}
					else {
						while (getline(inputFile, fileLineNew)) {
							cout << fileLineNew << endl;
						}
					}
					inputFile.close();
					cout << endl;
				}
				else {
					cout << "File isn't open" << endl << endl;
				}
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

		//empty file:
			case 3: {
				//empty file, if not already empty
				inputFile.open("Finances.txt");
				if (inputFile.peek() == ifstream::traits_type::eof()) {
					cout << "File is empty" << endl << endl;
					inputFile.close();
				}
				else {
					inputFile.close();
					inputFile.open("Finances.txt", ofstream::out | ofstream::trunc);
					inputFile.close();
					cout << "Notes deleted." << endl << endl;
				}
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

		//print summary report:
			case 4: {
				//print summary: sum of incomes, expenses and resulting difference, all if file isn't empty
				float incomeSum = 0;
				float expenseSum = 0;
				float totalSum = 0;

				cout << "Summary report:" << endl;
				fstream inputFile("Finances.txt");
				if (inputFile.is_open()) {
					if (inputFile.peek() == ifstream::traits_type::eof()) {
						cout << "File is empty" << endl;
					}
					else {
						while (inputFile >> readTransactionType >> readMoney >> readDescription >> readDate) {
							if (readTransactionType == 'i' || readTransactionType == 'I') {
								incomeSum = incomeSum + readMoney;
							}
							else if (readTransactionType == 'e' || readTransactionType == 'E') {
								expenseSum = expenseSum + readMoney;
							}
							else {
								cout << "Error" << endl;
							}
						}
						cout << "Income sum: " << incomeSum << endl;
						cout << "Expense sum: " << expenseSum << endl;
						totalSum = incomeSum - expenseSum;
						if (totalSum > 0) {
							cout << "Difference: +" << totalSum << endl << endl;
						}
						else {
							cout << "Difference: " << totalSum << endl << endl;
						}
					}
				}
				else {
					cout << "File isn't open" << endl << endl;
				}
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

		//stop:
			case 5: {
				break;
			}

		//invalid input:
			default: {
				cout << "Error - enter valid option" << endl << endl;
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
		}
	} while (selection != 5);

	//check for memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}

string removeSpaces(string String) {
	int j = 0;
	int k = 0;
	//iterate through string and skip all spaces when inserting back
	for (string::iterator it = String.begin(); it != String.end(); ++it) {
		if (String[j] == ' ') {
			j++;
		}
		else if (String[j] != ' ') {
			String[k] = String[j];
			j++;
			k++;
		}
	}
	//append amount of spaces from length
	String.erase(k);
	return String;
}
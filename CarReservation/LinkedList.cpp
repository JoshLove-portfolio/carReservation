#include "carHeader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace Car;

void LinkedList::getNewCar(LinkedList linkedList)
{
	unsigned int i = 0;

	unsigned int year = 0;

	std::cout << std::endl;
	std::cout << "How many cars do you wish you enter?" << std::endl;

	std::cin >> i;

	std::cin.ignore();

	for (unsigned int j = 0; j < i; j++)
	{
		//create car object
		LinkedList::carModel newCar;

		//prompt and input the model
		std::cout << "Enter car model: " << std::endl;
		std::getline(std::cin, newCar.model);

		//prompt and input the color
		std::cout << "Enter car color: " << std::endl;
		std::getline(std::cin, newCar.color);

		//prompt and input the manufacturer
		std::cout << "Enter car manufacturer: " << std::endl;
		std::getline(std::cin, newCar.manuf);

		//prompt and input the year
		std::cout << "Enter car year: " << std::endl;
		std::cin >> year;
		newCar.yearConversion = std::to_string(year);

		//prompt and input the VIN
		std::cout << "Enter car VIN: " << std::endl;
		std::cin.ignore();
		std::getline(std::cin, newCar.VIN);
		std::cout << std::endl;

		LinkedList::prependList(newCar);
	}

}

void LinkedList::prependList(LinkedList::carModel newCar)
{
	//create new node out of passed in object
	carLink* prependNode = new carLink(newCar);

	//check if list is empty
	if (headPtr == nullptr)
	{
		//list is empty, set head and tail to the new node
		headPtr = prependNode;
		tailPtr = prependNode;
	}
	else //list is not empty
	{
		prependNode->nextPtr = headPtr; //assign next pointer of new node as the current head
		headPtr = prependNode; //assign current head to the new pointer
	}
}

void LinkedList::printList()
{
	LinkedList::carLink* currentPtr = headPtr;

	while (currentPtr != nullptr)
	{
		std::cout << "| " << currentPtr->newCar.manuf << ": ";
		std::cout << currentPtr->newCar.color << " ";
		std::cout << currentPtr->newCar.model << " from ";
		std::cout << currentPtr->newCar.yearConversion << " with VIN: ";
		std::cout << currentPtr->newCar.VIN << std::flush;

		std::cout << std::endl;

		currentPtr = currentPtr->nextPtr;
	}

}

void LinkedList::toCSV()
{
	LinkedList::carLink* currentPtr = headPtr;

	std::ofstream newFile("car_save_data.csv", std::ios::out, std::ios::trunc);

	if (newFile)
	{
		while (currentPtr != nullptr) {

			newFile << currentPtr->newCar.manuf << ",";
			newFile << currentPtr->newCar.color << ",";
			newFile << currentPtr->newCar.model << ",";
			newFile << currentPtr->newCar.yearConversion << ",";
			newFile << currentPtr->newCar.VIN << ",\n";

			currentPtr = currentPtr->nextPtr;
		}

		std::cout << "Data saved successfully!\n";
		std::cout << std::endl;

	}
	else
	{
		std::cerr << "Error opening file, returning to menu!";
		return;
	}
}

void LinkedList::readCSV()
{
	LinkedList::carModel newCar;

	std::vector<std::string> rowStore;

	std::vector<std::vector<std::string>> dataStore;

	std::string row;

	std::ifstream newFile("car_save_data.csv");

	if (newFile)
	{
		while (std::getline(newFile, row, '\n'))
		{
			rowStore.clear();
			std::stringstream lineStream(row);
			std::string cellValue;

				while (std::getline(lineStream, cellValue, ','))
				{

					rowStore.push_back(cellValue);

				}

			dataStore.push_back(rowStore);
		}
	}
	else
	{
		std::cerr << "Error opening file - please save data first!";
		return;
	}

	for (int i = 0; i < dataStore.size(); i++)
	{
		newCar.manuf = dataStore[i][0];
		newCar.color = dataStore[i][1];
		newCar.model = dataStore[i][2];
		newCar.yearConversion = dataStore[i][3];
		newCar.VIN = dataStore[i][4];

		LinkedList::prependList(newCar);
	}
}

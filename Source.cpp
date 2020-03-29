#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;
int binCounter = 19670;
class HashNode {

private:
	string key;
	string value;
	HashNode* next;

public:

	HashNode(string key, string value) {
		this->key = key;
		this->value = value;
		this->next = NULL;
	}

	string getKey() {
		return key;
	}

	string getValue() {
		return value;
	}

	void setValue(string value) {
		this->value = value;
	}

	HashNode* getNext() {
		return next;
	}

	void setNext(HashNode* next) {
		this->next = next;
	}

};

class HashTable {

private:
	HashNode **hashTable;
	const int TABLE_SIZE = 200000;
	int nodeCount = 0;
public:

	HashTable() {

		hashTable = new HashNode*[TABLE_SIZE];

		for (int i = 0; i < TABLE_SIZE; i++)
			hashTable[i] = NULL;
	}

	int getCount() {
		return nodeCount;
	}

	void printHashTable() {

		ofstream myfile("output123.txt", std::fstream::app);
		if (myfile.is_open())
		{

			for (int i = 0; i < TABLE_SIZE; i++) {
				if (hashTable[i] != NULL) {
					myfile << i << endl;
					myfile << hashTable[i]->getKey() << endl;
					myfile << hashTable[i]->getValue() << endl;
					HashNode* entry = hashTable[i]->getNext();
					while (entry != NULL) {
						myfile << entry->getKey() << endl;
						myfile << entry->getValue() << endl;
						entry = entry->getNext();
					}
					myfile << "************************************" << endl;
				}
			}

			myfile.close();

		}
		
	}

	HashNode* get(string key) {

		int hash = hashFunction(key);
		return hashTable[hash];

	}

	void insert(string key, string value) {
		

		int hash = hashFunction(key);
		HashNode* previousNode = NULL;
		HashNode* newNode = hashTable[hash];
		while (newNode != NULL)
		{
			previousNode = newNode;
			newNode = newNode->getNext();
		}
		if (newNode == NULL)
		{
			newNode = new HashNode(key, value);
			if (previousNode == NULL)
			{
				hashTable[hash] = newNode;
				nodeCount++;
			}
			else
			{
				previousNode->setNext(newNode);
			}
		}
		else
		{
			newNode->setValue(value);
			
		}
		
	}

/*	void printNumberOfBins()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (hashTable[i] != NULL)
			{
				binCounter++;
			}
		}
	}*/

	~HashTable() {

		for (int i = 0; i < TABLE_SIZE; i++) {
			if (hashTable[i] != NULL)
				binCounter++;
				delete hashTable[i];
		}
		cout << "Bin count is: " << binCounter << endl;
		delete[] hashTable;

	}

	int hashFunction(std::string const& s) {
		unsigned long hash = 5381;
		char c;
		for (int i = 0; i<s.size(); i++) {
			c = s[i];
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		}
		hash %= TABLE_SIZE;
		return hash;
	}

};

class Anagram {
private:
	string dictionaryArr[25000];
	string sortedDictionary[25000];
	HashTable *hashTable = new HashTable();
public:
	Anagram() {
		

	}
	~Anagram() {

	}

	/*void countSort(char arr[])
	{
		const int RANGE = 255;
		const int length = strlen(arr);
		char output[length];

		int count[RANGE + 1], i;
		memset(count, 0, sizeof(count));

		for (i = 0; arr[i]; ++i)
			++count[arr[i]];

		for (i = 1; i <= RANGE; ++i)
			count[i] += count[i - 1];

		for (i = 0; arr[i]; ++i)
		{
			output[count[arr[i]] - 1] = arr[i];
			--count[arr[i]];
		}

		for (i = 0; arr[i]; ++i)
			arr[i] = output[i];
	}*/
	/*------------------------QUICK SORT START--------------------------*/

	void quickSort(string &str, int left, int right) {
		int i = left, j = right;
		int mid = str[(left + right) / 2];

		/* partition */
		while (i <= j) {
			while (str[i] < mid)
				i++;
			while (str[j] > mid)
				j--;
			if (i <= j) {
				std::swap(str[i], str[j]);
				i++; j--;
			}
		};

		/* recursion */
		if (left < j)
			quickSort(str, left, j);
		if (i < right)
			quickSort(str, i, right);
	}
	/*-------------------------QUICK SORT END---------------------------*/


	void loadDictionary() {

		string line;
		int count = 0;
		ifstream myfile("words.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line) && count < 25000)
			{
				dictionaryArr[count] = line;
				sortedDictionary[count] = line;

				quickSort(sortedDictionary[count], 0, sortedDictionary[count].length() - 1);

				hashTable->insert(sortedDictionary[count], dictionaryArr[count]);

				count++;
			}
			cout << hashTable->getCount() << endl;
			//hashTable->printHashTable();
			cout << endl;
			cout << "*****************SUCCESSFULLY LOADED DICTIONARY******************" << endl << endl;
			myfile.close();

		}

		else cout << "Unable to open file";

	}

	void loadInputStrings() {

		string line;
		ifstream myfile("input.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				int count = 0;
				string input = line, outputBeforeCount, outputAfterCount, output = "";
				quickSort(line, 0, line.length() - 1);
				HashNode* node = hashTable->get(line);

				if (node == NULL || (input == node->getValue() && node->getNext() == NULL)) {
					output = input + " 0";
				}
				else {
					string key = node->getKey();
					outputBeforeCount = input + " ";
					while (node != NULL) {
						
						if (count > 0 && node->getKey() != key) {
							node = node->getNext();
							continue;
						}
						
						else if (input != node->getValue()) {
							outputAfterCount += node->getValue() + " ";
							count++;
						}

						node = node->getNext();
						output = outputBeforeCount + to_string(count) + " " + outputAfterCount;

					}
					
				}
				writeToOutputFile(output);

			}
			myfile.close();
			
		}

		else cout << "Unable to open file";

	}

	void writeToOutputFile(string output) {

		ofstream myfile("output.txt", std::fstream::app);
		if (myfile.is_open())
		{
			
			myfile << output << endl;
			myfile.close();

		}
		
		else cout << "Unable to open file";

	}
};

int main()
{
	Anagram *anagram = new Anagram();
	anagram->loadDictionary();
	anagram->loadInputStrings();
	cout << "Bins used: " << binCounter << endl;
	system("pause");
	return 0;
}
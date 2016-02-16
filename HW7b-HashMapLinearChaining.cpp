//#include <HashMapLinearProbing.h>
//#include <HashMapLinearChaining.h>
#include <iostream>
#include <fstream>
#include<string>
#include<cmath>
using namespace std;

class HashMapLinearChaining {
private:
	class Node
	{
	public:
		string word;
		int count = 0;//how many same words in this node
		Node* next = nullptr;
	};

	Node** table;
	int size;
	int used; // how many symbols are in the table

	void clear()//Îö¹¹
	{
		for (int i = 0; i < size; i++)
		{
			Node* p = table[i];
			while (p != nullptr)
			{
				Node* q = p;
				p = p->next;
				delete q;
			}
		}
		delete[] table;
	}

public:
	HashMapLinearChaining(int initial)
	{
		used = 0;
		size = initial;// initial size of the table
		table = new Node*[size];
		for (int i = 0; i < size; ++i)
		{
			table[i] = nullptr;
		}
	}
	~HashMapLinearChaining()
	{
		clear();
	}
	unsigned int Hashfunction(string word)// turn word into key
	{

		unsigned int key = 0;
		for (unsigned int i = 0; i < word.size(); i++)
		{
			key *= 128;
			key += word.at(i);
			key %= size;
		}
		return key;

	}
	void grow()//the size of the table grow double
	{
		used = 0;
		Node** temp = table;
		int temp_size = size;
		size = size * 2 + 1;
		table = new Node*[size];
		for (int i = 0; i < size; ++i)
			table[i] = nullptr;
		for (int i = 0; i < temp_size; i++)
		{
			Node* p = temp[i];
			while (p != nullptr)
			{
				add(p->word, p->count);
				p = p->next;
			}
		}

		for (int i = 0; i < temp_size; i++)
		{
			Node* p = temp[i];
			while (p != nullptr)
			{
				Node* q = p;
				p = p->next;
				delete q;
			}
		}

		delete[] temp;
		cout << "double size, the new size is: " << size << endl;
	}
	void add(string word, int count = 1)
	{
		if (used > (size / 2))// if a=1/2 then grow the table
			grow();
		int key = Hashfunction(word);
		Node* p = table[key];
		Node* q = nullptr;
		while (p != nullptr && p->word != word)
		{
			q = p;
			p = p->next;
		}
		if (p == nullptr)
		{
			used++;
			p = new Node;
			p->word = word;
			p->count += count;
			if (q == nullptr)
				table[key] = p;
			else
				q->next = p;
		}
		else
		{
			p->count += count;
		}
	}
	void display_check_times() //times of searches for each word
	{
		int check[12] = { 0 };
		string str;
		for (int i = 0; i < size; i++)
		{
			Node* p = table[i];
			int j = 1;
			while (p != nullptr)
			{
				if (j < 11)
					check[j++]++;
				else
					check[11]++;
				p = p->next;
			}
		}
		cout << "The numbers of checks list below:" << endl;
		for (int i = 1; i < 11; i++)
			cout << i << " : " << check[i] << endl;
		cout << "11 or more : " << check[11] << endl;
	}
	bool hasString(string word)//²»ÓÃÕû¸öÊý×é¶¼²é£¬Ö»Òª²éµ½Ã»ÓÐµ¥´Ê¾ÍÍ£
	{
		int key = Hashfunction(word);
		Node* p = table[key];
		while (p != nullptr)
		{
			if (p->word == word)
				return true;
			p = p->next;
		}
		return false;
	}
	int getused()//how many words in the table
	{
		return used;
	}
	int getsize()//return the size of table
	{
		return size;
	}
};


void loadDict(HashMapLinearChaining& dict, string dictname)
{
	ifstream f(dictname);
	if (!f)
	{
		cerr << "doesn't exist!" << endl;
		exit(1);
	}
	while (!f.eof())
	{
		string word;
		f >> word;
		dict.add(word);
	}
	f.close();
	//dict = new HashMapLinearProbing(2000);
	//wordCount = new HashMapLinearProbing(200000);
	//misspelled = new HashMapLinearProbing(200000);
}
/*

void spellcheck(string book) {
ifstream f(book);
while (!f.eof()) {
// read in the book....
// look up regex in C++
// words are any sequence of letters, digits, or ' (apostrophe)
if (dict.contains(word))
;// correctly spelled
else
; //incorrectly spelled

}
}

void displayTop100Words(String book) {
// find all the elements in the hash map
// sort them by value
//display only the top 100 words in descending order by count
// YOU DO NOT HAVE TO WRITE THE SORT!!!
// IF YOU WANT to be clever, you can avoid sorting the whole data set
}
*/

int main()
{
	int initial = 701;
	HashMapLinearChaining dict(initial);//it's better to be prime, 701
	cout << "The initial size is " << initial << endl;
	loadDict(dict, "wordsEn.txt");
	cout << "The size of hashmap is " << dict.getsize() << endl;
	cout << "The number of words in this dictionary is " << dict.getused() << endl;
	dict.display_check_times();
	system("pause");
}

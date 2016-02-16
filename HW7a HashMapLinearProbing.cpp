//#include <HashMapLinearProbing.h>
//#include <HashMapLinearChaining.h>
#include <iostream>
#include <fstream>
#include<string>
#include<cmath>
using namespace std;

class HashMapLinearProbing {
private:
	class Node{
	public:
		string word;
		int count = 0;//how many same words in this node
	};

	Node* table;
	int size;
	int used; // how many symbols are in the table


public:
	HashMapLinearProbing(int initial)
	{
		used = 0;
		size = initial;// initial size of the table
		table = new Node[size];
	}
	~HashMapLinearProbing()
	{
		delete[] table;
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
		Node* temp = table;
		int temp_size = size;
		size = size * 2 + 1;
		table = new Node[size];
		for (int i = 0; i < temp_size; i++)
		{
			while (temp[i].count != 0)
			{
				add(temp[i].word);
				temp[i].count--;
			}
		}
		cout << "double size, the new size is: " << size << endl;
		delete[] temp;
	}
	void add(string word)
	{
		int key = Hashfunction(word);
		while (table[key].count != 0)
		{
			if (table[key].word == word)
			{
				table[key].count++;
				return;
			}
			key = (key + 1) % size;
		}
		table[key].word = word;
		table[key].count++;
		used++;

		if (used > (size / 2))// if a=1/2 then grow the table
			grow();
	}
	bool hasString(string word)//²»ÓÃÕû¸öÊý×é¶¼²é£¬Ö»Òª²éµ½Ã»ÓÐµ¥´Ê¾ÍÍ£
	{
		int key = Hashfunction(word);
		while (table[key].count != 0)
		{
			if (table[key].word == word)
				return true;
			else
				key = (key + 1) % size;
		}
		return false;//can not find the word
	}
	void display_check_times() //times of searches for each word
	{
		int check[12] = { 0 };
		string str;
		for (int i = 0; i < size; i++)
		{
			if (table[i].count != 0)
			{
				int temp = table[i].count;//how many words in this grid
				str = table[i].word;
				int key = Hashfunction(str);
				int times = 1; //×î´óÎª11
				//find table[key] is or not str
				while (table[key].word != str)//ÐèÒªbreak
				{
					times++;
					key = (key + 1) % size;//key++
				}
				if (times < 11)
					check[times] = check[times] + temp;
				else
					check[11] = check[11] + temp;//11 or more
			}
		}
		cout << "The numbers of checks list below:" << endl;
		for (int i = 1; i < 11; i++)
			cout << i << " : " << check[i] << endl;
		cout << "11 or more : " << check[11] << endl;
	}
	int getCount(string word) // return the number of times the word has appeared!
	{
		int key = Hashfunction(word);
		for (int length = size; length > 0; length--)
		{
			if (table[key].word == word)
				return table[key].count;
			else
				key = (key + 1) % size;
		}
		return 0;
	}
	int getused()//how many rooms are occupied
	{
		return used;
	}
	int getwords()
	{
		int count = 0;
		for (int i = 0; i < size; i++)
			count += table[i].count;
		return count;
	}
	int getsize()//return the size of table
	{
		return size;
	}
};


void loadDict(HashMapLinearProbing& dict, string dictname)
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
	HashMapLinearProbing dict(initial);//it's better to be prime, 701
	cout << "The initial size is " << initial << endl;
	loadDict(dict, "wordsEn.txt");
	cout << "The size of hashmap is " << dict.getsize() << endl;
	cout << "How many rooms are occupied: " << dict.getused() << endl;
	cout << "The number of words in this dictionary is " << dict.getwords() << endl;
	dict.display_check_times();
}

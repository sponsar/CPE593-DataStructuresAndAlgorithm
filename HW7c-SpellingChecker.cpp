#include <iostream>
#include <fstream>
#include<time.h>
#include<string>
using namespace std;

class Node
{
public:
	char* word;
	int count = 0;//how many same words in this node
	Node()
	{
		word = new char[1024];
	}
	~Node()
	{
		delete[] word;
	}

};
class HashMapLinearProbing {
private:


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
	unsigned int Hashfunction(char* word)// turn word into key
	{

		unsigned int key = 0;
		for (unsigned int i = 0; i < strlen(word); i++)
		{
			key *= 31;
			key += word[i];
			key %= size;
		}
		return key;

	}
	void grow()//the size of the table grow double
	{
		used = 0;
		Node* temp = table;
		int temp_size = size;
		size = size * 2 ;
		table = new Node[size];
		for (int i = 0; i < temp_size; i++)
		{
			while (temp[i].count != 0)
			{
				add(temp[i].word);
				temp[i].count--;
			}
		}
		//cout << "double size, the new size is: " << size << endl;
		delete[] temp;
	}
	void add(char* word)
	{
		int key = Hashfunction(word);
		while (table[key].count != 0)
		{
			if (!strcmp(table[key].word, word))//ÕâÀï´ýÉÌÁ¿
			{
				table[key].count++;
				return;
			}
			key = (key + 1) % size;
		}
		strcpy(table[key].word, word);
		table[key].count++;
		used++;

		if (used > (size / 2))// if a=1/2 then grow the table
			grow();
	}

	bool hasString(char* word)//²»ÓÃÕû¸öÊý×é¶¼²é£¬Ö»Òª²éµ½Ã»ÓÐµ¥´Ê¾ÍÍ£
	{
		int key = Hashfunction(word);
		while (table[key].count != 0)
		{
			if (!strcmp(table[key].word, word))
				return true;
			else
				key = (key + 1) % size;
		}
		return false;//can not find the word
	}


	void display_check_times() //times of searches for each word
	{
		int check[12] = { 0 };
		char* str = new char[1024];
		for (int i = 0; i < size; i++)
		{
			if (table[i].count != 0)
			{
				int temp = table[i].count;//how many words in this grid
				strcpy(str, table[i].word);
				int key = Hashfunction(str);
				int times = 1; //×î´óÎª11
				//find table[key] is or not str
				while (strcmp(table[key].word, str))//ÐèÒªbreak  ,  table[key].word != str
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
		delete[] str;
	}

	void frequency()
	{
		//0µ½n-1;
		Node* frequency = new Node[100];
		int j = 0;//¼ÇÂ¼table¶Áµ½ÄÄÀï
		for (int i = 0; i < 100; i++)//ÔØÈëÒ»°Ù¸öÊý½øÀ´
		{
			while (table[j].count == 0)
				j++;
			frequency[i].count = table[j].count;
			strcpy(frequency[i].word, table[j].word);
			j++;
			if (j == size)//ÕâÀïÒªÅÐ¶Ïµ±j×ßµ½tableµÄ¾¡Í·ÔõÃ´°ì
			{
				cout << "There are only " << i << " numbers in the hash table!" << endl;
				return;
			}
		}
		for (int i = 1; i < 100; i++)//ÅÅÐòfrequency,´Ó0~99
		{
			int temp_int;
			char* temp_str = new char[1024];
			temp_int = frequency[i].count;
			strcpy(temp_str, frequency[i].word);
			int j = i - 1;
			while ((j >= 0) && (frequency[j].count>temp_int))
			{
				frequency[j + 1].count = frequency[j].count;
				strcpy(frequency[j + 1].word, frequency[j].word);
				j--;
			}
			if (j != i - 1)
			{
				frequency[j + 1].count = temp_int;
				strcpy(frequency[j + 1].word, temp_str);
			}
			delete[] temp_str;
		}
		for (; j<size; j++)//½«ÐÂµÄµ¥´Ê´Ótable²åÈëµ½frequency²¢ÅÅÐò
		{
			if (table[j].count == 0)
				continue;

			if (table[j].count <= frequency[0].count)
				continue;
			int x = 1;
			while (x < 100 && frequency[x].count < table[j].count)
			{
				frequency[x - 1].count = frequency[x].count;
				strcpy(frequency[x - 1].word, frequency[x].word);
				x++;
			}
			frequency[x - 1].count = table[j].count;
			strcpy(frequency[x - 1].word, table[j].word);
		}
		cout << "Top 100 frequency:" << endl;
		for (int i = 99; i >= 0; i--)
			cout << 100 - i << ".    " << frequency[i].word << "   " << frequency[i].count << endl;
		delete[] frequency;
	}

	Node* getTable()
	{
		return table;
	}
	int getCount(char* word) // return the number of times the word has appeared!
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


void loadDict(HashMapLinearProbing& dict, char* dictname)
{
	ifstream f(dictname);
	if (!f)
	{
		cerr << "doesn't exist!" << endl;
		exit(1);
	}
	while (!f.eof())
	{
		char word[1024];
		f >> word;
		dict.add(word);
	}
	f.close();
}

void loadBook(HashMapLinearProbing& book, char* name)
{
	ifstream f(name);
	if (!f)
	{
		cerr << "doesn't exist!" << endl;
		exit(1);
	}
	char* word = new char[1024];
	while (!f.eof())
	{
		f >> word;
		int length = strlen(word);
		int p = 0;//pÊÇÎªÁË·Ö´Ê£¬Èçwww.amazon.com£¬·Ö³ÉwwwºÍamazonºÍcom
		for (int i = 0; i < length; i++)//±éÀúµ¥´ÊµÄÃ¿Ò»¸ö×Ö·û
		{
			char c = word[i];
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '\''))
			{
				if (i > p)
				{
					char* w = new char[1024];
					//string w = word.substr(p, i - p);
					strncpy(w, word + p, i - p);
					w[i - p] = '\0';
					book.add(w);
					delete[] w;
				}
				p = i + 1;
			}
		}
		if (length > p)
		{
			//string w = word.substr(p, length - p);
			char* w = new char[1024];
			strncpy(w, word + p, length - p);
			w[length - p] = '\0';
			book.add(w);
			delete[] w;
		}
	}
	f.close();
	delete[] word;
}

void spellcheck(HashMapLinearProbing& book, HashMapLinearProbing& dict)
{
	int wrongWords = 0;
	int rightWords = 0;
	Node* newtable = book.getTable();//book.getsize()
	char* word = new char[1024];
	for (int i = 0; i < book.getsize(); i++)
	{
		if (newtable[i].count != 0)
		{
			strcpy(word, newtable[i].word);
			if (!dict.hasString(word))
				wrongWords++;
			else
				rightWords++;
		}
	}
	cout << endl << "The number of wrong spelling is " << wrongWords << endl;
	cout << "The number of right spelling is " << rightWords << endl;
	delete[] word;
}




int main()
{
	clock_t start, finish;
	start = clock();
	int initial = 701;
	HashMapLinearProbing book(initial);//it's better to be prime, 701
	HashMapLinearProbing dict(initial);
	loadDict(dict, "wordsEn.txt");
	loadBook(book, "CompletWorksOfShakespeare.txt");
	//cout << "The size of hashmap is " << book.getsize() << endl;
	//cout << "How many rooms are occupied: " << book.getused() << endl;
	//cout << "The number of words in this dictionary is " << book.getwords() << endl;
	book.display_check_times();
	book.frequency();
	cout << endl;
	spellcheck(book, dict);
	finish = clock();
	int time = finish - start;
	cout << endl << "it costs " << time <<"ms"<< endl;


}

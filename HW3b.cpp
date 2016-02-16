#include <iostream>
using namespace std;

class LinkedList {
private:
	class Node {
	public:
		int val;
		Node* next;
		Node* previous;
	};
	Node* head;
	Node* tail;
public:
	void copy(const LinkedList& orig) 
	{
		if (orig.head == nullptr) 
		{
			head = tail = nullptr;
			return;
		}
		Node* p = orig.head;//p is original
		head = new Node;
		Node* q = head;//q is new
		q->val = p->val;
		q->previous = nullptr;
		for (p = p->next; p != nullptr; p = p->next, q = q->next)
		{
			Node* temp = new Node;
			temp->val = p->val;

			q->next = temp;
			temp->previous = q;
		}
		q->next = nullptr;
		tail = q;
		/*
		head = new Node();
		head->val = orig.head->val;
		Node* p;
		Node* q;
		q = head;
		for (p = orig.head->next; p != nullptr; p = p->next) {
			Node* temp = new Node();
			temp->val = p->val;
			q->next = temp;
			q = q->next;
		}
		q->next = nullptr;
		*/
	}
	void clear() 
	{
		if (head == nullptr)
			return;
		for (Node* p = head->next; p != nullptr; p = p->next)
		{
			delete p->previous;
		}
		delete tail;
		head = tail = nullptr;
	}
	LinkedList() {
		head = tail = nullptr;
	}
	~LinkedList() {
		clear();
	}
	LinkedList(const LinkedList& orig)
	{
		copy(orig);
	}
	LinkedList& operator =(const LinkedList& orig) 
	{
		if (this != &orig) 
		{
			clear();
			copy(orig);
		}
		return *this;
	}
	void addFirst(int v) 
	{
		if (head == nullptr)
		{
			head = new Node;
			head->val = v;
			head->next = head->previous = nullptr;
			tail = head;
			return;
		}
		Node* temp = new Node();
		temp->val = v;
		temp->next = head;
		head->previous = temp;
		temp->previous = nullptr;
		head = temp;
	}
	void addLast(int v) 
	{
		if (head == nullptr) 
		{
			head = new Node();
			head->val = v;
			head->next = nullptr;
			tail = head;
			return;
		}
		Node* temp=new Node;
		temp->val = v;
		temp->next = nullptr;
		temp->previous = tail;
		tail->next = temp;
		tail = temp;
	}
	void deleteFirst() 
	{
		if (head == nullptr)//when there is no node
			return;
		if (head == tail)//when there is one node
		{
			delete head;
			head = tail = nullptr;
			return;
		}
		head = head->next;
		delete head->previous;
		head->previous = nullptr;
	}
	void deleteLast() 
	{
		if (head == nullptr)//when there is no node
			return;
		if (head == tail)//when there is one node
		{
			delete head;
			head = tail = nullptr;
			return;
		}
		tail = tail->previous;
		delete tail->next;
		tail->next = nullptr;
	}
	friend ostream& operator <<(ostream& s, const LinkedList& list) {
		s << '['<<' ';
		for (Node* p = list.head; p != nullptr; p = p->next)
			s << p->val << ' ';
		return s << ']';
	}
};


int main() 
{
	LinkedList a;
	for (int i = 0; i < 10; i++)
		a.addFirst(i);
	for (int i = 0; i < 10; i++)
		a.addLast(i);
	a.deleteFirst();
	a.deleteLast();
	LinkedList b;
	b = a;
	cout << b << endl;
}

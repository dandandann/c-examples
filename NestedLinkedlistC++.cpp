#include <stdio.h>
#include <string>

using namespace std;

struct Food{
	string name;
	int price;
	Food *next;
	
	Food(string name, int price){
		this->name = name;
		this->price = price;
		this->next = NULL;
	}
};

class FoodList{
private:
	Food *head, *tail;
	
public:
	FoodList(){
		head= tail = NULL;
	}
	
	void addList(string name, int price){
		Food *newFood = new Food(name, price);
		if(!head) head = tail = newFood;
		else{
			tail->next = newFood;
			tail = newFood;
		}
	}
	
	void del(string name){
		if(!head) return;
		
		if(name == head->name){  ////////////POP HEAD
			if(head == tail){
				head = tail = NULL;
			}
			else{
				Food* next = head->next;
				delete head;
				head = next;
			}
		}
		else if(name == tail->name){ // POPTAIL
			Food *prev = head;
			while(prev->next != tail) prev = prev->next;
			delete tail;
			tail = prev;
			prev->next = NULL;
		}
		else{ // Popmid
			Food *curr = head;
			while(curr->next && name != curr->next->name){
				curr = curr->next;
			}
			if(!curr->next){
				return;
			}
			
			Food *toDel = curr->next;
			curr->next = toDel->next;
			delete toDel;
		}
	}
	
	Food* getHead(){
		return head;
	}
};

struct Person{
	string name;
	FoodList *list;
	Person *next;
	
	Person(string name){
		this->name = name;
		this->list = new FoodList();
		this->next = NULL;
	}
};

class PersonList{
private:
	Person *head, *tail;
public:
	PersonList(){
		head = tail = NULL;
	}
	
	void addPerson(string name){
		Person *newPerson = new Person(name);
		if(!head) head = tail = newPerson;
		else{
			tail->next = newPerson;
			tail = newPerson;
		}
	}
	
	void removePerson(string name){
		if(!head) return;
		if(name == head->name){
			if(head == tail){
				delete head;
				head = tail = NULL;
			}else{
				Person* next = head->next;
				delete head;
				head = next;
			}
		}
		else if(name == tail->name){ // POPTAIL
			Person *prev = head;
			while(prev->next != tail) prev = prev->next;
			delete tail;
			tail = prev;
			prev->next = NULL;
		}
		else{ // Popmid
			Person *curr = head;
			while(curr->next && name != curr->next->name){
				curr = curr->next;
			}
			if(!curr->next){
				return;
			}
			
			Person *toDel = curr->next;
			curr->next = toDel->next;
			delete toDel;
		}
	}
	
	Person* findPerson(string name){
		Person* curr = head;
		while(curr){
			if(name == curr->name) return curr;
			curr = curr->next;
		}
		return NULL;
	}
	void addList(string personName, string name, int price){
		Person *person = findPerson(personName);
		person->list->addList(name, price);
	}
	
	void removeList(string personName, string nama){
		Person*person = findPerson(personName);
		person->list->del(nama);
	}
	
	void view(){
		Person *curr = head;
		while(curr){
			printf("%s\n", curr->name.c_str());
			Food *currFood = curr->list->getHead();
			while(currFood){
				printf("%s %d\n", currFood->name.c_str(), currFood->price);
				currFood = currFood->next;
			}
			curr = curr->next;
		}
	}
};



int main(){
	PersonList A;
	A.addPerson("Andi");
	A.addList("Andi", "Jeruk", 10);
	A.addPerson("Budi");
	A.addList("Budi", "Apel", 20);
	A.removeList("Budi", "Apel");
	A.view();
	return 0;
}



// Linked LIST review
// Hash Table
/*
Data Structure yang dimana ia menyimpan sebuah value dan juga hash key, biasa hash table ini digunakan
untuk menjaga hal-hal yang membutuhkan prov


Collision terjadi ketika satu nata menabrak data laiin, dimana ian melakukan linear probing dan headw wing
2 hal dari handlingL
linear probing
Contoh linear probling:




chaning

*/


// Nested Linked List
// Mutiple Linked List
// {???}  --> OOP
// {???}


#include <stdio.h>
//#include <stdlib.h>
#include <string>

using namespace std;

struct Node{
	string name;
	int score;
	Node *next, *prev;
	
	Node(string name,int score){
		this->name = name;
		this->score = score;
		this->next = this->prev = NULL;
	}
};

class HashTable{
private:
	Node *head[26], *tail[26];
	
	int hashing(string name){
		if(name[0] >= 'A' && name[0] <= 'Z'){
			return name[0] - 'A';
		}
		
		if(name[0] >= 'a' && name[0] <= 'z'){
			return name[0] - 'a';
		}
		
		return -1;
	}
	
	
public:
	HashTable(){
		for(int i = 0 ; i < 26 ; i++){
			head[i] = tail[i] = NULL;
		}
	}
	
	void insert(string name, int score){
		int hash = hashing(name);
		Node *newNode = new Node(name, score);
		
		if(!head[hash]){
			head[hash] = tail[hash] = newNode;
			return;	
		}
		
		
		
		tail[hash]->next = newNode;
		newNode->prev = tail[hash];
		tail[hash] = newNode; 
		
		
		
		
	}
	
	void view(){
		for(int i = 0 ; i < 26 ; i++){
			if(!head) continue;
	
			Node* curr = head[i];
			while(curr){
				printf("%s %d->",curr->name.c_str(), curr->score);
				curr = curr->next;
			}
		}
	}
	
	void del(string name){
		int hash = hashing(name);
		if(!head[hash]) return;
		
		if(name == head[hash]->name){ // Pophead
			
			
			if(head[hash] == tail[hash]){
				delete head[hash];
				head[hash] = tail[hash] = NULL;
			}
			
			
			else{
				
				Node* next = head[hash]->next;
				delete head[hash];
				head[hash] = next;
				next->prev = NULL;
				
			}
		} 
		
		
		
		else if(name == tail[hash]->name){ // PopTAIL
			
			Node* prev = tail[hash]->prev;
			delete tail[hash];
			tail[hash] = prev;
			prev->next = NULL;
			
			}
			else{ // Popmid
				
				Node* curr = head[hash];
				while(curr && name != curr->name){ // if curr exist and name is not target
					curr = curr->next;
				}
				
				if(!curr){
					return;
				}
				
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				delete curr;
			}
		}
		
		
	};
	



int main(){
	HashTable A;
	A.insert("Adit", 10);
	A.insert("Dodi", 50);
	A.insert("Asiau", 21);
	A.insert("Tono", 1);
	A.insert("Apa", 1);
	A.insert("itu", 1);
	A.insert("akecil", 12121);
	A.insert("adudu", 1);
//	A.del("adudu");
//	A.del("akecil");
//	A.del("itu");
//	A.del("Apa");
//	A.del("Dodi");
//	A.del("Adit");
//	A.del("Asiau");
//	A.del("Tono");
	
	
	
	A.view();
//	printf("%d",sizeof(HashTable));
	return 0;
}





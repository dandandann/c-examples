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
	
	Node(string nama,int score){
		this->name = nama;
		this->score = score;
	}
};

class HashTable{
private:
	Node *head[26];
	
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
			head[i] = NULL;
		}
	}
	
	void insert(string name, int score){
//		Node *newNode = new Node(name, score);
		int hash = hashing(name);
		int idx = hash;
		
		do{
			if(!head[idx]){ // Kalau head null, create newnode
				head[idx] = new Node(name, score);
				return;
			}
			idx = (idx + 1) % 26;
		}while(idx != hash);

		return;
	}
	
	void view(){
		for(int i = 0 ; i < 26 ; i++){
			if(!head[i]) continue;
			printf("%s %d\n", head[i]->name.c_str(), head[i]->score);
		}
	}
	
	void del(string name){
		int hash = hashing(name);
		int idx = hash;
		
		do{
			if( head[idx] && name == head[idx]->name){ // if head exist and name == head->name
				delete head[idx];
				head[idx] = NULL;
				return;
			}
			idx = (idx + 1) % 26;
		}while(idx != hash);
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
////	A.del("Dodi");
//	A.del("Adit");
//	A.del("Asiau");
//	A.del("Tono");
	
	
	
	A.view();
	printf("%d",sizeof(HashTable));
	return 0;
}





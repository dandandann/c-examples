#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
	char nama[20];
	float jmlPenduduk;
	int dikunjungi;
	struct Node *south, *north, *east, *west;
}*root;

struct Node* createNode(char nama[], float jmlPenduduk)
{
	struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
	strcpy(newNode->nama, nama);
	newNode->jmlPenduduk = jmlPenduduk;
	newNode->dikunjungi = 0;
	newNode->south = newNode->north = newNode->east = newNode->west = NULL;
	return newNode;
}

void pushNorth(struct Node *curr, char nama[], float jmlPenduduk)
{
	if(curr->north != NULL)
	{
		printf("Ada kota di Utara %s\n", curr->nama);
	}
	else
	{
		struct Node *newNode = createNode(nama, jmlPenduduk);
		newNode->south = curr;
		curr->north = newNode;		
	}
}

void pushEast(struct Node *curr, char nama[], float jmlPenduduk)
{
	if(curr->east != NULL)
	{
		printf("Ada kota di Timur %s\n", curr->nama);
	}
	else
	{
		struct Node *newNode = createNode(nama, jmlPenduduk);
		curr->east = newNode;		
		newNode->west = curr;
	}
}

void pushSouth(struct Node *curr, char nama[], float jmlPenduduk)
{
	if(curr->south != NULL)
	{
		printf("Ada kota di Selatan %s\n", curr->nama);
	}
	else
	{
		struct Node *newNode = createNode(nama, jmlPenduduk);
		curr->south = newNode;		
		newNode->north = curr;
	}
}

void pushWest(struct Node *curr, char nama[], float jmlPenduduk)
{
	if(curr->west != NULL)
	{
		printf("Ada kota di Barat %s\n", curr->nama);
	}
	else
	{
		struct Node *newNode = createNode(nama, jmlPenduduk);
		curr->west = newNode;		
		newNode->east = curr;
	}
}

void viewAll(struct Node *curr, int level, int maxLevel)
{
	if(level == 0) printf("City: ");
	else if(curr == NULL)
	{
		printf("-\n");
		return;
	}
	printf("%s (%.2f Jt)\n", curr->nama, curr->jmlPenduduk);
	if(curr->dikunjungi == 1 || level > maxLevel)
		return;
		
	curr->dikunjungi = 1;
	
	for(int i = 0; i <= level; i++) printf("   ");
	printf("North: ");
	viewAll(curr->north, level+1, maxLevel);
	for(int i = 0; i <= level; i++) printf("   ");
	printf("East: ");
	viewAll(curr->east, level+1, maxLevel);
	for(int i = 0; i <= level; i++) printf("   ");
	printf("South: ");
	viewAll(curr->south, level+1, maxLevel);
	for(int i = 0; i <= level; i++) printf("   ");
	printf("West: ");
	viewAll(curr->west, level+1, maxLevel);
}

void netral(struct Node *curr)
{
	if(curr== NULL || curr->dikunjungi == 0)
		return;
	curr->dikunjungi = 0;
	netral(curr->north);
	netral(curr->east);
	netral(curr->south);
	netral(curr->west);
}

void joinEastWest(struct Node *curr1, struct Node *curr2)
{
	curr1->east = curr2;
	curr2->west = curr1;
}

void joinNorthSouth(struct Node *curr1, struct Node *curr2)
{
	curr1->south = curr2;
	curr2->north = curr1;
}

int main()
{
	root = createNode("Central City", 2.1);
	pushNorth(root, "Bekasi", 0.8);
	pushEast(root, "Gojong", 1.3);
	pushSouth(root, "Konoha", 1.3);
	pushWest(root, "Desa Api", 1.3);
	pushEast(root->north, "Desa Banyu", 0.5);
	joinNorthSouth(root->north->east, root->east);
	viewAll(root, 0, 1);
	
	return 0;
}

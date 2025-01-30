#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>


#define MAGENTA 	"\x1b[35m"
#define YELLOW		"\x1b[33m"
#define GREEN 		"\x1b[32m"
#define RED 		"\x1b[31m"
#define RESET 		"\x1b[0m"
#define HASH_SIZE 26


// data value account simpen dalam table hash, hubungin sama USERNAME hash value
// double link list buat naik turun candel,????????

int val, sl = -1 , tp = -1, pos = -1;
bool trade = false;
int reward = 0;


struct node{
	int open, close, highest, lowest;
	node *next, *prev;
}*head = NULL, *tail = NULL;

node* createCan(int open, int close, int highest, int lowest){
	node* newCan =(node *)malloc(sizeof(node));
	newCan->open = open;
	newCan->close = close;
	newCan->highest = highest;
	newCan->lowest = lowest;
	newCan->next = newCan->prev = NULL;
	return newCan;
}

struct account{
	char username[101];
	char email[101];
	char password[101];
	int currency;
};


void pushTail(int open, int close, int highest, int lowest){  // BERBEDA
	node* newCan = createCan(open,close,highest,lowest);
	
	if(head == NULL){
		head = tail = newCan;
	}
	else{
		tail->next = newCan;
		newCan->prev = tail;
		tail = newCan;
	}
}

void printCan(){
	node *curr = head;
	while(curr){
		
		printf("Open: %d, Close: %d, Highest: %d, Lowest: %d\n", curr->open,curr->close,curr->highest,curr->lowest);
		curr = curr->next;
	}
}



void printmap(char username[], int num);

//int main(){
//	pushTail(200,210,240,190);
//	pushTail(140,200,210,140);  // int open, int close, int highest, int lowest
//	pushTail(178,240,258,170);
//	pushTail(240,280,300,200);
//	
//	printmap("Loak", 10000);
//
//}

bool percent(int x){
	if(rand() % 100 > x)return true;
	return false;
}

void newDay(){
	int open = tail->close;
	int close, highest, lowest;
	
	int chance = rand () % 10;
	int num = rand() % 100;
	int num2 = (rand() % 3) * 10;
	
	close = (rand() % 3 ) * 10;
	if( num > 50){
		close *= -1;
	}
	close = open + close;
	if(close < 0) close = 0;
	
	if(close > open){
		if(num < 3){
			highest = close;
			lowest = open;
		}else{
			highest = close + num2;
			lowest = open - num2;
		}
	}else{
		if(num < 3){
			highest = open;
			lowest = close;
		}else{
			highest = open + num2;
			lowest = close - num2;
		}
	}
	if(highest > 330) highest = 330;
	if(lowest < 0) lowest = 0;
	if(lowest > 330) lowest = 0;
	pushTail(open,close,highest,lowest);
}

int valtrue = 0;
void valValid(int val){
	account account;
	if(val < 10 || val > account.currency){
		valtrue = 0;
	}else{
		valtrue = 1;
	}
}

int postrue = 0;
void posValid(int pos){
	if(pos % 10 != 0 || pos < 20 || pos > 330 ){
		postrue = 0;
	}else{
		postrue = 1;
	}
}

int proftrue = 0;

void tpValid(int tp){
	if( tp < pos || tp % 10 != 0 || tp < 10 || tp > 330 ){
		proftrue = 0;
	}else{
		proftrue = 1;
	}
}

int sltrue = 0;
void slValid(int sl){
	if(sl > pos || sl % 10 != 0 || sl < 10 || sl > 330){
		sltrue = 0;
	}else{
		sltrue = 1;
	}
}

int longtrade = 0;


void trdLong(){
	valtrue = 0;
	sltrue = 0;
	postrue = 0;
	proftrue = 0;
	longtrade = 0;
	
	inputval:
	printf("\nEnter value : ");
	scanf("%d", &val);
	valValid(val);
	if(valtrue == 0){
		goto inputval;
	}
	
	inputpos:
	printf("\nEnter pos : ");
	scanf("%d", &pos);
	posValid(pos);
	if(postrue == 0){
		printf("Invalid position\n");
		goto inputpos;
	}
	
	inputpt:
	printf("\nEnter tp : ");
	scanf("%d", &tp);
	tpValid(tp);
	if(proftrue == 0){
		printf("Invalid take profit [Must be higher than position, between 10-330, and mutiple of ten] !");
		goto inputpt;
	}	
	
	inputsl:
	printf("\nEnter sl : ");
	scanf("%d", &sl);
	slValid(sl);
	if(sltrue == 0){
		printf("Invalid stop loss! [Must be higher than postition, between 10 - 330, and mutiple of ten] !");
		goto inputsl;
	}
	longtrade = 1;
}

int shorttrade = 0;
void trdShort(){
	valtrue = 0;
	sltrue = 0;
	postrue = 0;
	proftrue = 0;
	shorttrade = 0;
	
	inputval:
	printf("\nEnter value : ");
	scanf("%d", &val);
	valValid(val);
	if(valtrue == 0){
		goto inputval;
	}
	
	inputpos:
	printf("\nEnter pos : ");
	scanf("%d", &pos);
	posValid(pos);
	if(postrue == 0){
		printf("Invalid position\n");
		goto inputpos;
	}
	
	inputpt:
	printf("\nEnter tp : ");
	scanf("%d", &tp);
	tpValid(tp);
	if(proftrue == 0){
		printf("Invalid take profit [Must be higher than position, between 10-330, and mutiple of ten] !");
		goto inputpt;
	}	
	
	inputsl:
	printf("\nEnter sl : ");
	scanf("%d", &sl);
	slValid(sl);
	if(sltrue == 0){
		printf("Invalid stop loss! [Must be higher than postition, between 10 - 330, and mutiple of ten] !");
		goto inputsl;
	}
	shorttrade = 1;
}

int idx = 0;

void fullscreen(){
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

int counterUser = 1;
int counterEmail = 1;
int counterPass = 1;
int randomcounter = 0;
int logged = 1;



int hashsum(char* username){
	int sum = 0;
    for (int i = 0; username[i] != '\0'; i++) {
        sum += username[i]; 
    }
    return sum % HASH_SIZE;  
}



void encryptedpassword(char *password){  // UTK KETIK BINTANG SAAT INpUT password
	int i = 0;
    int ch;
    while (i < 36) {
        ch = getch();
        if (ch == ' ' || ch == 27) {
            continue;
        } else if (ch == '\b') {
            if (i > 0) {
                printf("\b \b");
                --i;
            } else {
                continue;
            }
        } else if (ch == '\r' || ch == '\t') {
            break;
        } else if (ch == 0 || ch == 224) {
            ch = getch();
            continue;
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int cekinkarakter(const char *str) {
    while (*str) {
        if (!isalnum(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}
void confirm(){
		clearBuffer();
        getchar();
        return;
}

void validusername(char username[]){
	FILE *f = fopen("user.txt","r");
	account account;
	counterUser = 1;
	int length = strlen(username);
    if (length > 20) {
        printf("Username length must be between 1 and 20 characters.\n");
        counterUser = 0;
        confirm();
    }
    if (!cekinkarakter(username)) {
        printf("Username must contain only alphabets and numbers.\n");
        counterUser = 0;
        confirm();
    }
    while (fscanf(f, "%[^#]#%[^#]#%[^#]#%d\n", account.username, account.email, account.password, &account.currency) == 4) {
    	if (strcmp(account.username, username) == 0) {
        	printf("Username must be unique!!");
        	counterUser = 0;
			confirm();
			return;
    	}
	}
	fclose(f);
}

void validationemail(char email[]){
	FILE *f = fopen("user.txt", "r");
	account account;
	counterEmail = 1;
	int letakadd = 0;
	int counteradd = 0;
	int len = strlen(email);
	if(len < 6 || len > 36){
		printf("Email must be between 6 and 36 characters long!");
      	counterEmail = 0;
    	confirm();
    	return;
	}
	for(int i = 0 ; i < len ; i++){
		if(email[i] ==  '@'){
			counteradd++;
			letakadd = i;
		}
		if(email[i] == '#'){
			printf("Email must not contain #");
			counterEmail = 0;
			confirm();
		}
		if(email[i] == ' '){
			printf("Email must not contain space!");
			counterEmail = 0;
			confirm();
		}
	}
	if(counteradd > 1){
		printf("Email must contain only one @ !");
      	counterEmail = 0;
      	confirm();
      	return;
	}
	if (counteradd == 1 && (email[letakadd + 1] < 'A' || email[letakadd + 1] > 'Z' && email[letakadd + 1] < 'a' || email[letakadd + 1] > 'z')) {
    	printf("Email must have domain!");
    	counterEmail = 0;
    	confirm();
	}	
	
	
	if(!((email[0] >= 'A' && email[0] <= 'Z') || (email[0] >= 'a' && email[0] <= 'z'))) {
		printf("The first letter must be alphabet!");
		counterEmail = 0;
		confirm();
	}
	if(strcmp(email + len - 4, ".com") != 0){
		printf("Email must end with .com !\n");
		counterEmail = 0;
		confirm();
	}
	
	while (fscanf(f, "%[^#]#%[^#]#%[^#]#%d\n", account.username, account.email, account.password, &account.currency) == 4) {
    	if (strcmp(account.email, email) == 0){
    		counterEmail = 0;
      	  	printf("Email must be unique!!");
			confirm();
    		}
	}
	fclose(f);
}

void validationpassword(char password[]){
	FILE *f = fopen("user.txt","r");
	account account;
	counterPass = 1;
	int alphabetcount = 0;
	int numcount = 0;
	int len = strlen(password);
	if(len < 8 || len > 36){
		printf("\nPassword must be between 8 - 36 characters!");
		counterPass = 0;
		confirm();
		return;
	}
	
	for (int i = 0; i < len; i++) {
        if ((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z')) {
            alphabetcount++;
        } else if (password[i] >= '0' && password[i] <= '9') {
            numcount++;
        }else {
            	printf("\nPassword must not contain symbols!\n");
            	counterPass = 0;
            	confirm();
            	return;
        }
    }
    
    fclose(f);
}

void registeraccount(){
	account account;
	FILE *f = fopen("user.txt", "a");
	account.currency= 10000;
	
// --------------------------- 
	user:
	system("cls");
	printf("Username (0 to Exit): ");
	scanf("%s", account.username);
	if (strcmp(account.username, "0") == 0) {
   		return; 
	}
	
	validusername(account.username);
	if(counterUser == 0){
		goto user;
	}
//  -------------------- email

	email:
	system("cls");
	printf("Email (0 to Exit): ");
	scanf("%s", account.email);
	if(strcmp(account.email,"0") == 0 ){
		return;
	}
	validationemail(account.email);
	if(counterEmail == 0){
		goto email;
	}
	
// --------------------------------
	pass:
	system("cls");
	printf("Password (0 to Exit): ");
	encryptedpassword(account.password);
	if(strcmp(account.password,"0") == 0 ){
		return;
	}
	validationpassword(account.password);
	if(counterPass == 0){
		goto pass;
	}
	fprintf(f,"%s#%s#%s#%d\n", account.username, account.email, account.password, account.currency);
	fclose(f);
}


// History
struct queue{
	int val1 , pos1, tp1, sl1, reward1;
	int priority;
	struct queue *next1, *prev1;
}*head1 = NULL, *tail1 =NULL;


void pushAdv(int val1, int pos1, int tp1, int reward1,int sl1, int priority){
	queue *curr = (queue *)malloc(sizeof(queue));
	curr->pos1 = pos1;
	curr->tp1 = tp1;
	curr->reward1 = reward1;
	curr->sl1 = sl1;
	 curr->priority = priority;
	 
	if(head1 == NULL){
		head1 = tail1 = curr;
		head1->next1 = NULL;
		head1->prev1 = NULL;
	}else{
		if(priority < head1->priority){
			curr->next1 = head1;
			head1->prev1 = curr;
			head1 = curr;
			head1->prev1 = NULL;
		}else if(priority >= tail1->priority){
			tail1->next1 = curr;
			curr->prev1 = tail1;
			tail1=curr;
			tail1->next1 = NULL;
		}else{
			queue *temp = head1;
			while(temp->next1->priority <= priority){
				temp = temp->next1;
			}
			curr->next1 = temp->next1;
			temp->next1->prev1 = curr;
			temp->next1 = curr;
			curr->prev1 = temp;
		}
	}
}

//queue* compare(int reward){
//	queue *curr = head;
//	if(head1 == NULL){
//		head1->reward1;
//	}
//	    if(curr->prev1->reward1 > reward){
//	    	
//		}else{
//			c
//		}
//}

void historyshow(char username[]){
	system("cls");
	account account;
	int i = 1;
	if(!head){
		printf("No trade history...\n");
	}else{
		printf("Username: %s\n", username);
		queue* curr =head1;
		while(curr){  // random value??
			printf("No.%d\nValue\t\t:%d\nPosition\t:%d\nTake Profit\t:%d\nStop Loss\t:%d\nReward\t\t:%d\n", i, curr->val1, curr->pos1, curr->tp1, curr->sl1, curr->reward1);
			curr = curr->next1;
			i++;
		}
	}
	printf("Press enter to continue...\n");
	getch();
}









void guide(){
		system("cls");
	printf("What Is Forex?\n");
	printf("'Forex', short for foreign exchange, is a global decentralized marketplace for trading currencies.\n");
	printf("In forex trading, participants buy one currency by selling another currency simultaneously, with the aim of profiting from fluctuat ions in exchange rates. It is one of the largest and most liquid financial markets in the world, operating 24 hours a day, five days a week.\n");
	
	printf("\n");
	
	printf("What Is Candle Stick?\n");
	printf("'Canlde Stick' in charts are a type of financial chart used to represent price movements in trading markets, including forex.\n"); 
	printf("They visually display the open, high, low, and close prices for a specific period.\n");
	printf("If the close price is higher than the open price, the candle color will be green.\n");
	printf("then if the close price is less than the open price, the candle color will be red.\n");
	printf("shadow or tick is the highest and the lowest price of a candle.\n");
	
	printf("\n");
	
	printf("What Is Position?\n");
	printf("'Position'' in forex trading refers to where we want to enter the market at certain price point\n");
	
	printf("\n");
	
	printf("What Is Long?\n");
	printf("'Long' in forex trading refers to a trading position where a trader buys a currency pair\nwith the expectation that its value will increase over time.\n");
	
	printf("\n");
	
	printf("What Is Short?\n");
	printf("'Short' in forex trading refers to a trading position where a trader sells a currency pair\nwith the expectation that its value will decrease over time.\n");
	
	printf("\n");
	
	printf("What is Take Profit?\n");
	printf("'Take Profit' in forex trading refers to where we will leave the market at the specified price point\nour position will automatically closed after the market price hit our take profit price.\n");
	
	printf("\n");
	
	printf("What Is Stop Loss?\n");
	printf("'Stop Loss' in forex trading refers to where we will leave the market at the specified price point.\nit's used to make sure that we don't loss all of our money and many more\nsame like take profit, our position will automatically closed after the market price hit our take profit price\n");
	
	printf("\n");
	
	printf("Press Enter To Continue...\n");
	confirm();
	
}

void printmap(char username[], int currency) {
	pushTail(200,210,240,190);
	pushTail(140,200,210,140);  // int open, int close, int highest, int lowest
	pushTail(178,240,258,170);
	pushTail(240,280,300,200);
	int choice;
	account account;
	do{
 		 system("cls");
 		 int xLen = 140, yLen = 40;
  
 		 int yGraph = yLen - 5;
  		// grafik
  		int num = 330;
  		for(int y = 0 ; y <= yGraph; y++){
  				int open,close,highest,lowest;
  				int upCandle, dowCandle;
  				node* curr = head;
  				
  				int i = 0;
  				while (i < idx){
  					curr = curr->next;
  					i++;
				  }
  				
				for(int x = 0 ; x <= xLen ; x++){
					if(curr){
						open = curr->open;
						close = curr->close;
						highest = curr->highest;
						lowest = curr->lowest;
					}else{
						open = close = highest = lowest = -1;
					}
					
					if(open < close){
						upCandle = close;
						dowCandle = open;
					}else{
						upCandle = open;
						dowCandle = close;
					}
					
					int HiCandle, LoCandle;
					if(tail->open > tail->close){
						HiCandle = tail->open;
						LoCandle = tail->close;
					}else{
						HiCandle = tail->close;
						LoCandle = tail->open;
					}
					if(pos <= HiCandle && pos >= LoCandle && !trade){
						trade = true;
					}
					
					if(trade && longtrade == 1){
						if(tp <= HiCandle && tp >= LoCandle){
							reward = (val *abs(close - pos)) / 100;
							currency += reward;
							trade = false;
							longtrade = 0;
							tp = sl = pos = val = -1;
							pushAdv(val,pos,tp,reward,sl,1);
						}else if(sl <= HiCandle && sl >= LoCandle && longtrade == 1){
							reward = (val *abs(close - pos)) / 100;
							currency -= reward;
							trade = false;
							longtrade = 0;
							tp = sl = pos = val = -1;
							pushAdv(val,pos,tp,-1*reward,sl,1);

						}
					}
					
					if(trade && shorttrade == 1){
						if(tp <= HiCandle && tp >= LoCandle){
							reward = (val *abs(close - pos)) / 100;
							currency -= reward;
							trade = false;
							longtrade = 0;
							tp = sl = pos = val = -1; 
							pushAdv(val,pos,tp,reward,sl,1);
						}else if(sl <= HiCandle && sl >= LoCandle && shorttrade){
							reward = (val *abs(close - pos)) / 100;
							currency += reward;
							trade = false;
							longtrade = 0;
							tp = sl = pos = val = -1;
							pushAdv(val,pos,tp,reward,sl,1);
		
						}
					}
  					if (y == 0 && x == 0){
  						printf("%c", 201);
					}else if(y == 0 && x == xLen){
						printf("%c", 187);
					}else if(y == yGraph && x == 0){
						printf("%c", 204);		
					}else if( x== xLen && y == yGraph){
						printf("%c", 185);
					}else if(x == 54 && y == yGraph || x == 119 && y == yGraph){
						printf("%c", 203 );
					}else if(y == 0 && x == xLen - 6){
						printf("%c", 203 );
					}else if(y == yGraph && x == xLen - 6){
						printf("%c", 202 );
					}else if(y == 0 || y == yGraph){
						printf("%c", 205 );
					} else if(x == 0 || x== xLen){
						printf("%c", 186);
					} else if(x >= xLen - 6){
						if( x == xLen - 6){
							printf("%c" , 186 );
						} else if( x== xLen - 4){
							printf("%-3d", num);
							num -= 10;
						}else if( x == xLen - 5 || x == xLen - 3){
							printf(" ");
						}
					}
					else{
						if(num >= lowest && num <= highest && x > 0){
							if(curr->prev && highest > curr->prev->highest){
								printf(GREEN);
							}else{
								printf(RED);
							}
							if(num <= upCandle && num >= dowCandle){
								printf("%c", 219);
							}else{
								printf("%c", 179);
							}
							printf(RESET);
							
						}else{
							if(num == pos){
								printf(YELLOW);
							}else if(num == sl){
								printf(RED);
							}else if(num == tp){
								printf(GREEN);
							}
							printf("-");
							printf(RESET);
						}
					}
					if(curr && x>0)curr = curr->next;
				}
			 printf("\n");
			}
			printf("%cWelcome to METAFI, %-20s              %c                                                                %c                    %c\n", 186, username, 186, 186, 186);
			printf("%c1. New day    3. Next   5.Short                      %c                                                                %c   $%-10d      %c\n", 186, 186, 186, currency, 186);
			printf("%c2. Previous   4. Long   6.Logout                     %c                                                                %c                    %c\n", 186, 186, 186, 186);
			for(int x = 0; x<=xLen;x++){
				if(x == 0){
					printf("%c", 200);
				}else if( x == 54 || x == 119){
					printf("%c", 202);
				}else if (x == xLen){
					printf("%c", 188 );
				}
				else{
					printf("%c", 205);
				}
			}
			printf("\n");
			scanf("%d", &choice);
			switch(choice){
				case 1:
					newDay();
					break;
				case 2:
					idx--;
					break;
				case 3:
					idx++;
					break;
				case 4:
					trdLong();
					break;
				case 5:
					trdShort();
					break;
				case 6:
					return;
					
			}
	} while(choice != 6);
}



void usermenu(char username[], int balance){
	int choice2;
	logged = 1;
	account account;
	do{
			system("cls");
		printf("MetaFi - User's Menu\n");
		printf("--------------------\n");
		printf("1. Start Trade\n");
		printf("2. Trade History\n");
		printf("3. Guide\n");
		printf("4. Log out\n");
		printf(">>>");
		scanf("%d", &choice2);
		switch(choice2){
			case 1:
				printmap(username, balance);
				break;
			case 2:
				historyshow(username);
				break;
			case 3:
				guide();
				break;
			case 4:
				logged = 0;
				return;
		}
	}while(choice2 != 4);
	
}

void ispwTrue(char email[], char password[]){
	FILE* f = fopen("user.txt", "r");
	account account;
	randomcounter = 0;
	while (fscanf(f, "%[^#]#%[^#]#%[^#]#%d\n", account.username, account.email, account.password, &account.currency) == 4) {
    	if (strcmp(account.email, email) == 0 && strcmp(account.password, password) == 0){
    		randomcounter = 1;
    		usermenu(account.username, account.currency);
    		} else{
    			randomcounter = 0;
			}
	}
}

void loginaccount(){
	char email[101];
	char password[101];
	account account;
	retry:
	if(logged == 0){
		printf("LOASLOASLAO\n");
		printf("%d", logged);
		return;
	}
	
	printf("%d", logged);
	system("cls");
	printf("Email (0 to exit): ");
	scanf("%s", email);
	if(strcmp(email,"0") == 0 ){
		return;
	}
	
	system("cls");
	printf("Password (0 to exit): ");
	encryptedpassword(password);
	if(strcmp(password,"0") == 0 ){
		return;
	}
	ispwTrue(email, password);
	if(randomcounter == 1){
		usermenu(account.username, account.currency);
	}else{
		printf("\nInvalid Email and Password!");
		goto retry;
	}
	
}



void exitmsg(){
	system("cls");
	printf("\n\n\n\n\n\n");
	printf(MAGENTA "\t\tMeta Fi\n\n" RESET);
	printf(GREEN "\t\tCreated with 24-2 Squad\n\n" RESET);
	printf(RESET "\t\tThank you 24-2 !\n\n");
	
		printf("                                                       ......................\n");
    printf("                                                 ............:::::::::::...........\n");
    printf("                                              .......::--==================---::.......\n");
    printf("                                          .....:::--==+++*####%%%%%%%%%%%%%%%%####*++====--::.....\n"); 
    printf("                                        ....::--==+*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%#*+==---:.....\n");
    printf("                                      ...::--=+*##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##*=---:....\n");
    printf("                                    ....:-=+*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##*=---:....\n");
    printf("                                  ....:-=*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%%%%%%%%%%%%%%%#+=--:....\n");
    printf("                                ....:-=*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%####%%%%##%%%%%%%%%%%%%%%%%%%%%%%%#+--::...\n");
    printf("                               ..:.:-+#%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%%%###%%#*+**%%#**####%%%%%%%%%%%%%%%%%%%%#+--:...\n");
    printf("                              ..:::=*%%%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%**#%%###%%%%#**#%%*+=+=#*++**++#%%%%#%%%%%%%%%%%%%%%%*-:::...\n");
    printf("                             ..:::+#%%%%%%%%%%%%%%%%%%%%%%%%########++#%%***#**+++#+=---++--==-=*%%%%%%%%%%%%%%%%%%%%%%%%%%=:::...\n");
    printf("                            ..::-*#%%%%%%%%%%%%%%%%%%%%%%%%%%*+**+*##==+*===*=+-=-+--:::=-:::-::*%%%%%%%%%%%%%%%%%%%%%%%%%%#+:::..\n");
    printf("                           ..:::+#%%#%%%%%%%%%%%%%%%%%%%%%%#+==+==++--=+:--=--:::-:...... ..:-=*%%%%%%%%%%%%%%%%%%%%%%%%%%%%#+:-:..\n");
    printf("                           .:::+#%%%%%%%%%%%%%%%%%%%%%%%%%%#*---=---=:::-.:.:.... ::--=+**#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#=:-...\n");
    printf("                          ..:.=#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#+::::...:   ..:-=+++*#%%%%###%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*-:-..\n");
    printf("                          .:::*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%*-...:--=+*##%%%%%%%%%%%%#++##%%#**%%%%%%%%%%%%%%%%%%###%%%%%%#%%%%%%%%%%%%%%%%%%%%#+:-:..\n");
    printf("                         ..:.=#%%%%%%%%%%%%%%%%%%%%%%#%%%%%%*::+***#%%%%%%###%%%%%%%%%%*==+*#+++%%###%%%%%%%%%%**#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*-:-..\n");
    printf("                         ..:.+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+-=*+=+*###**#%%%%%%%%%%*-:==+===#*++%%####++*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*-:-..\n");
    printf("                         ..::+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*--==-==**#++*####%%+..::-:::+==-=:-=*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#=:-:.\n");
    printf("                         ...:+###############%%*:.:-:--+=+==*#**#%%*=--.. ..-:::+==--+#%%###############%%=:::.\n");
    printf("                         ...:+#################+..:..:--=:-=+==*#**#####*+=-:.:.:.:-=################*=-::.\n");
    printf("                         ...:=###################=-.  ..:..:-:-=+=+*###########*-.+###############*=-:..\n");
    printf("                          ::.-+*######################*+=-:.....:-:-+***#############*-.+#############+:-:..\n");
    printf("                          .:.:-*####################***#####*+=--:.=+++*****#***#****=-+#############=--:..\n");
    printf("                           ..:-=+*****#************++************++===**+=+*+++*++==-:+*********#**+--:..\n");
    printf("                           .:.:-=*****#@@#******+++*===+===+==---+--:::--:::-:::-.:...+*********#@#=--:..\n");
    printf("                            .:.--=+***%%@@%%*****+===+---=---=--:::-::...::.... . ..:-+**********#%%%%+=-:..\n");
    printf("                             .:.--+*#%%%%@@@#****+----:::-.:.:.:...:.   ..::--==++++++++***#%%****##+==:..\n");
    printf("                              ...-=+#@@@@@%%%%*+*+:.::....   ...::--===+++++++++++++++*++#@@%%+#%%*===:..\n");
    printf("                               ...:==#%%@@@@@*+%%*  .:::--==+++++++++++++++++++++++++*@%%++%%@@%%##+==-..\n");
    printf("                                 ..:-=+%%@@@#+%%@@++++++++++++++*#++++++++++++++++++++++%%@%%#%%%%@@%%+-==-..\n");
    printf("                                  ...:-=+%%@@@@@@%%++++++++++++*%%@#++++++++++@%%+++++++*%%@@@@@@%%#+==-..\n");
    printf("                                    ..::-=+#%%@@@@%%+=+*@*====+#@@%%*=======+%%@@*+==*@@@@%%%%*+==-..\n");
    printf("                                      ..::--=+***#@@@*==*@@@@@@%%#%%+==*%%%%%%#*+=====-*@@@%%%%%%*+===-:..\n");
    printf("                                        ...::--=+#%%@%%==+@@%%+==+%%@@@@*+++*#@@@%%#+==+@@@%%*+===-::..\n");
    printf("                                          ....:-----+*#%%%%***%%@@@@@%%@@*==+%%%%%%#*+====--::..\n");
    printf("                                             ....::-------=++********+=====-------::..\n");
    printf("                                                  ....::---======--=====-----::..\n");
    printf("                                                        ........::::........\n\n");
    
    printf("                                      \"Inspired by passion, driven by purpose, together we\n");
    printf("                                            shatter limits and redefine boundaries.\"\n");
   
    exit(0);  
}

void mainmenu(){
	fullscreen();
	int choice = 1;
	account account;
	do{
		system("cls");

		puts( " _____ ______   _______  _________  ________  ________ ___" );
        puts("|\\   _ \\  _   \\|\\  ___ \\|\\___   ___\\\\   __  \\|\\  _____\\\\  \\");
        puts("\\ \\  \\\\\\__\\ \\  \\ \\   __/\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\__/\\ \\  \\");
        puts(" \\ \\  \\\\|__| \\  \\ \\  \\_|/__  \\ \\  \\ \\ \\   __  \\ \\   __\\\\ \\  \\");
        puts("  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\  \\ \\  \\ \\ \\  \\ \\  \\ \\  \\_| \\ \\  \\");
        puts("   \\ \\__\\    \\ \\__\\ \\_______\\  \\ \\__\\ \\ \\__\\ \\__\\ \\__\\   \\ \\__\\");
        puts("    \\|__|     \\|__|\\|_______|   \\|__|  \\|__|\\|__|\\|__|    \\|__|");
        printf("\n\n\n\n");
		printf("\t1. Log in to Trade\n");
		printf("\t2. Register Account\n");
		printf("\t3. Exit application\n");
		printf("\t>>>>");
		scanf("%d", &choice);
	
		switch(choice){
			case 1:
				logged = 1;
				loginaccount();
				break;
			case 2:
				registeraccount();
				break;
			case 3:
				exitmsg();
				break;
		}
			
	} while(choice != 3);
	while(1){

	}
}


int main(){
	mainmenu();	
}

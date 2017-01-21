#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"
#define GRN   "\x1B[32m"
int level = 0;
int breakpoint = 0;
float wpm = 0;
float cpm = 0;
int count = 0;
struct node {
	char word[50] ;
	struct node * next;
};
struct player {
	float point[3] = { 0 };
	char name[50]=" ";
	int lastlevel; 
};
struct node* create (char *s)
{
	struct node *tmp;
	int i = 0;
	tmp = (struct node*)malloc(sizeof(struct node));
	while (s[i] != '\0')
	{
		tmp->word[i] = s[i];
		i++;
	}
	tmp->word[i] = '\0';
	tmp->next = NULL;
	return tmp;
}
void add_end (struct node *list, struct node* newnode) {
	struct node *current;
	int i = 0;
	int j = 0;
		for (current = list; current->next != NULL; current = current->next);
			current->next = newnode;
	newnode->next = NULL;
}
void printnodes (struct node * str)
{ 
	struct node *cur = str;
	while (cur != NULL) {
		printf("%s\n", cur->word);
		cur = cur->next;
	}
}
struct node* fill (FILE * ptr)
{
	struct node * str=NULL;
	struct node*cur=NULL;
	char i;
    char s[50] = {};
	int k = 0;
	rewind(ptr);
	i = fgetc(ptr);
	str = create(s);
	int node = 0;
	while (i != EOF) {

		while (i != ' ' && i != '\n' && i != EOF)
		{
	
			s[k] = i;
            k++;
			i = fgetc(ptr);

		}
	  
		cur = create(s);
		add_end(str, cur);
		int j = 0;
		while (s[j] != '\0') {
			s[j] = 0;
			j++;
		}
		k = 0;
		i = fgetc(ptr);
		node++;
	}
	str = str->next;
	printnodes(str);
	return str;
}
void deletenode (struct node* cur)
{
	struct node*temp = cur->next;
	cur->next = cur->next->next;
	free(temp);
}

float play (struct node* str)
{
	int nomove = 0;
	int  sum = 0;
	int i = 0;
	int t = 0;
	system("cls");
	int words = strlen(str->word);
	int mistakes = 0;
	char k;
	printf("%s\n", str->word);
	clock_t start = clock();
		while (str->word[i] != '\0') {
			while (1) {
				clock_t first = clock();
					if (kbhit()) {
						//printf("Hit\n");
						k = getch();
							if (k == str->word[i]) {
								printf(GRN "%c" RESET, k);
								printf("\n");
								str->word[i] = toupper(str->word[i]);
								printf("%s\n", str->word);
								i++;
							}

							else if (k == 'P') {
							char c = 0;
							clock_t start1 = clock();
								while (c != 'R') {
									printf(RED "PAUSE\n" RESET "You can resume by pressing R\n");
									c = getch();
								}
							clock_t end1 = clock();
							t = t + (end1 - start1);
							printf(GRN "RESUME\n" RESET);
							printf("%s\n", str->word);

						}
							else if (k == 'Q') {
								printf(RED "%c\n" RESET, k);
								printf("Exiting :( \n");
								printf("Do You want to save the current state?[Y/N]\n");
									while (1) {
										char c = getch();
											if (c == 'y' || c == 'Y') {
												return -1;
											}
											else if (c == 'N' || c == 'n')
											exit(0);
											else
												printf("You must enter y,Y or n,N\nOther characters aren't acceptable!\n");
									}

							}
					else {
						mistakes++;
						printf(RED "%c" RESET, k);
						printf("\n%s\n", str->word);
					}
						nomove = 0;
						sum = 0;
						break;
					}
				clock_t second = clock();
				sum = sum + (second - first);
					if (sum > 2000) {
						nomove++;
						printf("\n%s\n", str->word);
						sum = 0;
					}
					if (nomove == 5)
						return -1;
			}
		}
	clock_t end = clock();
	cpm = 60 * words / ((end - start - t) / 1000.0);
	wpm = 60 / ((end - start - t) / 1000.0);
	return (3 * words - mistakes) / ((end - start - t) / 1000.0);
}

	
int checklevel ()
{
	FILE *ptr;
	char s[100] = "level-";
	char c[200] = {};
	char format[] = ".txt";
	int i = 1;
	int k = 0;
	char j = 0;
		while (1) {
			itoa(i, c, 10);
			strcat(s, c);
			strcat(s, format);
			ptr = fopen(s, "r");
			strcpy(s, "level-");
				if (ptr == NULL)
					break;
			fclose(ptr);
			i++;
		}
	return i - 1;
}
void printnode (struct node * str) {
	printf("%s\n", str->word);
}
int toUpperCase(char c) {

	return c - 32;
}
float openlevel (int a)
{
	float wordp = 0;
	float carp = 0;
	time_t t = time(NULL);
	struct node* str, *cur, *prev;
	srand(t);
	int random;
	clock_t start = clock();
	FILE *ptr;
	int words;
	char s[100] = "level-";
	char c[200] = {};
	char d[50];
	char format[] = ".txt";
	system("cls");
	itoa(a, c, 10);
	strcat(s, c);
	strcat(s, format);
	ptr = fopen(s, "r");
	if (ptr == NULL) {
		printf("Problem with levels Please rerun the game\n");
		exit(0);
	}
	count++;
	str = fill(ptr);
	cur = str;
	char i=0;
	int inc = 0;
	int num = 0;
	float time = 0;
	float check;
	int played = 0;
		while (cur != NULL) {
			num++;
			cur = cur->next;
		}
	cur = str;
	for (int j = num; j > 0; j--) {
		random = (rand() % j) + 1;
		for (int k = 0; k < random - 1; k++) {
			prev = cur;
			cur = cur->next;
			
		}
		check = play(cur);
		if (check == -1) {
			breakpoint = 1;
			if (played == 0)
				{
					cpm = 0;
					wpm = 0;
					return 0;
			    }
				else
				{
					cpm = carp / played;
					wpm = wordp / played;
					return time / played;
				}
		}
		wordp += wpm;
		carp += cpm;
		time = time + check;
		played++;
			if (random == j) {
				free(prev->next);
				prev->next = NULL;
			}
			else if (random == 1) {
				struct node *temp = str;
				str = str->next;
				free(temp);
			}
			else 
				deletenode(prev);
		cur = str;
		prev = str;
	}

	free(str);
	fclose(ptr);
	wpm = wordp / num;
	cpm = carp / num;
	return time / num;
	
}
int checkfinish (int *p, int n)
{
	for (int i = 0; i < n; i++) {
			if (p[i] == 0)
				return 0;
		}
	return 1;
}
float resumegame (int n)
{
	float points = 0;
	int f = 1;
	float temp = 0;
	float temp2 = 0;
		while (1) {

				if (n > checklevel() || n < 0) {
					printf(RED "This level is not available\n" RESET);
					exit(0);
				}
			level = n;
			points = points + openlevel(n);
			temp2 = temp2 + cpm;
			temp = temp + wpm;
				if (n == checklevel() || breakpoint == 1) {
					printf(GRN "The game finished\n" RESET);
					return points;
				}
				
			n = n + 1;
			system("cls");
			printf("Do you want to play next level?[Y/N]\n");
				while (1) {
					char c = getch();
						if (c == 'Y' || c == 'y') {
							f = 0;
							break;
						}
						if (c == 'N' || c == 'n') {
							printf(RED "Saving current status\n" RESET);
							f = 1;
							break;
						}
						else
							printf(RED "You must enter y,Y or n,N\nOther characters aren't acceptable!\n" RESET);
				}
				
					if (f == 1)
						break;
					
		}
		cpm = temp2 / count;
		wpm = temp / count;
		
	return points;
}
float  newgame ()
{
	int n,f=1;
	system("cls");
	printf("%d Levels Loaded\n", checklevel());
	float points = 0.0;
	printf("Enter the level You Want:\n");
	scanf("%d", &n);
	float temp = 0;
	while (1) {
			if (n > checklevel() || n < 0) {
				printf(RED "This level is not available\n" RESET);
				exit(0);
			}
		level = n;
		//printf("%d\n", level);
		//getch();
		points = points + openlevel(n);
     	temp = temp + wpm;
			if (n == checklevel() || breakpoint==1) {
				printf(GRN "The game finished\n" RESET);
				return points;
			}
		n = n + 1;
		system("cls");
		printf("Do you want to play next level?[Y/N]\n");
			while (1) {
				char c = getch();
					if (c == 'Y' || c == 'y') {
						f = 0;
						break;
					}
					if (c == 'N' || c == 'n') {
						printf(RED "Saving current status\n" RESET);
						f = 1;
						break;
					}
					else
						printf(RED "You must enter y,Y or n,N\nOther characters aren't acceptable!\n" RESET);
			}
			if (f == 1)
				break;
	}
	wpm = temp / count;
	return points;
}


void showtop(FILE *ptr,int mode)
{
	system("cls");
	struct player *temp, t;
	char name[50];
	fseek(ptr, 0, SEEK_END);
	float point = 0;
	int a = ftell(ptr);
	
	rewind(ptr);
	int i = 0;
	
		while (ftell(ptr) != a) {
			fread(&t, 1, sizeof(struct player), ptr);
			i++;
		}
	temp = (struct player*)malloc(i * sizeof(struct player));
	rewind(ptr);
	i = 0;
		while (ftell(ptr) != a) {
			fread(&t, 1, sizeof(struct player), ptr);
			temp[i] = t;
			i++;
		}
		for (int j = 0; j < i; j++) {
			for (int k = 0 ; k < i; k++) {
					if (temp[k].point[mode] < temp[j].point[mode]) {
						struct player tmp;
						tmp = temp[j];
						temp[j] = temp[k];
						temp[k] = tmp;
					}
			}
		}
	if (i < 10) {
		for (int j = 0; j < i; j++) {
				printf(GRN "%d.%s" RESET, j+1, temp[j].name);
					for (int s = 0; s < 20-strlen(temp[j].name); s++)
						printf(" ");
				printf(RED "%0.2f\n" RESET, temp[j].point[mode]);
		}

	}
	else 
		for (int j = 0; j < 10; j++) {
			printf(GRN "%d.%s" RESET, j + 1, temp[j].name);
				for (int s = 0; s < 20 - strlen(temp[j].name); s++)
					printf(" ");
			printf(RED "%0.2f\n" RESET, temp[j].point[mode]);
		}
	fclose(ptr);
}
		
int main ()
{
	int mode = 0;
	struct player temp;
	char name[50];
	printf("Enter Your name:\n");
	scanf("%s", name);
	FILE *ptr=fopen("players.bin", "rb+");
	system("cls");
	printf("Choose how to calculate the points \n");
	printf("[1]Default\n[2]WPM(Words per minute)\n[3]CPM(Characters per minute)\n");
	scanf("%d", &mode);
	mode--;
	system("cls");
		if (ptr == NULL) {
			printf("Creating new file\n");
			ptr = fopen("players.bin", "wb+");
			strcpy(temp.name, name);
			printf("Hello %s,You are a new player\n[1]Play new game\n[2]Show top players\n[3]exit\n", name);
			char c = getch();
			if (c == 49) {
				float k = newgame();
				temp.point[0] = k;
				temp.lastlevel = level;
				temp.point[1] = wpm;
				temp.point[2] = cpm;
				if (mode==0)
				printf("Your point is %0.2f\n", k);
				else if (mode==1)
					printf("Your point is %0.2f\n", wpm);
				else if (mode == 2)
					printf("Your point is %0.2f\n", cpm);
				fseek(ptr, 0, SEEK_END);
				fwrite(&temp, 1, sizeof(struct player), ptr);
				fclose(ptr);
			}
			else if (c == 50)
				showtop(ptr,mode);
			return 0;
		}
		
	fseek(ptr, 0, SEEK_END);
	int a = ftell(ptr);
	a = ftell(ptr);
	rewind(ptr);
	int flag = 0;
		while (ftell(ptr)!= a) {
			fread(&temp,1, sizeof(struct player), ptr);
		//	printf("%s\n", temp.name);
				if (strcmp(temp.name, name) == 0) {
					printf("Hello %s\n",name);
					flag = 1;
					break;
				}
		}
		if (flag == 0) {
			strcpy(temp.name, name);
			printf("You are a new player\n[1]Play new game\n[2]Show top players\n[3]exit\n");
			char c = getch();
			if (c == 49) {
				float k = newgame();
				temp.point[0] = k;
				temp.point[1] = wpm;
				temp.point[2] = cpm;
				temp.lastlevel = level;
				if (mode == 0)
					printf("Your point is %0.2f\n", k);
				else if (mode == 1)
					printf("Your point is %0.2f\n", wpm);
				else if (mode == 2)
					printf("Your point is %0.2f\n", cpm);
			//	printf("%d", level);
				fseek(ptr, 0, SEEK_END);
				fwrite(&temp, 1, sizeof(struct player), ptr);
				fclose(ptr);
			}
			else if (c == 50)
				showtop(ptr,mode);
		}
		else if (flag == 1) {
			printf("[1]play New game\n[2]Resume game\n[3]Show top players\n[4]exit\n");
			if (mode==0)
				printf("Your last point was %0.2f\n", temp.point[0]);
			else if (mode==1)
				printf("Your last point was %0.2f\n", temp.point[1]);
			else if (mode == 2)
				printf("Your last point was %0.2f\n", temp.point[2]);
			printf("Previous level : %d\n", temp.lastlevel);
			char c = getch();
			if (c == 49) {
				float k = newgame();
				
				rewind(ptr);
					while (ftell(ptr) != a) {
						fread(&temp, 1, sizeof(struct player), ptr);
					//	printf("%s\n", temp.name);
							if (strcmp(temp.name, name) == 0) {
						//		printf("found the name\n");
								break;
							}
					}
					if (mode == 0)
						printf("Your point is %0.2f\n", k);
					else if (mode == 1)
						printf("Your point is %0.2f\n", wpm);
					else if (mode == 2)
						printf("Your point is %0.2f\n", cpm);
				
				temp.point[0] = k;
				temp.point[1] = wpm;
				temp.point[2] = cpm;
				temp.lastlevel = level;
				fseek(ptr, -1 * sizeof(struct player), SEEK_CUR);
				fwrite(&temp, 1, sizeof(struct player), ptr);
				fclose(ptr);
			}
			else if (c == 50)
			{
				//printf("Last level was %d", temp.lastlevel);
				float s = resumegame(temp.lastlevel);
				
				rewind(ptr);
					while (ftell(ptr) != a) {
						fread(&temp, 1, sizeof(struct player), ptr);
						//	printf("%s\n", temp.name);
							if (strcmp(temp.name, name) == 0) {
							//	printf("found the name\n");
								break;
							}
					}
					if (mode == 0)
						printf("Your point is %0.2f\n", s);
					else if (mode == 1)
						printf("Your point is %0.2f\n", wpm);
					else if (mode == 2)
						printf("Your point is %0.2f\n", cpm);
				temp.point[0] = s;
				temp.lastlevel = level;
				temp.point[1] = wpm;
				temp.point[2] = cpm;
				fseek(ptr, -1 * sizeof(struct player), SEEK_CUR);
				fwrite(&temp, 1, sizeof(struct player), ptr);
				fclose(ptr);
			}
			else if (c == 51) 
				showtop(ptr,mode);
			else return 0;
		}
	return 0;
}
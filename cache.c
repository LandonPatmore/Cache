#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Prototypes
void freeMem(void); //to free memory
void userInput(int S, int E, int B, int m); //for user input
void setUp(void); //set up the cache

//struct for the Line
typedef struct Line{
    char valid;
    long long tag;

    int LFUCounter;
    int LRUCounter;
} Line;

//globals
Line **cache;
int hits = 0;
int misses = 0;
int cycles = 0;

int getSetIndex(long long a, int S, int b){
    return (a >> b) & (S - 1);
}

long long getTag(long long a, int t, int s, int b){
    return (a >> (s + b)) & ((1 << t) - 1);
}



void freeMem(void){
	free(cache);
}

void setUp(void){
    int S, E, B, m, h, mp;
    char policy[3];

    scanf("%d %d %d %d %s %d %d", &S, &E, &B, &m, policy, &h, &m);

    int s = (int)log2f((float)S);
    int b = (int)log2f((float)B);
    int t = m - (s + b);

    cache = (Line **)calloc(S, sizeof(Line));
    for (int i = 0; i < S; i++){
        cache[i] = calloc(E, sizeof(Line));
        for (int j = 0; j < E; j++){
            cache[i][j].valid = '0';
        }
    }

    userInput(S, E, B, m);
}

void userInput(int S, int E, int B, int m){
    int s = (int)log2f((float)S);
    int b = (int)log2f((float)B);
    int t = m - (s + b);

    long long input;

    while(input != -1){
        scanf("%10llx", &input);

        if(input == -1){
            freeMem();
        }

        int check = 0;
        int setIndex = getSetIndex(input, S, b);
        long long setTag = getTag(input, t, s, b);

        Line *cLine = cache[setIndex];

        if(E == 1){ //direct mapped cache
            if((cLine->valid == '0') || (cLine->valid == '1' && cLine->tag != setTag)){
                printf("%10llx M <--- X\n", input);
                cLine->valid = '1';
                cLine->tag = setTag;
            } else {
                printf("%10llx H\n", input);
            }
        } else { //set associative and fully associative
            for(int i = 0; i < E; i++){
                if(cLine[i].valid == '0'){
                    printf("%10llx M ASS\n", input);
                    cLine[i].valid = '1';
                    cLine[i].tag = setTag;
                    break;
                } else if(cLine[i].tag != setTag) {
                    printf("%10llx HM ASS\n", input);
                } else {
                    printf("%10llx H ASS\n", input);
                    break;
                }
            }
        }

    }
}

int main(void){
    setUp();
    return 0;
}
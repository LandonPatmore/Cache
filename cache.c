#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// struct for the Line
typedef struct Line{
    char valid;
    long long tag;
    int LFUCounter;
    int LRUCounter;
} Line;

// Prototypes
void freeMem(void); // to free memory
void userInput(int S, int E, int B, int m, char policy[]); // for user input
void setUp(void); // set up the cache
void incrementer(Line *l, char policy[]); // incr/decr a specific line based on policy
int checker(char policy[]); // checks to see what policy is being used
void LRU(Line *l, int E, long long t); // evict using LRU policy
void LFU(Line *l, int E, long long t); // evict using LFU policy
void misser(void); // calculates misses
void hitter(void); // calculates hits
int getSetIndex(long long a, int S, int b); // gets the set index of the hex
long long getTag(long long a, int t, int s, int b); // gets the tag of the hex

// globals
Line **cache;
int hits;
int misses;
int cycles;

int hitTime;
int missPenalty;

int getSetIndex(long long a, int S, int b){
    return (a >> b) & (S - 1);
}

long long getTag(long long a, int t, int s, int b){
    return (a >> (s + b)) & ((1 << t) - 1);
}

void freeMem(void){
	free(cache);
    exit(0);
}

void setUp(void){
    int S, E, B, m;
    char policy[3];

    scanf("%d %d %d %d %s %d %d", &S, &E, &B, &m, policy, &hitTime, &missPenalty);

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

    userInput(S, E, B, m, policy);
}

void userInput(int S, int E, int B, int m, char policy[]){
    int s = (int)log2f((float)S);
    int b = (int)log2f((float)B);
    int t = m - (s + b);

    long long input;

    while(input != -1){
        scanf("%10llx", &input);

        if(input == -1){
            printf("%d %d\n", (misses * 100)/(misses + hits), cycles);
            freeMem();
        }

        int check = 0;
        int setIndex = getSetIndex(input, S, b);
        long long setTag = getTag(input, t, s, b);

        Line *cLine = cache[setIndex];

        if(E == 1){ // direct mapped cache
            if((cLine->valid == '0') || (cLine->valid == '1' && cLine->tag != setTag)){
                printf("%llx M <--- X\n", input);
                cLine->valid = '1';
                cLine->tag = setTag;
                misser();
            } else {
                printf("%llx H\n", input);
                hitter();
            }
        } else { // set associative and fully associative
            for(int i = 0; i < E; i++){
                cLine[i].LRUCounter++;
            }

            int fulLCheck = 0;

            for(int i = 0; i < E; i++){                
                if(cLine[i].valid == '0'){
                    printf("%llx M <---\n", input);
                    cLine[i].valid = '1';
                    cLine[i].tag = setTag;
                    misser();
                    break;
                } else if(cLine[i].tag != setTag){
                    fulLCheck++;
                    misser();
                    printf("%llx NOT RIGHT TAG\n", input);
                }else {
                    printf("%llx H\n", input);
                    incrementer(&cLine[i], policy);
                    hitter();
                    break;
                }
                if(fulLCheck == E){
                    printf("%s\n", "FULL EVICT");
                    if(checker(policy)){
                        printf("%s\n", "LRU");
                        LRU(cLine, E, setTag);
                    } else {
                        printf("%s\n", "LFU");
                        LFU(cLine, E, setTag);
                    }
                }
            }
        }

    }
}

void misser(void){
    misses++;
    cycles += missPenalty + hitTime;
}

void hitter(void){
    hits ++;
    cycles += hitTime;
}

void LRU(Line *l, int E, long long t){
    int check = 0;
    int index;
    for(int i = 0; i < E; i++){
        if(l[i].LRUCounter > check){
            check = l[i].LRUCounter;
            index = i;
        }
    }
    l[index].LRUCounter = 0;
    l[index].tag = t;
}

void LFU(Line *l, int E, long long t){
    int check = l[0].LFUCounter;
    int index;
    for(int i = 0; i < E; i++){
        if(l[i].LFUCounter < check){
            check = l[i].LFUCounter;
            index = i;
        }
    }
    l[index].LFUCounter = 0;
    l[index].tag = t;
}

int checker(char policy[]){
    if(policy[1] == 'F'){
        return 0;
    } else {
        return 1;
    }
}

void incrementer(Line *l, char policy[]){
    if(policy[1] == 'F'){
        l->LFUCounter++;
    } else {
        l->LRUCounter--;
    }
}

int main(void){
    setUp();
    return 0;
}
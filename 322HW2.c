#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
00000000 1010 1 001
11111010
00001010 <-- gets the tag


S = sets
B
E = lines per set
m = 64
s = log2(S)
b = log2(B)
t = 32 - s + b

int getSetIndex(long long a, int m, int S, int B){
    (a >> b) & (S - 1);
}

long long getTag(long long a, int m, int s, int b){
    return (a >> (s + b)) & ((1 << t) - 1);
}

Fully associative caches have 1 Set

& is a mask
a & 0x7 <-- byte offset of a 8 bit number


a & ((1 << b) - 1)



typedef struct line {
    char valid;
    long long tag;

    int LFUCounter;
    int LRUCounter;

} line;

line **cache;
cache = (line**)calloc(sizeof(line)*E*S)
line[i][j]

long long address;

look {
    read address
    if cache[getSetIndex(address, m, s, B)]
}



**/

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

void setUp(void){
    int S, E, B, m, h, mp;
    char policy[3];
    long long input;

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


    while(input != -1){
        scanf("%10llx", &input);
        int check = 0;
        int setIndex = getSetIndex(input, s, b);
        printf("%d\n", setIndex);

        if(E == 1){

        }

        

    }
}

int main(void){
    setUp();
    return 0;
}
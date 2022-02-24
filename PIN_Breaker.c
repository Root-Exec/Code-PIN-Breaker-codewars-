#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//--->Build an adjacency list (buildList() and adjList[])
//--->dynamic programming to find all permutations based off of potential adjacent letters
//--->build a temp string, once PIN potential is built, add it to solution array

struct number {
    int elements;
    int adjacent_Nums[5];
};
typedef struct number Number;

unsigned long global_items;

void buildList(Number* adjList) {
    adjList[0].elements = 2;
    adjList[0].adjacent_Nums[0] = 0; adjList[0].adjacent_Nums[1] = 8;
  
    adjList[1].elements = 3;
    adjList[1].adjacent_Nums[0] = 1; adjList[1].adjacent_Nums[1] = 2; adjList[1].adjacent_Nums[2] = 4;
  
    adjList[2].elements = 4;
    adjList[2].adjacent_Nums[0] = 1; adjList[2].adjacent_Nums[1] = 2; adjList[2].adjacent_Nums[2] = 3; adjList[2].adjacent_Nums[3] = 5;
  
    adjList[3].elements = 3;
    adjList[3].adjacent_Nums[0] = 2; adjList[3].adjacent_Nums[1] = 3; adjList[3].adjacent_Nums[2] = 6;
  
    adjList[4].elements = 4;
    adjList[4].adjacent_Nums[0] = 1; adjList[4].adjacent_Nums[1] = 4; adjList[4].adjacent_Nums[2] = 5; adjList[4].adjacent_Nums[3] = 7;

    adjList[5].elements = 5;
    adjList[5].adjacent_Nums[0] = 2; adjList[5].adjacent_Nums[1] = 4; adjList[5].adjacent_Nums[2] = 5; adjList[5].adjacent_Nums[3] = 6;
    adjList[5].adjacent_Nums[4] = 8;

    adjList[6].elements = 4;
    adjList[6].adjacent_Nums[0] = 3; adjList[6].adjacent_Nums[1] = 5; adjList[6].adjacent_Nums[2] = 6; adjList[6].adjacent_Nums[3] = 9;
  
    adjList[7].elements = 3;
    adjList[7].adjacent_Nums[0] = 4; adjList[7].adjacent_Nums[1] = 7; adjList[7].adjacent_Nums[2] = 8;

    adjList[8].elements = 5;
    adjList[8].adjacent_Nums[0] = 0; adjList[8].adjacent_Nums[1] = 5; adjList[8].adjacent_Nums[2] = 7; adjList[8].adjacent_Nums[3] = 8; 
    adjList[8].adjacent_Nums[4] = 9;
  
    adjList[9].elements = 3;
    adjList[9].adjacent_Nums[0] = 6; adjList[9].adjacent_Nums[1] = 8; adjList[9].adjacent_Nums[2] = 9;

}


void recurse(Number adjList[], char** solution, char* currentString, const char* originalString, int cindex, int oindex, int len, int* sindex) {
    if (cindex < len - 1) {
        for (int i = 0; i < adjList[*(originalString + oindex) - '0'].elements; i++) {
          currentString[cindex] = adjList[originalString[oindex] - '0'].adjacent_Nums[i] + '0';
          recurse(adjList, solution, currentString, originalString, cindex + 1, oindex + 1, len, sindex);
        }
        return;
    }
  
    if (cindex == len - 1) {
        for (int i = 0; i < adjList[*(originalString + oindex) - '0'].elements; i++) {
            currentString[cindex] = adjList[originalString[oindex] - '0'].adjacent_Nums[i] + '0';
            currentString[cindex + 1] = '\0';
            strcpy(solution[*sindex], currentString);
            (*sindex)++;
        }
        return;
    }
}


const char** get_pins(const char* observed, size_t* count) {
  
    Number adjList[10];
    buildList(adjList);
    *count = 1;
    int len = strlen(observed);
    for (int i = 0; i < len; i++) {
        *count *= adjList[observed[i] - '0'].elements;
    }
    global_items = *count;
    char** solution = calloc(*count, sizeof(char*));
  
    for (size_t i = 0; i < *count; i++) solution[i] = calloc(len + 1, sizeof(char));
   
    char* currentString = calloc(len + 1, sizeof(char));
    int cindex = 0;
    int long oindex = 0;
    int sindex = 0;
  
    if (len == 1) {
        for (int i = 0; i < adjList[*(observed + 0) - '0'].elements; i++) {
          currentString[0] = adjList[*(observed + 0) - '0'].adjacent_Nums[i] + '0';
          currentString[1] = '\0';
          strcpy(solution[i], currentString);
        }
        *count = adjList[*(observed + 0) - '0'].elements;
        free(currentString);
        return (const char**) solution;
    }

    recurse(adjList, solution, currentString, observed, cindex, oindex, len, &sindex);
    free(currentString);
    memset(&sindex, 0, sizeof(unsigned long));

    return (const char**) solution;
}


void free_pins(const char ** pins) {
    unsigned long i = 0;
    for (; i < global_items; i++) {
      free((void*) pins[i]);
    }
}

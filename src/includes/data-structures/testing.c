#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "./trie.h"

int main() {
    char *words[] = {"cas", "ce", "des", "ao", "case", "boit", "feuille", "look"};
    const int size_Words = 8;

    ListTrie dict = initiliazeListTrie(26);

    for (int i=0; i<size_Words; i++) {
        char firstSymbol = words[i][0];
        if (dict.array_roots[getAlphabeticalOrder(toupper(firstSymbol)) -1 ] == NULL ) {
            Trie* trieP = initiliazeTrie(firstSymbol);
            if (trieP!=NULL) {
                dict.array_roots[getAlphabeticalOrder(toupper(firstSymbol))-1]= trieP;

            }else {
                printf("Error in allocation of TrieP pointer \n");
            }
        }
        addWordToTrie(words[i],1,strlen(words[i]), dict.array_roots[getAlphabeticalOrder(toupper(firstSymbol))-1]);
        
    }

    for (int i=0; i< 26; i++) {
        if (dict.array_roots[i]!=NULL){
            printf("Array at : %d has value : %c \n",i,dict.array_roots[i]->data);
            if(i<25) {
                printf("the node with value %c has a right sibling : %c \n",dict.array_roots[i]->data, getFirstRightLeftChild(i+1,1,dict.array_roots)->data);
            }
        }
    }
    char* str = "ccc";
    printf("The word : %s, exists : %d",str,wordExists(str,0,strlen(str),dict.array_roots[getAlphabeticalOrder(toupper(str[0]))-1 ] ) );


    free(dict.array_roots);
    return 0;

}
#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "./binary_tree.h"

typedef struct Trie Trie;

struct Trie {
    char data;
    Trie** array_node_sons;
};

typedef struct ListTrie {
    Trie** array_roots;
} ListTrie;

ListTrie initiliazeListTrie(int size);
int getAlphabeticalOrder(char c);
void addWordToTrie(char* word, int i, int length, Trie* trie);
int wordExists(char * word, int i, int length, Trie* trie);
Trie* getFirstRightLeftChild (int tab_index, int j, Trie** array_node_sons);
int isNodeLeaf(int i, Trie** array_node_sons);

// is the variable i was passed initially as 0, then the function is getFirstLeftChild
// if the variable > 0, it means that the main program calling the function is searching for the index
// of the next (first) non null sibling i.e it's a getFirstRightChild
Trie* getFirstRightLeftChild (int i, int j, Trie** array_node_sons) {
    if (array_node_sons[i] != NULL) {
        return array_node_sons[i];
    }
    if (i>=(26-j) && array_node_sons[i] == NULL){
        return NULL;
    }
    if (array_node_sons[i] == NULL && i<(26-j)) {
        return getFirstRightLeftChild(i+1, j,array_node_sons);
    }
}

// this is a function that verifies whether a Node in the genereic tree is a leaf or not, i.e 
// all its children are NULL
int isNodeLeaf(int i,Trie** array_node_sons) {
    if (i==26 && array_node_sons[i] != NULL ) {
        return 1;
    }
    if (array_node_sons[i] != NULL) {
        return 0; // NOT a leaf
    }
    return isNodeLeaf(i+1,array_node_sons);
}

ListTrie initiliazeListTrie(int size) {
    Trie** array = (Trie**)malloc(size * sizeof(Trie*));
    for (int i=0; i<size ; i++) {
        array[i]=NULL;
    }
    ListTrie list_Trie = {array};
    return list_Trie;
};

Trie* initiliazeTrie(char data) {
    Trie* trieP = (Trie*) malloc (sizeof(Trie));
    trieP->data=data;
    Trie** array = (Trie**)malloc(27 * sizeof(Trie*));
    for (int i=0; i<27 ; i++) {
        array[i]=NULL;
    }
    trieP->array_node_sons=array;
    return trieP;
}


int wordExists(char *word, int i, int length, Trie *trie) {
    if(i==length-1 && trie->array_node_sons[0]== NULL){
        return 0;
    }
    if (i==length-1 && trie->array_node_sons[0]->data == '\0') {
        return 1;
    }
    if (trie== NULL) {
        return 0;
    }
    else {
        return wordExists(word, i+1, length, trie->array_node_sons[getAlphabeticalOrder(toupper(word[i+1]))] );
    }
}

int searchWordTrie(char * word, ListTrie dict){
    if(word==NULL || word[0] == '\0') return 0;
    return wordExists(word,0,strlen(word),dict.array_roots[getAlphabeticalOrder(word[0])-1 ] );
}

void addWordToTrie(char * word, int i, int length, Trie* trie) {
    if(i==length || length==i==1) {
        Trie* trieP = initiliazeTrie('\0');
        trie->array_node_sons[0]= trieP;
    }
    else {
        char symbol = word[i];
        if(trie->array_node_sons[getAlphabeticalOrder(toupper(symbol))] == NULL) {
            Trie* trieP = initiliazeTrie(symbol);
            if (trieP!=NULL) {
                trie->array_node_sons[getAlphabeticalOrder(toupper(symbol))]= trieP;
            } 
            else {
                printf("Error in allocation of TrieP pointer \n");
            }
        }
        addWordToTrie(word, i+1, length, trie->array_node_sons[getAlphabeticalOrder(toupper(symbol))]);
    }
};


int getAlphabeticalOrder(char c) {
    if(c=='\0') {
        return 0;
    }
    c=toupper(c);
    // Ensure the character is an uppercase letter
    if (c >= 'A' && c <= 'Z') {
        // Subtract the ASCII value of 'A' to get the alphabetical order
        return c - 'A' +1;
    } else {
        // Handle invalid input (not an uppercase letter)
        printf("Invalid input: %c\n", c);
        return -1; 
    }
}

ListTrie createTrieFromWords(WordList words){
    ListTrie dict = initiliazeListTrie(26);
    for (int j=0; j<words.words_array_size; j++) {
        char firstSymbol = (words.words_array[j]).word[0];
        if (dict.array_roots[getAlphabeticalOrder(firstSymbol) -1 ] == NULL ) {
            Trie* trieP = initiliazeTrie(firstSymbol);
            if (trieP!=NULL) {
                dict.array_roots[getAlphabeticalOrder(firstSymbol)-1]= trieP;

            }else {
                printf("Error in allocation of TrieP pointer \n");
            }
        }
        addWordToTrie((words.words_array[j]).word,1,strlen((words.words_array[j]).word), dict.array_roots[getAlphabeticalOrder(firstSymbol)-1]);
        
    }
    return dict;
}


BinaryTree* convertTrieToBT (Trie* trie) {
    if (trie != NULL) {

        BinaryTree* newBT = createNode(trie->data, NULL, NULL);

        if(isNodeLeaf(0,trie->array_node_sons) == 1) {
            printf("%c this is a leaf \n", trie->data);
            return newBT;
        }
        else {
            Trie* trie_first_left_child = getFirstRightLeftChild(0,0,trie->array_node_sons);
            newBT->left_child = convertTrieToBT(trie_first_left_child);
            if(trie_first_left_child!= NULL) {
                int j=getAlphabeticalOrder(trie_first_left_child->data) +1;
                newBT->left_child->right_child = convertTrieToBT(getFirstRightLeftChild(j,0,trie->array_node_sons));
                
                BinaryTree* nextBT = newBT->left_child->right_child;
                if(nextBT!=NULL) {
                    j= getAlphabeticalOrder(nextBT->data) + 1;
                    while(j<=26) {
                        if(trie->array_node_sons[j] != NULL) {
                            if(j==26) {
                                nextBT->right_child= NULL;
                                break;
                            }
                            
                            nextBT->right_child = convertTrieToBT(trie->array_node_sons[j]);

                            if(nextBT->right_child != NULL) {
                                j= getAlphabeticalOrder(nextBT->right_child->data)+1;
                                nextBT = nextBT->right_child;
                            }
                            else{
                                return newBT;
                            }
                        }
                        else {
                            j++;
                        }
                        
                    }
                }
                return newBT;
                
            }
            return newBT;

        }

    }
    else {
        return NULL;
    }

    
}

BinaryTree* convertTrieListToBT (Trie** array_roots) {
    BinaryTree* BT;
    Trie* trie_first_left_child = getFirstRightLeftChild(0,1,array_roots);

    if(trie_first_left_child != NULL) {
        int i= getAlphabeticalOrder(trie_first_left_child->data) -1 ;
        BT = convertTrieToBT(trie_first_left_child);
        printf("first index : %d \n", i);
        printf("data : %c \n", BT->data);
        
        if(i<25) {
            BinaryTree* newBT = BT;
            while(i<=25) {
                if(array_roots[i] != NULL) {
                    if(i==25) {
                        newBT->right_child = NULL;
                        break;
                    }
                    else {
                        newBT->right_child = convertTrieToBT(getFirstRightLeftChild(i+1,1,array_roots));
                        if(newBT->right_child != NULL) {
                            i=getAlphabeticalOrder (newBT->right_child->data) - 1;
                            newBT= newBT->right_child;
                        }
                        else {
                            break;
                        }
                    }
                }
                else {
                    i++;
                }
                
            }

        }
        return BT;

    }
    else {
        return NULL;
    }
}

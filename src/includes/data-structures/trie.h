#pragma once

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


int wordExists(char * word, int i, int length, Trie* trie) {
    if(i==length-1 && trie->array_node_sons[0]== NULL){
        return 0;
    }
    if (i==length-1 && trie->array_node_sons[0]->data == '0') {
        return 1;
    }
    if (trie== NULL) {
        return 0;
    }
    else {
        return wordExists(word, i+1, length, trie->array_node_sons[getAlphabeticalOrder(toupper(word[i+1]))] );
    }
}

void addWordToTrie(char * word, int i, int length, Trie* trie) {
    if(i==length || length==i==1) {
        Trie* trieP = initiliazeTrie('0');
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
#include<stdio.h>
#include "./includes/utils/file_parsing.h"
#include "./includes/data-structures/binary_tree.h"
#include "./includes/data-structures/trie.h"
int main(void){
    Words words = parseFile("./assets/words.txt");
    // char *words[] = {"cas", "ce", "ces", "ci", "de", "des", "do"};
    const int size_Words = words.words_array_size;
    ListTrie dict = initiliazeListTrie(26);

    for (int j=0; j<size_Words; j++) {
        char firstSymbol = words.words_array[j][0];
        if (dict.array_roots[getAlphabeticalOrder(firstSymbol) -1 ] == NULL ) {
            Trie* trieP = initiliazeTrie(firstSymbol);
            if (trieP!=NULL) {
                dict.array_roots[getAlphabeticalOrder(firstSymbol)-1]= trieP;
            }else {
                printf("Error in allocation of TrieP pointer \n");
            }
        }
        addWordToTrie(words.words_array[j],1,strlen(words.words_array[j]), dict.array_roots[getAlphabeticalOrder(firstSymbol)-1]);
        
    }

    // for (int i=0; i< 26; i++) {
    //     if (dict.array_roots[i]!=NULL){
    //         printf("Array at : %d has value : %c \n",getAlphabeticalOrder(dict.array_roots[i]->data) - 1,dict.array_roots[i]->data);
    //         if(i<25) {
    //             printf("the node with value %c has a right sibling : %c \n",dict.array_roots[i]->data, getFirstRightLeftChild(i+1,1,dict.array_roots)->data);
    //         }
    //     }
    // }
    // char* str = "ccc";
    // printf("The word : %s, exists? : %d \n",str,wordExists(str,0,strlen(str),dict.array_roots[getAlphabeticalOrder(str[0])-1 ] ) );

    BinaryTree* BT =convertTrieListToBT(dict.array_roots);
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    printf("business = %d\n",search_word("businesss",BT,q));
    generateImageFromBinaryTree(BT);
    //recursiveBFS(BT);
    free(BT);
    free(dict.array_roots);
    // BinaryTree* root = addWords(wordsroot);


    return 0;
}
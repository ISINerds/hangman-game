#include <criterion/criterion.h>
#include "../src/includes/data-structures/trie.h"

Test(test_trie, trie_creation) {
    // Test case 1: Creating a Trie from a not empty list of words.
    WordScore* words_array = (WordScore*)malloc(sizeof(WordScore*)*5);
    words_array[0].word = "school";
    words_array[0].difficulty = EASY;
    
    words_array[1].word = "apple";
    words_array[1].difficulty = EASY;
    
    words_array[2].word = "tree";
    words_array[2].difficulty = EASY;
    
    words_array[3].word = "education";
    words_array[3].difficulty = EASY;
    
    words_array[4].word = "evaluation";
    words_array[4].difficulty = EASY;
    WordList words = {
        .words_array = words_array,
        .words_array_size = 5
    };
    ListTrie dict = createTrieFromWords(words);
    cr_assert(dict.array_roots != NULL, "Failed to create Trie.");
}

Test(test_trie, trie_conversion_to_BT) {
    // Test case 1: Converting a Trie to a binary tree.
    WordScore* words_array = (WordScore*)malloc(sizeof(WordScore*)*5);
    words_array[0].word = "ce";
    words_array[0].difficulty = EASY;
    
    words_array[1].word = "cas";
    words_array[1].difficulty = EASY;
    
    words_array[2].word = "ces";
    words_array[2].difficulty = EASY;
    
    words_array[3].word = "do";
    words_array[3].difficulty = EASY;
    
    words_array[4].word = "des";
    words_array[4].difficulty = EASY;
    WordList words = {
        .words_array = words_array,
        .words_array_size = 5
    };
    ListTrie dict = createTrieFromWords(words);
    cr_assert(dict.array_roots != NULL, "Failed to create Trie.");
    BinaryTree* root = convertTrieListToBT(dict.array_roots);
    cr_assert(root != NULL, "Failed to convert Trie to Binary Tree.");
    int res = generateImageFromBinaryTree(root,"./tests/images/test_trie_conversion_to_BT","./assets/tree.gv");
    cr_assert(res == 0, "Failed to generate graph image.");
}

Test(test_trie, trie_word_search) {
    WordScore* words_array = (WordScore*)malloc(sizeof(WordScore*)*5);
    words_array[0].word = "school";
    words_array[0].difficulty = EASY;
    
    words_array[1].word = "apple";
    words_array[1].difficulty = EASY;
    
    words_array[2].word = "tree";
    words_array[2].difficulty = EASY;
    
    words_array[3].word = "education";
    words_array[3].difficulty = EASY;
    
    words_array[4].word = "evaluation";
    words_array[4].difficulty = EASY;
    WordList words = {
        .words_array = words_array,
        .words_array_size = 5
    };
    ListTrie dict = createTrieFromWords(words);

    // Test case 1: searching for a word that exists in the Trie. 
    cr_assert(searchWordTrie("school",dict) == 1, "Failed to find the word 'school' in the Trie.");

    // Test case 2: searching for a word that  doesn't exist in the Trie. 
    cr_assert(searchWordTrie("flower",dict) == 0, "Unexpected result when searching for a non-existing word.");

    // Test case 3: searching for an empty string should return 0 
    cr_assert(searchWordTrie("",dict) == 0, "Unexpected result when searching for an empty string.");

}

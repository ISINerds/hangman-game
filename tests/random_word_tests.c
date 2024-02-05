#include <criterion/criterion.h>
#include "../src/includes/utils/file_parsing.h"

Test(test_random_word, random_word_choice) {
    WordScore* words_array = (WordScore*)malloc(sizeof(WordScore*)*5);
    words_array[0].word = "school";
    words_array[0].difficulty = MEDIUM;
    
    words_array[1].word = "apple";
    words_array[1].difficulty = EASY;
    
    words_array[2].word = "tree";
    words_array[2].difficulty = EASY;
    
    words_array[3].word = "education";
    words_array[3].difficulty = HARD;
    
    words_array[4].word = "evaluation";
    words_array[4].difficulty = HARD;
    WordList words = {
        .words_array = words_array,
        .words_array_size = 5
    };

    // Test case 1: getting a random word with difficulty level EASY
    const char* word1= getRandomWord(EASY, words);
    cr_assert(word1 != NULL && getWordDifficulty(word1) == EASY, "Failed to get a random word with difficulty EASY.");

    // Test case 2: getting a random word with difficulty level MEDIUM
    const char* word2= getRandomWord(MEDIUM, words);
    cr_assert(word2 != NULL && getWordDifficulty(word2) == MEDIUM, "Failed to get a random word with difficulty MEDIUM.");

    // Test case 3: getting a random word with difficulty level HARD
    const char* word3= getRandomWord(HARD, words);
    cr_assert(word3 != NULL && getWordDifficulty(word3) == HARD, "Failed to get a random word with difficulty HARD.");

}

Test(test_random_word, random_word_choice2) {
    
    // Test case 1: getting a random word with difficulty level EASY that does not exist in the list 
    WordScore* words_array1 = (WordScore*)malloc(sizeof(WordScore*)*3);
    words_array1[0].word = "school";
    words_array1[0].difficulty = MEDIUM;
    
    words_array1[1].word = "education";
    words_array1[1].difficulty = HARD;
    
    words_array1[2].word = "evaluation";
    words_array1[2].difficulty = HARD;
    WordList words1 = {
        .words_array = words_array1,
        .words_array_size = 3
    };
    char* word1= getRandomWord(EASY, words1);
    cr_assert(word1 == NULL , "Unexpected result when trying to get a random word with difficulty EASY non-existing in the list.");

    // Test case 2: getting a random word with difficulty level MEDIUM that does not exist in the list 
    WordScore* words_array2 = (WordScore*)malloc(sizeof(WordScore*)*4);
    
    words_array2[0].word = "apple";
    words_array2[0].difficulty = EASY;
    
    words_array2[1].word = "tree";
    words_array2[1].difficulty = EASY;
    
    words_array2[2].word = "education";
    words_array2[2].difficulty = HARD;
    
    words_array2[3].word = "evaluation";
    words_array2[3].difficulty = HARD;
    WordList words2 = {
        .words_array = words_array2,
        .words_array_size = 4
    };
    char* word2= getRandomWord(MEDIUM, words2);
    cr_assert(word2 == NULL , "Unexpected result when trying to get a random word with difficulty MEDIUM non-existing in the list.");

    // Test case 3: getting a random word with difficulty level HARD that does not exist in the list 
    WordScore* words_array3 = (WordScore*)malloc(sizeof(WordScore*)*4);
    
    words_array3[0].word = "apple";
    words_array3[0].difficulty = EASY;
    
    words_array3[1].word = "tree";
    words_array3[1].difficulty = EASY;
    
    words_array3[2].word = "service";
    words_array3[2].difficulty = MEDIUM;
    
    words_array3[3].word = "party";
    words_array3[3].difficulty = MEDIUM;
    WordList words3 = {
        .words_array = words_array3,
        .words_array_size = 4
    };
    char* word3= getRandomWord(HARD, words3);
    cr_assert(word3 == NULL , "Unexpected result when trying to get a random word with difficulty HARD non-existing in the list.");
}
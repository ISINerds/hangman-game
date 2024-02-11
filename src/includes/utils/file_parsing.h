#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char** words_array;
    int words_array_size;
} Words;

typedef enum {
    EASY,
    MEDIUM,
    HARD
} Difficulty;
typedef struct {
    char* word;
    Difficulty difficulty;
} WordScore;
typedef struct {
    WordScore* words_array;
    int words_array_size;
} WordList;

const int easy_bound = 5;
const int medium_bound = 7;


float averageCharOccurrence(const char* word) {
    if (word == NULL || *word == '\0') {
        return 0.0;
    }

    int word_length = strlen(word);
    int unique_indexes = 0; //  an integer in the binary format as 1 bit for each index
    int unique_count = 0;
    for (const char* ptr = word; *ptr != '\0'; ++ptr) {
        char c = tolower(*ptr);
        if ((unique_indexes & (1 << (c - 'a'))) == 0) {
            unique_indexes |= (1 << (c - 'a'));
            unique_count++;
        }
    }

    return (float)word_length/unique_count;
}

int nbVowels(const char* word) {
    if (word == NULL || *word == '\0') {
        return 0;
    }

    int nb_vowels = 0;

    while (*word != '\0') {
        char c = tolower(*word);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            nb_vowels++;
        }
        word++;
    }

    return nb_vowels;
}

float calculateDifficulty(const char* word){
    int length = strlen(word);
    int nb_vowels = nbVowels(word);
    float avg_char_occ = averageCharOccurrence(word);
    // float score = (length + 0.5*avg_char_occ)*nb_vowels/10;
    float score = (length +nb_vowels)/avg_char_occ;
    // printf("%s -- %.2f\n",word,score);
    return score;
}

Difficulty getWordDifficulty(const char *word){
    float score = calculateDifficulty(word);
    if(score>0 && score<=easy_bound) return EASY;
    else if (score>easy_bound && score<=medium_bound) return MEDIUM;
    else if (score>medium_bound) return HARD;
}

WordList parseFile(const char *file_path) {
    WordList words;
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }else {

        words.words_array_size = 0;
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '\n') {
                words.words_array_size ++;
            }
        }
        if (ch != '\n') {
            words.words_array_size++;
        }

        // go back to the beginning of the file
        fseek(file, 0, SEEK_SET);
            
        
        words.words_array = (WordScore*)malloc(words.words_array_size * sizeof(WordScore));
        if (words.words_array== NULL) {
            printf("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < words.words_array_size; i++) {
            size_t buffer_size = 0;
            getline(&words.words_array[i].word, &buffer_size, file);

            // remove the newline character if exist
            size_t length = strlen(words.words_array[i].word);
            if (words.words_array[i].word[length - 1] == '\n') {
                words.words_array[i].word[length - 2] = '\0';
            }
            words.words_array[i].difficulty = getWordDifficulty(words.words_array[i].word);
            printf("%s -- %d\n",words.words_array[i].word,words.words_array[i].difficulty);
            // printf("%s -- %.2f\n",words.words_array[i].word,score);
        }
        fclose(file);

        return words;

    }   
   
}

char* getRandomWord(Difficulty difficulty_choice, WordList list_words) {
    WordScore* array_scores = list_words.words_array;
    int nb=0;

    for(int i=0; i< list_words.words_array_size; i++) {
        if (array_scores[i].difficulty == difficulty_choice) nb++;
    }

    if(nb != 0) {
        int* array_difficulty_choice = (int*) malloc (nb * sizeof(int));

        nb=0;
        for(int i=0; i< list_words.words_array_size; i++) {
            if(array_scores[i].difficulty == difficulty_choice) {
                array_difficulty_choice[nb] = i;
                nb++;
            }
        }

        srand(time(NULL)); // Seed the random number generator

        int randomIndex = rand() % (nb);

        return array_scores[array_difficulty_choice[randomIndex]].word;

    }

    else{
        printf("No word found for the specified difficulty.\n");
        return NULL; // Return NULL if no word is found after the maximum attempts
    }
}
// usage example 
// int main() {
//         WordScore wordArray[] = {
//         {"apple", MEDIUM},
//         {"banana", EASY},
//         {"cherry", HARD},
//         {"dog", EASY},
//         {"elephant", EASY},
//         {"fox", HARD},
//         {"grape", EASY},
//         {"horse", EASY},
//         {"iguana", HARD},
//         {"jaguar", EASY}
//     };

//     int arraySize = sizeof(wordArray) / sizeof(wordArray[0]);

//     WordList list_words;
//     list_words.wordsArray = wordArray;
//     list_words.wordsArraySize = arraySize;

//     // Test getRandomWord function
//     Difficulty chosenDifficulty = MEDIUM; // Change this to test different difficulty levels
//     char* randomWord = getRandomWord(chosenDifficulty, list_words);

//     if (randomWord != NULL) {
//         printf("Random word for difficulty %d: %s\n", chosenDifficulty, randomWord);
//     }

//     return 0;
// }

void freeWordsArray(WordList words){
    for (int i=0; i<words.words_array_size; i++){
        free(words.words_array[i].word);
    }
    free(words.words_array);
}

//to test that include that file and copy these lines to the main 
    // Words words = parseFile("./assets/words.txt");
    // printf("%d",words.words_array_size);
    // freeWordsArray(words);

//--------------

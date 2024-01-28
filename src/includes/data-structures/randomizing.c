#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
    WordScore* wordsArray;
    int wordsArraySize;
} WordList;

char* getRandomWord(Difficulty difficulty_choice, WordList list_words) {
    WordScore* array_scores = list_words.wordsArray;
    int nb=0;

    for(int i=0; i< list_words.wordsArraySize; i++) {
        if (array_scores[i].difficulty == difficulty_choice) nb++;
    }

    if(nb != 0) {
        int* array_difficulty_choice = (int*) malloc (nb * sizeof(int));

        nb=0;
        for(int i=0; i< list_words.wordsArraySize; i++) {
            if(array_scores[i].difficulty == difficulty_choice) {
                array_difficulty_choice[nb] = i;
                nb++;
            }
        }

        srand(time(NULL)); // Seed the random number generator

        int randomIndex = rand() % (nb);

        printf("Size of the array with the difficulty choice is %d \n",nb);

        return array_scores[array_difficulty_choice[randomIndex]].word;

    }

    else{
        printf("No word found for the specified difficulty.\n");
        return NULL; // Return NULL if no word is found after the maximum attempts
    }
    

}

int main() {
        WordScore wordArray[] = {
        {"apple", MEDIUM},
        {"banana", EASY},
        {"cherry", HARD},
        {"dog", EASY},
        {"elephant", EASY},
        {"fox", HARD},
        {"grape", EASY},
        {"horse", EASY},
        {"iguana", HARD},
        {"jaguar", EASY}
    };

    int arraySize = sizeof(wordArray) / sizeof(wordArray[0]);

    WordList list_words;
    list_words.wordsArray = wordArray;
    list_words.wordsArraySize = arraySize;

    // Test getRandomWord function
    Difficulty chosenDifficulty = MEDIUM; // Change this to test different difficulty levels
    char* randomWord = getRandomWord(chosenDifficulty, list_words);

    if (randomWord != NULL) {
        printf("Random word for difficulty %d: %s\n", chosenDifficulty, randomWord);
    }

    return 0;
}
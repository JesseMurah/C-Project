#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORD_LEN 20
#define MAX_GUESSES 6

// Word database
const char *words[] = {"apple", "banana", "cherry", "date", "elderberry","fig", "grape", "honeydew", "kiwi", "lemon", "mango", "nectarine","orange", "peach", "pear", "quince", "raspberry", "strawberry","tangerine", "watermelon"};

// Function prototypes
void clear_input_buffer(void);
int read_int(const char *prompt, int min, int max);
void get_random_word(char *word);
void print_word(const char *word, const int *guessed_letters);
int play_game(const char *word);
void print_clue(const char *word, const int *guessed_letters);

int main(void) {
    srand((unsigned int) time(NULL));  // seed random number generator
    printf("*** WORD GUESS GAME ***\n\n");
    int num_games = read_int("How many games do you want to play? ", 1, 10);
    int total_score = 0;
    for (int i = 0; i < num_games; i++) {
        char word[MAX_WORD_LEN+1];
        get_random_word(word);
        printf("\nGame %d: Guess the word in %d tries or less!\n", i+1, MAX_GUESSES);
        int score = play_game(word);
        total_score += score;
        printf("The word was %s. Your score for this game is %d.\n\n", word, score);
    }
    printf("Total score: %d\n", total_score);
    return 0;
}

// Helper function to clear input buffer
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Helper function to read an integer from input with bounds checking
int read_int(const char *prompt, int min, int max) {
    int value;
    do {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1) {
            clear_input_buffer();
            continue;
        }
        if (value < min || value > max) {
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        } else {
            break;
        }
    } while (1);
    clear_input_buffer();
    return value;
}

// Helper function to randomly select a word from the database
void get_random_word(char *word) {
    strcpy(word, words[rand() % (sizeof(words)/sizeof(words[0]))]);
}

// Helper function to print the word with underscores for unguessed letters
void print_word(const char *word, const int *guessed_letters) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed_letters[i]) {
            putchar(word[i]);
        } else {
            putchar('_');
        }
        putchar(' ');
    }
    putchar('\n');
}

// Main game function
int play_game(const char *word) {
    int guessed_letters[MAX_WORD_LEN] = {0};  // array of guessed letters (1 if guessed, 0 if not)
    int num_guesses = 0;  // number of guesses so far
    int score = 0; 
    while (num_guesses < MAX_GUESSES) {
        printf("\n");
        print_word(word, guessed_letters);
        printf("Guess a letter: ");
        char input;
        if (scanf("%c", &input) != 1) {
            clear_input_buffer();
            continue;
        }
        input = tolower(input);  // convert to lowercase
        if (!isalpha(input)) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }
    int already_guessed = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (tolower(word[i]) == input) {
            if (guessed_letters[i]) {
                already_guessed = 1;
                break;
            } else {
                guessed_letters[i] = 1;
            }
        }
    }
    if (already_guessed) {
        printf("You already guessed that letter!\n");
    } else {
        num_guesses++;
        if (memcmp(word, guessed_letters, strlen(word)) == 0) {
            printf("\nCongratulations, you guessed the word!\n");
            score = (MAX_GUESSES - num_guesses + 1) * 10;
            break;
        } else {
            printf("Sorry, that letter is not in the word.\n");
        }
    }
    printf("You have %d guess%s left.\n", MAX_GUESSES - num_guesses, (MAX_GUESSES - num_guesses == 1) ? "" : "es");
    print_clue(word, guessed_letters);
}
if (score == 0) {
    printf("\nSorry, you did not guess the word. The word was %s.\n", word);
}
return score;
}

// Helper function to print a clue for the word based on guessed letters
void print_clue(const char *word, const int *guessed_letters) {
    printf("Clue: ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed_letters[i]) {
            putchar(word[i]);
        } else {
            putchar('_');
        }
    }
    printf("\n");
}



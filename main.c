#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_GUESSES 6
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

// Function prototypes
int play_game(const char *word);
void print_word(const char *word, const int *guessed_letters);
void print_clue(const char *word, const int *guessed_letters);
void clear_input_buffer();

int main() {
    // Initialize random number generator
    srand(time(NULL));

    // Initialize word database
    const char *words_easy[] = {"cat", "dog", "sun", "hat", "car", "red", "pen", "cup", "bug", "toy"};
    const char *words_medium[] = {"apple", "banana", "orange", "lemon", "grape", "melon", "cherry", "pear", "peach", "plum"};
    const char *words_hard[] = {"elephant", "giraffe", "rhinoceros", "hippopotamus", "crocodile", "alligator", "kangaroo", "jaguar", "cheetah", "gorilla"};

    int num_games;
    do {
        printf("How many games do you want to play (1-10)? ");
        if (scanf("%d", &num_games) != 1) {
            clear_input_buffer();
        }
    } while (num_games < 1 || num_games > 10);

    int total_score = 0;
    for (int i = 0; i < num_games; i++) {
        // Select difficulty level
        int difficulty;
        do {
            printf("Choose difficulty level (1-easy, 2-medium, 3-hard): ");
            if (scanf("%d", &difficulty) != 1) {
                clear_input_buffer();
            }
        } while (difficulty < 1 || difficulty > 3);

        // Select random word from database based on difficulty level
        const char **words;
        int num_words;
        switch (difficulty) {
            case 1:
                words = words_easy;
                num_words = sizeof(words_easy) / sizeof(words_easy[0]);
                break;
            case 2:
                words = words_medium;
                num_words = sizeof(words_medium) / sizeof(words_medium[0]);
                break;
            case 3:
                words = words_hard;
                num_words = sizeof(words_hard) / sizeof(words_hard[0]);
                break;
            default:
                words = words_easy;
                num_words = sizeof(words_easy) / sizeof(words_easy[0]);
        }
        const char *word = words[rand() % num_words];

        // Play the game and add score to total score
        int score = play_game(word);
        total_score += score;

        printf("Your score for this game is: %d\n", score);
        printf("Your total score so far is: %d\n", total_score);
    }

    printf("Thank you for playing!\n");
    return 0;
}

// Play a single game with the given word
int play_game(const char *word) {
    int score = 0;
    int num_guesses = 0;
    int guessed_letters[MAX_WORD_LENGTH] = {0};

    printf("\nGame start!\n");
   
// Keep playing until the player guesses the word or runs out of guesses
    while (num_guesses < MAX_GUESSES) {
    print_word(word, guessed_letters);
    print_clue(word, guessed_letters);
        // Get guess from player
    char guess;
    do {
        printf("Guess a letter (%d guesses left): ", MAX_GUESSES - num_guesses);
        scanf(" %c", &guess);
        guess = tolower(guess);
    } while (!isalpha(guess) || guessed_letters[guess - 'a']);

    // Update guessed letters
    guessed_letters[guess - 'a'] = 1;
    num_guesses++;

    // Check if the guess is in the word
    if (strchr(word, guess) != NULL) {
        printf("Correct!\n");
        score += 10;
    } else {
        printf("Wrong!\n");
    }

    // Check if the word has been completely guessed
    if (strspn(word, "abcdefghijklmnopqrstuvwxyz") == strspn(word, guessed_letters)) {
        print_word(word, guessed_letters);
        printf("Congratulations, you guessed the word!\n");
        score += 50;
        break;
    }
}

// Print the word if the player ran out of guesses
if (num_guesses == MAX_GUESSES) {
    printf("You ran out of guesses!\n");
    print_word(word, guessed_letters);
}

return score;
}

// Print the word with guessed letters filled in
void print_word(const char *word, const int *guessed_letters) {
    printf("Word: ");
    for (int i = 0; i < strlen(word); i++) {
    if (guessed_letters[word[i] - 'a']) {
    printf("%c", word[i]);
    } else {
    printf("_");
    }
    }
    printf("\n");
}
// Print a clue for the word
void print_clue(const char *word, const int *guessed_letters) {
    printf("Clue: ");
// TODO: add clues for each word in the database
    printf("\n");
}

// Clear input buffer
void clear_input_buffer() {
    int c;
    do {
    c = getchar();
    } while (c != '\n' && c != EOF);
}

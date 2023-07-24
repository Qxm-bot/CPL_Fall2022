//
// Created by 25378 on 2022/9/24.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){

    int high = 100;

    int number_of_tries = 7;

    printf("Let us play the Guess the Number game!\n"
           "The computer will generate a number between 1 and %d.\n"
           "You have %d tries.\n\n",high,number_of_tries);

    srand(time(NULL));
    int secret = rand()%high + 1;

    for (number_of_tries = 7;number_of_tries > 0;number_of_tries--) {

        printf("Please input your guess, "
               "You still have %d tries.\n", number_of_tries);

        int guess = 0;
        scanf("%d", &guess);
        printf("Your guess is %d.\n", guess);

        if (guess == secret) {
            printf("You win!\n");
            break;
        } else if (guess > secret) {
            printf("Your guess > secret\n");
        } else {
            printf("guess < secret\n");
        }
    }
    if(number_of_tries == 0){
        printf("You lose!\n"
               "The answer is %d.\n",secret);
    }
    return 0;
}
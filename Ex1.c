#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int secret_number;
int attempts = 0;
pid_t child_pid;

void handler_guess(int sig) {
    attempts++;
    printf("Попытка %d: Угадал число %d\n", attempts, secret_number);
    if (secret_number == attempts) {
        kill(child_pid, SIGUSR1); // Угадал
    } else {
        kill(child_pid, SIGUSR2); // Не угадал
    }
}

void handler_result(int sig) {
    if (sig == SIGUSR1) {
        printf("Игрок 2 угадал число %d за %d попыток!\n", secret_number, attempts);
        exit(0);
    } else if (sig == SIGUSR2) {
        printf("Игрок 2 не угадал. Попробуйте снова.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    
    while (1) {
        secret_number = rand() % N + 1;
        attempts = 0;

        child_pid = fork();
        
        if (child_pid < 0) {
            perror("Ошибка fork");
            exit(1);
        } else if (child_pid == 0) { // Процесс игрока 2
            signal(SIGUSR1, handler_result);
            signal(SIGUSR2, handler_result);

            while (1) {
                pause(); // Ожидание сигнала
            }
        } else { // Процесс игрока 1
            signal(SIGUSR1, handler_guess);
            signal(SIGUSR2, handler_guess);

            while (attempts < N) {
                printf("Игрок 1 загадывает число...\n");
                sleep(1); // Задержка для симуляции раздумий
                raise(SIGUSR1); // Уведомление игрока 2 о попытке
            }

            wait(NULL); // Ожидание завершения игрока 2
            printf("Игра окончена.\n");
        }
    }

    return 0;
}

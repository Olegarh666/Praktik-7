#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define MAX_TRIES 10

typedef struct msg_buffer {
    long msg_type;
    int guess;
} msg_buffer;

int secret_number;
int attempts = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    while (1) {
        secret_number = rand() % N + 1;
        attempts = 0;

        if (fork() == 0) { // Процесс игрока 2
            msg_buffer message;
            while (attempts < MAX_TRIES) {
                msgrcv(msgid, &message, sizeof(message.guess), 1, 0);
                attempts++;
                printf("Попытка %d: Игрок 2 угадывает число %d\n", attempts, message.guess);

                if (message.guess == secret_number) {
                    printf("Игрок 2 угадал число %d за %d попыток!\n", secret_number, attempts);
                    exit(0);
                } else {
                    printf("Игрок 2 не угадал. Попробуйте снова.\n");
                }
            }
            exit(0);
        } else { // Процесс игрока 1
            for (int i = 1; i <= MAX_TRIES; i++) {
                msg_buffer message;
                message.msg_type = 1;
                message.guess = rand() % N + 1; // Генерация случайного числа для угадывания
                msgsnd(msgid, &message, sizeof(message.guess), 0);
                sleep(1); // Задержка между попытками
            }
            wait(NULL); // Ожидание завершения игрока 2
            msgctl(msgid, IPC_RMID, NULL); // Удаление очереди сообщений
            printf("Игра окончена.\n");
        }
    }

    return 0;
}

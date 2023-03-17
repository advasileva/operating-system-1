#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int input_size = 5000;
int output_size = 3;

void second_process(char* name1, char* name2) {
    printf("Processor PID: %d\n", getpid());

    int fd1;
    mknod(name1, S_IFIFO | 0666, 0);
    fd1 = open(name1, O_RDONLY);

    char size[10];
    read(fd1, size, 10);
    int num;
    sscanf(size, "%d", &num);

    char buffer[num];
    read(fd1, buffer, num);

    char min = buffer[0], max = buffer[0];
    for (size_t i = 1; i < num; i++)
    {
        if (min > buffer[i]) {
            min = buffer[i];
        }
        if (max < buffer[i]) {
            max = buffer[i];
        }
    }

    int fd2;
    mknod(name2, S_IFIFO | 0666, 0);
    fd2 = open(name2, O_WRONLY);

    buffer[0] = min;
    buffer[1] = '\n';
    buffer[2] = max;
    write(fd2, buffer, output_size);
}

int main(int argc, char **argv) {
    char* input = "input", *output = "output";

    second_process(input, output);
    return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int input_size = 2048;
int output_size = 3;

int read_string() {
    return 0;
}

int process(int fd[2], char* buffer, int num) {
    char min = buffer[0], max = buffer[0];
    for (size_t i = 1; i < num; i++)
    {
        if (min > buffer[i])
        {
            min = buffer[i];
        }
        if (max < buffer[i])
        {
            max = buffer[i];
        }
    }

    char buffer2[output_size];
    buffer2[0] = min;
    buffer2[1] = '\n';
    buffer2[2] = max;
    write(fd[1], buffer2, output_size);
    return 0;
}

int write_result(int fd[2], char* file) {
    char buffer2[output_size];
    read(fd[0], buffer2, output_size);

    int output = open(file, O_WRONLY | O_CREAT);
    write(output, buffer2, 3);
    return 0;
}

int main(int argc, char **argv) {
    int fd[2];
    int size = 2048;
    char buffer[size], buffer2[3];
    int input = open(argv[1], O_RDONLY);
    int num = read(input, buffer, size);

    pipe(fd);
    process(fd, buffer, num);
    write_result(fd, argv[2]);
    return 0;
}

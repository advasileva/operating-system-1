#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int input_size = 10;
int output_size = 3;

void first_read(char* name, char* file) {
    printf("Reader PID: %d\n", getpid());

    char buffer[input_size];
    int input = open(file, O_RDONLY);
    int num = input_size;

    while (num == input_size) {
        num = read(input, buffer, input_size);

        int fd;
        mknod(name, S_IFIFO | 0666, 0);
        fd = open(name, O_WRONLY);

        char size[10];
        sprintf(size, "%d", num);

        write(fd, size, 10);
        write(fd, buffer, num);
    }
}

void first_write(char* name, char* file) {
    printf("Writer PID: %d\n", getpid());

    int fd;
    mknod(name, S_IFIFO | 0666, 0);
    fd = open(name, O_RDONLY);

    char buffer[output_size];
    read(fd, buffer, output_size);

    int output = open(file, O_WRONLY | O_CREAT);
    write(output, buffer, output_size);
}

int main(int argc, char **argv) {
    char* input = "input", *output = "output";

    first_read(input, argv[1]);
    first_write(output, argv[2]);
    return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int input_size = 5000;
int output_size = 3;

void first_read(char* name, char* file) {
    printf("First PID: %d\n", getpid());

    char buffer[input_size];
    int input = open(file, O_RDONLY);
    int num = read(input, buffer, input_size);

    int fd;
    mknod(name, S_IFIFO | 0666, 0);
    fd = open(name, O_WRONLY);

    char size[10];
    sprintf(size, "%d", num);
    write(fd, size, 10);
    write(fd, buffer, num);
}

void second_process(char* name1, char* name2) {
    printf("Second PID: %d\n", getpid());

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

void third_write(char* name, char* file) {
    printf("Third PID: %d\n", getpid());

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
    
    int id = fork();
    if (id == 0) {
        first_read(input, argv[1]);
    } else {
        id = fork();
        if (id == 0) {
            second_process(input, output);
        }
        else {
            id = fork();
            if (id == 0) {
                third_write(output, argv[2]);
            }
        }
    }
    return 0;
}

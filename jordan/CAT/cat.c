#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 80
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
    int fd = STDIN_FILENO;
    if(argc > 1){
        fd = open(argv[1], O_RDONLY);
        if(fd == -1){
            write(STDERR_FILENO, "no file\n", 8);
            exit(EXIT_FAILURE);
        }
    }

    ssize_t bytes_read;
    while((bytes_read = read(fd, buffer, BUFFER_SIZE))){
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);
}

//ctr+d to end input
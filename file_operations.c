#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    
    int fd;
    ssize_t bytes_written;

    printf("Creating file: %s\n", filename);
    printf("Content to Write: %s\n", content);

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {

        perror("open");
        return -1;

    }

    printf("File Descriptor: %d\n", fd);

    bytes_written = write(fd, content, strlen(content));

    if (bytes_written == -1) {

        perror("write");
        close(fd);
        return -1;

    }

    printf("Successfully wrote %zd bytes to '%s'\n", bytes_written, filename);

    if (close(fd) == -1) {

        perror("close");
        return -1;

    }

    printf("File Closed Successfully\n");
    return 0;

}

int read_file_contents(const char *filename) {
    int fd;
    char buffer[1024];
    ssize_t bytes_read;

    printf("Reading File: %s\n", filename);

    fd = open(filename, O_RDONLY);

    if (fd == -1) {

        perror("open");
        return -1;

    }

    printf("File Descriptor: %d\n\n", fd);
    printf("Contents of '%s'\n", filename);

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {

        buffer[bytes_read] = '\0';
        printf("%s", buffer);

    }

    if (bytes_read == -1) {

        perror("read");
        close(fd);
        return -1;

    }

    printf("\nEnd of File\n");

    if (close(fd) == -1) {

        perror("close");
        return -1;

    }

    printf("File Closed Successfully\n");

    return 0;

}

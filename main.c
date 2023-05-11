#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

off_t filesize(int fd)
{
    struct stat buf;
    fstat(fd, &buf);
    return buf.st_size;
}
int main(int argc, char const *argv[])
{
    if(argc < 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return 1;
    }
    FILE* fp = fopen(argv[1], "r+");

    if(fp == NULL) {
        fprintf(stderr, "File not found\n");
        return 1;
    }

    char buf[filesize(fileno(fp))];
    fgets(buf, sizeof(buf), fp);
    
    for(size_t i = 0; i != sizeof(buf) - 1; i++)
        buf[i] ^= 193;
    
    rewind(fp);

    fwrite(buf, sizeof(buf) - 1, 1, fp);
    return 0;
}

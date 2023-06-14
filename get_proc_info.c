// 250201017 Yağmur Nisa Şekerci
// 260201011 Mert Ayaz Özkan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <module path> -pid|-pname <value>\n", argv[0]);
        return 1;
    }

    char cmd[256] = {0};

    if (strcmp(argv[2], "-pid") == 0)
    {
        sprintf(cmd, "insmod %s upid=%s", argv[1], argv[3]);
    }
    else if (strcmp(argv[2], "-pname") == 0)
    {
        sprintf(cmd, "insmod %s upname=%s", argv[1], argv[3]);
    }
    else
    {
        fprintf(stderr, "Unknown option: %s\n", argv[2]);
        return 1;
    }

    if (system(cmd) != 0)
    {
        perror("Failed to load module");
        return 1;
    }

    FILE *fp = fopen("/proc/proc_info_module", "r");
    if (fp == NULL)
    {
        perror("Failed to open /proc/proc_info_module");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);

    if (system("rmmod proc_info_module") != 0)
    {
        perror("Failed to remove module");
        return 1;
    }

    return 0;
}

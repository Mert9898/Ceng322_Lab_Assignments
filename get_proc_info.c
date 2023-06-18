// 250201017 Yağmur Nisa Şekerci
// 260201011 Mert Ayaz Özkan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char cmd[256] = {0};
    
    if (argc != 4)
    {
        printf("Incorrect number of arguments.\n");
        return 1;
    }

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
        printf("Invalid argument type. Use -pid or -pname.\n");
        return 1;
    }

    if (system(cmd))
    {
        printf("Error inserting module: %s\n", strerror(errno));
        return 1;
    }

    FILE *fp = fopen("/proc/proc_info_module", "r");
    if (fp == NULL)
    {
        printf("Error opening /proc file: %s\n", strerror(errno));
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);

    if (system("rmmod proc_info_module"))
    {
        printf("Error removing module: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "bstrlib.h"
#include <dbg.h>

#define SIZE 512

void
echo_ne(int percent)
{
    char text[] = "[Downloading]";
    printf("\r");
    int len = strlen(text);
    printf("%s", text);
    int left = 68 - len;
    int finished = (int)(left * percent * 1.0 / 100);

    for (int i = 0; i < left; ++i)
    {
        if (i <= finished)
            printf("+");
        else
            printf("-");
    }
    printf("[%d%%]", percent);
    fflush(stdout);
    return;
}


void
download_pkg(const char* url)
{
    char content_size[SIZE];
    char content[SIZE];
    size_t size_total = 0;
    size_t size_downloaded = 0;
    int size_read = 0;
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    FILE *fp_download = fopen("tree.tgz", "w");

    bstring cmd_size = bformat("curl -I --silent '%s' | awk '/Content-Length/ {print $NF}'", url);
    fp1 = popen((const char *)cmd_size->data, "r");
    while(fgets(content_size, SIZE - 1, fp1)) {
        size_total = atoi(content_size);
    }
    check(pclose(fp1) != -1, "pclose failed")

    bstring cmd = NULL;
    cmd = bformat("curl --silent '%s'", url);
    check(cmd != NULL, "bformat failed");
    fp2 = popen((const char *)cmd->data, "r");
    check(fp2 != NULL, "popen failed");

    while((size_read = fread(content, sizeof(char), SIZE - 1, fp2)) > 0) {
        size_downloaded += size_read;
        echo_ne((int)(size_downloaded * 100 / size_total));
        fwrite(content, sizeof(char), size_read, fp_download);
    }

    printf("\n");
    fclose(fp_download);

    check(pclose(fp2) != -1, "pclose failed")
    return;

error:
    return;
}


int
main(int argc, char *argv[])
{
    check(argc > 1, "url needed.")
    download_pkg(argv[1]);
    return 0;

error:
    return 1;
}

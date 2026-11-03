#include<stdio.h>
#include "header.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("\033[1;91m------------------------------\n");
        printf("| ERROR :                    |\n");
        printf("| USAGE : ./a.out file.c     |\n");
        printf("------------------------------\033[0m\n");
    }
    FILE *sfp = fopen(argv[1], "r");
    if(sfp == NULL)
    {
        perror("ERROR ");
        return -1;
    }
    FILE *dfp = fopen("output.html", "w");
    if(dfp == NULL)
    {
        perror("ERROR ");
        return -1;
    }

    html_initializer(dfp);
    source_to_html(sfp, dfp);
    html_ender(dfp);

    printf("==============================================\n");
    printf("   \U0001F389 SOURCE TO HTML CONVERSION COMPLETED \U0001F389    \n");
    printf("==============================================\n");
    printf("         \U0001F4C1 Output File : output.html           \n");
    printf("   \U0001F680 Open Browser To See Highlighted Code     \n");
    printf("==============================================\n");
    fclose(dfp);
    fclose(sfp);

    return 0;
}
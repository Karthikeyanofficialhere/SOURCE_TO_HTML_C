#include "header.h"

// writing headers of html

void html_initializer(FILE *dfp)
{
    fprintf(dfp, "<!DOCTYPE html>\n");
    fprintf(dfp, "<html lang =\"en\">\n");
    fprintf(dfp, "<head>\n");
    fprintf(dfp, "  <meta charset = \"UTF-8\">\n");
    fprintf(dfp, "  <title>SOURCE2HTML</title>\n");
    fprintf(dfp, "  <link rel = \"stylesheet\" href = \"style.css\">\n");
    fprintf(dfp, "<head>\n");
    fprintf(dfp, "<body style = \"background-color:lightgrey;\">\n");
    fprintf(dfp, "<pre>\n");
}

// writing footers of html

void html_ender(FILE *dfp)
{
    fprintf(dfp, "</pre>\n");
    fprintf(dfp, "</body>\n");
    fprintf(dfp, "</html>\n");
}
#include<stdio.h>
#include<stdbool.h>

void html_initializer(FILE *dfp);
void source_to_html(FILE *sfp, FILE *dfp);
void html_ender(FILE *dfp);
bool isoperator(char op);
bool iskeyword(char *token);
bool issymbol(char sym);
bool isrelationalop(char *op);
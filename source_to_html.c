#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include "header.h"

/* writing the html file with the input as input file*/

void source_to_html(FILE *sfp, FILE *dfp)
{
    int i = 0;
    char ch;
    while((ch = fgetc(sfp)) != EOF)
    {
        //checking space and writing to output file

        if(isspace(ch))
        {
            fprintf(dfp, "%c", ch);
            continue;
        }

        // identifying comments

        if(ch == '/')
        {
            char token[100];
            int i = 0;
            token[i++] = ch;
            token[i++] = fgetc(sfp);
            if(token[i - 1] == '*')
            {
                char prev;
                while(1)
                {
                    token[i] = fgetc(sfp);
                    if(prev == '*' && token[i] == '/')
                    {
                        token[i + 1] = '\0';
                        fprintf(dfp, "<span class = \"comment\">%s</span>", token);
                        break;
                    }
                    prev = token[i];
                    i++;
                }
                continue;
            }
            else if(token[i - 1] == '/')
            {
                while(1)
                {
                    token[i] = fgetc(sfp);
                    if(token[i] == '\n')
                    {
                        token[i] = '\0';
                        fprintf(dfp, "<span class = \"comment\">%s</span>", token);
                        break;
                    }
                    i++;
                }
                continue;
            }
            else
            {
                fseek(sfp, -1, SEEK_CUR);
            }
        }

        // identifying preprocessor directive

        if(ch == '#')
        {
            int i = 0;
            char token[100];
            token[i++] = ch;
            while(1)
            {
                token[i] = fgetc(sfp);
                if(token[i] == ' ' || !isalpha(token[i]))
                {
                    token[i] = '\0';
                    fprintf(dfp, "<span class = \"preprocessor\">%s</span>", token);
                    break;
                } 
                i++;
            }
            fseek(sfp, -1, SEEK_CUR);
        }

        // identifying header file

        if(ch == '<' || ch == '"')
        {
            int i = 0;
            char token[100];
            if(ch == '<')
            {
                token[i] = '\0';
                strcat(token, "&lt;");
                i += 4;
            }
            else
            {
                token[i++] = ch;
            }
            token[i++] = fgetc(sfp);
            if(isalpha(token[i - 1]))
            {
                while(1)
                {
                    token[i] = fgetc(sfp);
                    if(token[i] == '"')
                    {
                        token[i + 1] = '\0';
                        if(strstr(token, ".h") != NULL)
                        {
                            fprintf(dfp, "<span class = \"header\">%s</span>", token);
                        }
                        else
                        {
                            fprintf(dfp, "<span class = \"string\">%s</span>", token);
                        }
                        break;
                    }
                    if(token[i] == '\n')
                    {
                        token[i - 2] = '\0';
                        strcat(token, "&gt;");
                        fprintf(dfp, "<span class = \"header\">%s</span>\n", token);
                        break;
                    }
                    i++;
                }
                continue;
            }
            else if(ch == '"')
            {
                while(token[i - 1] != '"')
                {
                    token[i++] = fgetc(sfp);
                }
                token[i] = '\0';
                fprintf(dfp, "<span class = \"string\">%s</span>", token);
            }
        }

        // identifying operator and relational operator

        if(isoperator(ch))
        {
            int i = 0;
            char token[3];
            token[i++] = ch;
            token[i++] = fgetc(sfp);
            if(isoperator(token[i - 1]))
            {
                token[i] = '\0';
                if(isrelationalop(token))
                {
                    fprintf(dfp, "<span class = \"operator\">%s</span>", token);
                    continue;
                }
            }
            else
            {
                fprintf(dfp, "<span class = \"operator\">%c</span>", ch);
                fseek(sfp, -1, SEEK_CUR);
                continue;
            }
        }

        // identifying symbols

        if(issymbol(ch))
        {
            fprintf(dfp, "<span class = \"symbol\">%c</span>", ch);
        }

        // identifying keywords and identifier

        if(isalpha(ch) || ch == '_')
        {
            int i = 0;
            char token[50];
            token[i++] = ch;
            while(1)
            {
                token[i] = fgetc(sfp);
                if(token[i] == ' ' || issymbol(token[i]))
                {
                    token[i] = '\0';
                    if(iskeyword(token))
                    {
                        if(strcmp(token, "FILE") == 0 || strcmp(token, "STRUCT") == 0)
                        {
                            fprintf(dfp, "<span class = \"keyword1\">%s</span>", token);
                            fseek(sfp, -1, SEEK_CUR);
                            break;
                        }
                        else
                        {
                            fprintf(dfp, "<span class = \"keyword\">%s</span>", token);
                            fseek(sfp, -1, SEEK_CUR);
                            break;
                        }
                    }
                }
                if(!isalnum(token[i]) && token[i] != '_')
                {
                    token[i] = '\0';
                    fprintf(dfp, "<span class = \"identifier\">%s</span>", token);
                    fseek(sfp, -1, SEEK_CUR);
                    break;
                }
                i++;
            }
            continue;
        }

        // identifying numbers

        if(isdigit(ch))
        {
            int i = 0;
            char token[10];
            token[i++] = ch;
            token[i++] = fgetc(sfp);
            if(isdigit(token[i - 1]) || token[i - 1] == '.')
            {
                while(1)
                {
                    token[i] = fgetc(sfp);
                    if(!isdigit(token[i]) && token[i] != '.')
                    {
                        token[i] = '\0';
                        fprintf(dfp, "<span class = \"numeric_constant\">%s</span>", token);
                        fseek(sfp, -1, SEEK_CUR);
                        break;
                    }
                    i++;
                }
            }
            else
            {
                fprintf(dfp, "<span class = \"numeric_constant\">%c</span>", ch);
                fseek(sfp, -1, SEEK_CUR);
            }
        }
    }
}

// checking operator or not

bool isoperator(char op)
{
    static const char operator[] = {'+', '-', '*', '/', '=', '!', '<', '>', '&', '|', '^', '%'};
    int i;
    for(i = 0; i < 12; i++)
    {
        if(op == operator[i])
        {
            return true;
        }
    }
    return false;
}

// checking keyword or not

bool iskeyword(char *token)
{
    static const char *keyword[] = {"auto", "break", "case", "char", "const", "continue", "default", 
                                "do", "double", "else", "enum", "extern", "float", "for", "goto",
                                "if", "int", "long", "register", "return", "short", "signed", 
                                "sizeof", "static", "struct", "switch", "typedef", "union", 
                                "unsigned", "void", "volatile", "while"};
    int i;
    for(i = 0; i < 32; i++)
    {
        if(strcmp(token, keyword[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

// checking symbol or not

bool issymbol(char sym)
{
    static const char symbols[] = "(){}[];,:";
    int i, size = strlen(symbols);
    for(i = 0; i < size; i++)
    {
        if(sym == symbols[i])
        {
            return true;
        }
    }
    return false;
}

// checking relational operator or not

bool isrelationalop(char *op)
{
    static const char *operators[] = {"==", "!=", "<=", ">=", "+=", "-=", "*=", "/=", "&&", "||"};
    int i;
    for(i = 0; i < 10; i++)
    {
        if(strcmp(op, operators[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
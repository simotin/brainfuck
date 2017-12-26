#include <stdlib.h>
#include <stdio.h>

#define CODE_LEN_MAX            (1024)
#define DATA_LEN_MAX            (30000)
#define STACK_LEN_MAX           (32)

static unsigned char code[CODE_LEN_MAX]        = {0};
static unsigned char buf[DATA_LEN_MAX]         = {0};
static unsigned char stackframe[STACK_LEN_MAX] = {0};

int main(int argc, char **argv)
{
    int c;
    int ip = 0;
    int sp = 0;
    int ptr = 0;
    int clen = 0;
    FILE *fp;

    if (argc < 2)
    {
        fprintf(stderr, "Input Code File path.");
        exit(-1);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Source file open failed\n");
        exit(-1);
    }

    while(1)
    {
        c = fgetc(fp);
        if (c == EOF)
        {
            break;
        }

        if (CODE_LEN_MAX < clen)
        {
            fprintf(stderr, "Code Size too large\n");
            exit(-1);
        }
        if (c == '\n')
        {
            continue;
        }
        if (c == '\r')
        {
            continue;
        }
        if (c == ' ')
        {
            continue;
        }

        code[clen++] = c;
    }

    #if 0
    fprintf(stdout, "Program loaded, size:[%d] byte\n", clen);
    #endif

    ip = 0;
    while(1)
    {
        switch(code[ip])
        {
        case '>':
            ptr++;
            ip++;
            break;
        case '<':
            ptr--;
            ip++;
            break;
        case '+':
            buf[ptr]++;
            ip++;
            break;
        case '-':
            buf[ptr]--;
            ip++;
            break;
        case '.':
            printf("%c", buf[ptr]);
            ip++;
            break;
        case ',':
            buf[ptr] = getchar();
            ip++;
            break;
        case '[':
            stackframe[sp++] = ip;
            if (buf[ptr] == 0)
            {
                while(1)
                {
                    ip++;
                    if (code[ip] == ']')
                    {
                    	sp--;
                        ip++;
                        break;
                    }
                }
            }
            else
            {
                ip++;
            }
            break;
        case ']':
            if (buf[ptr] != 0)
            {
                ip = stackframe[sp-1];
                ip++;
            }
            else
            {
            	sp--;
                ip++;
            }
            break;
        default:
            fprintf(stderr, "err:%X, ip:%d, size:%d\n", code[ip], ip, clen);
            exit(-1);
            break;
        }

        if (clen <= ip)
        {
            break;
        }
    }
    exit(0);
}

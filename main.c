#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_SYMBOL 'a'
#define END_SYMBOL 'z'

int s_gets(char* str, int n)
{
    char* str_read = fgets(*str, n, stdin);
    if (!str_read)
        return 0;

    for(;*str >= START_SYMBOL && *str <= END_SYMBOL; str++);

    if (*str == '\n') *str = '\0';
    else if (*str && *str < START_SYMBOL || *str > END_SYMBOL)
        return 0;
    return 1;
}

void usage(){
    printf("encrypd|decrypt input.file output.file");
}

int main(int argc, char* argv[])
{
    if(argc < 3){
        printf("Wrong input!\n");
        usage();
        return 1;
    }
    FILE *fIn = fopen(argv[2],"r");
    if(!fIn){
        printf("Wrong input file path!\n");
        usage();
        return 2;
    }
    FILE *fOut = fopen(argv[3],"w");
    if(!fOut){
        printf("Wrong output file path!\n");
        usage();
        return 3;
    }
    char* key = malloc(501);
    if(!s_gets(key, 500)){
        printf("Wrong key format!\n");
        return 4;
    }
    int key_size = strlen(key);
    char next = 0, i = 0;
    if(strcmp(argv[1],"encrypd")==0){
        while((next = getc(fIn)) != EOF){
            printf("READ\n");
            char plain_c = next - START_SYMBOL;
            char key_c = key[i % key_size] - START_SYMBOL;
            char c = (plain_c + key_c) % (END_SYMBOL - START_SYMBOL);
            printf("%d %d %d\n",plain_c, key_c, c);
            fprintf(fOut,"%c",(char)(c + START_SYMBOL));
            i++;
        }
        return 0;
    }
    if(strcmp(argv[1],"decrypt")==0){
        while((next = getc(fIn)) != EOF){
            char chiper_c = next - START_SYMBOL;
            char key_c = key[i % key_size] - START_SYMBOL;
            char c = chiper_c - key_c;
            if (c < 0)
                c += END_SYMBOL - START_SYMBOL;
            fprintf(fOut,"%c",c + START_SYMBOL);
            i++;
        }
        return 0;
    }
    printf("Wrong command!\n");
    usage();
    return 4;
}

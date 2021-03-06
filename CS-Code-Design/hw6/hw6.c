/************************************************************
 * 學號：E64061151
 * 姓名：林友鈞
 * 編譯方式：gcc -std=c99 -o hw6 hw6.c
 * 執行方式：./hw6 filename
 * 程式功能：分析檔案裡的資料
 * 更新日期：2018/12/1
 ************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sRule{
    char **rule;
    int capacity;
    int size;
};

void REALLOC(struct sRule *rules){
    rules->rule = (char **)realloc((void *)rules->rule,(rules->capacity+=10)*sizeof(char *));
    if(!rules->rule){printf("realloc failed\n"); exit(0);}
}

void Push_NewRule(struct sRule *rules,char * rule){
    if(rules->size + 1 >= rules->capacity){REALLOC(rules);}
    char * new_rule = (char *)malloc((strlen(rule)+1)*sizeof(char));
    strcpy(new_rule,rule);
    rules->rule[rules->size++] =  new_rule;
}

void ComputeRule(struct sRule * rules,char * new){
    for(int i = 0; i < rules->size; i++) if(!strcmp(rules->rule[i],new)) return;
    Push_NewRule(rules,new);
}

struct sRule * Constructor(){
    struct sRule * rules = malloc(sizeof(struct sRule));
    rules->capacity = rules->size = 0;
    rules->rule = NULL;
    return rules;
}

void ComputeDontCare(char * newrule,char * dontcare,int * count){
    if(!strcmp(dontcare,newrule)) (*count)++;
}

int main(int argc, char const *argv[])
{
    if(argc == 1){printf("argument pass failed\n Please give the filename"); exit(0);}
    FILE * file = NULL;
    file  = fopen(argv[1],"r");
    if(!file){printf("FILE openning failed\nPlease check if file is under the directory\n");exit(0);}

    char **rule;
    struct sRule * fw[6];
    struct sRule sub_rule;

    // initialize for rule
    rule = malloc(6 * sizeof(char *));
    for(int i = 0; i < 5; i++) rule[i] = malloc(25 * sizeof(char));
    rule[5] = (char *)malloc(40 * sizeof(char));// for subrule
    
    int f3[2]={0,0},f4[2] = {0,0};// for integer which is store field 3 and field 4

    char **do_not_care = (char **)malloc(5 * sizeof(char *));
    {
        // initialize don't care
        for(int i = 0; i < 5; i++) do_not_care[i] = (char *)malloc(25 * sizeof(char));
        strcpy(do_not_care[0],"@0.0.0.0/0");
        strcpy(do_not_care[1],"0.0.0.0/0");
        strcpy(do_not_care[2],"0 : 65535");
        strcpy(do_not_care[3],"0 : 65535");
        strcpy(do_not_care[4],"0x00/0x00");
    }
    int dontcare_count[5] = {0,0,0,0,0};

    for(int i = 0; i < 6; i++) fw[i] = Constructor();
	int num = 0;
    while(EOF != fscanf(file,"%s %s %d : %d %d : %d %s",rule[0],rule[1],&f3[0],&f3[1],&f4[0],&f4[1],rule[4])){
        //printf("%s\n",rule[0]);
        sprintf(rule[2],"%d : %d",f3[0],f3[1]);
        sprintf(rule[3],"%d : %d",f4[0],f4[1]);
        sprintf(rule[5],"%s %s %s",rule[2],rule[3],rule[4]); // subrule
        for(int i = 0; i < 5; i++){
            ComputeRule(fw[i],rule[i]);
            ComputeDontCare(rule[i],do_not_care[i],&dontcare_count[i]);
        }
        ComputeRule(fw[5],rule[5]);
		num++;
    }
    for(int i = 0; i < 5; i++){
        printf("F%d: %d\n",i+1,fw[i]->size);
    }
	printf("\n");
    for(int i = 0; i < 5; i++){
        printf("F%d: %d\n",i+1,dontcare_count[i]);
    }
	printf("\n%d\n",num);
	printf("\n%d\n",fw[5]->size);
    fclose(file);
    return 0;
}

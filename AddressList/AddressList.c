#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 256

//����`
int Node_Id;
char Node_Lname[64];
char Node_Fname[64];
char Node_Email[64];

int read;
int total;//���R�[�h���L�^(countID-countDel)
int countId;//ID�Ǘ�
int countDel;//�폜����ID�̃J�E���g
int inputD;//�폜ID�i�[
int num;
char inputF[64];//����ID�i�[
int i;//���[�v�p
int j;
char *moji_kari;

//��RECORD�@�\����
typedef struct record{
    int id;
    char lname[64];
    char fname[64];
    char email[64];
    struct record *next;//���̃f�[�^
} RECORD;

RECORD *head = NULL;//�擪
RECORD *tail = NULL;//����
RECORD *Node_Make(void);
void ReadData(void);void WriteData(void);void Find(void);
void Add(void);void Delete(void);
void Sort(void);void Print(void);


//�m�[�h�쐬
RECORD *Node_Make(void){
    RECORD *Node_New;//�ꏊ��
    Node_New = (RECORD *)malloc(sizeof(RECORD));//�f�[�^�m�ہi�|�C���^���̂́j
    return Node_New;}

//��ReadData�@�ǂݍ���
void ReadData(void){
    FILE *fp;
    RECORD *Node_Read;

	char filename[]="AddressList.txt";
	char moji[N];
    char *p;
 
	fp = fopen(filename,"r");
	if(fp==NULL){printf("�t�@�C�����J���܂���c");return;}

	while((fgets(moji,sizeof(moji),fp))!=NULL){
        printf("%s", moji);
        i++;

        if(strcmp(moji,"--------------------------------------------\n")==0)continue;

        if(i>=3){//���R�[�h���̍s�͖���
            moji_kari = strtok(moji," ");//moji���X�y�[�X���Ƃɕ���
            strcpy(Node_Lname, moji_kari);
    
            moji_kari=strtok(NULL," ");//NULL���擪�ɂȂ��Ă���
            strcpy(Node_Fname, moji_kari);

            moji_kari=strtok(NULL," ");
            p=strchr(moji_kari,'\n');
            if(p!=NULL)*p='\0';
            strcpy(Node_Email, moji_kari);

            Add();
        }
	}
    read=1;
 
	fclose(fp);
    printf("�ǂݍ��݂܂���\n");
	return;
}

//��WriteData�@��������
void WriteData(void){
    FILE *fp;
    RECORD *Node_Write;
    fp = fopen("AddressList.txt","w");
    if(fp == NULL){printf("�����ȃR�}���h\n");exit(1);}

    if((head == NULL)&&(tail == NULL)){printf("�f�[�^�Ȃ�\n");return;}

    Node_Write = head;
    printf("--------------------------------------------\n");
    fputs("--------------------------------------------\n",fp);
    fprintf(fp,"%d",total);
    while(1){
        printf("%d\n",Node_Write->id);
        printf("%s ",Node_Write->lname);
        printf("%s ",Node_Write->fname);
        printf("%s\n",Node_Write->email);
        printf("--------------------------------------------\n");

        fputs("\n",fp);
        fputs(Node_Write->lname,fp);
        fputs(" ",fp);
        fputs(Node_Write->fname,fp);
        fputs(" ",fp);
        fputs(Node_Write->email,fp);
        if (Node_Write->next != NULL){Node_Write = Node_Write->next;}
        else{printf("�������݂܂���\n");break;}
    }
    fputs("\n--------------------------------------------\n",fp);
    fclose(fp);
}

//��Add�@�ǉ�
void Add(void){
    RECORD *Node_New;

    Node_New = Node_Make();
    Node_Id = countId + 1;
    //����
    Node_New->id = Node_Id;

    //�ǂݍ��ݏ���
    if(read==0){
        strcpy(Node_New->lname, Node_Lname);
        strcpy(Node_New->fname, Node_Fname);
        strcpy(Node_New->email, Node_Email);}
    else{
    printf("���F");scanf("%s", Node_Lname);strcpy(Node_New->lname, Node_Lname);
    printf("���F");scanf("%s", Node_Fname);strcpy(Node_New->fname, Node_Fname);
    printf("���[���A�h���X�F");scanf("%s", Node_Email);strcpy(Node_New->email, Node_Email);
    printf("�ǉ����܂���\n");}
    

    //����
    if ((head == NULL)&&(tail == NULL)){
        head = Node_New;
        tail = Node_New;}
    else{//����Ȃ�i1�ȏ�j
        tail->next = Node_New;//�����f�[�^�̌��ɐV�m�[�h
        tail = Node_New;}//�V�m�[�h�������f�[�^�ɂȂ�
        tail->next = NULL;
    countId = countId + 1;
    total = total + 1;}

//��Delete�@�폜
void Delete(void){
    RECORD *Node_Delete;
    RECORD *kakunoD;
    printf("�폜�������f�[�^��ID�F");
    scanf("%d", &inputD);
    if(inputD>countId){printf("�Ȃ��ł��B");return;}
    Node_Delete = head;
    kakunoD = Node_Delete;

    for (i=1; Node_Delete->id!=inputD; i++){//�폜ID�܂ňړ�����
        kakunoD = Node_Delete;//��O�̏����L�^
        Node_Delete = Node_Delete->next;}

    if(Node_Delete!=head){kakunoD->next = Node_Delete->next;}//�폜�Ώۂ̑OkakunoD�ƍ폜�Ώۂ̎����Ȃ���
    if((Node_Delete!=head)&&(Node_Delete==tail)){tail = kakunoD;}//tail�������ꍇ�A�O��tail��

    if((Node_Delete==head)&&(Node_Delete==tail)){tail = Node_Delete->next;}//tail�������ꍇ�A����tail��
    if(Node_Delete==head){head = Node_Delete->next;}//head�������ꍇ�A����head��

    free(Node_Delete);

    printf("�폜���܂���\n");
    countDel = countDel + 1;//���������̏��������炷(�������f�[�^��)
    total = total - 1;}

//��Find�@����
void Find(void){
    RECORD *Node_Find;
    Node_Find = head;
    i=0;
    printf("1�F���@2�F���@3�F���[���A�h���X\n");
    printf("�����ΏہF");
    scanf("%d", &num);

    printf("�����P��F");
    scanf("%s", inputF);

    while(i<countId){
        int find_ok = 0;
        switch (num){
            case 1:if(strcmp(inputF,Node_Find->lname)==0){find_ok=1;};break;
            case 2:if(strcmp(inputF,Node_Find->fname)==0){find_ok=1;};break;
            case 3:if(strcmp(inputF,Node_Find->email)==0){find_ok=1;};break;
            printf("\n");}
        
        if(find_ok == 1){
            printf("--------------------------------------------\n");
            printf("%d\n", Node_Find->id);
            printf("%s�@", Node_Find->lname);
            printf("%s�@", Node_Find->fname);
            printf("%s\n", Node_Find->email);
            printf("--------------------------------------------\n");}
            if(Node_Find->next!=NULL){Node_Find=Node_Find->next;}
            i++;}
    printf("�������܂���\n");
}

//��Sort�@����
void Sort(void){
    RECORD *Prev_L,*Node_Sort_L,*Next_L;
    RECORD *Prev_R,*Node_Sort_R,*Next_R;
    RECORD *Sort_L,*Sort_R;

    int i=0;j=1;
    int sort_ok;
    int sort_data;

    Sort_L = head;
    Sort_R = Sort_L->next;
    Prev_L = NULL;
    Prev_R = Sort_L;

    printf("1�F���@2�F���@3�F���[���A�h���X\n");
    printf("����ΏہF");
    scanf("%d", &num);
    printf("1�F�����@2�F�~���@���@");
    scanf("%d", &sort_ok);
    
    if(Sort_L->next==NULL)return;
    while(1){
        while(1){
            Node_Sort_L = Sort_R;
            Node_Sort_R = Sort_L;
            j=1;
            while(1){
                switch(num){
                    case 1:sort_data=strncmp(Sort_L->lname,Sort_R->lname, j);break;
                    case 2:sort_data=strncmp(Sort_L->fname,Sort_R->fname, j);break;
                    case 3:sort_data=strncmp(Sort_L->email,Sort_R->email, j);break;}
            if((sort_data!=0)||j==64)break;
            j++;}
            
            //L���傫���Ɛ��̒l
            if((sort_ok==1&&sort_data>0)||(sort_ok==2&&sort_data<0)){
                Next_L = Sort_L->next;
                Next_R = Sort_R->next;
                if(Prev_L!=NULL){Prev_L->next = Sort_R;}//Lp-R
                if(Prev_R!=Sort_L)Prev_R->next = Sort_L;//Rp-L
                Node_Sort_R->next = Next_R;//L-Rn

                //�אځEL�̎���R�̏ꍇ R-L
                if(Next_L == Sort_R){Node_Sort_L->next = Sort_L;}
                //�אڂ��Ă��Ȃ��ꍇ R-Ln
                else{Node_Sort_L->next = Next_L;}

                //������L��head���ǂ���
                if(Sort_L==head){head = Node_Sort_L;}
                //������R��tail���ǂ���
                if(Sort_R==tail){tail = Node_Sort_R;}

                Sort_L = Node_Sort_L;
                Sort_R = Node_Sort_R;
            }
        //tail�܂ł������ꍇ�i������or�����ρj
        if((Sort_R==tail)||(Sort_L==tail))break;

        //R�̑O�m�[�h���L���iR����������Ȃ���΁j
        Prev_R = Sort_R;
        Sort_R=Sort_R->next;}
    if(i==total-2)break;
    Prev_L = Sort_L;
    Sort_L=Sort_L->next;

    Prev_R = Sort_L;//���߁AR�̑O��L
    Sort_R = Sort_L->next;//R��L�̎�
    i++;}
    printf("���񂵂܂���\n");
}

//��Print�@�\��*�e�X�g�p
void Print(void){
    RECORD *Node_Write;
    i=0;
    if((head == NULL)&&(tail == NULL)){printf("�f�[�^�Ȃ�\n");return;}
    Node_Write = head;
    printf("--------------------------------------------\n");
    while(1){
        i++;
        printf("%d\n", Node_Write->id);
        printf("%s ", Node_Write->lname);
        printf("%s ", Node_Write->fname);
        printf("%s\n", Node_Write->email);
        printf("--------------------------------------------\n");
        if(i==15)break;
        if(Node_Write->next != NULL){Node_Write = Node_Write->next;}
        else{printf("�����I\n");break;}
    }
}

//�����C��
int main(void){
    int input;

    ReadData();

    while (1){
        printf("1:�ǉ��@2:�폜�@3:�����@4:����@5:�ۑ����ďI��\n");
        printf("����:");
        scanf("%d", &input);
        switch (input){
            case 1:Add();break;
            case 2:Delete();break;
            case 3:Find();break;
            case 4:Sort();break;
            case 5:WriteData();break;
            case 6:Print();break;
            default:printf("�����c\n");break;}
        printf("\n");}
    return 0;}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 256

//◆定義
int Node_Id;
char Node_Lname[64];
char Node_Fname[64];
char Node_Email[64];

int read;
int total;//レコード数記録(countID-countDel)
int countId;//ID管理
int countDel;//削除したIDのカウント
int inputD;//削除ID格納
int num;
char inputF[64];//検索ID格納
int i;//ループ用
int j;
char *moji_kari;

//◆RECORD　構造体
typedef struct record{
    int id;
    char lname[64];
    char fname[64];
    char email[64];
    struct record *next;//次のデータ
} RECORD;

RECORD *head = NULL;//先頭
RECORD *tail = NULL;//末尾
RECORD *Node_Make(void);
void ReadData(void);void WriteData(void);void Find(void);
void Add(void);void Delete(void);
void Sort(void);void Print(void);


//ノード作成
RECORD *Node_Make(void){
    RECORD *Node_New;//場所名
    Node_New = (RECORD *)malloc(sizeof(RECORD));//データ確保（ポインタ自体の）
    return Node_New;}

//◆ReadData　読み込み
void ReadData(void){
    FILE *fp;
    RECORD *Node_Read;

	char filename[]="AddressList.txt";
	char moji[N];
    char *p;
 
	fp = fopen(filename,"r");
	if(fp==NULL){printf("ファイルを開けません…");return;}

	while((fgets(moji,sizeof(moji),fp))!=NULL){
        printf("%s", moji);
        i++;

        if(strcmp(moji,"--------------------------------------------\n")==0)continue;

        if(i>=3){//レコード数の行は無視
            moji_kari = strtok(moji," ");//mojiをスペースごとに分割
            strcpy(Node_Lname, moji_kari);
    
            moji_kari=strtok(NULL," ");//NULLが先頭になっている
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
    printf("読み込みました\n");
	return;
}

//◆WriteData　書き込み
void WriteData(void){
    FILE *fp;
    RECORD *Node_Write;
    fp = fopen("AddressList.txt","w");
    if(fp == NULL){printf("無効なコマンド\n");exit(1);}

    if((head == NULL)&&(tail == NULL)){printf("データなし\n");return;}

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
        else{printf("書き込みました\n");break;}
    }
    fputs("\n--------------------------------------------\n",fp);
    fclose(fp);
}

//◆Add　追加
void Add(void){
    RECORD *Node_New;

    Node_New = Node_Make();
    Node_Id = countId + 1;
    //入力
    Node_New->id = Node_Id;

    //読み込み処理
    if(read==0){
        strcpy(Node_New->lname, Node_Lname);
        strcpy(Node_New->fname, Node_Fname);
        strcpy(Node_New->email, Node_Email);}
    else{
    printf("姓：");scanf("%s", Node_Lname);strcpy(Node_New->lname, Node_Lname);
    printf("名：");scanf("%s", Node_Fname);strcpy(Node_New->fname, Node_Fname);
    printf("メールアドレス：");scanf("%s", Node_Email);strcpy(Node_New->email, Node_Email);
    printf("追加しました\n");}
    

    //処理
    if ((head == NULL)&&(tail == NULL)){
        head = Node_New;
        tail = Node_New;}
    else{//あるなら（1つ以上）
        tail->next = Node_New;//末尾データの後ろに新ノード
        tail = Node_New;}//新ノードが末尾データになる
        tail->next = NULL;
    countId = countId + 1;
    total = total + 1;}

//◆Delete　削除
void Delete(void){
    RECORD *Node_Delete;
    RECORD *kakunoD;
    printf("削除したいデータのID：");
    scanf("%d", &inputD);
    if(inputD>countId){printf("ないです。");return;}
    Node_Delete = head;
    kakunoD = Node_Delete;

    for (i=1; Node_Delete->id!=inputD; i++){//削除IDまで移動する
        kakunoD = Node_Delete;//手前の情報を記録
        Node_Delete = Node_Delete->next;}

    if(Node_Delete!=head){kakunoD->next = Node_Delete->next;}//削除対象の前kakunoDと削除対象の次をつなげる
    if((Node_Delete!=head)&&(Node_Delete==tail)){tail = kakunoD;}//tailを消す場合、前をtailに

    if((Node_Delete==head)&&(Node_Delete==tail)){tail = Node_Delete->next;}//tailを消す場合、次をtailに
    if(Node_Delete==head){head = Node_Delete->next;}//headを消す場合、次をheadに

    free(Node_Delete);

    printf("削除しました\n");
    countDel = countDel + 1;//減った分の処理を減らす(消したデータ数)
    total = total - 1;}

//◆Find　検索
void Find(void){
    RECORD *Node_Find;
    Node_Find = head;
    i=0;
    printf("1：姓　2：名　3：メールアドレス\n");
    printf("検索対象：");
    scanf("%d", &num);

    printf("検索単語：");
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
            printf("%s　", Node_Find->lname);
            printf("%s　", Node_Find->fname);
            printf("%s\n", Node_Find->email);
            printf("--------------------------------------------\n");}
            if(Node_Find->next!=NULL){Node_Find=Node_Find->next;}
            i++;}
    printf("検索しました\n");
}

//◆Sort　整列
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

    printf("1：姓　2：名　3：メールアドレス\n");
    printf("整列対象：");
    scanf("%d", &num);
    printf("1：昇順　2：降順　→　");
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
            
            //Lが大きいと正の値
            if((sort_ok==1&&sort_data>0)||(sort_ok==2&&sort_data<0)){
                Next_L = Sort_L->next;
                Next_R = Sort_R->next;
                if(Prev_L!=NULL){Prev_L->next = Sort_R;}//Lp-R
                if(Prev_R!=Sort_L)Prev_R->next = Sort_L;//Rp-L
                Node_Sort_R->next = Next_R;//L-Rn

                //隣接・Lの次がRの場合 R-L
                if(Next_L == Sort_R){Node_Sort_L->next = Sort_L;}
                //隣接していない場合 R-Ln
                else{Node_Sort_L->next = Next_L;}

                //交換元Lがheadかどうか
                if(Sort_L==head){head = Node_Sort_L;}
                //交換先Rがtailかどうか
                if(Sort_R==tail){tail = Node_Sort_R;}

                Sort_L = Node_Sort_L;
                Sort_R = Node_Sort_R;
            }
        //tailまでいった場合（未交換or交換済）
        if((Sort_R==tail)||(Sort_L==tail))break;

        //Rの前ノードを記憶（Rが末尾でなければ）
        Prev_R = Sort_R;
        Sort_R=Sort_R->next;}
    if(i==total-2)break;
    Prev_L = Sort_L;
    Sort_L=Sort_L->next;

    Prev_R = Sort_L;//初め、Rの前はL
    Sort_R = Sort_L->next;//RはLの次
    i++;}
    printf("整列しました\n");
}

//◆Print　表示*テスト用
void Print(void){
    RECORD *Node_Write;
    i=0;
    if((head == NULL)&&(tail == NULL)){printf("データなし\n");return;}
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
        else{printf("完了！\n");break;}
    }
}

//◆メイン
int main(void){
    int input;

    ReadData();

    while (1){
        printf("1:追加　2:削除　3:検索　4:整列　5:保存して終了\n");
        printf("入力:");
        scanf("%d", &input);
        switch (input){
            case 1:Add();break;
            case 2:Delete();break;
            case 3:Find();break;
            case 4:Sort();break;
            case 5:WriteData();break;
            case 6:Print();break;
            default:printf("無効…\n");break;}
        printf("\n");}
    return 0;}

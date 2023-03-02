#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_STR 100
#define MAX_CSV 100

typedef struct
{
    char namae[50],iro[50];
    int kosuu,maisuu;
    double nagasa,haba;
}GDATA;

int i,num1;
char scan[100];
GDATA data[20],data2[20];
FILE*f1;

int yomikomi(char*fn,int data_num)/*ファイルの読み込み*/
{
    char str[MAX_STR];
    data_num=0;

    if(fn==NULL)
    {printf("ファイルが入力されませんでした");}
    else if((f1=fopen(fn,"r+"))==NULL)
    {printf("ファイルが見つかりません");}
    else 
    {
         while(fgets(str,MAX_STR,f1))/*whileがループした数を数える*/
        {
            sscanf(str,"%[^,],%[^,],%d,%d,%lf,%lf",data[data_num].namae,data[data_num].iro,&data[data_num].kosuu,&data[data_num].maisuu,&data[data_num].nagasa,&data[data_num].haba);
            data_num++;
            if(data_num>MAX_CSV)/*while終了の条件*/
            break;
        }

        for(i=0;i<data_num;i++)
        {fscanf(f1,"%[^,],%[^,],%d,%d,%lf,%lf",data[i].namae,data[i].iro,&data[i].kosuu,&data[i].maisuu,&data[i].nagasa,&data[i].haba);}
        fclose(f1);
    }
   
   return data_num;
}

int kairan(int data_num)/*回覧*/
{
    for(i=0;i<data_num;i++)
    {printf("\n%s,%s,%d,%d,%lf,%lf",data[i].namae,data[i].iro,data[i].kosuu,data[i].maisuu,data[i].nagasa,data[i].haba);}

    return data_num;
}

int tsuika(int data_num)/*追加*/
{
    char back_1[20]="9";

    printf("名称を入力してください（9.戻る）\n");
    scanf("%s",scan);
    if(strcmp(back_1,scan)==0)/*9が入力された場合*/
    {}
    else
    {
        strcpy(data[i].namae,scan);/*入力された文字列を構造体にコピー*/
        printf("色を入力してください：\n");
        scanf("%s",data[i].iro);
        printf("個数を入力してください：\n");
        scanf("%d",&data[i].kosuu);
        printf("葉の枚数を入力してください：\n");
        scanf("%d",&data[i].maisuu);
        printf("長さを入力してください：\n");
        scanf("%lf",&data[i].nagasa);
        printf("幅を入力してください：\n");
        scanf("%lf",&data[i].haba);
        data_num++;/*データ数の調節*/
        kairan(data_num);/*追加後の回覧*/
    } 

    return data_num;
}

int sakujo(int data_num)/*削除*/
{
    while(1)
    {
        data_num=kairan(data_num);

        printf("\n削除する行を入力してください(9.戻る)：\n");
        scanf("%d",&num1);

        if(num1==9)/*num1に入力された整数が"9"であれば戻るための命令*/
        {break;}
        else if((1<=num1)&&(num1<=data_num))/*num1に入力された整数が1以上現状あるデータ数以下であれば実行するための命令*/
        {
            num1=num1-1;
            for(i=0;i<data_num;i++)/*選択された行に一つ後の行を代入していくループ*/
            {
                data[num1]=data[num1+1];
                num1++;
            }

            data_num--;/*削除によるデータ数の変化に対応するための命令*/
            printf("\n");
            data_num=kairan(data_num);
            break;
        }
        else /*num1に入力された整数がその他であれば以下の文を表示し戻る*/
        {printf("入力に誤りがあります\n");}
    }
    return data_num;
}

int narabekae(int data_num)/*並び替え*/
{
    int t;
    
    while(1)
    {
        printf("\n個数で並び替えます\n\n1.昇順 2.降順 9.戻る\n\n番号を入力してください：");
        scanf("%d",&num1);/*入力した整数をnum1に代入する*/
        
        if(num1==9)/*num1に入力された整数が"9"であれば戻るための命令*/
        {break;}
        else if(num1==1)/*num1に入力された整数が"1"であれば昇順の並び替えを実行するための命令*/
        {
            for(i=0;i<data_num;i++)
            {
                for(t=i+1;t<data_num;t++)
                {
                    if(data[i].kosuu>data[t].kosuu)
                    {
                        data2[i]=data[i];
                        data[i]=data[t];
                        data[t]=data2[i];
                    }
                }
            }
            
            break;
        }
        else if(num1==2)/*num1に入力された整数が"2"であれば降順の並び替えを実行するための命令*/
        {
            for(i=0;i<data_num;i++)
            {
                for(t=i+1;t<data_num;t++)
                {
                    if(data[i].kosuu<data[t].kosuu)
                    {
                        data2[i]=data[i];
                        data[i]=data[t];
                        data[t]=data2[i];
                    }
                }
            }
            
            break;
        }
        else/*num1に入力された整数がその他であれば以下の文を表示し戻る*/
        {printf("\n入力に誤りがあります\n\n");}
    }

    data_num=kairan(data_num);
    printf("\n");

    return data_num;
} 

int save(char*fn,int data_num)/*上書き保存*/
{
    f1=fopen(fn,"w");
    for(i=0;i<data_num;i++)
    {fprintf(f1,"%s,%s,%d,%d,%lf,%lf\n",data[i].namae,data[i].iro,data[i].kosuu,data[i].maisuu,data[i].nagasa,data[i].haba);}
    fclose(f1);

    return data_num;
}

int new_save(int data_num)/*名前をつけて保存*/
{

    printf("「ファイル名.識別子」の形で入力してください\n");
    scanf("%s",scan);
    f1=fopen(scan,"w");
    for(i=0;i<data_num;i++)
    {fprintf(f1,"%s,%s,%d,%d,%lf,%lf\n",data[i].namae,data[i].iro,data[i].kosuu,data[i].maisuu,data[i].nagasa,data[i].haba);}
    fclose(f1);

    return data_num;
}

int main(int argc,char*argv[])//メイン関数
{
    int num_ed;
    int num=0;
    int data_num=0;
    char back_1[20]="9";
    char*fn=argv[1];
    
    data_num=yomikomi(fn,data_num);

    while(1)
    {
        num_ed=num;

        printf("\n\n番号を入力してください\n1.データの閲覧 \n2.追加 \n3.削除 \n4.並び替え \n5.ファイルを開く \n6.上書き保存 \n7.名前をつけて保存 \n8.終了\n\n");
        scanf("%d",&num);

        if (num==1)/*回覧*/
        {data_num=kairan(data_num);}
        else if(num==2)/*追加*/
        {data_num=tsuika(data_num);}
        else if(num==3)/*削除*/
        {data_num=sakujo(data_num);}
        else if(num==4)/*並べ替え*/
        {data_num=narabekae(data_num);} 
        else if(num==5)/*ファイルを開く*/
        {
            printf("ファイル名を入力してください(9.戻る)");
            scanf("%s",scan);

            if(strcmp(back_1,scan)==0)
            {}
            else
            {
                fn=scan;
                data_num=yomikomi(fn,data_num);
            }
        }
        else if(num==6)/*上書き保存*/
        {data_num=save(fn,data_num);}
        else if(num==7)/*名前をつけて保存*/
        {data_num=new_save(data_num);}
        else if(num==8)/*終了*/
        {
            if((num_ed==6)||(num_ed==7))
            {break;}
            else
            {
                printf("保存されていません\n1.終了\n2.上書き保存して終了\n3.名前をつけて保存して終了\n9.戻る");
                scanf("%d",&num1);

                if(num1==1)
                {break;}
                else if(num1==2)
                {
                    data_num=save(fn,data_num);
                    break;
                }
                else if(num1==3)
                {
                    data_num=new_save(data_num);
                    break;
                }
                else if(num1==9)
                {}
            }
        }
        else/*エラー処理*/
        {printf("入力に誤りがあります\n");}
    }
}


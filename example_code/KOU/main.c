#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_INVENTORY 100 // 最多有100筆存貨資料
#define MAX_ERRORS 100    // 最多有100筆錯誤資料

typedef char Str30[30]; // 能存放最多30個字元的字串

typedef struct Product {
    Str30 barCode;         // 條碼（有時稱「序號」）
    Str30 name;            // 商品名稱
    int cost;              // 成本
    int amountLeft;        // 倉庫中有多少貨
    int amountSold;        // 總共賣出幾件
    int bestProfitPerItem; // 單筆最佳利潤（注意！這是正數）
    int worstLossPerItem;  // 單筆最慘損失（注意！這是負數）
    int profit;            // 總共賺了多少
} Product;

int gNumOfProducts = 0; // 'inventory[]'之中總共有多少筆存貨資料

typedef enum ErrorType {
    BAR_CODE_FORMAT_ERROR = 1829371,  // 條碼格式錯誤
    BAR_CODE_WRONG = 2172429,         // 條碼錯誤（商品名稱有問題）
    NO_SUCH_PRODUCT = 3282617,        // 商品不存在
    NEGATIVE_NUMBER = 4791202,        // 負數錯誤
    NOT_ENOUGH_CAPITAL = 5012743,     // 資本不足
    NOT_ENOUGH_MERCHANDISE = 6139072, // 商品不足
    DATE_FORMAT_ERROR = 7791023,      // 日期格式錯誤
    DATE_CONTENT_ERROR = 8221719,     // 日期內容錯誤
    DATE_SEQUENCE_ERROR = 9237291     // 日期順序錯誤
} ErrorType;

typedef struct Error {
    ErrorType type; // 是什麼形式的錯誤
    Str30 barCode;  // 條碼（如果需要記下就記在這裡）
    Str30 name;     // 商品名稱（如果需要記下就記在這裡）
    Str30 dateStr;  // 日期的字串（如果需要記下就記在這裡）
} Error;


int gNumOfErrors = 0; // 'errors[]'之中總共有多少筆錯誤資料

typedef struct Date {
    int year;
    int month;
    int day;
} Date; // struct Date

Date gCurrentDate = {0, 0, 0}; // 目前的日期

typedef struct Statistics {
    int capital;                      // 目前本店手頭上有多少資本
    int salesOfCurrentDate;           // 到目前一天的銷售額
    int netSales;                     // 到目前為止全部的銷售額
    int netProfit;                    // 到目前為止全部（因為銷售貨品）賺到的錢
    int bestSalesYear, bestSalesMonth, bestSalesDay;   // 銷售額最高的是哪一年、哪個月、哪一天
    int bestSalesAmount;              // 銷售額最高的是多少
    int worstSalesYear, worstSalesMonth, worstSalesDay; // 銷售額最低的是哪一年、哪個月、哪一天
    int worstSalesAmount;             // 銷售額最低的是多少
} Statistics;

//Statistics gStat = {0, 0, 0, 0, 0, 0, 0, INT_MIN, 0, 0, 0, INT_MAX};

typedef struct PurchasedItem {
    Str30 barCode;  // 條碼（有時稱「序號」）
    Str30 name;     // 商品名稱
    int unitPrice;  // 單價
    int amount;     // 買的個數
} PurchasedItem; // struct PurchasedItem

typedef struct SoldItem {
    Str30 barCode;  // 條碼（有時稱「序號」）
    Str30 name;     // 商品名稱
    int unitPrice;  // 單價
    int amount;     // 賣出的個數
} SoldItem; // struct SoldItem

//--------------------------------------------------
Statistics gStat = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Product inventory[99];
Date last_date,now_date;
struct PurchasedItem PurchasedLog[99]; //儲存進貨的交易紀錄(使用陣列的位置當成是交易序號) 
int check_barcode(Str30 temp){
    char z[30];
    int i;
    if(strlen(temp)==6&&(temp[0]-'A'<26&&temp[0]-'A'>-1)){
        strcpy(z,temp);
        z[0]='0';
        if(sscanf(z,"%d",&i)==1){
            return 1;
        }
    }
    return 0;
}
void capital(void){
    scanf("%d",&gStat.capital);
    if(gStat.capital<0){
        //capital error
    }
}
int check_item(Product *test){
    char temp[40];
    for(int i=0;i<gNumOfProducts;i++){
        if(strcmp(test->barCode,inventory[i].barCode)==0&&strcmp(test->name,inventory[i].name)&&test->cost==inventory[i].cost){
            return i;
        }
    }
    return -404;
}
void STOCK(void){
    Product init;
    char temp[40];
    int z,state=0,count=0,i=0;
    while(1){
        state=0;
        count=0;
        scanf("%s",temp);
        if(strcmp(temp,"end")){
            break;
        }
        strcpy(init.barCode,temp);
        while(1){
            scanf("%s",temp);
            if(sscanf(temp,"%d",&z)!=1){
                init.cost=z;
                scanf("%d",&z);
                init.amountLeft=z;
                break;
            }else{
                if(count!=0){
                    strcat(init.name," ");
                }
                strcat(init.name,temp);
            }
        }
        //next is about checking
        if(init.cost<0){
            state=404;
        }
        if(init.amountLeft<0){
            state=404;
        }
        if(check_barcode(init.barCode)==0){
            state=404;
            //barcode error
        }
        if(state!=404){
            inventory[i]=init;
            gNumOfProducts++;
            i++;
        }
    }
}
void initial(void){
    char temp[40];
    scanf("%s",temp);
    if(strcmp(temp,"CAPITAL")==0){
        capital();
    }
    if(strcmp(temp,"STOCK")==0){
        STOCK();
    }
}
void DATE_Refresh(Date *z){
    char temp[40];
    scanf("%s",temp);
    sscanf(temp,"%d/%d/%d",&z->year,&z->month,&z->day);
    scanf("%s",temp);
}
int DATE_ToInt(Date temp){
    int ans;
    ans=temp.year*10000+temp.month*100+temp.day;
    return ans;
}
int  REVEIVING(void){ //注意他英文打錯receiving 
    Product init;
	char temp[40];
    int i,z,count=0;
    while(1){
        scanf("%s",temp);
        if(strcmp(temp,"end")==0){
            break;
        }
        while(1){
            scanf("%s",temp);
            if(sscanf(temp,"%d",&z)!=1){
                init.cost=z;
                scanf("%d",&z);
                init.amountLeft=z;
                break;
            }else{
                if(count!=0){
                    strcat(init.name," ");
                }
                strcat(init.name,temp);
            }
        }
    }

}
int main(){
    char temp[40];
	initial();
    while(scanf("%s",temp)!=EOF){
        if(strcmp(temp,"DATE")==0){
            DATE_Refrash(now_date);
            if(DATE_ToInt(now_date)<DATE_ToInt(last_date)){
                //Date_error
            }
            last_date=now_date;
        }
        if(strcmp(temp,"RECEIVING")==0){
            REVEIVING();
        }
        if(strcmp(temp,"SHIPPING")==0){
            SHIPPING();
        }
        if(strcmp(temp,"OUTPUT")==0){
            OUTPUT();
            break;
        }
    }
}


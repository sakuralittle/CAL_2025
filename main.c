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


struct PurchasedItem PurchasedLog[99]; //儲存進貨的交易紀錄(使用陣列的位置當成是交易序號) 
int  REVEIVING(void){ //注意他英文打錯receiving 
	int i=0,count=0; //i是輸入到purchaseLog的順序
    char input_str[99],temp[99];//input_str為輸入資料的緩衝變數 
	while(1){
		scanf("%s",input_str);
		if(strcmp(input_str,"end")==0){
			break;
		} 
        strcpy(PurchasedLog[i].barCode,input_str);//條碼輸入
        whlie(1){
            scanf("%c",&temp[count]);
            if(temp[count]=='\n'){ //還沒實驗過換行怎麼寫
                break;
            }
            count++;
        }
	}
	
	

}
int main(){
	printf("HELLO");
	
	
}


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
int gNumOfErrors = 0; // 'errors[]'之中總共有多少筆錯誤資料

typedef struct Date {
    int year;
    int month;
    int day;
} Date; // struct Date

Date gCurrentDate = {0, 0, 0}; // 目前的日期

void Stock(Product inventory[MAX_INVENTORY]){
    char temp[30];
    int isNumber = 1;  // 檢查是否是數字
    int count = 0;	// 貨品數量 

    while(1){
        scanf("%s",inventory[count].barCode);  // 輸入條碼

        if(strcmp(inventory[count].barCode,"end") == 0)	// 掃到 end 就結束 
            break;
            
        inventory[count].name[0] = '\0';
        
        while(1){		// 當 isNameFinished = 1 這裡的 !isNameFinished 為 Not True 代表已經讀完數字了 
		scanf("%s",temp);  // 讀取一個字串(name、cost都有) 
		isNumber = 1;	// 還原為初始值
			 
            for(int j = 0;temp[j] != '\0';j++){		// 檢查是不是整數 
                if(temp[j] < '0' || temp[j] > '9'){
                    isNumber = 0;
                    break;
                }
            }

            if(isNumber == 1){	               
              inventory[count].cost = atoi(temp);   // 把數字存到 inventory[i].cost 中
              break;
            }else{
                if(strlen(inventory[count].name) > 0) {
                    strcat(inventory[count].name," ");
                }
                strcat(inventory[count].name,temp);
            }
        }

        scanf("%d",&inventory[count].amountLeft); // 輸入初始庫存量

        inventory[count].amountSold = 0;		// 	設定已售出量的初始檔 
        inventory[count].profit = 0;		//  設定利潤的初始量 
        inventory[count].bestProfitPerItem = 2147483647;		// INT_MAX 變數類型為 int 的最大初始值	
        inventory[count].worstLossPerItem = -2147483647 - 1;		// INT_MIN 變數類型為 int 的最小初始值
        
        count++;
    }
    gNumOfProducts = count;		// 你媽全域變數下次再說 
} 

 //測試
int main() {
    Product inventory[MAX_INVENTORY];

    // 呼叫 Stock 函數來輸入資料
    Stock(inventory);

    // 印出資料
    printf("\nInventory Details:\n");
    for (int i = 0; i < gNumOfProducts; i++) {
        printf("Barcode: %s\n", inventory[i].barCode);
        printf("Name: %s\n", inventory[i].name);
        printf("Cost: %d\n", inventory[i].cost);
        printf("Stock: %d\n", inventory[i].amountLeft);
    }

    return 0;
}

/* 蘇寫的版本w
#include<string.h>
#define MAX_INVENTORY 100 // 最多有100筆存貨資料
#define MAX_ERRORS 100    // 最多有100筆錯誤資料

typedef char Str30[30]; // 能存放最多30個字元的字串



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

// 功能：
    // 1. 讀取商品數量 N
    // 2. 讀取每個商品的基本資料：
    //    - 條碼 (barCode)
    //    - 成本 (cost)
    //    - 初始庫存量 (amountLeft)
    // 3. 初始化商品其他資料：
    //    - 已售數量 amountSold = 0
    //    - 利潤 profit = 0
    //    - 最佳單品利潤 bestProfitPerItem = INT_MIN
    //    - 最差單品虧損 worstLossPerItem = INT_MAX
void Stock(Product inventory[MAX_INVENTORY]) {
    char temp[30];
    int count = 0;

    while (1) {
        scanf("%s", inventory[count].barCode);               // 掃描條碼
        if (strcmp(inventory[count].barCode, "end") == 0) {  // 如果掃到 "end" 程式終止
            break;
        }

        inventory[count].name[0] = '\0';                     // 初始化商品名稱 清空陣列
        scanf("%s", temp);
        while (!(temp[0] >= '0' && temp[0] <= '9')) {        // 如果不是數字，拼接為名稱
            if (inventory[count].name[0] != '\0') {          //如果字串裡面有內容就會自動加空格
                strcat(inventory[count].name, " ");          // 名稱中間加入空格
            }
            strcat(inventory[count].name, temp);
            scanf("%s", temp);
        }
        inventory[count].cost = atoi(temp);                  // 將成本儲存為數字
        scanf("%d", &inventory[count].amountLeft);           // 掃瞄並儲存

        inventory[count].amountSold = 0;                     // 初始化其他欄位
        inventory[count].profit = 0;
        inventory[count].bestProfitPerItem = 2147483647;		// INT_MAX 變數類型為 int 的最大初始值	
        inventory[count].worstLossPerItem = -2147483647 - 1;		// INT_MIN 變數類型為 int 的最小初始值

        count++;
    }
    gNumOfProducts = count; // 更新全域變數
}
int main() {
    Product inventory[MAX_INVENTORY];
    // 呼叫 Stock 函數來輸入資料
    Stock(inventory);
    // 印出資料
    printf("\nInventory Details:\n");
    for (int i = 0; i < gNumOfProducts; i++) {
        printf("Barcode: %s\n", inventory[i].barCode);
        printf("Name: %s\n", inventory[i].name);
        printf("Cost: %d\n", inventory[i].cost);
        printf("Stock: %d\n", inventory[i].amountLeft);
    }
    return 0;
}
*/

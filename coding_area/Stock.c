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
            } 
			      else{
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

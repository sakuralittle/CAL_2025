// 做一系列的輸入處理
// 錯誤處理
// 更新商品資訊
// 更新最佳/最差單筆利潤
// 更新統計資訊
// 更新最佳/最差銷售日

void Shipping(Product inventory[], Statistic *stat, Error errors[]);

void Shipping(Product inventory[], Statistics *stat, Error errors[]) {
    Str30 barcode;
    int amount , price;
    while(1) {
        scanf("%s", barcode);
        if(!strcmp(barcode,"end")) {
            break;
        }
        scanf("%d %d",amount,price);

        //錯誤處理

        //找貨物
        int found = -1;
        //found用於紀錄是否找到物品 如果有找到 紀錄所在位置
        for (int i = 0 ; i < gNumOfProducts ; i++) {
            if(strcmp(inventory[i].barCode, barcode) == 0) {
                found = i;
                break;
            }
        }
        if(found == -1) {
            //商品不存在
            errors[gNumOfErrors].type = NO_SUCH_PRODUCT;
            strcpy(errors[gNumOfErrors].barCode, barcode);
            gNumOfErrors++;
        }
        if(amount < 0 || price < 0 ) {
            //負數錯誤
            errors[gNumOfErrors].type = NEGATIVE_NUMBER;
            strcpy(errors[gNumOfErrors].barCode, barcode);
            gNumOfErrors++;
        }
        if(amount > inventory[found].amountLeft) {
            //判斷貨物是否足夠
            //因為還沒實作JudgeError的code，所以先寫條件判斷，因為JudgeError裡有NotEnoughMerchandise()可以用
            errors[gNumOfErrors].type = NOT_ENOUGH_MERCHANDISE;
            strcpy(errors[gNumOfErrors].barCode, barcode);
            gNumOfErrors++;
        }

        // 更新商品資訊
        int profit_per_item = price - inventory[found].cost;
        inventory[found].amountLeft -= amount;
        inventory[found].amountSold += amount; 
        inventory[found].profit = amount * profit_per_item;

        // 更新最佳/最差單筆利潤
        if (profit_per_item > inventory[found].bestProfitPerItem) {
            inventory[found].bestProfitPerItem = profit_per_item;
        }
        if (profit_per_item < inventory[found].worstLossPerItem) {
            inventory[found].worstLossPerItem = profit_per_item;
        }
        
        // 更新統計資訊 
        //stat -> salesOfCurrentDate相當於(*stat).salesofCurrentDate
        stat -> salesOfCurrentDate += (price * amount);
        stat -> netSales += (price * amount);
        stat -> netProfit += (profit_per_item * amount);
        
        // 更新最佳/最差銷售日
        if (stat -> salesOfCurrentDate > stat-> bestSalesAmount) {
            stat -> bestSalesAmount = stat -> salesOfCurrentDate;
            stat -> bestSalesYear = gCurrentDate.year;
            stat -> bestSalesMonth = gCurrentDate.month;
            stat -> bestSalesDay = gCurrentDate.day;
        }
        if (stat -> salesOfCurrentDate < stat -> worstSalesAmount) {
            stat -> worstSalesAmount = stat -> salesOfCurrentDate;
            stat -> worstSalesYear = gCurrentDate.year;
            stat -> worstSalesMonth = gCurrentDate.month;
            stat -> worstSalesDay = gCurrentDate.day;
        }
    }
}

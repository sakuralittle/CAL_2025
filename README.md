# CAL_2025

線上共編的連結(透過live share):
main bunch:

＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿by claude 3.5sonnet :D
1. Stock()
主要負責初始化和讀取商品基本資料

Copy
void Stock(Product inventory[]) {
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
}
2. Receiving()
負責處理進貨作業

Copy
void Receiving(Product inventory[], Error errors[]) {
    // 功能：
    // 1. 讀取進貨資料：
    //    - 條碼
    //    - 進貨數量
    // 2. 錯誤檢查：
    //    - 檢查商品是否存在
    //    - 檢查數量是否為負數
    // 3. 更新庫存：
    //    - 增加商品的 amountLeft
    // 4. 處理多批進貨：
    //    - 直到讀到 "end" 才結束
}
3. Shipping()
負責處理出貨銷售作業

Copy
void Shipping(Product inventory[], Statistics *stat, Error errors[]) {
    // 功能：
    // 1. 讀取銷售資料：
    //    - 條碼
    //    - 銷售數量
    //    - 銷售價格
    // 2. 錯誤檢查：
    //    - 檢查商品是否存在
    //    - 檢查數量是否為負數
    //    - 檢查庫存是否足夠
    // 3. 更新商品資訊：
    //    - 減少 amountLeft
    //    - 增加 amountSold
    //    - 計算並累加 profit
    //    - 更新 bestProfitPerItem
    //    - 更新 worstLossPerItem
    // 4. 更新統計資訊：
    //    - 累計 netSales
    //    - 累計 netProfit
    //    - 累計 salesOfCurrentDate
    //    - 更新最佳/最差銷售日
    // 5. 處理多批出貨：
    //    - 每批用一個 "end" 分隔
    //    - 最後一批後用兩個 "end" 結束
}
4. JudgeError()
負責錯誤資訊的輸出處理

Copy
void JudgeError(Error errors[]) {
    // 功能：
    // 1. 根據錯誤類型輸出對應訊息：
    //    - NO_SUCH_PRODUCT：找不到商品
    //    - NEGATIVE_NUMBER：數量為負數
    //    - NOT_ENOUGH_MERCHANDISE：庫存不足
    // 2. 輸出格式：
    //    - 錯誤訊息 + 商品條碼
    // 3. 按照錯誤發生順序輸出
}
5. Processing()
負責最終的資料處理和報表輸出

Copy
void Processing(Product inventory[], Statistics *stat) {
    // 功能：
    // 1. 輸出商品資訊：
    //    - 條碼
    //    - 剩餘庫存
    //    - 銷售數量
    //    - 總利潤
    //    - 最佳單品利潤
    //    - 最差單品虧損
    // 2. 輸出統計資訊：
    //    - 總銷售額
    //    - 總利潤
    //    - 最佳銷售日期及金額
    //    - 最差銷售日期及金額
    // 3. 資料排序：
    //    - 依照商品條碼排序
}
整體系統流程：
初始化階段：

執行 Stock() 讀取基本資料
操作階段：

執行 Receiving() 處理進貨
執行 Shipping() 處理銷售
錯誤發生時記錄到 errors 陣列
結算階段：

執行 JudgeError() 輸出所有錯誤
執行 Processing() 產生最終報表
資料結構：

Copy
typedef struct {
    Str30 barCode;
    int cost;
    int amountLeft;
    int amountSold;
    int profit;
    int bestProfitPerItem;
    int worstLossPerItem;
} Product;

typedef struct {
    int netSales;
    int netProfit;
    int salesOfCurrentDate;
    int bestSalesAmount;
    int bestSalesYear;
    int bestSalesMonth;
    int bestSalesDay;
    int worstSalesAmount;
    int worstSalesYear;
    int worstSalesMonth;
    int worstSalesDay;
} Statistics;

typedef struct {
    ErrorType type;
    Str30 barCode;
} Error;
這樣的模組化設計可以：

讓每個函式專注於特定功能
提高程式碼的可維護性
方便進行除錯和修改
使程式結構更清晰易懂

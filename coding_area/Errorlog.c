//陳哲瑋的Code
bool CheckBarCodeFormatOK(str30 barCode) {
    // 檢查條碼長度是否為 6
    if (strlen(barCode) != 6) {

        return false;
    }

    // 檢查第一個字元是否為英文字母
    if (!isalpha(barCode[0])) {

        return false;
    }

    // 檢查其餘 5 個字元是否全為數字
    for (int i = 1; i < 6; i++) {
        if (!isdigit(barCode[i])) {

            return false;
        }
    }

    // 如果條碼符合規範
   return true;
}



bool CheckBarcodeNameCorrect(str30 barCode,str30 name, Product inventory[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(inventory[i].barCode, barCode) == 0) {
            if (strcmp(inventory[i].name, name) == 0) {

                return true;
            }

            return false;
        }
    }

    return false;
}



bool NoSuchMerchandise(str barCode, Product inventory[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(inventory[i].barCode, barCode) == 0) {

            return true;
        }
    }
    printf("商品不存在\n");
    return false;
}

void CheckForNegativeNumber(int value) {
    if (value < 0) {
        printf("錯誤: 負數錯誤\n");
    }
}
/負數錯誤/

/資本不足/



bool NotEnoughCapital(int required, int currentCapital) {
    if (currentCapital < required) {

        return false;
    }
    return true;
}


bool NotEnoughMerchandise(int required, int stock) {
    if (stock < required) {

        return false;
    }
    return true;
}

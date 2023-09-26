#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <limits.h>
#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

typedef struct StockData SD;

struct StockData {
    int date;
    int g_1000People;
    double g_1000BigHolderPercent;
    double closingPrice;
    int totalStock;
    int totalHolder;
    double avgHold;
    int g_400BigHolderHolds;
    double g_400BigHolderPercent;
    int g_400BigHolderPeople;
    int h_400_600People;
    int h_600_800People;
    int h_800_1000People;
}; //%d %d %lf %lf %d %d %lf %d %lf %d %d %d %d

void rmvCommas(char *s) {
    // printf("%s\n", s);
    char *t, c;
    t = s;
    do {
        c = *s++;
        if(c != ',') 
            *t++ = c;
    } while(c);
}

/*副函式1 找出該檔股票在這三年內的最高價及最低價*/
void findMinMaxPrice(SD* data, int N) {
    double mi = 0xffffff;
    double ma = -1;
    for(int i=0; i<N; i++) {
        double tmp=data[i].closingPrice;
        mi = min(mi, tmp);
        ma = max(ma, tmp);
    }
    printf("Highest price: %.2lf\n", ma);
    printf("Lowest price: %.2lf\n", mi);

}

/*副函式2 該檔股票>1000張大股東持股最高及最低時的收盤價, 以及當時的總股東人數分別是多少*/
void findMinMaxTotalShareholders(SD* data, int N) {
    double mi = 0xffffff;
    double ma = -1;
    int mi_idx, ma_idx;
    for(int i=0; i<N; i++) {

        int tmp = data[i].g_1000BigHolderPercent;

        if(mi > tmp) 
            mi = tmp, mi_idx = i;
        
        if(ma < tmp) 
            ma = tmp, ma_idx = i;
    }
    printf("Price when max(Shareholder having >1000 stocks): %.2lf\n", data[ma_idx].closingPrice);
    printf("Shareholders when max(Shareholder having >1000 stocks): %.2lf\n", data[ma_idx].totalHolder);
    printf("Price when min(Shareholder having >1000 stocks): %.2lf\n", data[mi_idx].closingPrice);
    printf("Shareholders when min(Shareholder having >1000 stocks): %.2lf\n", data[mi_idx].totalHolder);
}

/*副函式3 使用者輸入某一價位, 系統輸出出現該價位的日期.(若有重覆資料, 就都輸出)*/
void findDatesByPrice(SD *data, int N) 
{
    double input;
    char flag=0;
    printf("Enter price desired to search: ");
    scanf("%lf", &input);
    for(int i=0; i<N; i++) {
        if(fabs(data[i].closingPrice - input) < 0.0001) {
            flag = 1;
            printf("Price found on date: %d\n", data[i].date);
        }
    }
    if(!flag) {
        printf("No data found...\n");
    }
}

/*副函式4 最近一週及最近四週的>1000張大股東進出比率是多少*/
void calculateChanges(SD *data)
{
    double latest0, last1, last4, ratio_last1, ratio_last4;
    latest0 = data[0].g_1000BigHolderPercent;
    last1 = data[1].g_1000BigHolderPercent;
    last4 = data[4].g_1000BigHolderPercent;
    ratio_last1 = (latest0 - last1) ;
    ratio_last4 = (latest0 - last4) ;

    printf("The ratio of (shareholder having >1000 stocks) latest week: %.2lf\n", ratio_last1);
    printf("The ratio of (shareholder having >1000 stocks) 4 weeks ago: %.2lf\n", ratio_last4);
}

int main() {

    FILE *fptr;

    SD stockData[200];

    fptr = fopen("1102.TW.csv", "r");

    if(fptr == NULL) {
        printf("Error reading file");
        return 1;
    }
    
    char line[256];

    int count=0;

    while (fgets(line, sizeof(line), fptr) ) {
        // printf("%s", line);
        char *next = line;
        next = strtok(line, ",");
        
        stockData[count].date = atoi(next);
        next = strtok(NULL, ",");

        stockData[count].g_1000People = atoi(next);
        next = strtok(NULL, ",");

        stockData[count].g_1000BigHolderPercent = atof(next);
        next = strtok(NULL, ",");

        stockData[count].closingPrice = atof(next);
        next = strtok(NULL, "\"");
        rmvCommas(next);

        stockData[count].totalStock = atoi(next);
        next = strtok(NULL, "\"");
        next = strtok(NULL, "\"");
        rmvCommas(next);

        stockData[count].totalHolder = atoi(next);
        next = strtok(NULL, ",");

        stockData[count].avgHold = atof(next);
        next = strtok(NULL, "\"");
        rmvCommas(next);

        stockData[count].g_400BigHolderHolds = atoi(next);
        next = strtok(NULL, ",");
        
        stockData[count].g_400BigHolderPercent = atof(next);
        next = strtok(NULL, ",");

        stockData[count].g_400BigHolderPeople = atoi(next);
        next = strtok(NULL, ",");

        stockData[count].h_400_600People = atoi(next);
        next = strtok(NULL, ",");

        stockData[count].h_600_800People = atoi(next);
        next = strtok(NULL, ",");

        stockData[count].h_800_1000People = atoi(next);
        next = strtok(NULL, ",");

        count++;
    }
/*
    printf("%d %d %lf %lf %d %d %lf %d %lf %d %d %d %d\n", 
        stockData[0].date, 
        stockData[0].g_1000People, 
        stockData[0].g_1000BigHolderPercent,
        stockData[0].closingPrice,
        stockData[0].totalStock, 
        stockData[0].totalHolder, 
        stockData[0].avgHold,
        stockData[0].g_400BigHolderHolds,
        stockData[0].g_400BigHolderPercent,
        stockData[0].g_400BigHolderPeople,
        stockData[0].h_400_600People,
        stockData[0].h_600_800People,
        stockData[0].h_800_1000People
    );
/*
    /*關閉檔案*/
    fclose(fptr);

    
    /*輸出格式 空格自行填入*/
    findMinMaxPrice(stockData, count);
    findMinMaxTotalShareholders(stockData, count);
    findDatesByPrice(stockData, count);
    calculateChanges(stockData);
    /*
    printf("最低價格: %.2f\n", );
    printf("最高價格: %.2f\n", );
    printf("對應最低收盤價: %.2f 人數: %d\n", , );
    printf("對應最高收盤價: %.2f 人數: %d\n", , );
  
    printf("請輸入目標收盤價格: ");
    scanf("%f", );

    printf("最近一週大股東進出比率: %.2f\n", );
    printf("最近四週大股東進出比率: %.2f\n", );
    */
    return 0;
}


#include <mbed.h>
#include "bkpRegister.hpp"

BKPRegister reg;

//mbed_error_hook()をオーバーライド

void mbed_error_hook(const mbed_error_ctx *error_context)
{
    //BKPレジスタに値の書き込み
    //LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0, 456);
    reg.open(0);
    reg.set(0,2,0);
    
    //プログラムを再スタート
    NVIC_SystemReset();
}


Ticker ticker;
void interrupt(){
    //エラーを発生させる
    printf("hoge\n");
}

int main() {
    reg.open(0);
    uint32_t bkpValue = reg.get(0,2); //BKPレジスタの値の読み込み
    wait_us(3000000);
    printf("%d\n", int(bkpValue)); //2回目以降456と出力
    ticker.attach(&interrupt, std::chrono::milliseconds(1000));
    while(1){

    }
}

/**/
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "qrcodegen.h"

//文字を設置する関数
void putWhite(){
    printf("\x1b[47m");     /* 背景色を白色に */
    printf("　");
    printf("\x1b[49m");     /* 背景色をデフォルトに戻す */
}

void putBlack(){
    printf("\x1b[40m");     /* 背景色を黒色に */
    printf("　");
    printf("\x1b[49m");     /* 背景色をデフォルトに戻す */
}

void putUpDownLine(int size){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < size+6; y++){
            putWhite();
        }
        printf("\n");
    }
}

//文字数を取得する関数
static const char utf8len_codepage[256] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,1,1,1,1,1,1,1,1,1,1,1,
};

int utf8len(const char* p)
{
    int len;
    int i;

    if (*p == 0) return 1;
    len = utf8len_codepage[(const unsigned char)*p];
    for (i = 1; i < len; ++i) {
        if ((p[i] & 0xc0) != 0x80) return 1;
    }
    return len;
}

int utf8strlen(const char* p)
{
    int len;
    for (len = 0; *p; ++len) {
        p += utf8len(p);
    }
    return len;
}


int main()
{
    //QRコード化する文字列を入力
    char str[1024];
    printf("\n> QRコード化したい文字を入力してください\n");
    scanf("%s", str);

    //QRコードの作成
    uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(str,
                                    tempBuffer, qr0, qrcodegen_Ecc_MEDIUM,
                                    qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX,
                                    qrcodegen_Mask_AUTO, true);
    if (!ok)
        return 0;

    //QRコードの大きさを取得
    int size = qrcodegen_getSize(qr0);

    //中に文字を入れれる量を取得
    int space = (size*2/3-size/3)-1;
    char letter[space+1];

    printf("\n> %d文字(全角のみ)まで中に表示することができます。\n", space);
    int letterSize = 0;

    do{
        scanf("%s", letter);
        letterSize = utf8strlen(letter);
        if(utf8strlen(letter) > space){
            printf("\n> %d文字多すぎます\n", utf8strlen(letter)-space);
        }
    }while(utf8strlen(letter) > space);

    //QRコードの表示
    putUpDownLine(size); 

    for (int y = 0; y < size; y++){

        //右端の白の部分を表示する
        for(int x = 0; x < 3; x++){
            putWhite();
        }

        //実際の表示部分
        for (int x = 0; x < size; x++)
        {
            //真ん中のクリ抜き作業部分
			if((size/3 < x && x < size*2/3)&&(size/2-3 < y && y < size/2+3)){

				if(y == size/2 && size/3+1 == x){

                    for(int i = 0; i < space/2-letterSize/2; i++){
                        putWhite();
                    }

					printf("\x1b[47m\x1b[30m");     /* 背景色を灰色に */
					printf("%s", letter);
					printf("\x1b[49m\x1b[39m");     /* 背景色をデフォルトに戻す */

                    for(int i = 0;i < (space - letterSize) - (space/2-letterSize/2);i++){
                        putWhite();
                    }

				}else if(y == size/2){
					continue;
				}else{
                    putWhite();
                }

			}else{
                
                //QRコードの表示
                if (qrcodegen_getModule(qr0, x, y)){
					putBlack();
				}else{
					putWhite();
				}
			}
        }

        //左端の白の部分を表示する
        for(int x = 0; x < 3; x++){
            putWhite();
        }

        printf("\n");
    }

    putUpDownLine(size); 

}

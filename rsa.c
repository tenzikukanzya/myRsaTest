#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

/* gcc -m hoge*/
bool primaryNum(long number){
    int i=0;
    bool flag=true;
    if(number<2){
        return false;
    }
    for(i=2;i<sqrt(number);i++){
        if(number%i==0){
            return false;
        }
    }
    return flag;
}
/*ユークリッドの互除法(最大公約数)
**a,b(a>=b)の時
**a%b=r(0)
**b%r(0)=r(1)
**...
**r(n-1)%r(n)=0
**となったときr(n-1)が最大公約数である。これはa%b=r(1)の公約数とb%r=r(1)の公約数が同じため
*/
long gcd(long a,long b){
    if(a<b){
        return false;
    }
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
}
/*最小公倍数
**a,bに対して最大公約数gと最小公倍数lとするとab=gl
*/
long leastCommonMultiple(long a,long b){
    return a*b/gcd(a,b);
}
/*拡張ユークリッド互除法
** ax+by=gcd(a,b)を求める問題を解く
** ただ、この関数ではgcd(a,b)=1の時のみ解く
*/
long euclidEx(long a,long b){
    long x;
    long y;
    long x1 = 1;
    long x2 = 0;
    long x3;
    long y1 = 0;
    long y2 = 1;
    long y3;
    long result1 = b;
    long result2 = a;
    long result3;
    long q;
    while(1){
        if(result2==0){
            printf("%ld\n",result1);
            printf("0乗算によるエラーもう一度実行してください\n");
            exit(1);
        }
        q = result1 / result2;
        x3 = x1 - (q*x2);
        y3 = y1 - (q*y2);
        result3 = result1 - q*result2;
        if(result3==1){
            if(y3<0){
                return y3+b;
            }
            return y3;
        }
        x1 = x2;
        y1 = y2;
        result1 = result2;
        x2 = x3;
        y2 = y3;
        result2 = result3;
    }
    return 0;
}
/*バイナリ法
**a^e≡result mod n
**ウィキペディアの執筆者. “冪剰余”. ウィキペディア日本語版.
**2018-10-23. https://ja.wikipedia.org/w/index.php?title=%E5%86%AA%E5%89%B0%E4%BD%99&oldid=70382867, (参照 2018-10-23).
**を参考
*/
long modpow(long a,long e,long n){
	long result = 1;
	while(e>0){
		if(e&1==1){
			result = (result*a)%n;
		}
		e>>=1;
		a=(a*a)%n;
	}
	return result;
}
/*
** 暗号化
*/
long encryption(long a,long e,long n){
    long code = modpow(a,e,n);
    if(code<0){
		code = (code+n)%n;
	}
	return code;
}
/*
** 復号化
*/
long decryption(long b,long d,long n){
    return modpow(b,d,n);
}

int main(){
    long q,p,n,e,d;
    long demoNum = 634;
    long code,plaintext;
    srand((unsigned) time(NULL));
    while(1){
        q=rand()%(9999-5+1)+5;
        if(primaryNum(q)){
            break;
        }
    }
    while(1){
        p=rand()%(9999-5+1)+5;
        if(primaryNum(p)&&p!=q){
            break;
        }
    }
    n=q*p;
    printf("n(公開鍵1)->%ld\n",n);
    while(1){
        e=rand()%((n-1)-5+1)+5;
        if(gcd((p-1)*(q-1),e)==1){
            break;
        }
    }
    printf("e(公開鍵2)->%ld\n",e);
    d = euclidEx(e,(p-1)*(q-1));
    printf("d(秘密鍵)->%ld\n",d);
    code = encryption(demoNum,e,n);
    printf("%ldを%ld,%ldで暗号化->%ld\n",demoNum,n,e,code);
    plaintext = decryption(code,d,n);
    printf("%ldを%ld,%ldで復号化->%ld\n",code,n,d,plaintext);
    return 0; 
}

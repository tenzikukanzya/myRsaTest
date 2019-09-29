#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

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
long encrypt(long a,long e,long n,long powNum,long result){
    long pow=2,i=1,r_pow=2,result;
    while(pow*2<e){
        pow*2;
    }
    while(pow!=r_pow){
        result = (long)powl(a,r_pow)%n;
    }
    /*
    long code,i=2,tempE=2;
    long tempA = a;
    long result;
    bool checkFlag = false;
    while(tempE*2<=e){
        tempE=tempE*2;
    }
    while(tempE!=i){
        tempA = (long)powl(tempA,i)%n;
        i=i*2;
    }
    result = tempA;
    while(checkFlag){
        if(e-tempA==0){
            return result
        }
    }*/
    return 0;
}
int main(){
    encrypt(12,19,35,1,1);
    long q,p,n,e,d;
    long demoNum = 634;
    long code,plaintext;
    srand((unsigned) time(NULL));
    while(1){
        q=rand()%(999-1+1)+1;
        q=5;
        if(primaryNum(q)){
            break;
        }
    }
    while(1){
        p=rand()%(9999-1+1)+1;
        p=3;
        if(primaryNum(p)&&p!=q){
            break;
        }
    }
    n=q*p;
    printf("n(公開鍵1)->%ld\n",n);
    while(1){
        e=rand()%((n-1)-1+1)+1;
        if(gcd((p-1)*(q-1),e)==1){
            break;
        }
    }
    printf("e(公開鍵2)->%ld\n",e);
    d = euclidEx(e,(p-1)*(q-1));
    printf("d(秘密鍵)->%ld\n",d);
    return 0; 
}
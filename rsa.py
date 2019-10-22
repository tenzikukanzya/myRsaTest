import math
import string
import base64
import secrets

#Miller–Rabin primality test
def primaryNum(number):
    if number==2:
        return True
    if number%2==0:
        return False
    k=20
    d = (number-1)//2
    s = 1
    while d%2==0:
        d//=2
        s+=1
    for i in range(k):
        a=secrets.randbelow(number-3)+2
        t=d
        y=modpow(a,t,number)
        while t != number-1 and y != 1 and y != number-1:
            y=modpow(y,2,number)
            t*=2
        if y!=number-1 and t%2==0:
            return False
    return True


def euclidEx(a,b):
    x1 = 1
    x2 = 0
    x3 = 0
    y1 = 0
    y2 = 1
    y3 = 0
    result1 = b
    result2 = a
    result3 = 0
    q = 0
    while True:
        if result2 == 0:
            print("Error:0乗算")
            exit()
        q = result1 // result2
        x3 = x1 - (q*x2)
        y3 = y1 - (q*y2)
        result3 = result1 - (q*result2)
        if result3 == 1:
            if y3<0:
                return y3+b
            
            return y3
        x1 = x2
        y1 = y2
        result1 = result2
        x2 = x3
        y2 = y3
        result2 = result3

def modpow(a:int,e:int,n:int):
    #result:int=1
    #while e>0:
    #    if e&1==1:
    #        result=(result*a)%n
    #    e>>=1
    #    a=(a*a)%n
    return pow(a,e,n)

def encryption(text:str,e:int,n:int):
    a = encodeASCII(encodeBase32(text))
    code = modpow(a,e,n)
    print(str(code).encode('utf-8'))
    if code<0:
        code = (code+n)%n
    return code

def decryption(a:int,e:int,n:int):
    return  decodeBase32(decodeASCII(str(modpow(a,e,n))))


def encodeASCII(text):
    strCode=""
    for char in text:
        strCode += str(ord(char))
    return int(strCode)

def decodeASCII(ascii):
    text=""
    for i in range(len(ascii)):
        if i%2==0:
            text += chr(int(ascii[i]+ascii[i+1]))
    return text

def encodeBase32(text):
    return base64.b32encode(text.encode('utf-8')).decode('utf-8')
def decodeBase32(text):
    return base64.b32decode(text.encode('utf-8')).decode('utf-8')

def main():
    print("暗号化テスト\n入力:")
    inputText=input()
    while True:
        q:int=secrets.randbits(1024)
        if primaryNum(q):
            break
    while True:
        p:int=secrets.randbits(1024//2)
        if primaryNum(p):
            break
    n=q*p
    while True:
        e:int=secrets.randbits(16)
        if math.gcd((p-1)*(q-1),e)==1:
            break
    d = euclidEx(e,(p-1)*(q-1))
    code = encryption(inputText,e,n)
    plaintext = decryption(code,d,n)
    print("inputText->{}".format(inputText))
    print("inputTextNum->{}".format(encodeASCII(encodeBase32(inputText))))
    #print("n->{}".format(n))
    #print("e->{}".format(e))
    #print("d->{}".format(d))
    #print("{}を{},{}で暗号化->{}".format(inputText,n,e,code))
    print("{}を暗号化->{}".format(inputText,code))
    #print("{}を{},{}で復号化->{}".format(code,n,d,plaintext))
    print("{}を復号化->{}".format(code,plaintext))


main()
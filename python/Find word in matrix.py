def f(tab,i):
    a=""
    for j in range(len(tab)):
        a=a+tab[j][i]
    return(a)

n,m=list(map(int, input().split()))
s=input()
s2=s[::-1]
tab=[]
k=True
for i in range(n):
    a=input()
    tab.append(a)
    if a.find(s)!=-1 or a.find(s2)!=-1:
        print("YES")
        k=False
        break
if k:
    w="NO"
    for i in range(m):
        if f(tab,i).find(s)!=-1 or f(tab,i).find(s2)!=-1:
            w="YES"
            break
    print(w)

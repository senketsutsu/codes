import re
def f(s,l):
    tab=[]
    for i in range(len(s)-l+1):
        tab.append(s[i:i+l])
    b=[]
    for i in range(len(tab)):
        b.append([tab.count(tab[i]),tab[i]])
    b.sort(reverse=True)
    x=b[0][0]
    #print(b)
    for i in range(len(b)):
        if b[i][0]!=x:
            b=b[:i]
            break
    b.sort()
    #print(b)
    x=b[0][1]
    print(x)
    
x=input()
for i in range(1,len(x)+1):
    f(x,i)
    

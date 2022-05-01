def f(tab,a):
    for i in tab:
        if i==a:
            return(False)
    return(True)

n = int(input())
kto=[]
co=[]
ile=[]
for i in range(n):
    a=input().split()
    b=[a[j].split(":") for j in range(1, len(a))]
    for j in range(len(b)):
        if f(co,b[j][0]):
            co.append(b[j][0])
            ile.append([b[j][0],float(b[j][1]),1])
        else:
            ile[co.index(b[j][0])][1]+=float(b[j][1])
            ile[co.index(b[j][0])][2]+=1
    kto.append([a[0],(sum(float(b[j][1]) for j in range(len(b)))/(len(b)))])
kto.sort()
for i in range(n):
    print(kto[i][0],kto[i][1])
ile.sort()
for i in range(len(co)):
    print(ile[i][0],(ile[i][1]/ile[i][2]))
    

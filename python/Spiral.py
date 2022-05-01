def pr(tab,p,k,i,j):
    return(tab[i][p:k+1],p,k,i+1,j)
def du(tab,p,k,i,j):
    a=[]
    for m in range(i,j+1):
        a.append(tab[m][k])
    return(a,p,k-1,i,j)
def le(tab,p,k,i,j):
    a=tab[j][p:k+1]
    return(a[::-1],p,k,i,j-1)
def gu(tab,p,k,i,j):
    a=[]
    for m in range(i,j+1):
        a.append(tab[m][p])
    return(a[::-1],p+1,k,i,j)
    
n=int(input())
tab=[list(input().split()) for m in range(n)]
m=0
i=0
j=n-1
p=0
k=n-1
a=[]
while not(p>k or i>j):
    if m%4==0:
        b,p,k,i,j=pr(tab,p,k,i,j)
        #print("0",p,k,i,j)
    if m%4==1:
        b,p,k,i,j=du(tab,p,k,i,j)
        #print("1",p,k,i,j)
    if m%4==2:
        b,p,k,i,j=le(tab,p,k,i,j)
        #print("2",p,k,i,j)
    if m%4==3:
        b,p,k,i,j=gu(tab,p,k,i,j)
        #print("3",p,k,i,j)
    a+=b
    m+=1
for m in a:
    print(m,end=" ")


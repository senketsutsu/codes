#def nwd(a[],n):
def mini(a):
    a.sort()
    while a[0]==0:
        del a[0]
    return(a)

def nwd(a):
    while sum(a)!=max(a):
        a=mini(a)
        for i in range(1,len(a)):
            a[i]=a[i]%a[0]
        a.sort()
        #print(a)
    return(max(a))
        
        
n=int(input())
a=[]
for i in range(n):
    a.append(int(input()))
a.sort()
b=[]
c=[]
for i in range(1,n):
    b.append(a[i]-a[i-1])
    c.append(a[i]-a[i-1])
#nwd
#print((b))
x=nwd(b)
z=max(a)-min(a)
z=z/x
z=z-n+1
print(int(z))

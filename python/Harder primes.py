import math
n=input()
t=[]
a=100000
for i in range(int(n)):
    t.append(input())

 
si=[]
for i in range(a):
    si.append(0)
i=2
si[0]=1
si[1]=1
while i*i<=a:
    if si[i]==0:
        j=i*i
        while j<a:
            si[j]=1
            j+=i
    i+=1

for k in range(int(n)):
    if si[int(t[k])]==0:
        print("YES")
    else:
        print("NO")

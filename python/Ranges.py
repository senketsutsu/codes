z = int(input())
for i in range(z):
    n = int(input())
    a = []
    b = []
    #m = 0
    for j in range(n):
        #b=input().split()
        a.append(list(map(int, input().split())))
        #a.append([int(b[0])-1,int(b[1])-1])
        #m=max(m,int(b[1])-1)
    #b=[0 for j in range(m)]
    a.sort()
    b.append([a[0][0], a[0][1]])
    for j in range(1,n):
        c=a[j]
        #b[a[j][0]:a[j][1]+1]=[1 for k in range(a[j][1]-a[j][0]+1)]
        if c[0]<b[-1][1]+2:
            if c[1]>b[-1][1]:
                b[-1][1]=c[1]
        else:
            b.append(a[j])

    print(sum((b[j][1]-b[j][0]+1) for j in range(len(b))))    

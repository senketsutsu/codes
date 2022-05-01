n,m = map(int,input().split())
s=input()
z=s
for i in range(m):
    a,b,c= input().split(';')
    a,b=min(int(a),int(b)),max(int(a),int(b))
    s=s[:a]+c+s[(b+1):]
    n=len(s)+1
    if len(s)>len(z):
        z=s
    #print(s)
print(s)
print(z)

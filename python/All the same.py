n=int(input())
a=input()
b=a
i="True"

for x in range(n-1):
    a=input()
    if a != b :
        i="False"
        break

print(i)

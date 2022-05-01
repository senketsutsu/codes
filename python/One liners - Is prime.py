s = input()
print(False if sum([ True if int(s)%i==0 else False for i in ( [2] + list(range(2, 1+int(int(s)/2)))) ]) else True)

#Algoritmo 4.2.1 

def buscar_texto(p,m,t,n):
    for i in range(1,n+m+1):
        j = 1
        while(t[i+j-1] == p[j]):
            if j > m:
                return i
    return 0

t = '01001'
n = len(t)
p = '001'
m = len(p)

print(buscar_texto(p,m,t,n))



#8. Escriba un algoritmo cuya salida sea el valor menor y mayor en la
#sucesión s1, . . . , sn.

def max_min(L):
    n = len(L)
    maximo = L[0]
    minimo = L[1]
    
    if maximo < minimo :
        maximo = L[1]
        minimo = L[0]
    
    for i in range(2,n):
        if L[i] > maximo :
            maximo = L[i]
        if L[i] < minimo :
            minimo = L[i]
    return maximo, minimo

L = [3,4,5,5,3,3,4,5,6,7,88,91,0,3,-4]

x,y = max_min(L)

print(f"el maximo es {x} y el minimo es {y}")
#Escriba un algoritmo que regrese el valor más grande y el segundo
#elemento más grande en la sucesión s1, . . . , sn. Suponga que n
#> 1 y que los valores de la sucesión son diferentes

L = [2,3,4,2,5,3,55,3,5,2,5,78,9]

def encontrarPrimerMaximo(L):
    n1 = len(L)
    maximo1 = L[0]
    
    for i in range(1,n1):
        if L[i]>maximo1:
            maximo1 = L[i]
    return maximo1

x = encontrarPrimerMaximo(L)

def encontrarSegundoMaximo(L):
    M = [num for num in L if num != x]
    maximo2 = encontrarPrimerMaximo(M)
    return maximo2
y = encontrarSegundoMaximo(L)


print(f"El 1er máximo es {x} y el 2do máximo es {y}")
    


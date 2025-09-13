#9. Escriba un algoritmo que regrese el índice de la primera ocurrencia
#del elemento más grande en la sucesión s, . . . , sn. Ejemplo: Si
#la sucesión es
#6.2 8.9 4.2 8.9,
#el algoritmo regresa el valor 2.

def index_primera_ocurrencia(L):
    n = len(L)
    valor_maximo = L[0]
    index_minimo = 1
    
    for i in range(1,n):
        if L[i] > valor_maximo:
            valor_maximo = L[i]
            index_minimo = i + 1
    return index_minimo
    

L = [3,4,91,5,5,3,3,4,5,6,7,88,91,0,3,-4]

print(f"El indice de la primera ocurrencia del valor máximo de L es {index_primera_ocurrencia(L)}")
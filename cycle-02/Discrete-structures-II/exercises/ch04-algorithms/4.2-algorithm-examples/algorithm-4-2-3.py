#Algoritmo 4.2.1 

def insertion_sort(lista):

    for i in range(1, len(lista)):
        
        valor_a_insertar = lista[i]
        j = i - 1
        while j >= 0 and valor_a_insertar < lista[j]:
            lista[j + 1] = lista[j]
            j = j - 1
        lista[j + 1] = valor_a_insertar    
    return lista

s = [18, 20, 17, 13] 
print(f"Lista original: {s}")
lista_ordenada = insertion_sort(s)
print(f"Lista ordenada: {lista_ordenada}")

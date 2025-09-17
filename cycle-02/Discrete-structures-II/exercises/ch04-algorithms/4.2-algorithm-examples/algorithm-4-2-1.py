#Algoritmo 4.2.1 

def busqueda_texto_corregida(texto, patron):
    """
    Busca la primera ocurrencia de un 'patron' dentro de un 'texto'.
    Devuelve el índice basado en 0 donde comienza el patrón, o -1 si no se encuentra.
    """
    n = len(texto)
    m = len(patron)

    for i in range(n - m + 1):
        
        j = 0
        while j < m and texto[i + j] == patron[j]:
            j = j + 1

        if j == m:
            
            return i # Devolvemos la posición de inicio i

    return -1

t = '01001'
p = '001'

indice = busqueda_texto_corregida(t, p)

if indice != -1:
    print(f"El patrón '{p}' se encontró en el texto '{t}' en el índice: {indice}")
else:
    print(f"El patrón '{p}' no se encontró en el texto '{t}'.")


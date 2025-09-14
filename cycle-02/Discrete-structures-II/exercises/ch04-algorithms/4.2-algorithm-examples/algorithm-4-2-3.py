#Algoritmo 4.2.1 

def insertion_sort(lista):
    """
    Ordena una lista usando el algoritmo de Ordenamiento por Inserción.
    """
    # Empezamos desde el segundo elemento (índice 1),
    # ya que el primero forma la sublista ordenada inicial.
    for i in range(1, len(lista)):
        
        # 'valor_a_insertar' es la "carta" que tomamos de la parte desordenada.
        valor_a_insertar = lista[i]
        
        # 'j' es el índice del último elemento en la sublista ordenada.
        j = i - 1
        
        # --- Bucle para "hacer espacio" ---
        # Movemos los elementos de la sublista ordenada que son mayores
        # que nuestro 'valor_a_insertar' una posición a la derecha.
        while j >= 0 and valor_a_insertar < lista[j]:
            lista[j + 1] = lista[j]  # Desplazamiento
            j = j - 1
            
        # --- Inserción ---
        # Colocamos nuestra "carta" en el hueco que hemos creado.
        lista[j + 1] = valor_a_insertar
        
    return lista

# --- Ejemplo de Uso ---
s = [18, 20, 17, 13]
print(f"Lista original: {s}")
lista_ordenada = insertion_sort(s)
print(f"Lista ordenada: {lista_ordenada}")
# Salida:
# Lista original: [18, 20, 17, 13]
# Lista ordenada: [13, 17, 18, 20]
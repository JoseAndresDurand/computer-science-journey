#24. Escriba un algoritmo cuya entrada sea una sucesión s1, . . . , sn y
#un valor x. (Suponga que todos los valores son números reales.) El
#algoritmo regresa verdadero si si + sj = x, para alguna i  j, y falso
#de otra manera. Ejemplo: Si la sucesión de entrada es
#2, 12, 6, 14
#y x = 26, el algoritmo regresa verdadero porque 12 + 14 = 26. Si
#la sucesión de entrada es
#2, 12, 6, 14
#y x = 4, el algoritmo regresa falso

def sum_value(L,x):
    revisados = set()
    for elemento in L:
        complemento = x - elemento
        if complemento in revisados:
            return True
        revisados.add(elemento)
    return False
        
        
x = 31
L = [2,12,6,14,18]
print(f"Dos términos de la sucesión suman X? {sum_value(L,x)}")
    
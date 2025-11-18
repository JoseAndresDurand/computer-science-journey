/*
7. Escriba un programa que a través de punteros a funciones halle 
la longitud de una cadena y la posición en la que se encuentra 
el carácter mayor en orden lexicográfico.
*/


#include <iostream>
using namespace std;

int resultado(int(*func)(char*), char *cadena)
{
   return (*func)(cadena);
}
int longitud(char *cadena)
{  
    int count = 0;
    while(cadena[count] != '\0'){
        count++;
    }
    return count;
}
int posicionMayor(char *cadena)
{  
    int caracterMayor = cadena[0];
    int posicionMayor = 0;
    for (int i=1; cadena[i] != '\0'; i++){
        if (cadena[i]> caracterMayor){
            caracterMayor = cadena[i];
            posicionMayor = i;
        }
    }
    return posicionMayor;
}

int main()
{
    char cadena[] = "Hola mucho gusto";
    cout<<"La cadena es: "<<cadena<<endl;
    cout<<"La longitud de la cadena es: "<<endl;
    cout<<resultado(longitud,cadena)<<endl;
    cout<<"La posición del mayor carácter lexicografico es: "<<endl;
    cout<<resultado(posicionMayor,cadena)<<endl;
    
    return 0;
}

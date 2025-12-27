/*
completar con:

- Definición de clases: Profesor, Administrativo (también que hereden de la clase Persona).

- Completar con un menú principal, así:

Agregar Registro (Dar la posibilidad a elegir: Agregar Alumno, Profesor o Administrativo).
Buscar Registro (Dar la posibilidad a elegir: Buscar Alumno, Buscar Profesor o Buscar Administrativo).
Actualizar Registro (Dar la posibilidad a elegir: Actualizar Alumno, Actualizar Profesor o Actualizar Administrativo).
Eliminar Registro (Dar la posibilidad a elegir: Eliminar Alumno, Eliminar Profesor o Eliminar Administrativo).
Listar Registros (Dar la posibilidad a elegir: Listar Alumnos, Listar Profesores o Listar Administrativos).
El programa debe contener tres listas de punteros a objetos de las tres clases derivadas.

Ej: Alumno *ListaAlumnos[100];

*/

#include <iostream>
#include <stdlib.h>
using namespace std;
//Persona*****************************************
class Persona{
    protected:
        string nombre;
        int edad;
    public:
        Persona(string, int);
        void mostrar();
};
Persona::Persona(string n, int e){
    nombre = n;
    edad = e;
    cout<<"Construyendo persona"<<endl;
}
void Persona::mostrar(){
    cout<<"Su nombre es "<<nombre<<" y tiene "<<edad<<" años \n";
}
//Alumno*****************************************
class Alumno:public Persona{
    protected:
        string especialidad;
    public:
        Alumno(string, int, string);
};
Alumno::Alumno(string n, int e, string esp):Persona(n,e){
    especialidad = esp,
    cout<<"Construyendo Alumno"<<endl;
}
//Profesor*****************************************
class Profesor:public Persona{
    protected:
        string curso;
    public:
        Profesor(string, int, string);
};
Profesor::Profesor(string n, int e, string cur):Persona(n,e){
    curso = cur;
    cout<<"Construyendo Profesor"<<endl;
}
//Administrativo*****************************************
class Administrativo:public Persona{
    protected:
        string area;
    public:
        Administrativo(string, int, string);
};
Administrativo::Administrativo(string n, int e, string are):Persona(n,e){
    area = area,
    cout<<"Construyendo Alumno"<<endl;
}

int main(){
    Alumno *listaAlumnos[10];
    Profesor *listaProfesor[10];
    Administrativo *listaAdministrativo[10];
    


    return 0;
}


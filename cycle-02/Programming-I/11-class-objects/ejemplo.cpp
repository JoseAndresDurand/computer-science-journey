#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
// CONSTRUCTORES DE CLASES DERIVADAS
class ClaseA {
  protected:
   int datoA;

  public:
   ClaseA() : datoA(10) {
      cout << "Constructor de A" << endl;
   }
   int getA() { return datoA; }
};

class ClaseB : public ClaseA {
  protected:
   int datoB;

  public:
   ClaseB() : datoB(20) {
      cout << "Constructor de B" << endl;
   }
   int getB() { return datoB; }

};

int main() {
   ClaseB objeto;

   cout << "a = " << objeto.getA()
        << ", b = " << objeto.getB() << endl;

   return 0;
}
*/



class Persona
{protected:
    string nombre;
    int edad;
public:
    Persona(string, int);
    void mostrar();
};
Persona::Persona(string n,int e)
{
    nombre=n;
    edad=e;
    cout<<"Costruyendo Persona"<<endl;
}
void Persona::mostrar()
{
    cout<<"su nombre es "<<nombre<<" y tiene "<<edad<<" años\n";
}


class Alumno:public Persona
{
    protected:
    string especialidad;
public:
    Alumno(string,int,string);
};

Alumno::Alumno(string n,int e,string esp):Persona(n,e)
{
    especialidad=esp;
    cout<<"Costruyendo Alumno"<<endl;
}
int main()
{
    /*
    Persona p1("Luis",15);
    p1.mostrar();
    */

    Alumno a1("Alvaro",18,"Matemáticas");
    a1.mostrar();
    return 0;
}
// COMPLETAR EL PROGRAMA, AÑADIENDO LAS CLASES PROFESOR Y ADMINISTRATIVO QUE HEREDEN TAMBIÉN DE PERSONA,
// AGREGAR EJEMPLOS DE USO (CREANDO OBJETOS ALUMNO, PROFESOR, ADMINISTRATIVO, AGREGÁNDOLOS A UNA LISTA DE ALUMNOS,
// O PROFESORES O ADMINISTRATIVOS, MOSTRAR LOS LISTADOS).

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
#include <iomanip> //Para el TUI
using namespace std;
//Persona*****************************************
class Persona{
    protected:
        string nombre;
        int edad;
    public:
        Persona(string, int);
        string getNombre();
        void setNombre(string);
        void setEdad(int);
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
string Persona::getNombre(){
    return nombre;
}
void Persona::setNombre(string name){
    nombre = name;
}
void Persona::setEdad(int age){
    edad = age;
}
//Alumno*****************************************
class Alumno:public Persona{
    protected:
        string especialidad;
    public:
        Alumno(string, int, string);
        void setEspecialidad(string);
};
Alumno::Alumno(string n, int e, string esp):Persona(n,e){
    especialidad = esp,
    cout<<"Construyendo Alumno"<<endl;
}
void Alumno::setEspecialidad(string especiality){
    especialidad = especiality;
}
//Profesor*****************************************
class Profesor:public Persona{
    protected:
        string curso;
    public:
        Profesor(string, int, string);
        void setCurso(string);
};
Profesor::Profesor(string n, int e, string cur):Persona(n,e){
    curso = cur;
    cout<<"Construyendo Profesor"<<endl;
}
void Profesor::setCurso(string course){
    curso = course;
}
//Administrativo*****************************************
class Administrativo:public Persona{
    protected:
        string area;
    public:
        Administrativo(string, int, string);
        void setArea(string);
};
Administrativo::Administrativo(string n, int e, string are):Persona(n,e){
    area = are,
    cout<<"Construyendo Alumno"<<endl;
}
void Administrativo::setArea(string areah){
    area = areah;
}

//Text User Interfaces************************************

const int ANCHO_TOTAL = 80;
const char BORDE = '*';


void imprimirLineaHorizontal() {
    cout << setfill(BORDE) << setw(ANCHO_TOTAL) << "" << setfill(' ') << endl;
}


void imprimirCentrado(string texto) {

    int espacioLibre = ANCHO_TOTAL - 2 - texto.length();
    int espacioIzq = espacioLibre / 2;
    int espacioDer = espacioLibre - espacioIzq;

    cout << BORDE;
    cout << string(espacioIzq, ' '); 
    cout << texto;
    cout << string(espacioDer, ' '); 
    cout << BORDE << endl;
}


void imprimirOpcion(string texto) {

    int sangria = 15;
    
 
    int espacioDer = ANCHO_TOTAL - 2 - sangria - texto.length();

    cout << BORDE;
    cout << string(sangria, ' '); 
    cout << texto;
    cout << string(espacioDer, ' '); 
    cout << BORDE << endl;
}
//********************************************************

int main(){
    Alumno *listaAlumnos[10];
    Profesor *listaProfesor[10];
    Administrativo *listaAdministrativo[10];
    int option;
    int contAlumno=0,contProfesor=0,contAdministrativo=0;
do{
//Menú ***************************************************
    imprimirLineaHorizontal();
    imprimirCentrado("SISTEMA ALUMNOS, PROFESORES Y ADMINISTRATIVOS");
    imprimirLineaHorizontal();

    imprimirCentrado(""); 
    
    imprimirOpcion("( 1 )   Agregar");
    imprimirOpcion("( 2 )   Buscar");
    imprimirOpcion("( 3 )   Actualizar");
    imprimirOpcion("( 4 )   Eliminar");
    imprimirOpcion("( 5 )   Listar");
    imprimirOpcion("( 6 )   Salir");
    
    imprimirCentrado(""); // Línea vacía final

    cout << BORDE << string(15, ' ') << "Elija una opcion: ";
   
    cin >> option;

    imprimirLineaHorizontal();
//********************************************************

    if (option==1){
        //Agregar registro
        cout<<"Agregar: "<<endl;
        cout<<"(1) Alumno"<<endl;
        cout<<"(2) Profesor"<<endl;
        cout<<"(3) Administrativo"<<endl;
        cout<<"(6) Salir"<<endl;
        cout<<"Opcion: ";
        cin>>option;
        if (option==1){
            string nombre, especialidad;
            int edad;
            cout<<"******Nuevo Alumno*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<"Ingrese edad: ";
            cin>>edad;
            cout<<"Ingrese especialidad: ";
            cin>>especialidad;
            cout<<endl;
            listaAlumnos[contAlumno] = new Alumno(nombre, edad, especialidad);
            contAlumno++;
        }else if (option==2){
            string nombre, curso;
            int edad;
            cout<<"******Nuevo Profesor*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<"Ingrese edad: ";
            cin>>edad;
            cout<<"Ingrese curso: ";
            cin>>curso;
            cout<<endl;
            listaProfesor[contProfesor] = new Profesor(nombre, edad, curso);
            contProfesor++;
        }else if (option==3){
            string nombre, area;
            int edad;
            cout<<"******Nuevo Administrativo*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<"Ingrese edad: ";
            cin>>edad;
            cout<<"Ingrese area: ";
            cin>>area;
            cout<<endl;
            listaAdministrativo[contAdministrativo] = new Administrativo(nombre, edad, area);
            contAdministrativo++;
        }
        
    }else if (option==2){
        //Buscar registro
        cout<<"Buscar: "<<endl;
        cout<<"(1) Alumno"<<endl;
        cout<<"(2) Profesor"<<endl;
        cout<<"(3) Administrativo"<<endl;
        cout<<"(6) Salir"<<endl;
        cout<<"Opcion: ";
        cin>>option;
        if (option==1){
            bool encontrado=false;
            string nombre;
            cout<<"******Buscar Alumno*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contAlumno;i++){
                if (listaAlumnos[i]->getNombre()==nombre){
                    cout<<"El alumno fue encontrado"<<endl;
                    encontrado = true;
                    break;
                }
            }
            if (encontrado!=true){
                cout<<"El Alumno no fue encontrado"<<endl;
            }
        }else if (option==2){
            bool encontrado=false;
            string nombre;
            cout<<"******Buscar Profesor*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contProfesor;i++){
                if (listaProfesor[i]->getNombre()==nombre){
                    cout<<"El Profesor fue encontrado"<<endl;
                    break;
                }
            }
            if (encontrado!=true){
                cout<<"El Profesor no fue encontrado"<<endl;
            }
        }else if (option==3){
            bool encontrado=false;
            string nombre;
            cout<<"******Buscar Administrativo*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contAdministrativo;i++){
                if (listaAdministrativo[i]->getNombre()==nombre){
                    cout<<"El Administrativo fue encontrado"<<endl;
                    break;
                }
            }
            if (encontrado!=true){
                cout<<"El Administrativo no fue encontrado"<<endl;
            }
        }
    }else if (option==3){
        //Actualizar registro
        cout<<"Actualizar: "<<endl;
        cout<<"(1) Alumno"<<endl;
        cout<<"(2) Profesor"<<endl;
        cout<<"(3) Administrativo"<<endl;
        cout<<"(6) Salir"<<endl;
        cout<<"Opcion: ";
        cin>>option;
        if (option==1){
            bool encontrado=false;
            string nombre, especialidad;
            int edad, indice=0;
            cout<<"******Actualizar Alumno*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contAlumno;i++){
                if (listaAlumnos[i]->getNombre()==nombre){
                    cout<<"El alumno fue encontrado"<<endl;
                    encontrado = true;
                    indice = i;
                    break;
                }
            }
            if (encontrado=true){
                cout<<"Cambiemos el nombre del Alumno"<<endl;
                cin>>nombre;
                cout<<"Cambiemos la edad del Alumno"<<endl;
                cin>>edad;
                cout<<"Cambiemos la especialidad del Alumno"<<endl;
                cin>>especialidad;
                listaAlumnos[indice] -> setNombre(nombre);
                listaAlumnos[indice] -> setEdad(edad);
                listaAlumnos[indice] -> setEspecialidad(especialidad);
            }else{
                cout<<"El alumno no fue encontrado"<<endl;
            }
        }else if (option==2){
            bool encontrado=false;
            string nombre, curso;
            int edad, indice=0;
            cout<<"******Actualizar Profesor*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contProfesor;i++){
                if (listaProfesor[i]->getNombre()==nombre){
                    cout<<"El Profesor fue encontrado"<<endl;
                    encontrado = true;
                    indice = i;
                    break;
                }
            }
            if (encontrado=true){
                cout<<"Cambiemos el nombre del Profesor"<<endl;
                cin>>nombre;
                cout<<"Cambiemos la edad del Profesor"<<endl;
                cin>>edad;
                cout<<"Cambiemos el curso del Profesor"<<endl;
                cin>>curso;
                listaProfesor[indice] -> setNombre(nombre);
                listaProfesor[indice] -> setEdad(edad);
                listaProfesor[indice] -> setCurso(curso);
            }else{
                cout<<"El Profesor no fue encontrado"<<endl;
            }
        }else if (option==3){
            bool encontrado=false;
            string nombre, area;
            int edad, indice=0;
            cout<<"******Actualizar Administrativo*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contAdministrativo;i++){
                if (listaAdministrativo[i]->getNombre()==nombre){
                    cout<<"El Administrativo fue encontrado"<<endl;
                    encontrado = true;
                    indice = i;
                    break;
                }
            }
            if (encontrado=true){
                cout<<"Cambiemos el nombre del Administrativo"<<endl;
                cin>>nombre;
                cout<<"Cambiemos la edad del Administrativo"<<endl;
                cin>>edad;
                cout<<"Cambiemos el curso del Administrativo"<<endl;
                cin>>area;
                listaAdministrativo[indice] -> setNombre(nombre);
                listaAdministrativo[indice] -> setEdad(edad);
                listaAdministrativo[indice] -> setArea(area);
            }else{
                cout<<"El Administrativo no fue encontrado"<<endl;
            }
        }
    }else if(option==4){
        //Eliminar registro
        cout<<"Eliminar: "<<endl;
        cout<<"(1) Alumno"<<endl;
        cout<<"(2) Profesor"<<endl;
        cout<<"(3) Administrativo"<<endl;
        cout<<"(6) Salir"<<endl;
        cout<<"Opcion: ";
        cin>>option;
        if (option==1){
            string nombre;
            int indice=0;
            cout<<"******Eliminar Alumno*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contAlumno;i++){
                if (listaAlumnos[i]->getNombre()==nombre){
                    cout<<"El alumno fue encontrado"<<endl;
                    cout<<"Se procede a eliminarlo de la lista"<<endl;
                    for (int j=i; j<contAlumno-1;j++){
                        listaAlumnos[j]=listaAlumnos[j+1];
                    }
                    contAlumno--;
                    break;
                }
            }

        }else if (option==2){
            string nombre;
            int indice=0;
            cout<<"******Eliminar Profesor*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contProfesor;i++){
                if (listaProfesor[i]->getNombre()==nombre){
                    cout<<"El Profesor fue encontrado"<<endl;
                    cout<<"Se procede a eliminarlo de la lista"<<endl;
                    for (int j=i; j<contProfesor-1;j++){
                        listaProfesor[j]=listaProfesor[j+1];
                    }
                    contProfesor--;
                    break;
                }
            }
        }else if (option==3){
            string nombre;
            int indice=0;
            cout<<"******Eliminar Administrativo*******"<<endl,
            cout<<"Ingrese nombre: ";
            cin>>nombre;
            cout<<endl;
            for (int i=0;i<contAdministrativo;i++){
                if (listaAdministrativo[i]->getNombre()==nombre){
                    cout<<"El Administrativo fue encontrado"<<endl;
                    cout<<"Se procede a eliminarlo de la lista"<<endl;
                    for (int j=i; j<contAdministrativo-1;j++){
                        listaAdministrativo[j]=listaAdministrativo[j+1];
                    }
                    contAdministrativo--;
                    break;
                }
            }
        }
    }else if(option==5){
        //Listar registros
        cout<<"Listar: "<<endl;
        cout<<"(1) Alumno"<<endl;
        cout<<"(2) Profesor"<<endl;
        cout<<"(3) Administrativo"<<endl;
        cout<<"(6) Salir"<<endl;
        cout<<"Opcion: ";
        cin>>option;
        if (option==1){
            cout<<"******Listar Alumnos*******"<<endl;
            for (int i=0;i<contAlumno;i++){
                cout<<listaAlumnos[i]->getNombre()<<endl;
            }
        }else if (option==2){
            cout<<"******Listar Profesores*******"<<endl;
            for (int i=0;i<contProfesor;i++){
                cout<<listaProfesor[i]->getNombre()<<endl;
            }
        }else if (option==3){
            cout<<"******Listar Administrativo*******"<<endl;
            for (int i=0;i<contAdministrativo;i++){
                cout<<listaAdministrativo[i]->getNombre()<<endl;
            }
        }
    }
}while(option!=6);
    return 0;
}


#include <iostream>
#include <stdio.h>
#include <string.h> // Necesario para strcmp
#include <stdlib.h>
using namespace std;

class Sistema; // Declaración adelantada

//PERSONA************************************************
class Persona{
    protected:
        friend class Sistema;
        char *nombre = new char[100];
        int vecesPrestamo;
    public:
        Persona() { vecesPrestamo = 0; } // Inicializar contador
        virtual void llenar_data();     // VIRTUAL para polimorfismo
        virtual void mostrar_data();    // VIRTUAL para polimorfismo
        virtual int getLimite() = 0;    // Método puro: cada hijo define su límite
        char* getNombreBase() { return nombre; }
};

void Persona::llenar_data(){
    fflush(stdin);
    cout<<"Nombre : ";
    cin.getline(nombre,100,'\n');
}
void Persona::mostrar_data(){
    cout<<"Nombre : "<<nombre<<endl;
    cout<<"Prestamos actuales: "<<vecesPrestamo<<"/"<<getLimite()<<endl;
}

//ALUMNO************************************************
class Alumno:public Persona{
    public:
        void llenar_data();
        void mostrar_data();
        int getLimite(); // Implementación de la regla
};
void Alumno::llenar_data(){
    cout<<"--- REGISTRANDO ALUMNO ---"<<endl;
    Persona::llenar_data();
}
void Alumno::mostrar_data(){
    cout<<"[ALUMNO] ";
    Persona::mostrar_data();
}
int Alumno::getLimite(){
    return 2; // Regla: Máximo 2 libros
}

//PROFESOR************************************************
class Profesor:public Persona{
    public:
        void llenar_data();
        void mostrar_data();
        int getLimite();
};
void Profesor::llenar_data(){
    cout<<"--- REGISTRANDO PROFESOR ---"<<endl;
    Persona::llenar_data();
}
void Profesor::mostrar_data(){
    cout<<"[PROFESOR] ";
    Persona::mostrar_data();
}
int Profesor::getLimite(){
    return 3; // Regla: Máximo 3 libros
}

//DOCUMENTOS************************************************
class Documentos{
    protected:
        friend class Sistema; // Corregido: debía coincidir con la clase Sistema
        bool disponible;
        char *nombre = new char[100];
    public:
        Documentos() { disponible = true; }
        virtual void llenar_data();
        virtual void mostrar_data();
        char* getNombreDoc() { return nombre; }
        bool estaDisponible() { return disponible; }
        void prestar() { disponible = false; }
        void devolver() { disponible = true; }
};
void Documentos::llenar_data(){
    fflush(stdin);
    cout<<"Titulo del Documento: ";
    cin.getline(nombre,100,'\n');
    disponible = true;
}
void Documentos::mostrar_data(){
    cout<<"Titulo: "<<nombre;
    if(disponible) cout<<" [DISPONIBLE]"<<endl;
    else cout<<" [NO DISPONIBLE]"<<endl;
}

//LIBROS************************************************
class Libros:public Documentos{
        char *autor = new char[100];
    public:
        void llenar_data();
        void mostrar_data();
};
void Libros::llenar_data(){
    cout<<"--- REGISTRANDO LIBRO ---"<<endl;
    Documentos::llenar_data();
    cout<<"Autor: ";
    cin.getline(autor,100,'\n');
}
void Libros::mostrar_data(){
    cout<<"[LIBRO] ";
    Documentos::mostrar_data();
    cout<<"   Autor: "<<autor<<endl;
}

//TESIS************************************************
class Tesis:public Documentos{
        char *tema = new char[100];
    public:
        void llenar_data();
        void mostrar_data();
};
void Tesis::llenar_data(){
    cout<<"--- REGISTRANDO TESIS ---"<<endl;
    Documentos::llenar_data();
    cout<<"Tema: ";
    cin.getline(tema,100,'\n');
}
void Tesis::mostrar_data(){
    cout<<"[TESIS] ";
    Documentos::mostrar_data();
    cout<<"   Tema: "<<tema<<endl;
}

//REVISTAS************************************************
class Revistas:public Documentos{
        char *editorial = new char[100];
    public:
        void llenar_data();
        void mostrar_data();
};
void Revistas::llenar_data(){
    cout<<"--- REGISTRANDO REVISTA ---"<<endl;
    Documentos::llenar_data();
    cout<<"Editorial: ";
    cin.getline(editorial,100,'\n');
}
void Revistas::mostrar_data(){
    cout<<"[REVISTA] ";
    Documentos::mostrar_data();
    cout<<"   Editorial: "<<editorial<<endl;
}

//CLASE SISTEMA (El Controlador) *************************
class Sistema{
    private:
        // Listas de punteros para soportar polimorfismo
        Persona* listaPersonas[100];
        Documentos* listaDocumentos[100];
        int contPersonas;
        int contDocumentos;

    public:
        Sistema(){
            contPersonas = 0;
            contDocumentos = 0;
        }

        void agregarPersona(int tipo); // 1: Alumno, 2: Profesor
        void agregarDocumento(int tipo); // 1: Libro, 2: Tesis, 3: Revista
        void listarPersonas();
        void listarDocumentos();
        void realizarPrestamo();
        
        // Métodos de búsqueda auxiliares
        Persona* buscarPersona(char* nombreBusq);
        Documentos* buscarDocumento(char* nombreBusq);
};

void Sistema::agregarPersona(int tipo){
    if(contPersonas >= 100) { cout<<"Lista llena"<<endl; return; }
    
    Persona* p;
    if(tipo == 1) p = new Alumno();
    else p = new Profesor();

    p->llenar_data();
    listaPersonas[contPersonas] = p;
    contPersonas++;
}

void Sistema::agregarDocumento(int tipo){
    if(contDocumentos >= 100) { cout<<"Almacen lleno"<<endl; return; }

    Documentos* d;
    if(tipo == 1) d = new Libros();
    else if(tipo == 2) d = new Tesis();
    else d = new Revistas();

    d->llenar_data();
    listaDocumentos[contDocumentos] = d;
    contDocumentos++;
}

void Sistema::listarPersonas(){
    cout<<"\n--- LISTA DE USUARIOS ---"<<endl;
    for(int i=0; i<contPersonas; i++){
        cout<< (i+1) << ". ";
        listaPersonas[i]->mostrar_data(); // Llama al mostrar del hijo gracias a virtual
    }
}

void Sistema::listarDocumentos(){
    cout<<"\n--- LISTA DE DOCUMENTOS ---"<<endl;
    for(int i=0; i<contDocumentos; i++){
        cout<< (i+1) << ". ";
        listaDocumentos[i]->mostrar_data();
    }
}

Persona* Sistema::buscarPersona(char* nombreBusq){
    for(int i=0; i<contPersonas; i++){
        // strcmp devuelve 0 si son iguales
        if(strcmp(listaPersonas[i]->getNombreBase(), nombreBusq) == 0){
            return listaPersonas[i];
        }
    }
    return NULL;
}

Documentos* Sistema::buscarDocumento(char* nombreBusq){
    for(int i=0; i<contDocumentos; i++){
        if(strcmp(listaDocumentos[i]->getNombreDoc(), nombreBusq) == 0){
            return listaDocumentos[i];
        }
    }
    return NULL;
}

void Sistema::realizarPrestamo(){
    char nombreUser[100];
    char nombreDoc[100];
    
    fflush(stdin);
    cout<<"\n--- REALIZAR PRESTAMO ---"<<endl;
    cout<<"Ingrese nombre del Usuario: ";
    cin.getline(nombreUser, 100, '\n');

    Persona* p = buscarPersona(nombreUser);
    if(p == NULL){
        cout<<"ERROR: Usuario no encontrado."<<endl;
        return;
    }

    // 1. VERIFICAR LIMITE DE PRESTAMOS (Polimorfismo en accion)
    if(p->vecesPrestamo >= p->getLimite()){
        cout<<"ERROR: El usuario ha alcanzado su limite de prestamos ("<<p->getLimite()<<")."<<endl;
        return;
    }

    cout<<"Ingrese titulo del Documento: ";
    cin.getline(nombreDoc, 100, '\n');
    Documentos* d = buscarDocumento(nombreDoc);

    if(d == NULL){
        cout<<"ERROR: Documento no encontrado."<<endl;
        return;
    }

    // 2. VERIFICAR DISPONIBILIDAD
    if(!d->estaDisponible()){
        cout<<"ERROR: El documento ya se encuentra prestado."<<endl;
        return;
    }

    // SI TODO ESTA BIEN, EJECUTAR PRESTAMO
    d->prestar();
    p->vecesPrestamo++;
    cout<<"EXITO: Prestamo realizado correctamente."<<endl;
}

// MAIN ****************************************************
int main(){
    Sistema biblioteca;
    int opcion;
    
    do{
        cout<<"\n******** BIBLIOTECA UNSA ********"<<endl;    
        
        cout<<"1. Agregar Alumno"<<endl;
        cout<<"2. Agregar Profesor"<<endl;
        cout<<"3. Agregar Documento"<<endl;
        cout<<"4. Listar Usuarios"<<endl;
        cout<<"5. Listar Documentos"<<endl;
        cout<<"6. REALIZAR PRESTAMO"<<endl;
        cout<<"7. Salir"<<endl;
        cout<<"Elija una opcion: ";
        cin>>opcion;
        cin.ignore(); 
        switch(opcion){
            case 1: biblioteca.agregarPersona(1); break;
            case 2: biblioteca.agregarPersona(2); break;
            case 3: 
                int tipoDoc;
                cout<<"Tipo (1:Libro, 2:Tesis, 3:Revista): ";
                cin>>tipoDoc;
                cin.ignore(); 
                biblioteca.agregarDocumento(tipoDoc);
                break;
            case 4: biblioteca.listarPersonas(); break;
            case 5: biblioteca.listarDocumentos(); break;
            case 6: biblioteca.realizarPrestamo(); break;
        }
    }while(opcion != 7);

    return 0;
}
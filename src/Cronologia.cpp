#include <iostream>
#include "Cronologia.h"
#include "Fecha_Historica.h"

using namespace std;

//Resize
  void Cronologia::resize(int r){
     if(r>reservados){
     Fecha_Historica *aux = new Fecha_Historica[r];
     for (int i=0; i<neventos; i++)
        aux[i]=event[i];
     delete[] event;
     event = aux;
     reservados=r;
     }
  }

//Ordena
  void Cronologia::ordenar(){
     for (int i=neventos-1; i>0; --i)
      for (int j=0; j<i; ++j)
         if (event[j].getAnio() > event[j+1].getAnio()) {
            Fecha_Historica aux;
            aux = event[j];
            event[j] = event[j+1];
            event[j+1]= aux;
         }
  }

  void Cronologia::liberarMemoria(){
    neventos=reservados=0;
    delete [] event;
  }

  void Cronologia::reservarMemoria(int reserv){
    if(reserv>0){
      reservados=reserv;
      Fecha_Historica *event = new Fecha_Historica [reserv];
    }
    else
      reservados=0;
  }

  void Cronologia::copiar(Fecha_Historica *f, int reserv, int eventos){
    reservarMemoria(reserv);
    neventos=eventos;
    for(int i= 0; i< eventos; i++)
      event[i]=f[i];
  }

//Constructor vacío
  Cronologia::Cronologia():reservados(0),neventos(0),event(0){}


//Constructor con parámetro cadena de Fecha_Historica y número de objetos
  Cronologia::Cronologia(Fecha_Historica *eh, int n){
     copiar(eh,n,n);
  }

//Constructor de copia
   Cronologia::Cronologia(const Cronologia& c){
    *this=c;
   }


  Cronologia& Cronologia::operator=(const Cronologia& c){
    if(this != &c){
      liberarMemoria();
      copiar(c.event, c.reservados, c.neventos);
    }
    return *this;
  }

//Añade objeto de Fecha_Historica
  void Cronologia::addEvento(Fecha_Historica& eh){
     if (neventos == reservados){
        if (neventos==0)
           resize(1);
        else
           resize(2*reservados);
     }
     event[neventos]=eh;
     neventos++;
     ordenar();
  }


//Busca un año en la Cronología y devuelve si dicho año está en la cronología o no.
  int Cronologia::buscarAnio(int f){
     int i=0;
     bool valido=false;
     while(i<neventos && !valido){
        if(event[i].getAnio()==f)
           valido = true;
        else
           ++i;
     }
     if(!valido)
        i=-1;
     return i;
  }

//Devuelve el año en el que ha habido un mayor número de eventos
  int Cronologia::maxNumEvents(){
    int max= event[0].getNumEventos();
    int anio_max= event[0].getAnio();

    for(int i=1; i< neventos; i++){
      if(event[i].getNumEventos() > max){
        max= event[i].getNumEventos();
        anio_max= event[0].getAnio();
      }
    }
    return anio_max;
  }

//Devuelve si un año está repetido o no dentro de la Cronología
  bool Cronologia::estaRepetido(int anio){
    bool repetido= false;

    for(int i= 0; i< neventos && !repetido; i++){
      if(event[i].getAnio() == anio)
        repetido= true;

    }
    return repetido;
  }



//Busca un evento en la Cronología y devuelve su posición en el vector
  Cronologia Cronologia::buscarEventos(string s){
     Cronologia nuevo;
     for (int i=0; i < neventos; ++i){
        Fecha_Historica aux;
        if(event[i].buscarEventos(s,aux)){
           nuevo.addEvento(aux);
        }
     }
     nuevo.ordenar();
     return nuevo;
   }

//Operador <<
  ostream& operator<< (ostream& os, const Cronologia& c){
     for(int i=0; i<c.neventos; i++)
        os << c.event[i];
     return os;
  }

//Operador >>
  istream& operator>> (istream& is, Cronologia& c){
     Fecha_Historica b;
     while(is >> b){
        c.addEvento(b);
     }
     return is;
}

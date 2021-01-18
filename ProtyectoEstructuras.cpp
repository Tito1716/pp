#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <stdlib.h>
#include <cctype>

using namespace std;
int ni = 0;
int IdSacos = 0;
int Idzona = 0;
struct Transporte
{
    int id;
    string Nombre;
    string Modelo;
    int placa;
    int cantidad_viajes;
    float precio;
};

struct SacoCafe
{
    int Id_Entrega;
    int Encargado;
    int CantidadSacos;
    float Peso;
    string NombreFinca;
};
typedef Transporte Ta;
const Ta noValido = { -1, {" "}, {" "}, - 1 , -1};

struct ZonaCorte
{
    int id;
    string Zona;
    float Area;
    bool cortada;
};

struct Nodo
{
    Ta dato;
    struct Nodo* sig;
};
Nodo* pInicio;

void BorrarC()
{
    system("cls");
}

void Pausa()
{
    system("pause");
}

bool esNumerico(string linea)
{
    bool b = true;
    int longitud = linea.size();

    if (longitud == 0)
    {
        b = false;
    }
    else if (longitud == 1 && !isdigit(linea[0])){
        b = false;
    }
    else
    {
        int i;
        if (linea[0] == '+' || linea[0] == '-')
            i = 1;
        else
            i = 0;

        while (i < longitud) {
            if (!isdigit(linea[i])) 
            {
                b = false;
                break;
            }
            i++;
        }
    }
    return b;
}
bool EsFloat(string const& numero)
{
    bool toReturn = false;

    try
    {
       size_t pos = 0;
        stof(numero, &pos);

        toReturn = (pos == numero.length());
    }

    catch (exception const&)
    {
        // 123o00 -> std::out_of_range      
        // HOLA      -> std::invalid_argument
    }

    return toReturn;
}

//Declaraciones de funciones 
Ta Referecia();
void MostrarDatos(Transporte p, bool MI);
void Mostrar(bool MI);
void MenuTransportistas();
void Eliminar();
void Buscar();
void Agregar();
void Vaciar(Nodo** nodoInicio);
bool Comparar(Transporte a, Transporte b);
bool CompararId(Transporte a, int b);
// Funciones Cafe
void MenuSacosCafe(stack <SacoCafe> &T, stack <SacoCafe> &B, stack <SacoCafe> &A, stack <SacoCafe> &P);
void AgregarCafe(stack <SacoCafe> &E, int T);
void Mostrarcafes(stack <SacoCafe>& T, stack <SacoCafe>& B, stack <SacoCafe>& A, stack <SacoCafe>& P);
void MD(stack <SacoCafe>& T, int i);
void MenuEliminar_Datos(stack <SacoCafe>& T, stack <SacoCafe>& B, stack <SacoCafe>& A, stack <SacoCafe>& P);
void SacarDatos(stack <SacoCafe>& T, int i);
//Zona del area de corte
void MenuCorte();
void AgregarCorte(queue <ZonaCorte> &Z);
void PasoDatosMostrar(queue <ZonaCorte>& Z, queue <ZonaCorte>& Z1);
void MostrarZona(queue <ZonaCorte>& Z, int i);
void CambiarEstadoZona(queue <ZonaCorte>& Z, queue <ZonaCorte>& Z1 );
int main()
{
    bool continuar = true, con2  = true;
    stack <SacoCafe> Tekisic, Bourbon, arabigo, Pacamara;
    string opcion ;
    int op;

    do
    {
        BorrarC();
       
        cout << "\n ---------------MENU PRINCIPAL---------------"<< endl;
        cout << "|1.Menu de transportista.                   |" << endl;
        cout << "|2.Agregar sacos al recibidero.             |" << endl;
        cout << "|3.Mostrar sacos en el recibidero.          |" << endl;
        cout << "|4.Retirar sacos de cafe del recibidero.    |" << endl;
        cout << "|5.Menu zonas de corte.                     |" << endl;
        cout << "|6.Salir.                                   |" << endl;
        cout << " -------------------------------------------" << endl;
        do
        {
            cout << "Opcion a elegir: ";
            getline(cin, opcion);
            if (esNumerico(opcion))
            {
                con2 = false;
                op = atoi(opcion.c_str());
                if (op > 0)
                {
                    con2 = false;
                }
                else
                {
                    cout << "\nIngrese un numero valido." << endl;
                    con2 = true;
                }
            }
            else
            {
                cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
                con2 = true;
            }
        } while (con2);
        
        switch (op)
        {
        case 1: MenuTransportistas();
            break;
        case 2: MenuSacosCafe(Tekisic, Bourbon, arabigo, Pacamara);
            break;
        case 3: Mostrarcafes(Tekisic, Bourbon, arabigo, Pacamara);
            break;
        case 4: MenuEliminar_Datos(Tekisic, Bourbon, arabigo, Pacamara);
            break;
        case 5: MenuCorte();
            break;
        case 6: continuar = false;
        default:
            break;
        }
    } while (continuar);
    return 0;
}
//Zona Cafe
void MenuSacosCafe(stack <SacoCafe>& T, stack <SacoCafe>& B, stack <SacoCafe>& A, stack <SacoCafe>& P)
{
    bool con = true, con2 = true;
    string op;
    int opcion, po2 = 0;
    do
    {
        system("cls");
        cout << " \n ----------------------------------" << endl;
        cout << "|  Agregar Sacos de tipo de cafe   |" << endl;
        cout << "|        1. Cafe Tekisic           |" << endl;
        cout << "|        2. Cafe Bourbon           |" << endl;
        cout << "|        3. Cafe Arabigo           |" << endl;
        cout << "|        4. Cafe Pacamara          |" << endl;
        cout << "|        5. Salir                  |" << endl;
        cout << " ----------------------------------" << endl;
        
        do
        {
            cout << "  Opcion a elegir: ";
            getline(cin, op);
            if (esNumerico(op))
            {
                con = false;
                opcion = atoi(op.c_str());
                if ((opcion > 0))
                {
                    con2 = false;
                }
                else
                {
                    cout << "\nIngrese un numero valido." << endl;
                    con2 = true;
                }
            }
            else
            {
                cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
            }
        } while (con2);
        
        switch (opcion)
        {
        case 1: AgregarCafe(T, 1);
            break;
        case 2:  AgregarCafe(B, 2);
            break;
        case 3:  AgregarCafe(A, 3);
            break;
        case 4: AgregarCafe(P, 4);
            break;
        case 5: con = false;
            break;
        default:
            cout << "\nIngrese un digito corecto." << endl;
            break;
        }
    } while (con);
}

void AgregarCafe(stack <SacoCafe>& E, int T)
{
    SacoCafe Sa;
    bool con2 = true, Vcs = true, Vp = true;
    
    string Cs , P ;
    int Ncs;
    float Np;
    Nodo* s = pInicio;

    if (s != NULL)
    {
        BorrarC();
        switch (T)
        {
        case 1:
            cout << " -----------Agregar cafe Tekisic ----------- " << endl;
            break;
        case 2:
            cout << " -----------Agregar cafe Bourbon ----------- " << endl;
            break;
        case 3:
            cout << " -----------Agregar cafe arabigo ----------- " << endl;
            break;
        case 4:
            cout << " -----------Agregar cafe Pacamara ----------- " << endl;
            break;
        default:
            cout << "Cafe no encontrado.";
            break;
        }
        cout << "|                                            |" << endl;

            bool band = false;
            Ta ref = Referecia();
            while (s != NULL)
            {
                if (Comparar(s->dato, ref))
                {
                    IdSacos++;
                    Sa.Id_Entrega = IdSacos;
                    MostrarDatos(s->dato, true);
                    Sa.Encargado = s->dato.id;
                    cout << "\n|Encargado sera: " << s->dato.Nombre << endl;
                    do
                    {
                        cout << "|Sacos a ingresar: ";
                        getline(cin, Cs);
                        if (esNumerico(Cs))
                        {
                            Ncs = atoi(Cs.c_str());
                            if ((Ncs > 0))
                            {
                                Sa.CantidadSacos = Ncs;
                                Vcs = false;
                            }
                            else
                            {
                                cout << "\nIngrese un numero valido." << endl;
                                Vcs = true;
                            }
                        }
                        else
                        {
                            cout << "\nNo ha ingresado un numero. Intente nuevamente" << endl;
                            Vcs = true;
                        }
                    } while (Vcs);
                    cout << "|Finca de procendencia: ";
                    getline(cin, Sa.NombreFinca);
                    do
                    {
                        cout << "|Peso (En libras): ";
                        getline(cin, P);
                        if (EsFloat(P))
                        {
                            Np = atoi(P.c_str());
                            if ((Np > 0))
                            {
                                Sa.Peso = Np;
                                Vp = false;
                            }
                            else
                            {
                                cout << "\nIngrese un numero valido." << endl;
                                Vp = true;
                            }
                        }
                        else
                        {
                            cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
                            Vp = true;
                        }
                    } while (Vp);

                    //Agregando el precio y entragas al Transportista
                    s->dato.cantidad_viajes++;
                    s->dato.precio += s->dato.precio + 5;
                    E.push(Sa);
                    cout << "\n-Sacos Ingresados al recibidero Exitosamente.-" << endl;
                    Pausa();
                    return;
                }
                s = s->sig;
            }
                cout << "\n|Transportista no encontrado." << endl;
                Pausa();
                return;
    }
    else
    {
        cout << "|NO hay transportistas ingresados. " << endl;
    }
    Pausa();
}

void Mostrarcafes(stack <SacoCafe>& T, stack <SacoCafe>& B, stack <SacoCafe>& A, stack <SacoCafe>& P)
{
    int iden = 1;
    bool band = true;
    do
    {
        switch (iden)
        {
        case 1: MD(T, iden);
            iden = 2;
            break;
        case 2: MD(B, iden);
            iden = 3;
            break;
        case 3: MD(A, iden);
            iden = 4;
            break;
        case 4: MD(P, iden);
            iden  = 5;
            break;
        case 5: band = false;
        default:
            cout << "Error raro :c";
            break;
        }
    } while (band);
    //Tekisic, Bourbon, arabigo, Pacamara
}
void MD(stack<SacoCafe>& T, int i)
{
    stack <SacoCafe> Copia = T;
    if (i == 1)
    {
        cout << "\n----------------Cafe Takisic----------------" << endl;
    }
    else if (i == 2)
    {
        cout << "\n\n----------------Cafe Bourbon----------------" << endl;
    }
    else if (i == 3)
    {
        cout << "\n\n----------------Cafe Arabigo----------------" << endl;
    }
    else if (i == 4)
    {
        cout << "\n\n----------------Cafe Pacamara---------------" << endl;
    }
    while (!Copia.empty())
    {
        SacoCafe Sa = Copia.top();
        cout << "\n|Identifcador de la entrega: " << Sa.Id_Entrega << endl;
        cout << "|Identificador del encargado: " << Sa.Encargado << endl;
        cout << "|Nombre de la finca: " << Sa.NombreFinca << endl;
        cout << "|Peso: " << Sa.Peso << endl;
        cout << "|Cantidad de sacos: " << Sa.CantidadSacos <<  endl;
        Copia.pop();
    }
    cout << "\n----------------Lista vacia-----------------" << endl;
    Pausa();
}

void MenuEliminar_Datos(stack <SacoCafe>& T, stack <SacoCafe>& B, stack <SacoCafe>& A, stack <SacoCafe>& P)
{
    // Tekisic, Bourbon, arabigo, Pacamara
    bool continuar = true, val = true;
    string dato;
    int Id = 0;
    do
    {
        BorrarC();
        cout << "\n----------------Sacar Datos-----------------" << endl;
        cout << "|         1.Sacar Datos de cafe Tekisic      | " << endl;
        cout << "|         2.Sacar Datos de cafe Bourbon      | " << endl;
        cout << "|         3.Sacar Datos de cafe arabigo      | " << endl;
        cout << "|         4.Sacar Datos de cafe Pacamara     | " << endl;
        cout << "|         5.Salir                            |" << endl;
        cout << " ------------------------------------------" << endl;
        do
        {
            cout << "Elegir opcion: ";
            getline(cin, dato);
            if (esNumerico(dato))
            {
                Id = atoi(dato.c_str());
                if ((Id > 0))
                {
                    val = false;
                }
                else
                {
                    cout << "\nIngrese un numero valido." << endl;
                    val = true;
                }
            }
            else
            {
                cout << "\nNo ha ingresado un entero. Intente nuevamente(Enter par continuar)" << endl;
                break;
            }
        } while (val);

        switch (Id)
        {
        case 1: SacarDatos(T, 1);
            break;
        case 2: SacarDatos(B, 2);
            break;
        case 3: SacarDatos(A, 3);
            break;
        case 4: SacarDatos(B, 4);
            break;
        case 5: continuar = false;
            break;
        default: cout << "Ingrese un nunero valido" << endl;
            break;
        }

    } while (continuar);

}

void SacarDatos(stack<SacoCafe>& T, int i)
{
    int Tamaño = 0, HaRea = 0;
    string valRea;
    bool ValidadcionNumero = true;
    BorrarC();
    if (!T.empty())
    {
        if (i == 1)
        {
            cout << "\n----------------Cafe Takisic----------------" << endl;
        }
        else if (i == 2)
        {
            cout << "\n----------------Cafe Bourbon----------------" << endl;
        }
        else if (i == 3)
        {
            cout << "\n----------------Cafe Arabigo----------------" << endl;
        }
        else if (i == 4)
        {
            cout << "\n----------------Cafe Pacamara---------------" << endl;
        }
        Tamaño = T.size();
        do
        {
            cout << "|Hay: " << Tamaño << " Cuantos sacos se retiraran: ";
            getline(cin, valRea);
            if (esNumerico(valRea))
            {
                HaRea = atoi(valRea.c_str());
                if ((HaRea > 0))
                {
                    ValidadcionNumero = false;
                }
                else
                {
                    cout << "\nIngrese un numero valido." << endl;
                    ValidadcionNumero = true;
                }
            }
            else
            {
                cout << "\nNo ha ingresado un entero. Intente nuevamente(Enter par continuar)" << endl;
                break;
            }
        } while (ValidadcionNumero);
        if (!HaRea < Tamaño || !(HaRea > Tamaño))
        {
            for (int a = 1; a <= HaRea; a++)
            {
                SacoCafe Sa = T.top();
                cout << "| Se sacaran: " << Sa.CantidadSacos << " , con un peso de: " << Sa.Peso << endl;
                T.pop();
                cout << "\nSe han sacado exitosamente";
            }
        }
        else
        {
            cout << "\n|Ingrese un numero existente." << endl;
        }
    }
    else
    {
        cout << "\n|No se encuentran sacos de este tipo.";
    }
    Pausa();
}
//Zona de las zonas de corte
void MenuCorte()
{
    queue <ZonaCorte> ZonaHecha, ZonaNohecha;
    bool valcorte = true, continuar = true;
    int op = 0;
    string opcion;
    do
    {
        BorrarC();
        cout << "\n ---------------MENU PRINCIPAL---------------" << endl;
        cout << "|1.Agregar zona de corte                    |" << endl;
        cout << "|2.Mostrar zona de corte                    |" << endl;
        cout << "|3.Terminar zona de corte                   |" << endl;
        cout << "|4.Salir.                                   |" << endl;
        cout << " -------------------------------------------" << endl;
        do
        {
            cout << "Opcion a elegir: ";
            getline(cin, opcion);
            if (esNumerico(opcion))
            {
                op = atoi(opcion.c_str());
                if ((op > 0))
                {
                    valcorte = false;
                }
                else
                {
                    cout << "\nIngrese un numero valido." << endl;
                    valcorte = true;
                }
            }
            else
            {
                cout << "\nNo ha ingresado un entero. Intente nuevamente(Enter par continuar)" << endl;
                break;
            }
        } while (valcorte);
        switch (op)
        {
        case 1:AgregarCorte(ZonaNohecha);
            break;
        case 2: PasoDatosMostrar(ZonaNohecha, ZonaHecha);
            break;
        case 3: CambiarEstadoZona(ZonaNohecha, ZonaHecha);
            break;
        case 4: continuar = false;
        default:
            break;
        }
    } while (continuar);
   

}
void AgregarCorte(queue<ZonaCorte>& Z)
{
    bool continuar = true, val = true;
    char op = 's';
    string Zona;
    float zo;
   
    BorrarC();
    do
    {
        cout << "Desea agregar una zona de corte Si(S) o NO(Cualquier tecla): ";
        cin >> op;
        if (op == 's' || op == 'S')
        {
            cout << "------------Agregado zona------------" << endl;
            ZonaCorte za;
            Idzona++;
            cout << "\nId de zona: " << Idzona << endl;
            za.id = Idzona;
            cin.ignore();
            cout << "Ingrese el nombre de la zona: "; getline(cin, za.Zona);
            do
            {
                cout << "Ingrese el tamaño del area: "; getline(cin, Zona);
                if (EsFloat(Zona))
                {
                    zo = atoi(Zona.c_str());
                    if ((zo > 0))
                    {
                        za.Area = zo;
                        val = false;
                    }
                    else
                    {
                        cout << "\nIngrese un numero valido." << endl;
                        val = true;
                    }
                }
                else
                {
                    cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
                }
            } while (val);
            za.cortada = true;
            Z.push(za);
            continuar = true;
        }
        else
        {
            cout << "\nSaliendo......" << endl;
            continuar = false;
            cin.ignore();
            break;
        }
        Pausa();
    } while (continuar);
}

void PasoDatosMostrar(queue<ZonaCorte> &Z, queue<ZonaCorte> &Z1)
{
    int iden = 1;
    bool band = true;
    BorrarC();
    do
    {
        switch (iden)
        {
        case 1: MostrarZona(Z, iden);
            iden = 2;
            break;
        case 2: MostrarZona(Z1, iden);
            iden = 3;
            break;
        case 3: band = false;
            break;
        default:
            cout << "Error raro :c";
            break;
        }
    } while (band);
    Pausa();
}

void MostrarZona(queue<ZonaCorte>& Z, int i)
{
    queue <ZonaCorte> copia = Z;
    if (i == 1)
    {
        cout << "\n------------Zonas no cortadas------------" << endl;
    }
    else if (i == 2)
    {
        cout << "\n------------Zona ya cortadas--------------" << endl;
    }
    while (!copia.empty())
    {
        ZonaCorte Za = copia.front();
        cout << "\nId de la zona: " << Za.id << endl;
        cout << "Nombre de la zona: " << Za.Zona << endl;
        cout << "Area de la zona: " << Za.Area << endl;
        copia.pop();
    }
    cout << "\n------------Lista Vacia. ------------" << endl;
}

void CambiarEstadoZona(queue<ZonaCorte>& Z, queue<ZonaCorte>& Z1)
{
    char c = 's';
    if (!Z.empty())
    {
        ZonaCorte za = Z.front();
        cin.ignore();
        cout << "\nLa zona: " << za.Area << " Ha sido cortada por completo?: ";
        cin >> c;
        if ((c == 's') || c == 'S')
        {
            Z1.push(za);
            Z.pop();
            cout << "\nZona ha cambiado de estado. ";
            cin.ignore();
        }
        else
        {
            cout << "Accion cancelada." << endl;
            cin.ignore();
        }
    }
    else
    {
        cout << "Zona de corte hecha vacia, ";
    }
    Pausa();
}

//Zona transportisas
bool Comparar(Transporte a, Transporte b)
{
    return (a.id == b.id) && (a.Nombre == b.Nombre) && (a.Modelo == b.Modelo) && (a.placa == b.placa);
}

bool CompararId(Transporte a, int b)
{
    return (a.id == b);
}

Ta Referecia()
{
    string Idl;
    int Id;
    bool con = true, con2 = true;
    do
    {
        cin.ignore();
        cout << "|   Ingrese el numero de identificacion: ";
        getline(cin, Idl);
        if (esNumerico(Idl))
        {
            con = false;
            Id = atoi(Idl.c_str());
            if ((Id > 0))
            {
                con2 = false;
            }
            else
            {
                cout << "\nIngrese un numero valido." << endl;
                con2 = true;
            }
        }
        else
        {
            con2 = true;
            cout << "\nNo ha ingresado un entero. Intente nuevamente(Enter par continuar)" << endl;
        }
    } while (con2);
    Transporte p;
    bool band = true;
    Nodo* actual = new Nodo();
    actual = pInicio;
    p.id == Id;

    while (actual != NULL)
    {
        if (CompararId(actual->dato, Id))
        {
            return actual->dato;
        }
        
        actual = actual->sig;
    }
    if (actual == NULL)
    {
        cout << "No se encuentra"  << endl; 
        Pausa();
        return noValido;
  
    }
    Pausa();
    
}

void Vaciar(Nodo **nodoInicio)
{
    system("cls");
    Nodo* current = *nodoInicio;
    Nodo* next;

    while (current != NULL) {
        next = current->sig;
        delete(current);
        current = next;
    }
    *nodoInicio = NULL;
    cout << "\nLista vacia" << endl;
    system("pause");
}

void Buscar()
{
    system("cls");
    Nodo* s = pInicio;
    bool continuar = true;
    char c = 's';
    do
    {
        cout << "\nDesea buscar un dato S = Si, Salir(No) = N: ";
        cin >> c;
        if (c == 'S' || c == 's')
        {
            if (s != NULL)
            {
                bool band = false;
                cout << "\n   ---------BUSQUEDA DE DATOS---------" << endl;
                Ta ref = Referecia();
                while (s != NULL)
                {
                    if (Comparar(s->dato, ref))
                    {
                        cout << "El dato SI se encuentra" << endl;
                        MostrarDatos(s->dato, false);
                        system("pause");
                        return;
                    }
                    s = s->sig;
                }
                    cout << "El dato NO se encuentra" << endl;
                    system("pause");
                    return;
            }
            else
            {
                cout << "No hay elementos ingresados." << endl;
                continuar = false;
                
            }
        }
        else
        {
            continuar = false;
            cin.ignore();
        }
    } while (continuar);
    Pausa();
}
void Eliminar()
{
    BorrarC();
    Nodo* p = pInicio, * q = NULL;
    if (p != NULL)
    {
        bool mi = true;
        Mostrar(mi);
        cout << "\nDATOS A ELIMINAR." << endl;
        Ta ref = Referecia();
        while (p != NULL)
        {
            if (Comparar(p->dato, ref))
            {
                if (p == pInicio)
                {
                    pInicio = pInicio->sig;
                }
                else
                
                    q->sig = p->sig;
                
                delete(p);
                cout << "Dato borrado!" << endl;
                Pausa();
                return;
            }
            q = p;
            p = p->sig;
        }
        if (p == NULL)
        {
            system("pause");
            return;
        }
        
            
    }
    else
    {
        cout << "No hay elementos ingresados." << endl;
    }
    system("pause");
}

void MostrarDatos(Transporte p, bool MI)
{
    cout << "\n\n--------------Mostrando Datos.--------------" << endl;
    cout << "\n|Numero de identificacion:            " << p.id <<endl;
    cout << "|Nombre: " << p.Nombre << endl;
    if (MI == false)
    {
        cout << "|Placa: " << p.placa << endl;
        cout << "|Modelo: " << p.Modelo << endl;
        cout << "|Cantidad de viajes: " << p.cantidad_viajes  << endl;
        cout << "|A pagar: " << p.precio << endl;
    }
}

void Mostrar(bool MI)
{
    BorrarC();
    cout << "\n\n------Mostrando los datos.------" << endl;
    Nodo* s = pInicio;
    if (s != NULL)
    {
        while (s != NULL)
        {
            MostrarDatos(s->dato, MI);
            s = s->sig;
        }
    }
    else
    {
        cout << "\nNo hay elementos." << endl;
    }
    system("pause");
}
void Agregar()
{
    bool continuar = true, con = true, con2 = true;
    char c = 's';
    string pla;
    int placa = 0;
    system("cls");
   
    do
    {
        cout << "\nDesea agregar un usuario: (SI = S / Salir = cualquier tecla) ";
        cin >> c;
        if (c == 's' || c == 'S')
        {

            cout << "\n------Agregando Transportista------" << endl;
            Transporte T;
            ni++;
            int i;
            i = ni;
            T.id = i;
            cout << "\nNumero de identificacion: " << i << endl; cin.ignore();
            cout << "|Nombre del conductor: ";
            getline(cin, T.Nombre); 
            cout << "|Modelo del carro: ";
            getline(cin, T.Modelo);
            do
            {
                cin.ignore();
                cout << "|Ingrese numero de placa: ";
                getline(cin, pla);
                if (esNumerico(pla))
                {
                    con2 = true;
                    placa = atoi(pla.c_str());
                    if ((placa >= 000001 && placa <= 999999 ))
                    {
                        T.placa = placa;
                        con2 = false;
                    }
                    else
                    {
                        cout << "\nIngrese un numero valido." << endl;
                        con2 = true;
                    }
                }
                else 
                {
                    con2 = true;
                    cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
                    cin.ignore();
                }

            } while (con2);
            T.cantidad_viajes = 0;
            T.precio = 0;
            //Creacion de viajes u Cantidad a pagar

            /*Nodo* nuevo = new Nodo;
            nuevo->dato = T;
            nuevo->sig = pInicio;

            pInicio = nuevo;*/
            Nodo* nuevo = new Nodo;
            nuevo->dato = T;
            nuevo->sig = NULL;

            if (pInicio == NULL) {
                pInicio = nuevo;
            }
            else {
                Nodo* p = pInicio;
                Nodo* q = NULL;
                while (p != NULL) {
                    q = p;
                    p = p->sig;
                }
                q->sig = nuevo;
            }

            cout << "\nElemento  insertado a lista correcta" << endl;
            continuar = true;
        }
        else
        {
            continuar = false;
            cin.ignore();
        }
        system("pause");
    } while (continuar);
}
void Actualizar()
{
    BorrarC();
    Transporte T;
    Nodo* actual = pInicio;
    bool encontrado = false, con2 = true, viajes = true, pagar = true;
    string pla, viaje, pagars;
    int placa, viajar;
    float pagando;
    if (actual != NULL)
    {
        cout << "\n------DATO A BUSCAR------" << endl;
        Ta ref = Referecia();
        while (actual != NULL)
        {
            if (Comparar(actual->dato, ref))
            {
                cout << "El numero de identificacion es: " << ref.id;
                actual->dato.id = ref.id;
                cout << "\nEl nombre actual es: " << ref.Nombre << ", El nuevo sera: "; getline(cin, T.Nombre);
                actual->dato.Nombre = T.Nombre;
                cout << "\nEl modelo es: " << ref.Modelo << " el nuevo sera: "; getline(cin, T.Modelo);
                actual->dato.Modelo = T.Modelo;
                do
                {
                    cout << "\nLa placa es: " << ref.placa << " la nueva placa es: ";
                    getline(cin, pla);
                    if (esNumerico(pla))
                    {
                        placa = atoi(pla.c_str());
                        if ((placa >= 000001 && placa <= 999999))
                        {
                            T.placa = placa;
                            actual->dato.placa = T.placa;
                            con2 = false;
                        }
                        else
                        {
                            cout << "\nIngrese un numero valido." << endl;
                            con2 = true;
                        }
                    }
                    else
                    {
                        cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
                    }
                } while (con2);
                do
                {
                    cout << "\nLa canitidad de viajes realizada es: " << ref.cantidad_viajes << " nueva cantidad de viajes: ";
                    getline(cin, viaje);
                    if (esNumerico(viaje))
                    {
                        viajar = atoi(viaje.c_str());
                        if ((viajar >= 0))
                        {
                            T.cantidad_viajes = viajar;
                            actual->dato.cantidad_viajes = T.cantidad_viajes;
                            viajes = false;
                        }
                        else
                        {
                            cout << "\nIngrese un numero valido." << endl;
                            viajes = true;
                        }
                    }
                    else
                    {
                        cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
                    }

                } while (viajes);
                do
                {
                    cout << "A pagar: " << ref.precio << " A pagar ahora: ";
                    getline(cin, pagars);
                    if (EsFloat(pagars))
                    {
                        pagando = atoi(pagars.c_str());
                        if ((pagando >= 0))
                        {
                            T.precio = pagando;
                            actual->dato.precio = T.precio;
                            pagar = false;
                        }
                        else
                        {
                            cout << "\nIngrese un numero valido." << endl;
                            pagar = true;
                        }
                    }
                    else
                    {
                        cout << "\nNo ha ingresado un numero. Intente nuevamente" << endl;
                    }
                } while (pagar);
                cout << "\nEl dato ha sido modificado." << endl;
                Pausa();
                return;
            }
            actual = actual->sig;
        }
        cout << "El dato no se encuentra. " << endl;
        Pausa();
        return;
    }
    else
    {
        cout << "\nNo hay elementos ingresados." << endl;
    }
    system("pause");
}
void MenuTransportistas()
{
    bool con = true, con2 = true;
    bool mi = false;
    string opcion;
    int dato = 0;
    do
    {
        BorrarC();
        cout << "\n -------------Menu Tranportistas-------------" << endl;
        cout << "|1.Agregar Transportista                     |" << endl;
        cout << "|2.Mostrar lista de transportistas.          |" << endl;
        cout << "|3.Eliminar Lista de transportistas.         |" << endl;
        cout << "|4.Buscar transportista.                     |" << endl;
        cout << "|5.Actualizar.                               |" << endl;
        cout << "|6.Borrar Todo.                              |" << endl;
        cout << "|7. Salir.                                   |" << endl;
        cout << " --------------------------------------------" << endl;
        do
        {
            cout << "Ingrese su opcion: ";
            getline(cin, opcion);
            if (esNumerico(opcion))
            {
                dato = atoi(opcion.c_str());
                if (dato > 0)
                {
                    con2 = false;
                }
                else
                {
                    cout << "\nIngrese un numero valido." << endl;
                    con2 = true;
                }
            }
            else
            {
                con2 = true;
                cout << "\nNo ha ingresado un entero. Intente nuevamente" << endl;
            }
        } while (con2);
        
            switch (dato)
            {
            case 1: Agregar();
                break;
            case 2: Mostrar(mi);
                break;
            case 3: Eliminar();
                break;
            case 4: Buscar();
                break;
            case 5: Actualizar();
                break;
            case 6: Vaciar(&pInicio);
                break;
            case 7: con = false;
                cin.ignore();
                break;
            default: cout << "Ingresar un digito valido." << endl;
                break;
            }
    } while (con);
    Pausa();
}

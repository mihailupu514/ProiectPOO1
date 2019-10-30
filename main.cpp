#include <iostream>
#include <list>
using namespace std;

int Matrice[20][20],matrice_drumuri[20][20],matrice_adiacenta1[20][20],matrice_adiacenta2[20][20];
int verif[10],verif2[10],coada[10],N;
struct Nod {
    int val;      //valoarea numerica
    Nod* next;   //structura de stocare pentru lista de adiacenta
};

struct Muchie {
    int src, dest;   //structura de stocare muchie
};
class Graph
{
    // Functie de alocare nod nou la lista de adiacenta
    static Nod* AdaugareNod(int dest, Nod* rad)
    {
        Nod* newNod = new Nod;
        newNod->val = dest;

        // pointeaza noul nod la rad actuala
        newNod->next = rad;

        return newNod;
    }

    int N;  // numar de noduri in graf


public:
    // Un vector de pointeri la Nod
    // lista de adiacenta
    Nod **rad;

    // Constructor
    Graph(Muchie edges[], int n, int N)
    {
        //incercarea nr 1 matrice adiacenta
           //functie de adaugare muchie in matrice

        // alocare memorie
        rad = new Nod*[N]();
        this->N = N;

        // initializarea pointerului radacinii
        for (int i = 0; i < N; i++)
            rad[i] = NULL;

        // adauga muchii la graful
        for (unsigned i = 0; i < n; i++)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;
            Matrice[src][dest] = 1;
            Matrice[dest][src] = 1;

            // inserare la inceput
            Nod* newNode = AdaugareNod(dest, rad[src]);

            // pointare rad la noul nod
            rad[src] = newNode;

            newNode = AdaugareNod(src, rad[dest]);

            // schimbare
            rad[dest] = newNode;

        }
    }

    friend ostream& operator<<(ostream&,const Graph&); //Operatorul << pentru printarea metodelor de afisare
    friend Graph operator+(const Graph&); //operatorul + pentru reuniunea grafurilor
    // Destructor
    ~Graph() {
        for (int i = 0; i < N; i++)
            delete[] rad[i];

        delete[] rad;
    }
    static void printareLista(Nod* ptr);
    static void AfisareMatrice(int p);
    void parcurgere_adancime(int k);
    void parcurgere_latime(int start);
    void matricea_drumurilor();
    void componente_conexe();
    void graf_conex();
    void stocare_matrice1();
    void stocare_matrice2();
    void reunine();
};

void Graph::graf_conex() {
    int iterator1,iterator2;
    int count=0; //In matricea de adiacenta a unui graf conex toate elementele de pe diagonala principala sunt 0 iar restul 1 si verificam acest lucru.
    for(iterator1=1; iterator1 <= N; iterator1++)
        for(iterator2=1; iterator2 <= N; iterator2++)
        {
            if(Matrice[iterator1][iterator2]==0)
                count++;
        }
    if(count==N)
        cout<<endl<<"Graful este conex";
    else
        cout<<endl<<"Graful nu este conex";

}

void Graph::printareLista(Nod *ptr)
{
    while (ptr != NULL)
    {
        cout << " -> " << ptr->val << " ";
        ptr = ptr->next;
    }
    cout <<" / "<<endl;
}

void Graph::AfisareMatrice(int p)
{//p este Numarul de noduri
    int i, j;
    for (i = 0; i < p; i++) {
        for (j = 0; j < p; j++)
        {
            cout << Matrice[i][j] << " ";
        }
        cout << endl;
    }

}

ostream& operator<<(ostream& out,const Graph& graf)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
        {
            out << Matrice[i][j] << " ";
        }
        out << endl;
    }
    cout<<endl;
    for (int iterator = 0; iterator < N; iterator++)
    {        cout << i << " --";
        while (graf.rad[iterator] != NULL)
    {
        cout << " -> " << graf.rad[iterator]->val << " ";
        graf.rad[iterator] = graf.rad[iterator]->next;
    }
    cout <<" / "<<endl;}
    return out;
}

Graph operator+(const Graph& graf,const Graph& graf2)
{
    for (int iterator1 = 0; iterator1 < N; iterator1++)
        for (int iterator2 = 0; iterator2 < N; iterator2++) {
            Matrice[iterator1][iterator2] =
                    matrice_adiacenta1[iterator1][iterator2] + matrice_adiacenta2[iterator1][iterator2];
            if (Matrice[iterator1][iterator2] > 1)
                Matrice[iterator1][iterator2] = 1;
        }
    for (int iterator1 = 0; iterator1 < N; iterator1++) {
        for (int iterator2 = 0; iterator2 < N; iterator2++) {
            cout << Matrice[iterator1][iterator2] << " ";
        }
        cout << endl;
    }
return graf;
}

void Graph::parcurgere_adancime(int k)
{
    verif[k]=1; // in vectorul verif punem valoarea 1 daca am trecut prin nodul respectiv
    cout<<k<<" ";
    for(int i=0;i<N;i++)
        if(Matrice[k][i]==1 && verif[i]==0) //daca exista muchie intre nodurile k si i si nodul nu a fost vizitat apelam functia pt nodul i
        {
            parcurgere_adancime(i);

        }
}

void Graph::parcurgere_latime(int start)
{
    int i,k,st,dr;
    st=dr=0;
    coada[0]=start;
    verif2[start]=1; // dam check la primul nod
    while(st<=dr)
    {
        k=coada[st];
        for(i=0;i<N;i++)
            if(verif2[i]==0 && Matrice[k][i]==1) // daca i este vecin cu k si nu este vizitat
            {
                verif2[i]=1;
                coada[++dr]=i;
            }
        st++;
    }
    for(i=0;i<N;i++)
    {
        cout<<coada[i]<<" ";
    }
}

void Graph::matricea_drumurilor()
{
    int i, j, k;
    for(k=0;k<N;k++)
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                if(i!=j)
                    if(Matrice[i][j]==0)
                        matrice_drumuri[i][j]=Matrice[i][k]*Matrice[k][j];

    for(i=0;i<N;i++)
    {for(j=0;j<N;j++)
            cout<<matrice_drumuri[i][j]<<" ";
        cout<<endl;}
}

void Graph::componente_conexe()
{
    // Marcam toate nodurile care nu au fost vizitate
    for(int iterator = 0; iterator < N; iterator++)
        verif[iterator] = 0;

    for (int iterator=0; iterator < N ; iterator++)
    {
        if (verif[iterator] == 0)
        {
            // Printam toate nodurile la care putem sa ajungem folosind parcurgerea in adancime
            parcurgere_adancime(iterator);
            cout << "\n";
        }
    }

}

void Graph::stocare_matrice1() {
    for (int iterator1 = 0; iterator1 < N; iterator1++)
        for (int iterator2 = 0; iterator2 < N; iterator2++) {
            *(*(matrice_adiacenta1 + iterator1) + iterator2) = Matrice[iterator1][iterator2];

            Matrice[iterator1][iterator2] = 0;

        }

}
void Graph::stocare_matrice2() {
    for (int iterator1 = 0; iterator1 < N; iterator1++)
        for (int iterator2 = 0; iterator2 < N; iterator2++) {
            *(*(matrice_adiacenta2 + iterator1) + iterator2) = Matrice[iterator1][iterator2];

            Matrice[iterator1][iterator2] = 0;

        }

}

void Graph::reunine() {
    for (int iterator1 = 0; iterator1 < N; iterator1++)
        for (int iterator2 = 0; iterator2 < N; iterator2++) {
            Matrice[iterator1][iterator2] =
                    matrice_adiacenta1[iterator1][iterator2] + matrice_adiacenta2[iterator1][iterator2];
            if (Matrice[iterator1][iterator2] > 1)
                Matrice[iterator1][iterator2] = 1;
        }
    for (int iterator1 = 0; iterator1 < N; iterator1++) {
        for (int iterator2 = 0; iterator2 < N; iterator2++) {
            cout << Matrice[iterator1][iterator2] << " ";
        }
        cout << endl;
    }
}
int main()
{
int operatie;
cout<<"Ce operatii se doresc ? "<<endl<<
      "1.Creare Graf"<<endl<<"2.Creare a n Grafuri"<<endl;
cin>>operatie;
    switch(operatie) {
        case 1: {
            int Nr_noduri = 0;
            int Nr_muchii = 0;
            cout << endl;
            cout << "Cate noduri sa aiba graful?";
            cin >> Nr_noduri;
            cout << endl;
            cout << "Cate muchii se doresc ?";
            cin >> Nr_muchii;
            cout << endl;
            cout
                    << "Introduceti perechile de muchii.Graful este neorientat . Prin urmare (x,y)=(y,x) . Precizare , primul nod are index 0";
            Muchie edges[Nr_muchii];
            for (int i = 0; i < Nr_muchii; i++) {
                cout << "Pereche : x=";
                cin >> edges[i].src;
                cout << "y=";
                cin >> edges[i].dest;
            }
            cout << "Ce operatii se doresc ? " << endl <<
                 "1.Printarea listei de adiacenta a unui graf 2.Printarea matricei de adiacenta" << endl <<
                 "3.Parcurgerea in adancime a grafului 4.Parcurgerea in latime a grafului 5.Matricea de existenta a drumurilor"
                 << endl <<
                 "6.Determinarea componentelor conexe 7.Determinare daca graful este conex 8.Reuniune 2 grafuri";
            cin >> operatie;
            Graph graf(edges, Nr_muchii, Nr_noduri);
            cout << endl;
            if (operatie == 1)
                for (int i = 0; i < Nr_noduri; i++) {
                    // printare nod start
                    cout << i << " --";

                    // printare noduri vecine
                    graf.printareLista(graf.rad[i]);
                }
            if (operatie == 2) {
                graf.AfisareMatrice(Nr_noduri); //afisare matrice de adiacenta
            }
            if (operatie == 3) {
                int nod_ales;
                cout << "1.Parcurgerea in adancime pentru un nod";
                cout << endl;
                cout << "2.Parcurgerea in adancime pentru toate nodurile";
                cout << endl;
                cin >> operatie;
                if (operatie == 1) {
                    cout << endl;
                    cout << "Din ce nod ?";
                    cout << endl;
                    cin >> nod_ales;
                    graf.parcurgere_adancime(nod_ales);
                }
                if (operatie == 2) {
                    for (int i = 0; i < Nr_noduri; i++) {
                        for (int j = 0; j < Nr_noduri; j++)
                            verif[j] = 0;
                        cout << "Nod:";
                        cout << i << " ->";
                        graf.parcurgere_adancime(i);
                        cout << endl;
                    }
                }

            }
            if (operatie == 4) {

                int nod_ales;
                cout << "1.Parcurgerea in latime pentru un nod";
                cout << endl;
                cout << "2.Parcurgerea in latime pentru toate nodurile";
                cout << endl;
                cin >> operatie;
                if (operatie == 1) {
                    cout << endl;
                    cout << "Din ce nod ?";
                    cout << endl;
                    cin >> nod_ales;
                    graf.parcurgere_latime(nod_ales);
                }
                if (operatie == 2) {
                    for (int i = 0; i < Nr_noduri; i++) {
                        for (int j = 0; j < Nr_noduri; j++)
                            verif2[j] = 0;
                        cout << "Nod:";
                        cout << i << " ->";
                        graf.parcurgere_latime(i);
                        cout << endl;
                    }
                }

            }
            if (operatie == 5) {
                graf.AfisareMatrice(Nr_noduri);
                graf.matricea_drumurilor();
            }
            if (operatie == 6) {
                graf.componente_conexe();
            }
            if (operatie == 7) {
                graf.graf_conex();
            }
            if (operatie ==8)
            {
                int Nr_noduri2 = 0;
                int Nr_muchii2 = 0;
                cout << endl;
                cout << "Cate noduri sa aiba graful al 2 lea?";
                cin >> Nr_noduri2;
                cout << endl;
                cout << "Cate muchii se doresc ?";
                cin >> Nr_muchii2;
                cout << endl;
                cout<< "Introduceti perechile de muchii.";
                Muchie edges2[Nr_muchii2];
                for (int i = 0; i < Nr_muchii2; i++) {
                    cout << "Pereche : x=";
                    cin >> edges2[i].src;
                    cout << "y=";
                    cin >> edges2[i].dest;}
                    graf.stocare_matrice1();
                    Graph graph2(edges2,Nr_muchii2,Nr_noduri2);
                    graph2.stocare_matrice2();
                    if(Nr_noduri==Nr_noduri2)
                    graf.reunine();
                    else
                        cout<<"Grafurile nu au acelasi numar de noduri";
                }
            }

        case 2: {

            /* cout << endl;

             int Nr_grafuri;
             int Nr_noduri[20];
             int Nr_muchii[20];
             cout << "Cate grafuri ?";
             cin >> Nr_grafuri;
             cout << endl;
             cout << "Introduceti numarul de noduri";
             cout << endl;
             for (int i = 0; i < Nr_grafuri; i++) {
                 cout << "Graful " << i << " sa aiba ";
                 cin >> Nr_noduri[i];
             }
             cout << "Introduceti numarul de muchii";
             cout << endl;
             for (int i = 0; i < Nr_grafuri; i++) {
                 cout << "Graful " << i << " sa aiba ";
                 cin >> Nr_muchii[i];
             }
             Edge muchii[Nr_grafuri][*Nr_muchii];
             for (int i = 0; i < Nr_grafuri; i++) {
                 cout << endl;
                 cout << "Pentru graful " << i << " . Introduceti perechile";
                 cout << endl;
                 for (int j = 0; j < Nr_muchii[i]; j++) {

                     cout << "Pereche : x=";
                     cin >> muchii[i][j].src;
                     cout << "y=";
                     cin >> muchii[i][j].dest;
                 }
             }
             cout << endl;

             cout << "Operatiile se vor efectua pentru un graf sau pentru toate? 1.Un graf 2.Toate";
             int counter;
             int graf_ales;
             cin >> counter;
             cout << "Pentru ce graf?";
             cin >> graf_ales;
             /*  for(int k=0;k<Nr_grafuri;k++)
                   Graph graf[k];
               if(counter=1)
               {
               } */
        }
    }
 return 0;}

#include <iostream>
using namespace std;
#include <typeinfo>
#include <string.h>
//de facut la final:
///constr de copiere
///calculez pauza cum trebuie, cu nr de pauze
/// daca introducem ceva gresit(ziua lunii>31, cifra in loc d ecaracter
class Spectacol;
class Prezentare
{
    int numarLocuri;
    int dataPrez;
    int nrAdulti;
    int nrCopii;
    int durVarTeatru;
    friend class Spectacol;
    friend class Teatru;
public:
    Prezentare();
    Prezentare(int,int);
    Prezentare(const Prezentare&);
    ~Prezentare();
    friend istream& operator>>(istream&, Prezentare&);
    friend ostream& operator<<(ostream&, Prezentare&);
    Prezentare& operator=(const Prezentare&);
    void citirePtTeatru();
    void afisarePtTeatru();
    void modifyDurTeatru(int );
    int returnNrLoc()
    {
        return numarLocuri;
    };

};
class Dorinta;
class Exigenta;

class Spectacol
{
protected:
    string denumire;
    int durata; //durata in minute
    string gen;
    Prezentare *lista;
    int prezpeLuna; // nr de prezentari pe luna
public:
    Spectacol();
    Spectacol(string, string); //denumire, gen
    Spectacol(const Spectacol&);
    virtual ~Spectacol();
    friend istream& operator>>(istream&, Spectacol&);
    friend ostream& operator<<(ostream&, Spectacol&);
    Spectacol& operator=(const Spectacol&);
    virtual int calcDurata()
    {
        return durata;
    };
    virtual void citire();
    virtual bool criteriu(string)
    {
        return false;
    };
    virtual bool criteriuEx(bool)
    {
        return false;
    };
    virtual bool returnAdulti()
    {
        return false;
    };
    virtual void afisare();
    virtual void afisareFiltru(int); //afisam spectacolele din datile unde e nr de locuri adecvat dorintei clientului
    friend bool respecta(Spectacol,Dorinta);
    friend bool respectaEx(Spectacol, Exigenta);

};

class Opera;
class Act
{
    string numeSolist;
    string tipSolist;
    int durata; //in minute
    friend class Opera;
public:
    Act();
    Act(string,string,int);
    Act(const Act&);
    ~Act();
    friend istream& operator>>(istream&, Act&);
    friend ostream& operator<<(ostream&, Act&);
    Act& operator=(const Act&);
};

class Opera: public Spectacol
{
protected:
    int nrActe;
    Act *acte; // nr de acte intre 2 si 7
    int durataPauza;
    bool pentruAdulti; // 1 e doar pt adulti si 0 e pt toata lumea
public:
    Opera();
    Opera(string, string,int,int,bool);
    Opera(const Opera&);
    ~Opera();
    int calcDurata();

    friend istream& operator>>(istream&, Opera&);
    friend ostream& operator<<(ostream&, Opera&);
    Opera& operator=(const Opera&);
    friend class bazaDate;
    void citire();
    void afisare();
    bool criteriu(string);
    void afisareFiltru(int);
    bool returnAdulti()
    {
        return pentruAdulti;
    };
};

class Prestatie;
class Animal
{
    string tip; //domestic sau salbatic
    string denumire;
    int numar;
    friend class Prestatie;
public:
    Animal();
    Animal(string, string, int);
    Animal(const Animal&);
    ~Animal();
    Animal& operator=(const Animal&);
    friend istream& operator>>(istream&, Animal&);
    friend ostream& operator<<(ostream&, Animal&);

};

class Prestatie
{
    bool pentruAdulti;
    bool areAnimale;
    Animal *lista;
    int durataPres;
    int nrAnimale;

public:
    Prestatie();
    Prestatie(int,bool,bool);
    Prestatie(const Prestatie&);
    ~Prestatie();
    friend istream& operator>>(istream&, Prestatie&);
    friend ostream& operator<<(ostream&, Prestatie&);
    Prestatie& operator=(const Prestatie&);

    friend class Spectacol;
    friend class Circ;
    bool verificaAnimal(string);
    bool areSalbatic();
};

class Circ: public Spectacol
{
    //toate sunt comedii
    //fara pauze intre prestatii
    int numarPrestatii;
    Prestatie *p;
    bool pentruAdulti;
    friend class Prestatie; //ca sa actualizam variabila pentru adulti
public:
    Circ();
    Circ(string, string, int);
    Circ(const Circ&);
    ~Circ();
    friend istream& operator>>(istream&, Circ&);
    friend ostream& operator<<(ostream&, Circ&);
    Circ& operator=(const Circ&);
    bool returnAudienta();
    int calcDurata();
    friend class bazaDate;
    void citire();
    void afisare();
    void afisareFiltru(int);
    bool criteriu(string);
    bool criteriuEx(bool);
    bool returnAdulti()
    {
        return pentruAdulti;
    };
};

class Teatru: public Spectacol
{
    // un singur act
    bool interactiv;
public:
    Teatru();
    Teatru(string, string,bool);
    Teatru(const Teatru&);
    Teatru& operator=(const Teatru&);
    ~Teatru();
    friend istream& operator>>(istream&, Teatru&);
    friend ostream& operator<<(ostream&, Teatru&);
    friend class bazaDate;
    void citire();
    void afisare();
    void afisareFiltru(int);
    bool returnInter()
    {
        return interactiv;
    };
};

class bazaDate
{
private:
    int nrt,nro,nrc; //nr de spectacole de teatru, opera, circ
    Teatru *listaT;
    Circ *listaC;
    Opera *listaO;

public:
    bazaDate();
    bazaDate(int, int, int);
    bazaDate(const bazaDate&);
    ~bazaDate();
    friend istream& operator>>(istream&, bazaDate&);
    friend ostream& operator<<(ostream&, bazaDate&);

};

bazaDate::bazaDate()
{
    nrc=nro=nrt=1;
    listaC= new Circ[nrc];
    listaO= new Opera[nro];
    listaT=new Teatru[nrt];
}
bazaDate::bazaDate(int a, int b, int c)
{
    nrt=a;
    nrc=b;
    nro=c;
    listaC= new Circ[nrc];
    listaO= new Opera[nro];
    listaT= new Teatru[nrt];
}

bazaDate :: bazaDate(const bazaDate& ob)
{
    nrt=ob.nrt;
    nrc=ob.nrc;
    nro=ob.nro;
    listaC= new Circ[nrc];
    listaO= new Opera[nro];
    listaT= new Teatru[nrt];

    for(int i=0; i<nrc; i++)
        listaC[i]=ob.listaC[i];
    for(int i=0; i<nro; i++)
        listaO[i]=ob.listaO[i];
    for(int i=0; i<nrt; i++)
        listaT[i]=ob.listaT[i];
}

istream& operator>>(istream& in, bazaDate& ob)
{
    cout<<"Cate spectacole de opera sunt? ";
    in>>ob.nro;
    ob.listaO= new Opera[ob.nro];
    for(int i=0; i<ob.nro; i++)
        in>>ob.listaO[i];

    cout<<"Cate spectacole de teatru sunt? ";
    in>>ob.nrt;
    ob.listaT= new Teatru[ob.nrt];
    for(int i=0; i<ob.nrt; i++)
        in>>ob.listaT[i];

    cout<<"Cate spectacole de circ sunt? ";
    in>>ob.nrc;
    ob.listaC= new Circ[ob.nrc];
    for(int i=0; i<ob.nrc; i++)
        in>>ob.listaC[i];
    return in;
}
ostream& operator<<(ostream& out, bazaDate& ob)
{
    out<<"Spectacolele de teatru sunt: "<<endl;
    for(int i=0; i<ob.nrt; i++)
        out<<"Spectacolul "<<i+1<<" de teatru: "<<endl<<ob.listaT[i]<<endl;

    out<<"Spectacolele de opera sunt: "<<endl;
    for(int i=0; i<ob.nro; i++)
        out<<"Spectacolul "<<i+1<<" de opera: "<<endl<<ob.listaO[i]<<endl;

    out<<"Spectacolele de circ sunt: "<<endl;
    for(int i=0; i<ob.nrc; i++)
        out<<"Spectacolul "<<i+1<<" de circ: "<<endl<<ob.listaC[i]<<endl;

    return out;
}


bazaDate::~bazaDate()
{
    delete []listaC;
    delete []listaT;
    delete []listaO;
}

Spectacol :: Spectacol()
{
    denumire="";
    prezpeLuna=10; // in mod implicit
    lista=new Prezentare[prezpeLuna];
}

Spectacol :: Spectacol(string num, string g)
{
    denumire=num;
    prezpeLuna=10;
    lista=new Prezentare[prezpeLuna];
    gen=g;
}

Spectacol :: Spectacol(const Spectacol& ob)
{
    if(denumire!="")
        denumire=ob.denumire;
    else
        denumire="";
    durata=ob.durata;
    prezpeLuna=ob.prezpeLuna;
    lista=new Prezentare[prezpeLuna];
}

Spectacol ::~Spectacol()
{
    delete[] lista;
}


Spectacol& Spectacol :: operator=(const Spectacol& ob)
{
    if(this!= &ob)
    {
        denumire=ob.denumire;
        gen=ob.gen;
        durata=ob.durata;
        prezpeLuna=ob.prezpeLuna;
    }

    for(int i=0; i<ob.prezpeLuna; i++)
    {
        lista[i].dataPrez=ob.lista[i].dataPrez;
        lista[i].numarLocuri=ob.lista[i].numarLocuri;
    }

    return *this;
}
void Spectacol :: citire()
{
    cout<<"Cum se numeste spectacolul? ";
    cin>>denumire;
    cout<<"Care este genul spectacolului? ";
    cin>>gen;
    cout<<"Cat dureaza? ";
    cin>>durata;
    cout<<"Cate prezentari sunt pe luna? ";
    cin>>prezpeLuna;
    lista=new Prezentare[prezpeLuna];

    for(int i=0; i<prezpeLuna; i++)
        cin>>lista[i];
}

istream& operator>>(istream& in, Spectacol& ob)
{
    //supraincarcarea operatorului de citire
    cout<<"Cum se numeste spectacolul? ";
    in>>ob.denumire;
    cout<<"Cat dureaza? ";
    in>>ob.durata;
    cout<<"Cate prezentari sunt pe luna? ";
    in>>ob.prezpeLuna;
    ob.lista=new Prezentare[ob.prezpeLuna];
    cout<<"Care este genul spectacolului? ";
    in>>ob.gen;

    for(int i=0; i<ob.prezpeLuna; i++)
        in>>ob.lista[i];

    return in;
}

ostream& operator<< (ostream& out, Spectacol& ob)
{
    out<<"Spectacolul: "<<ob.denumire<<" | Gen: "<<ob.gen<<endl;
    out<<"Durata: "<<ob.durata<<endl;
    out<<"Detalii reprezentatii luna aceasta: "<<endl;
    for(int i=0; i<ob.prezpeLuna; i++)
    {
        out<<"Reprezentatia "<<i+1<<": "<<ob.lista[i]<<endl;
    }
    return out;
}

void Spectacol::afisareFiltru(int maxim)
{
    cout<<"Spectacolul: "<<denumire<<" | Gen: "<<gen<<endl;
    cout<<"Durata: "<<durata<<endl;
    cout<<"Detalii reprezentatii luna aceasta: "<<endl;
    for(int i=0; i<prezpeLuna; i++)
    {
        if(lista[i].returnNrLoc() <= maxim)
            cout<<"Reprezentatia "<<i+1<<": "<<lista[i]<<endl;
    }
}

void Spectacol :: afisare()
{
    cout<<"Spectacolul: "<<denumire<<" | Gen: "<<gen<<endl;
    cout<<"Durata: "<<durata<<endl;
    cout<<"Detalii reprezentatii luna aceasta: "<<endl;
    for(int i=0; i<prezpeLuna; i++)
    {
        cout<<"Reprezentatia "<<i+1<<": "<<lista[i]<<endl;
    }
}

Prezentare :: Prezentare()
{
    numarLocuri=0;
    dataPrez=0;
}

Prezentare :: Prezentare(int a, int b)
{
    dataPrez=a;
    numarLocuri=b;
}

Prezentare :: Prezentare(const Prezentare& ob)
{
    dataPrez=ob.dataPrez;
    numarLocuri=ob.numarLocuri;
    if (ob.durVarTeatru) //in cazul in care conteaza nr de copii si nr de adulti
    {
        durVarTeatru=ob.durVarTeatru;
        nrCopii=ob.nrCopii;
        nrAdulti=ob.nrAdulti;
    }
}

Prezentare ::~Prezentare()
{
    //destructor;
}

void Prezentare :: citirePtTeatru()
{
    cout<<"Dati data reprezentatiei si nr de locuri pt acea reprezentatie: ";
    cin>>dataPrez>>numarLocuri;
    cout<<"Cati adulti vor fi(care au cumparat deja bilet)? ";
    cin>>nrAdulti;
    if (nrAdulti > numarLocuri)
    {
        throw "Numarul adultilor nu poate fi mai mare decat numarul de locuri";
    }
    cout<<"Cati copii sub 16 ani vor fi(care au cumparat deja bilet)? ";
    cin>>nrCopii;
    if (nrCopii > numarLocuri - nrAdulti)
    {
        throw "Numarul spectatorilor(adulti + copii) nu poate fi mai mare decat numarul de locuri";
    }

    durVarTeatru=nrAdulti+2*nrCopii; //durata variabila pt aceasta reprezentatie
}

void Prezentare :: modifyDurTeatru(int a)
{
    durVarTeatru=durVarTeatru+a;
}

void Prezentare :: afisarePtTeatru()
{
    cout<<"Data: "<<dataPrez<<" | Nr. de locuri: "<<numarLocuri<<" | Durata totala reprezentatie: "<<durVarTeatru;
}

istream& operator>>(istream& in, Prezentare& ob)
{
    cout<<"Dati data reprezentatiei si nr de locuri pt acea reprezentatie: ";
    in>>ob.dataPrez>>ob.numarLocuri;
    return in;
}
ostream& operator<< (ostream& out, Prezentare& ob)
{
    out<<"Data: "<<ob.dataPrez<<" | Nr. de locuri: "<<ob.numarLocuri;
    return out;
}
Prezentare& Prezentare :: operator=(const Prezentare& ob)
{
    if(this!=&ob)
    {
        numarLocuri=ob.numarLocuri;
        dataPrez=ob.dataPrez;
    }
    return *this;
}

Opera :: Opera()
{
    durataPauza=10; //10 minute implicit
    nrActe=2; //cel putin 2 acte
    acte= new Act[nrActe];
    pentruAdulti=false;
}

Opera :: Opera(string a, string b, int x, int nr, bool adult) : Spectacol(a,b)
{
    durataPauza=x;
    pentruAdulti=adult;
    nrActe=nr;
    acte=new Act[nrActe];
}

Opera :: Opera(const Opera& ob)
{
    denumire=ob.denumire;
    gen=ob.gen;
    durata=ob.durata;
    prezpeLuna=ob.prezpeLuna;
    for(int i=0; i<prezpeLuna; i++)
        lista[i]=ob.lista[i];
    nrActe=ob.nrActe;
    acte=new Act[ob.nrActe];

    for(int i=0; i<nrActe; i++)
        ob.acte[i]=ob.acte[i];
    durataPauza=ob.durataPauza;
    pentruAdulti=ob.pentruAdulti;

}

Opera :: ~Opera()
{
    delete[] acte;

}

void Opera :: citire()
{
    cout<<"Dati denumirea piesei de opera ";
    cin>>denumire;
    cout<<"Dati genul piesei ";
    cin>>gen;
    cout<<"Cat dureaza pauzele dintre acte? ";
    cin>>durataPauza;
    cout<<"Este doar pentru adulti?(d/n) ";
    char aux;
    cin>>aux;
    if(aux=='d')
        pentruAdulti=true;

    if(aux=='n')
        pentruAdulti=false;
    cout<<"Cate acte are? ";
    cin>>nrActe;
    if(nrActe<2 || nrActe>7)
        throw "Un spectacol de opera trebuie neaparat sa aiba intre 2 si 7 acte!";

    acte=new Act[nrActe];

    for(int i=0; i<nrActe; i++)
    {
        cin>>acte[i];
    }
    durata=calcDurata();
    cout<<"Cate reprezentatii pe luna sunt? ";
    cin>>prezpeLuna;
    lista=new Prezentare[prezpeLuna];
    for(int i=0; i<prezpeLuna; i++)
        cin>>lista[i];
}
istream& operator>>(istream& in, Opera& op)
{
    // cout<<endl;
    cout<<"Dati denumirea piesei de opera ";
    in>>op.denumire;
    cout<<"Dati genul piesei ";
    in>>op.gen;
    cout<<"Cat dureaza pauzele dintre acte? ";
    in>>op.durataPauza;
    cout<<"Este doar pentru adulti?(d/n) ";
    char aux;
    in>>aux;
    if(aux=='d')
        op.pentruAdulti=true;

    if(aux=='n')
        op.pentruAdulti=false;
    cout<<"Cate acte are? ";
    in>>op.nrActe;
    op.acte=new Act[op.nrActe];

    for(int i=0; i<op.nrActe; i++)
    {
        in>>op.acte[i];
    }
    op.durata=op.calcDurata();
    cout<<"Cate reprezentatii pe luna sunt? ";
    in>>op.prezpeLuna;
    op.lista=new Prezentare[op.prezpeLuna];
    for(int i=0; i<op.prezpeLuna; i++)
        in>>op.lista[i];
    return in;
}

ostream& operator<<(ostream& out, Opera& op)
{
    out<<endl;
    out<<"Numele operei: "<<op.denumire<<" | Gen: "<<op.gen<<" | Durata totala: "<<op.durata<<endl;
    for(int i=0; i<op.nrActe; i++)
    {
        out<<"Act "<<i+1<<": "<<op.acte[i];
    }
    if(op.pentruAdulti)
        out<<"Doar pentru adulti"<<endl;
    else
        out<<"Audienta generala"<<endl;
    out<<"Durata pauza: "<<op.durataPauza<<endl;
    out<<"Lista de prezentari pe luna pentru aceasta piesa: "<<endl;
    for(int i=0; i<op.prezpeLuna; i++)
        out<<op.lista[i]<<endl;

    return out;
}

void Opera::afisare()
{
    cout<<endl;
    cout<<"Numele operei: "<<denumire<<" | Gen: "<<gen<<" | Durata totala: "<<durata<<endl;
    for(int i=0; i<nrActe; i++)
    {
        cout<<"Act "<<i+1<<": "<<acte[i];
    }
    if(pentruAdulti)
        cout<<"Doar pentru adulti"<<endl;
    else
        cout<<"Audienta generala"<<endl;
    cout<<"Durata pauza: "<<durataPauza<<endl;
    cout<<"Lista de prezentari pe luna pentru aceasta piesa: "<<endl;
    for(int i=0; i<prezpeLuna; i++)
        cout<<lista[i]<<endl;
}

bool Opera ::criteriu(string a)
{
    bool ok=false;
    for(int i=0; i<nrActe; i++)
    {
        if(acte[i].tipSolist==a)
        {
            ok=true;
            break;
        }
    }
    if(a=="null")
        ok=true;
    return ok;
}

void Opera::afisareFiltru(int maxim)
{
    for(int i=0; i<nrActe; i++)
    {
        cout<<"Act "<<i+1<<": "<<acte[i];
    }
    if(pentruAdulti)
        cout<<"Doar pentru adulti"<<endl;
    else
        cout<<"Audienta generala"<<endl;
    cout<<"Durata pauza: "<<durataPauza<<endl;
    cout<<"Lista de prezentari pe luna pentru aceasta piesa: "<<endl;
    for(int i=0; i<prezpeLuna; i++)
    {
        if(lista[i].returnNrLoc()<= maxim)
            cout<<lista[i]<<endl;
    }
}

int Opera::calcDurata()
{
    int durataTotala=0;
    for(int i=0; i<nrActe; i++)
    {
        durataTotala+=acte[i].durata;
    }
    durataTotala+=durataPauza*(nrActe-1);
    return durataTotala;
}

Act :: Act()
{
    numeSolist="";
    tipSolist="";
    durata=30; //durata minima pt un act
}

Act :: Act(string n, string t, int dur)
{
    numeSolist=n;
    tipSolist=t;
    durata=dur;
}

Act :: Act(const Act& ob)
{
    numeSolist=ob.numeSolist;
    tipSolist=ob.tipSolist;
    durata=ob.durata;
}

Act :: ~Act()
{
//destructor
}

istream& operator>>(istream& in, Act& ob)
{
    cout<<"Ce tip de solist canta in acest act? ";
    in>>ob.tipSolist;
    cout<<"Care este numele solistului? ";
    in>>ob.numeSolist;
    cout<<"Cat dureaza acest act? ";
    in>>ob.durata;

    return in;
}

ostream& operator<<(ostream& out, Act& ob)
{
    out<<"Tip solist: "<<ob.tipSolist<<" | Nume solist: "<<ob.numeSolist<<" | Durata : "<<ob.durata<<endl;
    return out;
}

Act& Act :: operator=(const Act& ob)
{
    if(this!= &ob)
    {
        numeSolist=ob.numeSolist;
        tipSolist=ob.tipSolist;
        durata=ob.durata;
    }

    return *this;
}

Opera& Opera :: operator=(const Opera& ob)
{
    if(this!= &ob)
    {
        denumire=ob.denumire;
        durata=ob.durata;
        gen=ob.gen;
        prezpeLuna=ob.prezpeLuna;
        lista=new Prezentare[prezpeLuna];
        for(int i=0; i<prezpeLuna; i++)
            lista[i]=ob.lista[i];

        nrActe=ob.nrActe;
        acte= new Act[ob.nrActe];
        for(int i=0; i<nrActe; i++)
            acte[i]=ob.acte[i];
    }
    durataPauza=ob.durataPauza;
    pentruAdulti=ob.pentruAdulti;

    return *this;
}

Circ :: Circ()
{
    gen="comedie";
    pentruAdulti=false; //default
    numarPrestatii=2; //minim 2 prestatii
    p=new Prestatie[numarPrestatii];
}

Circ :: Circ(string a, string b, int nr) : Spectacol(a,b)
{
    numarPrestatii=nr;
    p=new Prestatie[numarPrestatii];
}
Circ :: Circ(const Circ& ob)
{
    numarPrestatii=ob.numarPrestatii;
    if(numarPrestatii)
    {
        p=new Prestatie[numarPrestatii];
        for(int i=0; i<numarPrestatii; i++)
            p[i]=ob.p[i];
    }
    denumire=ob.denumire;
    gen=ob.gen;

    durata=ob.durata;
    prezpeLuna=ob.prezpeLuna;
    lista=new Prezentare[prezpeLuna];

    for(int i=0; i<prezpeLuna; i++)
        lista[i]=ob.lista[i];
}

Circ::~Circ()
{
    delete []p;
}

Circ& Circ :: operator=(const Circ& ob)
{
    if(this!=&ob)
    {
        numarPrestatii=ob.numarPrestatii;
        if(numarPrestatii)
        {
            p=new Prestatie[numarPrestatii];
            for(int i=0; i<numarPrestatii; i++)
                p[i]=ob.p[i];
        }
        denumire=ob.denumire;
        gen=ob.gen;

        durata=ob.durata;
        prezpeLuna=ob.prezpeLuna;
        lista=new Prezentare[prezpeLuna];

        for(int i=0; i<prezpeLuna; i++)
            lista[i]=ob.lista[i];
    }
    return *this;
}
bool Circ ::criteriu(string a)
{
    bool ok=false;
    for(int i=0; i<numarPrestatii; i++)
    {
        bool aux=p[i].verificaAnimal(a);
        if(aux== true)
        {
            ok=true;
            break;
        }
    }
    if(a=="null")
        ok=true;
    return ok;
}

bool Circ::criteriuEx(bool faraSalb)
{
    bool rez=true;
    bool ok=false;
    for(int i=0; i<numarPrestatii; i++)
        if(p[i].areSalbatic()== true)
        {
            ok=true;
        }
    if(ok== true && faraSalb==true)
        rez=false;
    return rez;
}

void Circ :: citire()
{
    cout<<"Dati denumirea spectacolului de circ: ";
    cin>>denumire;
    cout<<"Cate prezentari pe luna? ";
    cin>>prezpeLuna;
    for(int i=0; i<prezpeLuna; i++)
        cin>>lista[i];

    cout<<"Cate prestatii? ";
    cin>>numarPrestatii;
    if(numarPrestatii<2)
        throw "Un spectacol de circ trebuie sa aiba cel putin 2 prestatii";

    p=new Prestatie[numarPrestatii];

    for(int i=0; i<numarPrestatii; i++)
    {
        cin>>p[i];
    }
    pentruAdulti=returnAudienta();
    durata=calcDurata();
}

void Circ ::afisare()
{
    cout<<"Numele spectacolului de Circ: "<<denumire<<" | Gen: "<<gen<<" | Durata totala: "<<durata<<endl;
    for(int i=0; i<prezpeLuna; i++)
        cout<<lista[i]<<endl;

    cout<<numarPrestatii<<" prestatii, fara pauza intre ele"<<endl;
    for(int i=0; i<numarPrestatii; i++)
    {
        cout<<"Prestatia "<<i+1<<": "<<p[i]<<endl;
    }
    cout<<endl;
    if(pentruAdulti== true)
        cout<<"Acest spectacol este doar pentru adulti"<<endl;
    else
        cout<<"Audienta genarala pentru acest spectacol"<<endl;
}

istream& operator>>(istream& in, Circ& ob)
{
    cout<<"Dati denumirea spectacolului de circ: ";
    in>>ob.denumire;
    cout<<"Cate prezentari pe luna? ";
    in>>ob.prezpeLuna;
    for(int i=0; i<ob.prezpeLuna; i++)
        in>>ob.lista[i];

    cout<<"Cate prestatii? ";
    in>>ob.numarPrestatii;
    ob.p=new Prestatie[ob.numarPrestatii];

    for(int i=0; i<ob.numarPrestatii; i++)
    {
        in>>ob.p[i];
    }
    ob.pentruAdulti=ob.returnAudienta();
    ob.durata=ob.calcDurata();

    return in;
}

ostream& operator<<(ostream& out, Circ& ob)
{
    out<<"Numele spectacolului de Circ: "<<ob.denumire<<" | Gen: "<<ob.gen<<" | Durata totala: "<<ob.durata<<endl;
    for(int i=0; i<ob.prezpeLuna; i++)
        out<<ob.lista[i]<<endl;

    out<<ob.numarPrestatii<<" prestatii, fara pauza intre ele"<<endl;
    for(int i=0; i<ob.numarPrestatii; i++)
    {
        out<<"Prestatia "<<i+1<<": "<<ob.p[i]<<endl;
    }
    out<<endl;
    if(ob.pentruAdulti== true)
        out<<"Acest spectacol este doar pentru adulti"<<endl;
    else
        out<<"Audienta genarala pentru acest spectacol"<<endl;
    return out;
}

void Circ ::afisareFiltru(int maxim)
{
    cout<<"Numele spectacolului de Circ: "<<denumire<<" | Gen: "<<gen<<" | Durata totala: "<<durata<<endl;
    for(int i=0; i<prezpeLuna; i++)
        if(lista[i].returnNrLoc() <= 15)
            cout<<lista[i]<<endl;

    cout<<numarPrestatii<<" prestatii, fara pauza intre ele"<<endl;
    for(int i=0; i<numarPrestatii; i++)
    {
        cout<<"Prestatia "<<i+1<<": "<<p[i]<<endl;
    }
    cout<<endl;
    if(pentruAdulti== true)
        cout<<"Acest spectacol este doar pentru adulti"<<endl;
    else
        cout<<"Audienta genarala pentru acest spectacol"<<endl;
}

Prestatie :: Prestatie()
{
    pentruAdulti=false;
    areAnimale=false;
    nrAnimale=0;
    durataPres=20; //cel putin 20 min trebuie sa fie
}

Prestatie :: Prestatie(int dur,bool a, bool b)
{
    durataPres=dur;
    pentruAdulti=a;
    areAnimale=b;
    if(areAnimale == false)
        nrAnimale=0;
    else
    {
        nrAnimale=1;
        lista =new Animal[nrAnimale];
    }
}

Prestatie :: Prestatie(const Prestatie& ob)
{
    durataPres=ob.durataPres;
    pentruAdulti=ob.pentruAdulti;
    areAnimale=ob.areAnimale;
    nrAnimale=ob.nrAnimale;
    if(areAnimale==true)
        lista= new Animal[nrAnimale];
}

Prestatie :: ~Prestatie()
{
    delete []lista;
}

Prestatie& Prestatie :: operator=(const Prestatie& ob)
{
    if(this!=&ob)
    {
        durataPres=ob.durataPres;
        pentruAdulti=ob.pentruAdulti;
        areAnimale=ob.areAnimale;
        nrAnimale=ob.nrAnimale;
        if(areAnimale==true)
            lista= new Animal[nrAnimale];
    }
    return *this;
}

bool Prestatie::verificaAnimal(string a)
{
    bool ok= false;
    for(int i=0; i<nrAnimale; i++)
        if(lista[i].denumire==a)
        {
            ok=true;
            break;
        }
    if(a=="null")
        ok=true;
    return ok;
}

bool Prestatie ::areSalbatic()
{
    bool ok=false;
    for(int i=0; i<nrAnimale; i++)
        if(lista[i].tip=="salbatic")
        {
            ok=true;
            break;
        }
    return ok;
}

istream& operator>>(istream& in, Prestatie& ob)
{
    cout<<"Este doar pentru adulti prestatia? ";
    char aux2;
    cin>>aux2;
    if(aux2=='d')
        ob.pentruAdulti=true;
    else
        ob.pentruAdulti=false;

    cout<<"Are animale aceasta prestatie?(d/n) ";
    char aux;
    in>>aux;
    if(aux=='d')
        ob.areAnimale=true;
    if(aux=='n')
        ob.areAnimale=false;
    if(ob.areAnimale == true)
    {
        cout<<"Cate tipuri de animale sunt in aceasta prestatie? ";
        in>>ob.nrAnimale;
        ob.lista=new Animal[ob.nrAnimale];

        for(int i=0; i<ob.nrAnimale; i++)
            in>>ob.lista[i];
    }
    if(ob.areAnimale== false)
    {
        ob.nrAnimale=0;
    }
    cout<<"Cat dureaza? ";
    in>>ob.durataPres;

    return in;
}

ostream& operator<<(ostream& out, Prestatie& ob)
{
    if(ob.pentruAdulti == true)
    {
        out<<"Doar pentru adulti!"<<endl;
    }
    else
        out<<"Audienta generala"<<endl;
    if(ob.areAnimale== true)
    {
        out<<"In aceasta prestatie apar urmatoarele animale:"<<endl;
        for(int i=0; i<ob.nrAnimale; i++)
            out<<ob.lista[i]<<endl;
    }
    else
        out<<"Aceasta prestatie este fara animale."<<endl;
    out<<"Durata: "<<ob.durataPres<<endl;

    return out;
}

Animal :: Animal()
{
    tip="";
    denumire="";
    numar=0;
}
Animal :: Animal(string a, string b, int c)
{
    tip=a;
    denumire=b;
    numar=c;
}

Animal :: Animal(const Animal& ob)
{
    tip=ob.tip;
    denumire=ob.denumire;
    numar=ob.numar;
}

Animal :: ~Animal()
{
    //destructor
}

Animal& Animal :: operator=(const Animal& ob)
{
    if(this!= &ob)
    {
        tip=ob.tip;
        denumire=ob.denumire;
        numar=ob.numar;
    }
    return *this;
}

istream& operator>>(istream& in, Animal& ob)
{
    cout<<"Este domestic sau salbatic?(d/s) ";
    char a;
    in>>a;
    if(a=='d')
        ob.tip="domestic";
    else
        ob.tip="salbatic";
    cout<<"Cate astfel de animale? ";
    in>>ob.numar;
    cout<<"Ce animal? ";
    in>>ob.denumire;
    return in;
}

ostream& operator<<(ostream& out, Animal& ob)
{
    out<<ob.numar<<": "<<ob.tip<<" | "<<ob.denumire;

    return out;
}

int Circ :: calcDurata()
{
    int durataTot=0;
    for(int i=0; i<numarPrestatii; i++)
        durataTot+=p[i].durataPres;

    return durataTot;
}

bool Circ :: returnAudienta()
{
    for(int i=0; i<numarPrestatii; i++)
    {
        if(p[i].pentruAdulti==true)
            return true;
        else
            return false;
    }
}

Teatru :: Teatru()
{
    interactiv=false;
    durata=30;
}

Teatru :: Teatru(string a, string b, bool c) : Spectacol(a,b)
{
    interactiv=c;
}

Teatru :: Teatru(const Teatru& ob)
{
    denumire=ob.denumire;
    gen=ob.gen;
    prezpeLuna=ob.prezpeLuna;
    lista=new Prezentare[prezpeLuna];
    for(int i=0; i<prezpeLuna; i++)
        lista[i]=ob.lista[i];

    interactiv=ob.interactiv;
}

Teatru::~Teatru()
{
    delete []lista;
}

Teatru& Teatru:: operator=(const Teatru& ob)
{
    if(this!=&ob)
    {
        denumire=ob.denumire;
        gen=ob.gen;
        prezpeLuna=ob.prezpeLuna;
        lista=new Prezentare[prezpeLuna];
        for(int i=0; i<prezpeLuna; i++)
            lista[i]=ob.lista[i];

        interactiv=ob.interactiv;
    }
    return *this;
}

void Teatru :: citire()
{
    cout<<"Dati denumirea spectacolului de teatru: ";
    cin>>denumire;
    cout<<"Dati genul piesei de teatru: ";
    cin>>gen;
    cout<<"Cat dureaza piesa? ";
    cin>>durata;
    if(durata<0)
        throw "Durata spectacolului de teatru nu poate fi negativa.";
    cout<<"Este interactiva piesa?(d/n) ";
    char a;
    cin>>a;
    if(a=='d')
        interactiv=true;
    if(a=='n')
        interactiv=false;

    cout<<"Cate prezentari pe luna? ";
    cin>>prezpeLuna;
    if(interactiv== true)
    {
        for(int i=0; i<prezpeLuna; i++)
        {
            try
            {
                lista[i].citirePtTeatru();
            }
            catch(const char *mesaj)
            {
                cout<<mesaj<<endl;
                cout<<"Incercati din nou";
                i--;
            }
            lista[i].modifyDurTeatru(durata);
        }
    }
    else
    {
        for(int i=0; i<prezpeLuna; i++)
            cin>>lista[i];
    }

}

istream& operator>>(istream& in, Teatru& ob)
{
    cout<<"Dati denumirea spectacolului de teatru: ";
    in>>ob.denumire;
    cout<<"Dati genul piesei de teatru: ";
    in>>ob.gen;
    cout<<"Cat dureaza piesa? ";
    in>>ob.durata;
    cout<<"Este interactiva piesa?(d/n) ";
    char a;
    in>>a;
    if(a=='d')
        ob.interactiv=true;
    if(a=='n')
        ob.interactiv=false;

    cout<<"Cate prezentari pe luna? ";
    in>>ob.prezpeLuna;
    if(ob.interactiv== true)
    {
        for(int i=0; i<ob.prezpeLuna; i++)
        {
            try
            {
                ob.lista[i].citirePtTeatru();
            }
            catch(const char *mesaj)
            {
                cout<<mesaj<<endl;
                cout<<"Va rugam, introduceti datele din nou";
                i--;
            }

            ob.lista[i].modifyDurTeatru(ob.durata);
        }
    }
    else
    {
        for(int i=0; i<ob.prezpeLuna; i++)
            in>>ob.lista[i];
    }

    return in;
}
ostream& operator<<(ostream& out, Teatru& ob)
{
    out<<"Numele piesei de teatru: "<<ob.denumire<<" | Gen: "<<ob.gen;
    if(ob.interactiv==false)
    {
        out<<" | Durata totala: "<<ob.durata<<endl;
        for(int i=0; i<ob.prezpeLuna; i++)
            out<<ob.lista[i]<<endl;
    }
    else
    {
        out<<endl;
        for(int i=0; i<ob.prezpeLuna; i++)
        {
            ob.lista[i].afisarePtTeatru();
            out<<endl;
        }
    }

    return out;
}

void Teatru::afisareFiltru(int maxim)
{
    cout<<"Numele piesei de teatru: "<<denumire<<" | Gen: "<<gen;
    if(interactiv==false)
    {
        cout<<" | Durata totala: "<<durata<<endl;
        for(int i=0; i<prezpeLuna; i++)
            cout<<lista[i]<<endl;
    }
    else
    {
        cout<<endl;
        for(int i=0; i<prezpeLuna; i++)
        {
            if(lista[i].returnNrLoc() <= maxim)
            {
                lista[i].afisarePtTeatru();
                cout<<endl;
            }
        }
    }
}

void Teatru::afisare()
{
    cout<<"Numele piesei de teatru: "<<denumire<<" | Gen: "<<gen;
    if(interactiv==false)
    {
        cout<<" | Durata totala: "<<durata<<endl;
        for(int i=0; i<prezpeLuna; i++)
            cout<<lista[i]<<endl;
    }
    else
    {
        cout<<endl;
        for(int i=0; i<prezpeLuna; i++)
        {
            lista[i].afisarePtTeatru();
            cout<<endl;
        }
    }
}

class Client;

class Dorinta
{
    string gen;
    string tip;
    int timp;
    string genAnimale;
    bool interactiv;
    string tipVoce;
public:
    Dorinta();
    Dorinta(string,string, string, string,int);
    Dorinta(const Dorinta&);
    ~Dorinta();
    Dorinta& operator=(const Dorinta&);
    friend istream& operator>>(istream&, Dorinta&);
    friend ostream& operator<<(ostream&, Dorinta&);
    friend class Client;
    friend bool respecta(Spectacol, Dorinta);
    string returnVoce()
    {
        return tipVoce;
    };
    string returnAnimale()
    {
        return genAnimale;
    };
    bool returnInteractiv()
    {
        return interactiv;
    };
};

class Exigenta
{
    int varsta;
    int maxTimp;
    bool faraAnSalb;
    int maxLocuri;
    bool ptAdulti;
    string combtip;
    string combgen;

public:
    Exigenta();
    Exigenta(string,string,int,int,bool,bool);
    Exigenta(const Exigenta& );
    ~Exigenta();
    friend istream& operator>>(istream&, Exigenta&);
    friend ostream& operator<<(ostream&, Exigenta&);
    Exigenta& operator=(const Exigenta&);
    friend class Client;
    friend bool respectaEx(Spectacol, Exigenta);
    bool returnFaraAn()
    {
        return faraAnSalb;
    };
    int returnMaxLoc()
    {
        return maxLocuri;
    };
    bool returnAdult()
    {
        return ptAdulti;
    };
};

class Client
{
    int varsta;
    Dorinta d;
    Exigenta e;
public:
    Client();
    Client(int);
    Client(const Client&);
    ~Client();
    friend istream& operator>>(istream&, Client&);
    friend ostream& operator<<(ostream&, Client&);
    Client& operator=(const Client&);
    void modifyAudienta(int);

};

Exigenta :: Exigenta()
{
    maxTimp=-1;
    maxLocuri=-1;
    faraAnSalb=false;
    ptAdulti=-1;
    combgen="null";
    combtip="null";
}
Exigenta :: Exigenta(string a, string b, int c,int d, bool e, bool f)
{
    combtip=a;
    combgen=b;
    maxTimp=c;
    maxLocuri=d;
    faraAnSalb=e;
    ptAdulti=f;
}

Exigenta :: Exigenta(const Exigenta& ob)
{
    combtip=ob.combtip;
    combgen=ob.combgen;
    maxTimp=ob.maxTimp;
    maxLocuri=ob.maxLocuri;
    faraAnSalb=ob.faraAnSalb;
    ptAdulti=ob.ptAdulti;
}
Exigenta& Exigenta :: operator=(const Exigenta& ob)
{
    if(this != &ob)
    {
        combtip=ob.combtip;
        combgen=ob.combgen;
        maxTimp=ob.maxTimp;
        maxLocuri=ob.maxLocuri;
        faraAnSalb=ob.faraAnSalb;
        ptAdulti=ob.ptAdulti;
    }
    return *this;
}
Exigenta :: ~Exigenta()
{

}
istream& operator>>(istream& in, Exigenta& ob)
{
    char a;
    cout<<"Conteaza timpul pentru dumneavoasatra?(d/n) ";
    in>>a;
    if(a=='d')
    {
        cout<<"Care este timpul maxim pt un spectacol? ";
        in>>ob.maxTimp;
    }
    if(a=='n')
    {
        ob.maxTimp=-1;
    }
    cout<<"Conteaza cate locuri sunt alocate pentru spectacol?(d/n) ";
    in>>a;
    if(a=='d')
    {
        cout<<"Care este numarul maxim de locuri pe care vi-l doriti? ";
        in>>ob.maxLocuri;
    }
    if(a=='n')
    {
        ob.maxLocuri=-1;
    }
    cout<<"Daca ati merge la un circ, vreti sa fie animale salbatice periculoase sau nu?(d/n) ";
    in>>a;
    if(a== 'd')
        ob.faraAnSalb=false;
    if(a== 'n')
        ob.faraAnSalb=true;

    cout<<"Cati ani aveti? ";
    int v;
    in>>v;
    if(v>=18)
        ob.ptAdulti=true;
    if(v<=18)
        ob.ptAdulti=false;


    cout<<"Exista vreo combinatie de tip spectacol si gen care nu va convine?(d/n) ";
    in>>a;
    if(a== 'n')
    {
        ob.combtip="null";
        ob.combgen="null";
    }
    if(a== 'd')
    {
        cout<<"Dati tipul spectacolului(opera->o /teatru -> t/circ ->c) ";
        char aux;
        in>>aux;
         while(aux !='o' && aux!='t' && aux != 'c')
        {
            cout<<"Va rugam introduceti o optiune valida"<<endl;
            in>>aux;
        }
        switch (aux)
        {
        case 'o' :
        {
            ob.combtip="opera";
            break;
        }
        case 't' :
        {
            ob.combtip="teatru";
            break;
        }
        case 'c' :
        {
            ob.combtip="circ";
            break;
        }
        default:
            cout<<"Introduceti o optiune valida ";
        }

        cout<<"Dati genul spectacolului(comedie->c /drama -> d/actiune ->a) ";
        char aux2;
        in>>aux2;
        while(aux2 !='d' && aux2!='a' && aux2 != 'c')
        {
            cout<<"Va rugam introduceti o optiune valida"<<endl;
            in>>aux2;
        }
        switch (aux2)
        {
        case 'c' :
        {
            ob.combgen="comedie";
            break;
        }
        case 'd' :
        {
            ob.combgen="drama";
            break;
        }
        case 'a' :
        {
            ob.combgen="actiune";
            break;
        }
        default:
            cout<<"Introduceti o optiune valida ";

        }
    }

    return in;
}

Dorinta :: Dorinta ()
{
    gen="null";
    tip="null";
    timp=-1;
    genAnimale="null";
    interactiv=false;
    tipVoce="null";
}

Dorinta :: Dorinta(string a, string b, string c, string d, int e)
{
    gen=a;
    tip=b;
    genAnimale=c;
    tipVoce=d;
    timp=e;
    interactiv=false;
}

Dorinta :: Dorinta(const Dorinta& ob)
{
    gen=ob.gen;
    tip=ob.tip;
    genAnimale=ob.genAnimale;
    interactiv=ob.interactiv;
    tipVoce=ob.tipVoce;
}

Dorinta& Dorinta :: operator=(const Dorinta& ob)
{
    if(this!=&ob)
    {
        gen=ob.gen;
        tip=ob.tip;
        genAnimale=ob.genAnimale;
        interactiv=ob.interactiv;
        tipVoce=ob.tipVoce;
    }
    return *this;
}

bool respecta(Spectacol s, Dorinta d)
{
    bool ok=true;
    if(d.gen!="null" && s.gen != d.gen)
        ok =false;
    if(d.timp!=-1 && s.durata < d.timp)
        ok=false;
    const char *aux;
    aux=d.tip.c_str();
    if(  d.tip!="null" && strstr(typeid(s).name(),aux) == NULL )
        ok=false;
    return ok;
}

bool respectaEx(Spectacol s, Exigenta e)
{
    bool ok= true;
    if(e.maxTimp!=-1 && e.maxTimp > s.durata)
        ok=false;

    const char *aux;
    char *aux2;
    strcpy(aux2,e.combtip.c_str());
    aux2[0] = toupper(aux2[0]);
    aux = (const char *)aux2;
    if(strstr(typeid(s).name(),aux2)!=NULL  && s.gen==e.combgen ) //combinatia nedorita se intampla
        ok=false;
    return ok;

}

Dorinta :: ~Dorinta()
{
    //destructor
}
istream& operator>>(istream& in, Dorinta& ob)
{
    char a;
    cout<<"Conteaza genul piesei?(d/n) ";
    in>>a;
    if(a=='d')
    {
        cout<<"Ce gen doriti(comedie->c / drama ->d/ actiune ->a)? ";
        char aux;
        in>>aux;
        while(aux !='a' && aux!='d' && aux != 'c')
        {
            cout<<"Va rugam introduceti o optiune valida"<<endl;
            in>>aux;
        }

        switch (aux)
        {
        case 'c' :
        {
            ob.gen="comedie";
            break;
        }
        case 'd' :
        {
            ob.gen="drama";
            break;
        }
        case 'a' :
        {
            ob.gen="actiune";
            break;
        }
       // default:

        }

    }
    if(a== 'n')
        ob.gen="null";

    cout<<"Conteaza tipul de spectacol?(d/n) ";
    in>>a;
    if(a== 'd')
    {
        cout<<"Dati tipul spectacolului(opera->o /teatru -> t/circ ->c) ";
        char aux;
        in>>aux;
         while(aux !='o' && aux!='c' && aux != 't')
        {
            cout<<"Va rugam introduceti o optiune valida"<<endl;
            in>>aux;
        }
        switch (aux)
        {
        case 'o' :
        {
            ob.tip="opera";
            break;
        }
        case 't' :
        {
            ob.tip="teatru";
            break;
        }
        case 'c' :
        {
            ob.tip="circ";
            break;
        }
        default:

        {
            cout<<"Introduceti o optiune valida ";
            break;
        }
        }
    }
    if(a=='n')
    {
        ob.tip="null";
    }
    cout<<"Conteaza durata(d/n)? ";
    in>>a;
    if(a=='d')
    {
        cout<<"Dati durata minima (fara pauze) ";
        in>>ob.timp;
    }
    if(a=='n')
    {
        ob.timp=-1;
    }
    cout<<"Conteaza animalele care apar la un circ?(d/n) ";
    in>>a;
    if(a=='n')
    {
        ob.genAnimale="null";
    }
    if(a=='d')
    {
        cout<<"Ce tip de animale doriti neaparat la circ? ";
        in>>ob.genAnimale;
    }
    cout<<"Daca ar fi o piesa de teatru, doriti sa fie interactiva?(d/n) ";
    in>>a;
    if(a=='d')
        ob.interactiv=true;
    if(a=='n')
        ob.interactiv=false;
    cout<<"Daca ar fi opera, doriti un anumit tip de voce? (d/n) ";
    in>>a;
    if(a=='d')
    {
        cout<<"Ce tip de voce doriti?(tenor ->1 / bariton->2 / bas->3 ) ";
        int aux;
        in>>aux;
        switch (aux)
        {
        case 1:
        {
            ob.tipVoce="tenor";
            break;
        }
        case 2 :
        {
            ob.tipVoce="bariton";
            break;
        }
        case 3 :
        {
            ob.tipVoce="bas";
            break;
        }
        default:
            cout<<"Introduceti o optiune valida ";
        }

    }
    if(a=='n')
        ob.tipVoce="null";

    return in;
}

ostream& operator<<(ostream& out, Dorinta& ob)
{
    if(ob.gen!="null")
        out<<"Gen: "<<ob.gen;
    if(ob.tip!="null")
        out<<" |Tip: "<<ob.tip;
    if(ob.timp!=-1)
        out<<" |Durata min: "<<ob.timp<<endl;
    if(ob.genAnimale!="null")
        out<<" Cu animale "<<ob.genAnimale<<endl;
    if(ob.interactiv==true)
        out<<" |Sa fie interacticv";
    if(ob.tipVoce!="null")
        out<<" |Tip voce: "<<ob.tipVoce;
    return out;
}

ostream& operator<<(ostream& out, Exigenta& ob)
{
    if(ob.ptAdulti==false)
        out<<"Nu poate fi pentru adulti ";
    if(ob.maxTimp!=-1)
        out<<" |Durata maxima: "<<ob.maxTimp;
    if(ob.faraAnSalb== true)
        out<<" |Fara animale salbatice ";
    else
        out<<" |Pot aparea animale salbatice ";
    if(ob.maxLocuri!=-1)
        out<<" |maxim de locuri: "<<ob.maxLocuri;
    if(ob.combgen!="null" && ob.combtip!="null")
        out<<endl<<"Nu se poate combinatia de "<<ob.combtip<<" si "<<ob.combgen;

    return out;
}

Client :: Client()
{
    varsta=18;
}
Client::Client(int a)
{
    varsta=a;
}
Client :: Client(const Client& ob)
{
    varsta=ob.varsta;
    d=ob.d;
    e=ob.e;
}

Client& Client :: operator=(const Client& ob)
{
    if(this != &ob)
    {
        varsta=ob.varsta;
        e=ob.e;
        d=ob.d;
    }
    return *this;
}

Client :: ~Client()
{
    //destructor
}

void Client ::modifyAudienta(int v)
{
    if( v < 18)
        e.ptAdulti=false;
    else
        e.ptAdulti=true;
}

istream& operator>>(istream& in, Client& ob)
{
    cout<<"Ce varsta aveti? ";
    in>>ob.varsta;
    if(ob.varsta< 18)
        ob.modifyAudienta(ob.varsta);
    in>>ob.d;
    in>>ob.e;
    return in;
}


int main()
{

    cout<<"Bine ati venit la Teatrul Modern FMI!"<<endl;
    cout<<"Introducere spectacol nou de teatru ->t"<<endl;
    cout<<"Introducere spectacol nou de circ ->c"<<endl;
    cout<<"Introducere spectacol nou de opera ->o"<<endl;
    cout<<"Afisarea tuturor spectacolelor disponibile ->a"<<endl;
    cout<<"Spuneti-ne preferintele/exigentele pentru a va sugera lista de spectacole pe placul dumneavoastra ->p"<<endl;
    cout<<"Iesire ->x"<<endl;
    Spectacol **lista;
    lista= new Spectacol *[50]; //50  este maximul de spectacole pe care il poate gestiona acest teatru

    Dorinta d;
    Exigenta e;

    int i=0;
    char comanda;
    cin>>comanda;
    while(comanda!='x' && comanda!= 'X')
    {
        switch(comanda)
        {
        case 't':
        {
            Teatru *t=new Teatru();
            // lista[i]=new Teatru();
            try
            {
                t->citire();
                lista[i]=t;
            }
            catch(const char * mesaj)
            {
                cout<<mesaj<<endl;
                cout<<" Va rugam sa alegeti din nou o optiune!"<<endl;
            }
            i++;
            break;
        }
        case 'c':
        {
            Circ *c=new Circ();
            try
            {
                c->citire();
                lista[i]=c;
            }
            catch(const char * mesaj)
            {
                cout<<mesaj;
                cout<<" Va rugam sa alegeti din nou o optiune!"<<endl;
            }
            i++;
            break;
        }
        case 'o':
        {
            Opera *o=new Opera();
            // lista[i]=new Opera();
            try
            {
                o->citire();
                lista[i]=o;
            }
            catch(const char * mesaj)
            {
                cout<<mesaj;
                cout<<" Va rugam sa alegeti din nou o optiune!"<<endl;
            }

            i++;
            break;
        }
        case 'a':
        {
            for(int j=0; j<i; j++)
            {
                lista[j]->afisare();
                cout<<endl;
            }
            break;
        }
        case 'd':
        {
            cin>>d;
            cout<<endl;
            cin>>e;
            cout<<"Dorintele: "<<endl<<d<<endl<<"Exigentele:"<<endl<<e;
            break;
        }

        case 'p':
        {
            cin>>d;
            cin>>e;
            int gasit=0;
            for(int j=0; j<i; j++)
            {
                bool ok1=false;
                bool ok2=false;
                ok1=respecta(*(lista[j]),d);
                if( strstr( typeid(*(lista[j])).name(),"Opera")!=NULL && lista[j]->criteriu(d.returnVoce()) ==true  )
                    ok2=true;

                Teatru* der=dynamic_cast<Teatru *>(lista[j]);
                if( strstr( typeid(*(lista[j])).name(),"Teatru")!=NULL && der->returnInter() ==true  )
                    ok2=true;
                if( strstr( typeid(*(lista[j])).name(),"Circ")!=NULL && lista[j]->criteriu(d.returnAnimale()) ==true  )
                    ok2=true;

                bool ok3=false;
                bool ok4=false;
                bool ok5=true;
                ok3=respectaEx(*(lista[j]),e);

                if(strstr( typeid(*(lista[j])).name(),"Circ")!=NULL && lista[j]->criteriuEx(e.returnFaraAn())== true)
                    ok4=true;
                if(e.returnAdult()==false && lista[j]->returnAdulti()==true)
                    ok5=false;

                cout<<"----------------"<<endl;
                cout<<ok1<<endl<<ok2<<endl<<ok3<<endl<<ok4<<endl<<ok5<<endl;
                cout<<"-----------------"<<endl;

                if(ok1== true && ok2==true && ok3==true && ok4==true && ok5==true && e.returnMaxLoc()==-1)
                {
                    lista[j]->afisare();
                    cout<<endl;
                    gasit=1;
                }
                if(ok1== true && ok2==true && ok3==true && ok4==true && ok5==true &&  e.returnMaxLoc()!=-1)
                {
                    lista[j]->afisareFiltru(e.returnMaxLoc());
                    cout<<endl;
                    gasit=1;
                }
            }

            if (gasit==0)
                cout<<"Nu exista reprezentatii care sa se potriveasca dorintelor dumneavoastra!"<<endl<<"Va multumim!"<<endl;

            break;
        }
        }
        cin>>comanda;
    }

    return 0;
}

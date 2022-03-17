#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;

class individ
{
private:
    int i;
    char tip;
    int varsta;
    double energie;
    unsigned char viu;

public:

    individ(const individ& obj)
    {
        i = obj.i;
        tip = obj.tip;
        varsta = obj.varsta;
        energie = obj.energie;
        viu = obj.viu;
    }

    individ(int i = 0, char tip = '0')
    {
        this->i = i;
        this->tip = tip;
        varsta = 0;
        energie = 5;
        viu = 1;
    }

    void operator=(const individ& obj)
    {
        i = obj.i;
        tip = obj.tip;
        varsta = obj.varsta;
        energie = obj.energie;
        viu = obj.viu;
    }

private:
    void hraneste()
    {
        srand(time(0));
        int x = (rand() % 10) + 1;
        energie += x;
    }

    void inmulteste(individ indivizi[], int n)
    {

        if (n > i && !indivizi[i + 1].esteViu())
        {
            indivizi[i + 1].varsta = 0;
            indivizi[i + 1].tip = indivizi[i].tip;
            indivizi[i + 1].energie = indivizi[i].energie * 2;
            indivizi[i + 1].viu = 1;
            cout << endl << "A fost creat individul " << i + 1 << " de tip " << indivizi[i].tip << " si cu energia " << indivizi[i + 1].energie<<endl;
        }
        if (i > 1 && !indivizi[i - 1].esteViu())
        {
            indivizi[i - 1].varsta = 0;
            indivizi[i - 1].tip = indivizi[i].tip;
            indivizi[i - 1].energie = indivizi[i].energie * 2;
            indivizi[i - 1].viu = 1;
            cout << endl << "A fost creat individul " << i - 1 << " de tip " << indivizi[i].tip << " si cu energia " << indivizi[i - 1].energie<<endl;
        }
    }

    void ataca(individ indivizi[], int n)
    {

        if (n > i && indivizi[i + 1].tip != this->tip)
        {
            if (indivizi[i + 1].energie < this->energie)
            {
                this->energie -= indivizi[i + 1].energie;
                indivizi[i + 1].moare();
                cout << endl << "Individul " << i + 1 << " a fost omorat." << endl;
            }
            else if (indivizi[i + 1].energie == this->energie)
            {
                indivizi[i + 1].moare();
                moare();
                cout << endl << "Individul " << i + 1 << " a fost omorat." << endl;
                cout << endl << "Individul " << i << " a fost omorat." << endl;

                return;
            }
            else
            {
                indivizi[i + 1].energie -= energie;
                moare();
                cout << endl << "Individul " << i  << " a fost omorat." << endl;

                return;
            }
        }
        if (i > 1 && indivizi[i - 1].tip != this->tip)
        {
            if (indivizi[i - 1].energie < this->energie)
            {
                this->energie -= indivizi[i - 1].energie;
                indivizi[i - 1].moare();
                cout << endl << "Individul " << i - 1 << " a fost omorat." << endl;
            }
            else if (indivizi[i - 1].energie == this->energie)
            {
                indivizi[i - 1].moare();
                moare();
                cout << endl << "Individul " << i - 1<< " a fost omorat." << endl;
                cout << endl << "Individul " << i << " a fost omorat." << endl;


                return;
            }
            else
            {
                indivizi[i - 1].energie -= this->energie;
                moare();
                cout << endl << "Individul " << i  << " a fost omorat." << endl;

                return;
            }
        }
    }
    void imbatraneste()
    {
        varsta += 1;
        if (varsta == 99)
            moare();
    }

    void moare()
    {
        viu = 0;
    }

public:

    void setI(int i)
    {
        this->i = i;
    }
    
    void setTip(char tip)
    {
        this->tip = tip;
    }

    void setEnergie(double energy)
    {
        energie = energy;
    }

    void setViu(unsigned char v)
    {
        viu = v;
    }

    void setVarsta(int age)
    {
        varsta = age;
    }

    void actualizare(individ indivizi[], int n)
    {
        hraneste();
        inmulteste(indivizi, n);
        ataca(indivizi, n);
        imbatraneste();
    }

    int esteViu() //getViu
    {
        return viu;
    }

    int getTip()
    {
        return tip;
    }

    int getVarsta()
    {
        return varsta;
    }

    int getI()
    {
        return i;
    }

    int getEnergie()
    {
        return energie;
    }
    friend istream& operator >> (istream& in, individ& other);

    friend ostream& operator << (ostream& out, const individ& other);
};

istream& operator >> (istream& in, individ& other)
{
    other.tip = '1';
    do
    {
        in >> other.tip;
        if (other.tip != '0' && other.tip != '+')
            cout << "Va rugam sa introduceti un caracter valid ('0' sau '+'): ";

    } while (other.tip != '0' && other.tip != '+');
    return in;
}

ostream& operator << (ostream& out, const individ& other)
{

    if (other.viu == 0)
    {
        out << "Tipul " << other.tip << ", Mort la varsta " << other.varsta <<"." << endl;
    }
    else {
        out << "Tipul " << other.tip << ", varsta " << other.varsta << ", energia " << other.energie << "." << endl;
    }

    return out;
}

void Meniu(individ indivizi[], int n)
{
    cout << "Meniu" << endl << endl;
    cout << "1. Vedeti datele indivizilor dumneavoastra." << endl;
    cout << "2. Aplicati o actualizare unuia dintre indivizii dumneavoastra." << endl;
    cout << "3. Iesiti din program." << endl;
    cout << "Introduceti un numar de la 1 la 3 pentru a alege o optiune (daca nu alegeti un numar, veti fi scos din aplicatie): ";
    int k = 0;
    int i;
    do
    {
        cin >> k;
        if (k < 0 || k > 3)
            cout << "Va rugam sa introduceti un caracter valid ('1', '2', '3'): ";
    } while (k < 0 || k > 3);
    if (k == 1)
    {

        system("CLS");
        char buton;
        for (i = 1; i <= n; i++)
        {
            cout << "Individul " << i << ": " << indivizi[i] << endl;
        }
        cout << "Apasati orice tasta pentru a va intoarce la meniu. ";

        getchar();
        getchar();

        system("CLS");
        Meniu(indivizi, n);
    }
    if (k == 2)
    {
        int x;
        char buton;
        system("CLS");
        cout << "Daca vreti sa iesiti din aplicatie, tastati 0. Daca nu, introduceti numarul individului pe care doriti sa il actualizati " << "(de la 1 la " << n << "): ";

        do
        {
            cin >> x;

            if (x == 0)
                exit(EXIT_SUCCESS);
            if ((x > n || x < 1) || !indivizi[x].esteViu())
                cout << "Va rugam sa introduceti un caracter valid (un caracter de '0' la '" << n << "' si trebuie sa nu fie un individ mort :) ). Apasati '0' daca vreti sa iesiti din program (in cazul in care sunt toti indivizii morti, eventual). ";


        } while ((x > n || x < 1) || !indivizi[x].esteViu());
        indivizi[x].actualizare(indivizi, n);
        cout << "Ati actualizat individul cu numarul " << x << ". Acestea sunt datele lui acum:" << endl;
        cout << indivizi[x] << endl << "Apasati orice tasta pentru a va intoarce la meniu. ";

        getchar();
        getchar();

        system("CLS");
        Meniu(indivizi, n);

    }
    if (k == 3)
        exit(EXIT_SUCCESS);
}


int main()
{
    int n;
    int x;
    individ indivizi[30];

    cout << setw(87) << "My Guys\n" << endl << endl;
    cout << "Bun venit pe platforma noastra. Aici puteti crea proprii idivizi virtuali si le puteti aplica diverse comenzi.";
    cout << endl;
    cout << "Pentru a incepe, introduceti numarul de indivizi pe care doriti sa il memoreze baza de date si tipurile lor (maxim 30 de indivizi!). Exista doua tipuri: '0' si '+'.";
    cout << endl << endl;
    cout << "Daca numarul depaseste 30, veti fi scos din aplicatie. Numarul indivizilor este: ";
    cin >> n;
    if (n > 30)
        return 0;

    int i;

    for (i = 1; i <= n; i++)
    {
        cout << "Tipul individului cu numarul " << i << ": ";
        cin >> indivizi[i];
        indivizi[i].setI(i);
    }
    system("CLS");

    cout << "Acestia sunt indivizii creati de dumneavoastra: " << endl;
    for (i = 1; i <= n; i++)
    {
        cout << "Individul " << i << ": " << indivizi[i];
    }
    int ok = 2;
    cout << "Daca este in regula, apasati 1 pentru a accesa meniul. Daca doriti sa iesiti din aplicatie, apasati 0." << endl;
    do
    {
        cin >> ok;
        if (ok != 1 && ok != 0)
            cout << "Va rugam sa introduceti un numar valid ('0' sau '1'): ";

    } while (ok != 1 && ok != 0);

    if (ok == 1)
    {
        system("CLS");
        Meniu(indivizi, n);
    }
    else
        return 0;
    return 0;
}
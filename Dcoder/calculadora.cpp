#include<iostream>
using namespace std;

int main()

{
    setlocale(LC_ALL,"fr");
    
    int a,b,selection;
    
    cout<<"mettez 2 chiffres"<<endl;
    cin>>a>>b;
    
    cout<<"choisissez une opération mathématique"<<endl<<"1.additionn"<<endl<<"2.soustraction"<<endl<<"3.multiplication"<<endl<<"4.division"<<endl;
    cin>>selection;
    
    switch(selection)
    {
        case 1:
        cout<<"résultat addition"<<a+b  <<endl;
        break;
        case 2:
        cout<<"résultat soustraction"<<a-b  <<endl;
        break;
        case 3:
        cout<<"résultat multiplication"<<a*b  <<endl;
        break;
        case 4:
        cout<<"résultat division"<<(float)a/b  <<endl;
        break;
        default:
        cout<<"Erreur"<<endl;
        break;
    }

    
    
}
#include <iostream>
#include "DLList.h" //ist.h"
#include "fraction.h"
#include <string>
#include <list>
#include <vector>

using namespace std;

/*Fraction mediant(const& Fraction M, const& Fraction Mprime) {
Fraction Mdnt;
Mdnt.setNumerator(M.getNumerator() + Mprime.getNumerator());
Mdnt.setDenominator(M.getDenominator() + Mprime.getDenominator());
return Mdnt;
}*/

int main() {
    try {
        //list<Fraction> Farey01;
        //vector<Fraction> Farey01;
        Fraction F01(0, 1);
        Fraction F02(1, 0);
        //vector<Fraction>::iterator it = Farey01.begin();
        //Farey01.push_back(F01);
        //Farey01.push_back(F02);
        //for (it = Farey01.begin(); it != nullptr; ++it)
        //for (int i = 0; i < 2; ++i)
        //    cout << Farey01[i]; // *it;
        DNode<Fraction>* Farey01 = new DNode<Fraction>(Fraction(1, 1));
        List<Fraction> FareyList01(Farey01);
        Farey01 = Farey01->insert(FareyList01, new DNode<Fraction>(Fraction(1, 2)));
        Farey01 = Farey01->insert(FareyList01, new DNode<Fraction>(Fraction(3, 5)));
        Farey01 = Farey01->insert(FareyList01, new DNode<Fraction>(Fraction(5, 8)));
        Farey01 = Farey01->insert(FareyList01, new DNode<Fraction>(Fraction(8, 13)));
        print_all(FareyList01);

        DNode<Fraction>* Farey02 = new DNode<Fraction>(Fraction(0, 1));
        List<Fraction> FareyList02(Farey02);
        Farey02 = Farey02->add(FareyList02, new DNode<Fraction>(Fraction(1, 1)));
        Farey02 = Farey02->add(FareyList02, new DNode<Fraction>(Fraction(1, 2)));
        Farey02 = Farey02->add(FareyList02, new DNode<Fraction>(Fraction(2, 3)));
        Farey02 = Farey02->add(FareyList02, new DNode<Fraction>(Fraction(3, 5)));
        print_all(FareyList02);
        //Fraction F03(0,1);
        //Fraction F04(1,0);
        //Farey02.add(new DNode<Fraction>(F03));
        //Farey02.add(new DNode<Fraction>(F04));
        //cout << "Farey02.firstDNode->data = " << Farey02.first_DNode->data << endl;
        //Farey02.printDll();
        //Farey02.add();
        cin.get();
    }
    catch (string* errMess)    {
        cout << *errMess;
    }
    return 0;
}
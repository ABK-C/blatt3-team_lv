#include <iostream>
#include <fstream>
#include <vector>


double poisson(double mu, int k) {
    return 0;
}

int main() {

    using namespace std;
    ifstream fin("datensumme.txt"); //Einlesedatei festlegen
    ofstream fout("hist.txt");  //Ausgabedatei festlegen

    vector<int> zaehler(11);  //Vektor mit 11 Einträgen definieren
    int n_i;  //Variable definieren

    for(int i = 0 ; i < 234 ; ++i) {  //Vorschleife starten, die die nächsten Befehle 234 mal ausführt
        fin >> n_i; //aus Einlesedatei einlesen und den aktuell eingelesenen Wert nach n_i speichern
        zaehler [n_i] += 1; //Vektoreintrag an der Stelle des eingelesenen Eintrags um einen erhöhen
    }

    for(int j=0;j<11;++j) { //Vorschleife starten, die die nächsten Befehle 11 mal ausführt
        cout << zaehler [j] << endl;  //Vektoreintrag an j'ter Stelle ausgeben
        fout <<j; //j in Ausgabedatei schreiben
        fout <<" "; //leere Spalte in Ausgabedatei schreiben
        fout <<zaehler [j]<< endl;  //Vektoreintrag an j'ter Stelle in Ausgabedatei schreiben
    }

    fin.close();
    fout.close();

}
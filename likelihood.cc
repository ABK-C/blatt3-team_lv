#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;


double mu=3.11538;  //Mittelwert

double prob(vector<int> daten, double mu) { //Funktion außerhalb des Hauptprogramms starten

    double L=1; //Variable definieren

    double e_mu = exp(-mu); //Implementation der Exponentialfunktion

    for(int k : daten) {  //Vorschleife starten, die die nächsten Befehle mit allen Einträgen aus dem Vektor daten je einmal ausführt

        double mu_k = pow(mu, k); //Implementation für Potenz
        double k_f = tgamma(k+1); //Implementation für Fakultät

        L *=  mu_k * e_mu * (1/(k_f));  //Likelihood (Wahrscheinlichkeit, die Daten mit einem bestimmten mu zu erhalten)

    } //Vorschleife beenden

    return L; //Variable zurücksetzen

} //Funktion außerhalb des Hauptprogramms beenden



double pr(vector<int> daten) { //Funktion außerhalb des Hauptprogramms starten

    double L = 1; //Variable definieren

    for (int k : daten){  //Vorschleife starten, die die nächsten Befehle mit allen Einträgen aus dem Vektor daten je einmal ausführt 

        double k_k = pow(k, k); //Implementation für Potenz
        double k_f = tgamma(k+1); //Implementation für Fakultät
        double e_k = exp(-k); //Implementation der Exponentialfunktion
        L *= k_k*e_k*(1/(k_f)); //Likelihood geteilt durch bestmögliche Poissonwahrscheinlichkeit (mu=n_i)

    } //Vorschleife beenden

  return L; //Variable zurücksetzen

} //Funktion außerhalb des Hauptprogramms beenden



int main() {  //Hauptprogramm starten

    
    ifstream fin("datensumme.txt"); //Einlesedatei festlegen
    ofstream fout("likelihood.txt");  //Ausgabedatei festlegen
    ofstream fout2("nll.txt");  //weitere Ausgabedatei festlegen
    ofstream fout3("deltanll.txt");  //weitere Ausgabedatei festlegen

        vector<int> daten(0); //Vektor mit 0 Einträgen defineiren
        int n_i;  //Variable definieren

        for(int i = 0 ; i < 234 ; ++i) {  //Vorschleife starten, die folgenden Befehle 234 mal ausführt

            fin >> n_i; //aus Einlesedatei einlesen und den aktuell eingelesenen Wert nach n_i speichern
            daten.push_back(n_i); //den aktuell in n_i gespeicherten Wert dem Vektor hinzufügen

        } //vorschleife beenden

        cout << prob(daten , mu) << endl; //Likelihood für mu im Terminal ausgeben


        double j=0; //Variable festlegen
        
        do{ //nachfolgende Befehle ausführen, so lange Bedingung erfüllt ist

            j+=0.01;  //Schrittweite von j festlegen
            fout << j << " " << prob(daten,j) << endl;  //Wertepaare mu und L(mu) in Ausgabedatei schreiben
            fout2 << j << " " << -2*log(prob(daten,j)) << endl; //Wertepaare mu und -2ln L(mu) in Ausgabedatei 2 schreiben
            fout3 << j << " " << -2*log(prob(daten,mu))+2*log(prob(daten,j)) << endl; //Wertepaare mu und -2ln L(mu)-2ln L(3,11538)


        } while(j<6);  //Bedingung festlegen, die zum ausführen der obigen Befehle erfüllt sein muss

        double lambda = -2*log(prob(daten,mu)/pr(daten));  //Berechnung des Likelihood-Quotienten
        cout << lambda << endl;  //Ausgabe des Likelihood-Quotienten im Terminal

        double z = (lambda-233)/(sqrt(2*233)); //Berechnung der relativen Abweichung des Likelihood-Quotienten vom Mittelwert
        cout << z << endl;  //Ausgabe der relativen Abweichung des Likelihood-Quotienten vom Mittelwert
    
    fin.close();  //Einlesedatei schließen
    fout.close(); //Ausgabedatei schließen
    fout2.close();  //Ausgabedatei 2 schließen
    fout3.close();  //Ausgabedatei 3 schließen

} //Hauptprogramm beenden

//Schätzwert für mu liegt bei mu=3,12 
//Fehler auf geschätzten Wert mu: +-0,05

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
using namespace std;

// Implementacja pierwszego podejscia - brute force
void algorytmPierwszy(int A[], int N) {
    for(int i=0; i<N; i++){
        for(int j=i+1; j<N;j++){
            if(A[j]==A[i]){
                int pomoc=A[j];
                for(int k=j; k>i+1; k--){
                    A[k]=A[k-1];
                }
                A[i+1]=pomoc;
                i++;
            }
        }
    }
}

// Implementacja drugiego podejscia - zoptymalizowane
int algorytmDrugi(int A[], int N){
int kolejnosc[N];
    int liczniki[100]={0}; // Zakładam, że elementy będą w zakresie od 0 do 99
    int kolejnoscRozmiar=0;

    // Grupowanie elementow
    for(int i=0; i<N; i++){
        int liczba=A[i];
        if(liczniki[liczba]==0){
            kolejnosc[kolejnoscRozmiar++]=liczba;
        }
        liczniki[liczba]++;
    }

    // Rekonstrukcja tablicy
    int index=0;
    for(int i = 0; i<kolejnoscRozmiar; i++){
        int liczba = kolejnosc[i];
        for(int j=0; j<liczniki[liczba] ;j++){
            A[index++]=liczba;
        }
    }
};

int main()
{
    int wyborAlg;
    int wyborTab;
    int N;
    int zakr1,zakr2;
    do{ // Wyswietlamy glowne menu
        cout << "\033[2J\033[1;1H";
        cout << " Wybierz opcje wypelniania tablicy (1-2)"<<endl;
        cout << " 1. Liczby pseudolosowe"<<endl;
        cout << " 2. Wprowadzanie reczne"<<endl;
        cout << " 3. Zakoncz program"<<endl;
        if(!(cin >> wyborTab)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        //Wybor opcji
        switch (wyborTab){
            case 1:{ // Podajemy potrzebne wartosci do wygenerowanie tablicy
                cout << "\n Podaj rozmiar tablicy: ";
                if(!(cin >> N)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " Niepoprawna wartosc" << endl;
                    cout << " Nacisnij dowolny przycisk aby kontynuowac"<<endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
                cout << " Podaj poczatek zakresu: ";
                if(!(cin >> zakr1)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " Niepoprawna wartosc" << endl;
                    cout << " Nacisnij dowolny przycisk aby kontynuowac"<<endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
                cout << " Podaj koniec zakresu: ";
                if(!(cin >> zakr2)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " Niepoprawna wartosc" << endl;
                    cout << " Nacisnij dowolny przycisk aby kontynuowac"<<endl;
                    cin.ignore();
                    cin.get();
                    break;
                }

                if(zakr1>zakr2){
                    cout << " Blad: poczatek zakresu nie moze byc wiekszy niz koniec"<<endl;
                    cout << " Nacisnij dowolny przycisk aby kontynuowac"<<endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
                int A[N];
                for(int i=0; i<N; i++){
                    A[i]=zakr1+rand()%(zakr2-zakr1+1);
                }

                // Wypisujemy tablice nieuporzadkowana
                cout << endl << " Tablica liczb pseudolosowych: "<<endl;
                for(int i=0; i<N; i++){
                    cout<<" "<< A[i];
                }
                cout << endl;
                do { // Kolejne menu, wybor algorytmow
                    cout << "\n Wybierz Algorytm (1-2): "<<endl;
                    cout << " 1. Pierwsze podejscie"<<endl;
                    cout << " 2. Drugie podejscie (zoptymalizowane)"<<endl;
                    cout << " 3. Wroc"<<endl;
                    cout << endl;


                    if(!(cin >> wyborAlg)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        continue;
                    }

                    switch(wyborAlg){
                        case 1:{ // Gdy wybierzemy pierwszy algorytm
                            auto start1 = chrono::steady_clock::now();

                            algorytmPierwszy(A,N);
                            auto end1 = chrono::steady_clock::now();
                            chrono::duration<double, std::milli> duration1 = end1 - start1;

                            cout << endl << " Tablica uporzadkowana: "<<endl;
                            for(int i=0; i<N; i++){
                                cout<< A[i] << " ";
                            }
                            cout << endl << " Czas zajety przez funkcje:" << duration1.count() << " sekund" << endl;
                            cin.ignore();
                            cin.get();
                            break;
                            }

                        case 2:{ // Gdy wybierzemy drugi algorytm
                            auto start2 = chrono::steady_clock::now();
                            algorytmDrugi(A,N);
                            auto end2 = chrono::steady_clock::now();
                             chrono::duration<double, std::milli> duration2 = end2 - start2;
                            cout << endl << " Tablica uporzadkowana: "<<endl;
                            for(int i=0; i<N; i++){
                                cout<< A[i] << " ";
                            }
                            cout << endl << " Czas zajety przez funkcje:" << duration2.count() << " sekund" << endl;
                            cin.ignore();
                            cin.get();
                            break;
                            }

                        case 3:{
                            wyborAlg=3;
                            break;
                        }
                        default:{
                            cout << "Niepoprawny wybor. Sprobuj ponownie." << endl;
                            cin.clear();
                            cin.ignore(10000, '\n');
                            break;
                        }
                    }
                } while(wyborAlg != 3);
                break;
            }
            case 2:{ // Podajemy wartosci do tablicy
                cout << "\n Podaj rozmiar tablicy: ";
                if(!(cin >> N)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " Niepoprawna wartosc" << endl;
                    cout << " Nacisnij dowolny przycisk aby kontynuowac"<<endl;
                    cin.ignore();
                    cin.get();
                    break;
                }
                int A[N];
                cout<< " Podaj liczby: "<<endl;
                for(int i=0; i<N; i++){
                cin>>A[i];
                }
                // Wyswietlamy utworzona tablice
                cout << endl << " Tablica: "<<endl;
                for(int i=0; i<N; i++){
                    cout<<" "<< A[i];
                }

                cout << endl << endl;
                do {    // Wyswietlamy menu z wyborem algorytmow
                    cout << " Wybierz Algorytm (1-2): "<<endl;
                    cout << " 1. Pierwsze podejscie"<<endl;
                    cout << " 2. Drugie podejscie (zoptymalizowane)"<<endl;
                    cout << " 3. Wroc"<<endl;
                    cout << endl;


                    if(!(cin >> wyborAlg)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        continue;
                    }

                    switch(wyborAlg){
                        case 1:{    // Gdy wybierzemy pierwszy algorytm
                            auto start1 = chrono::steady_clock::now();

                            algorytmPierwszy(A,N);
                            auto end1 = chrono::steady_clock::now();
                            chrono::duration<double, std::milli> duration1 = end1 - start1;

                            cout << endl << " Tablica uporzadkowana: "<<endl;
                            for(int i=0; i<N; i++){
                                cout<< A[i] << " ";
                            }
                            cout << endl << " Czas zajety przez funkcje:" << duration1.count() << " sekund" << endl;
                            cin.ignore();
                            cin.get();
                            break;
                            }

                        case 2:{    // Gdy wybierzemy drugi algorytme
                            auto start2 = chrono::steady_clock::now();
                            algorytmDrugi(A,N);
                            auto end2 = chrono::steady_clock::now();
                             chrono::duration<double, std::milli> duration2 = end2 - start2;
                            cout << endl << " Tablica uporzadkowana: "<<endl;
                            for(int i=0; i<N; i++){
                                cout<< A[i] << " ";
                            }
                            cout << endl << " Czas zajety przez funkcje:" << duration2.count() << " sekund" << endl;
                            cin.ignore();
                            cin.get();
                            break;
                            }

                        case 3:{
                            wyborAlg=3;
                            break;
                        }
                        default:{
                            cout << "Niepoprawny wybor. Sprobuj ponownie." << endl;
                            cin.clear();
                            cin.ignore(10000, '\n');
                            break;
                        }
                    }
                } while(wyborAlg != 3);
                break;
            }
            case 3:{
                break;
            }

            default:
                cout << "Niepoprawny wybor. Sprobuj ponownie." << endl;
        }
    }while(wyborTab != 3);
    return 0;
}

// Santiago Salazar Osorio 9018674

#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <set>

using namespace std;

int nLocaciones;
vector<vector<pair<int, int>>> adyLocaciones(1000);
vector<int> p(1000);
vector<int> d(1000);
set<int> ansDef;

void bellmanFordOpt(int s){
    int i, j, u, v, peso, t, curr;

    for(i = 0; i < nLocaciones; i++){
        p[i] = -1;
        d[i] = INT_MAX;
    }

    d[s] = 0;
    i = 0;

    while(i < nLocaciones){
        t = -1;
        for(v = 0; v < nLocaciones; v++){
            for(j = 0; j < adyLocaciones[v].size(); j++){
                u = adyLocaciones[v][j].first;
                peso = adyLocaciones[v][j].second;
                if(d[v] != INT_MAX && d[u] > d[v] + peso){
                    d[u] = d[v] + peso;
                    p[u] = v;
                    t = v;
                }
            }
        }
        i++;
    }
    if(t != -1){
        for(i = 0; i < nLocaciones; ++i){
            t = p[t];
        }
        curr = t;
        while(curr != t || ansDef.empty()){
            ansDef.insert(curr);
            curr = p[curr];
        }
    }
}




void iniciarSimulacion(){
    int Tcasos, caso, i, mPortales, xOrigen, yDestino, tAnios;
    bool respuesta, primerDigito;
    for(caso = 1; caso < Tcasos + 1; caso++){
        cin >> nLocaciones >> mPortales;

        for(i = 0; i < nLocaciones; i++){
            adyLocaciones[i] = vector<pair<int, int>>();
        }
        
        for(i = 0; i < mPortales; i++){
            cin >> xOrigen >> yDestino >> tAnios;
            adyLocaciones[xOrigen].push_back({yDestino, tAnios});
        }
        primerDigito = true;
        ansDef.clear();
        for(i = 0; i < nLocaciones; i++){
            if(!ansDef.count(i)){
                bellmanFordOpt(i);
            } 
        }
        if(ansDef.empty()){
            cout << "Case " << caso << ":" << " impossible";
        } else {
            for(int elemento : ansDef){
                if(primerDigito){
                    cout << "Case " << caso << ":";
                }
                primerDigito = false;
                cout << " " << elemento;
            }
        }
        cout << "\n";
    }
    
}

int main(){
    iniciarSimulacion();

    return 0;
}
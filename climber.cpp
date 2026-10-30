// Santiago Salazar Osorio 9018674

#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

// Análisis complejidad BIG O : Se analizó la complejidad en tiempo del siguiente código y se puede describir
// mediante las siguientes variables y sus comportamientos:

// N -> Numero de marcas en la montaña que puedo visitar (Nodos)

// M -> Caminos para subir de un lugar a otro gastando w energia tal que, w: M -> R y los pesos de R siempre son positivos

// Primero debemos saber que cualquier grafo que nos den siempre va a ser un arbol con las aristas invertidas, por lo tanto
// sabemos que los nodos que quedarán de primeros en el orden topologico, debido a su incidencia, serán las hojas del mismo 
// (cuando me refiero a hojas es analizando el arbol pero con las aristas invertidas, es decir la raiz es el 1, todas las de subida ahora bajan, es raro pero asi funciona mi cabeza XD)
// Por lo tanto, lo que debemos hacer es calcular 2 valores, siempre y cuando lleguemos a la posicion de un amigo, cálculamos 
// el total de energía gastada para ir subiendo el arbol, y  el maximo de energía con la que puedo llegar a la adyacencia.
// Todo esto con el fin de al final saber cuanto me gasto para llegar a cada uno de los amigos y a ese total le resto al amigo el cual una vez visitado es demasiado costoso
// volver a subir, por lo cual a ese lo visitaré de último para terminar ahi y no subir mas y evitarme gastar toda esa energía

// Otro aspecto importante es que el numero de aristas M, al ser un arbol, este esta dictado por el numero N
// de nodos, por lo tanto M = N - 1, Si ya calculamos que todas las operaciones por usar lista de adyacencia
// nos dan una complejidad O(N + M) -> O(N + N - 1) -> O(2N - 1) y pues obviamente como ya sabemos la defincion de O grande
// pues sabemos que podemos descartar constantes, por lo tanto podemos reemplazar M y tendríamos como resultado una cota superior
// que solo depende del numero de nodos, entonces la complejidad final es O(N)

int nLandMarks, fAmigos;

vector<vector<pair<int, int>>> ady(100001);
vector<bool> esPosAmigo(100001);
vector<int> mayorE(100001);

vector<int> topoSort(){
    int i, j, u, v; // O(4)
    queue<int> q; // O(1)
    vector<int> topo; // O(1)
    vector<int> inc(nLandMarks + 1, 0); // O(N)

    for(i = 1; i < nLandMarks + 1; i++){ // O(N)
        for(j = 0; j < ady[i].size(); j++){ // O(M)
            inc[ady[i][j].first] += 1; // O(M)
        }
    }

    for(i = 1; i < nLandMarks + 1; i++){ // O(N)
        if(inc[i] == 0){ // O(N)
            q.push(i); // O(N)
        }
    }

    while(!q.empty()){ // O(N)
        u = q.front(); q.pop(); // O(N)
        topo.push_back(u); // O(N)

        for(i = 0; i < ady[u].size(); i++){ // O(M)
            v = ady[u][i].first; // O(M)
            inc[v] -= 1; // O(M)
            if(inc[v] == 0){ // O(M)
                q.push(v); // O(M)
            }
        }
    }
    return topo; // O(1)

} // Big O resultado : 7 + 8N + 7M ∈ O(N + M)

int ssspDAG(){
    int i, j, u, v, duv, ans = 0; // O(6)
   
    vector<int> topo = topoSort(); // O(N + M)
    
    for(i = 0; i < topo.size(); i++){ // O(N)
        u = topo[i]; // O(N)
        for(j = 0; j < ady[u].size(); j++){ // O(M)
            v = ady[u][j].first; // O(M)
            if(mayorE[u] != -1){ // O(M)
                duv = ady[u][j].second; // O(M)
                ans += duv; // O(M)
                if(duv + mayorE[u] > mayorE[v]){ // O(M)
                    mayorE[v] = duv + mayorE[u]; // O(M)
                }
            }
        }
    }

    ans = ans - mayorE[1]; // O(1)

    return ans; // O(1)

} // Big O Resultado: 8 + 2N + 7M + (N + M) = 8 + 3N + 8M ∈ O(N + M)

void iniciarSimulacion(){
    int i, cEnergia, aOrigen, bDestino, resultado; // O(5)

    while(cin >> nLandMarks >> fAmigos){ // O(1)
        for(i = 1; i < nLandMarks + 1; i++){ // O(N)
            ady[i] = vector<pair<int, int>>(); // O(N)
            esPosAmigo[i] = false; // O(N)
            mayorE[i] = -1; // O(N)
        }
        for(i = 0; i < nLandMarks - 1; i++){ // M = N - 1; O(M) ∈ O(N-1) ∈ O(N)
            cin >> aOrigen >> bDestino >> cEnergia; // O(M)
            ady[bDestino].push_back({aOrigen, cEnergia}); // O(M)
        }
        for(i = 0; i < fAmigos; i++){ // O(N)
            cin >> aOrigen; // O(N)
            esPosAmigo[aOrigen] = true; // O(N)
            mayorE[aOrigen] = 0; // O(N)
        }

        resultado = ssspDAG(); // O(N + M)

        cout << resultado << "\n"; // O(1)
    }

} // Big O resultado : 7 + 8N + 3M + (N + M) = 7 + 9N + 4M ∈ O(N + M)

int main(){

    iniciarSimulacion(); // O(N + M)

    return 0;

}


// Jesus Martin Moraleda

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
/*
El problema se resuelve mediante programacion dinamica ascendente. La idea es recorrer el tablero de arriba hacia abajo,
seleccionando solamente el mejor movimiento que podria hacer una determinada casilla cuando se llegara a ella
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
/*
El coste seria cuadratico, O(n^2), ya que recorremos todas las casillas del tablero con un bucle anidado
El coste en espacio tambien seria cuadratico ya que reutilizamos el mismo tablero de n*n
*/

typedef struct {
    int max_score;
    int initial_box;
}tSolucion;


tSolucion resolver(Matriz<int>& m, const int& N) {

    for (int i = 1; i < N; i++) { //Recorremos desde la segunda fila
        for (int j = 0; j < N; j++) { //Recorremos cada elemento de la fila

            if (j == 0) { //Si el elemento esta en la esquina izquierda
                m[i][j] = m[i][j] + max(m[i - 1][j], m[i - 1][j + 1]);
            }

            else if (j == N - 1) { //Si el elemento esta en la esquina derecha
                m[i][j] = m[i][j] + max(m[i - 1][j - 1], m[i - 1][j]);
            }

            else {  //En otro caso
                m[i][j] = m[i][j] + max(m[i - 1][j - 1], max(m[i - 1][j], m[i - 1][j + 1]));
            }
        }
    }

    tSolucion sol = { 0,0 };
    for (int i = 0; i < N; i++) {
        if (m[N - 1][i] > sol.max_score) {
            sol.max_score = m[N - 1][i];
            sol.initial_box = i + 1;
        }
    }

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada

    int N;
    cin >> N;

    if (!std::cin)
        return false;

    Matriz<int> matriz_inicial(N,N,0);
    int aux;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> aux;
            matriz_inicial[i][j] = aux;
        }
    }

    //resolver

    tSolucion sol = resolver(matriz_inicial, N);

    // escribir sol

    cout << sol.max_score << " " << sol.initial_box << endl;

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}


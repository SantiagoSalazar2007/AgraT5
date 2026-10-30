# Santiago Salazar Osorio 9018674

from sys import stdin

MAX = 2001

adj = [[] for i in range(MAX)]

def iniciarSimulacion():
    global adj
    linea = stdin.readline()
    while linea != "":
        nEstaciones, mRieles = map(int, linea.split())

        adj = [[]for i in range(nEstaciones)]

        for _ in range(mRieles):
            u, v, c = map(int, stdin.readline().split())
            adj[u].append((v, c))


        linea = stdin.readline()

        


def main():
    iniciarSimulacion()

main()
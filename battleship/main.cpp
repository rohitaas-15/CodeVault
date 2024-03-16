#include <bits/stdc++.h>
#include "Battleship.cpp"
using namespace std;

signed main()
{
    int n;
    cin >> n;
    Battleship plassey(n);

    int ships;
    cin >> ships;
    while (ships--)
    {
        int x, y, len;
        cin >> x >> y >> len;
        plassey.addShip(x, y, len);
    }

    int turn = 1;
    while (!plassey.playerALoses() && !plassey.playerBLoses())
    {
        int ship = plassey.chooseTarget(turn);
        if (ship)
        {
            cout << "Player"
                 << " " << (char)('A' + turn - 1) << " "
                 << "hits the ship " << ship << endl;
            plassey.destroyShip(ship);
        }
        else
        {
            cout << "Player"
                 << " " << (char)('A' + turn - 1) << " "
                 << "misses " << endl;
        }
        turn = 3 - turn;
    }
    if (plassey.playerALoses())
    {
        cout << "Player B wins";
    }
    else
        cout << "Player A wins";
}
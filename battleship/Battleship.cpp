#include <bits/stdc++.h>
using namespace std;

class Battleship
{
public:
    vector<vector<pair<int, int>>> field;
    vector<vector<int>> shipdetails;
    vector<set<pair<int, int>>> remainingPoints;
    vector<vector<int>> done;
    int n, shipcnt = 1;
    Battleship(int _n)
    {
        n = _n;
        field.clear();
        field.resize(n + 1, vector<pair<int, int>>(n + 1, {0, 0}));
        remainingPoints.clear();
        remainingPoints.resize(3);

        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=n;j++)
            {
                remainingPoints[1+(j>n/2)].insert({i,j});
            }
        }
        done.clear(), done.resize(n + 1, vector<int>(n + 1, 0));
        srand((unsigned) time(NULL));
    }

    void addShip(int x, int y, int len)
    {
        int player = 1 + (y > 2);
        for (int i = x; i < x + len; i++)
        {
            for (int j = y; j < y + len; j++)
            {
                field[i][j] = {player, shipcnt};
            }
        }
        shipdetails.push_back({x, y, len, player});
        shipcnt++;
    }

    int chooseTarget(int turn)
    {
        int defender = (3 - turn);
        auto initialRemainingPoints = remainingPoints[defender];

        vector<pair<int, int>> toBeRemoved;

        for (auto i : initialRemainingPoints)
        {
            if (done[i.first][i.second])
            {
                toBeRemoved.push_back(i);
            }
        }

        for (auto i : toBeRemoved)
        {
            initialRemainingPoints.erase(i);
        }

        int noRemainingPoints = initialRemainingPoints.size();

        int target = rand() % noRemainingPoints;

        pair<int, int> hitLocation;
        auto it = initialRemainingPoints.begin();
        while (target--)
        {
            it++;
        }

        hitLocation = *(it);

        if (field[hitLocation.first][hitLocation.second].first!=0)
        {
            return field[hitLocation.first][hitLocation.second].second;
        }
        else done[hitLocation.first][hitLocation.second]=1;
        return 0;
    }

    void destroyShip(int shipNumber)
    {
        auto details = shipdetails[shipNumber-1];
        int x = details[0], y = details[1], len = details[2], player = details[3];
            for (int i = x; i < x + len; i++)
            {
                for (int j = y; j < y + len; j++)
                {
                    remainingPoints[player].erase({i, j});
                    field[i][j] = {0, 0};
                    done[i][j]=1;
                }
            }
    }

    bool playerALoses()
    {
        bool shipPresent=0;
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=n;j++)
            {
                if(field[i][j].first==1)
                {
                    shipPresent=1;
                    break;
                }
            }
        }
        return !shipPresent;
    }

    bool playerBLoses()
    {
        bool shipPresent=0;
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=n;j++)
            {
                if(field[i][j].first==2)
                {
                    shipPresent=1;
                    break;
                }
            }
        }
        return !shipPresent;
    }


};

#include "D:/DSA Projects/Social Network/include/SocialGraph.h"

#include <iostream>

using namespace std;

int main()
{
    SocialGraph network;

    int choice;

    while(true)
    {
        cout << "\n===== SOCIAL NETWORK =====\n";

        cout << "1. Add User\n";
        cout << "2. Add Friendship\n";
        cout << "3. Show All Users\n";
        cout << "4. Show Friends\n";
        cout << "5. BFS\n";
        cout << "6. DFS\n";
        cout << "7. Shortest Path\n";
        cout << "8. Friend Recommendations\n";
        cout << "9. Search User\n";
        cout << "10. Mutual Friends\n";
        cout << "11. Remove User\n";
        cout << "12. Remove Friendship\n";
        cout << "13. Save Network\n";
        cout << "14. Load Network\n";
        cout << "0. Exit\n";

        cin >> choice;

        if(choice == 0)
            break;

        if(choice == 1)
        {
            int id, age;
            string name, city;

            cout << "ID: ";
            cin >> id;

            cout << "Name: ";
            cin >> name;

            cout << "Age: ";
            cin >> age;

            cout << "City: ";
            cin >> city;

            network.addUser(
                id,
                name,
                age,
                city
            );
        }

        else if(choice == 2)
        {
            int u1,u2;

            cin >> u1 >> u2;

            network.addFriendship(u1,u2);
        }

        else if(choice == 3)
        {
            network.displayAllUsers();
        }

        else if(choice == 4)
        {
            int id;

            cin >> id;

            network.displayFriends(id);
        }

        else if(choice == 5)
        {
            int start;

            cin >> start;

            auto bfs =
                network.bfs(start);

            for(int x : bfs)
                cout << x << " ";
        }

        else if(choice == 6)
        {
            int start;

            cin >> start;

            auto dfs =
                network.dfs(start);

            for(int x : dfs)
                cout << x << " ";
        }

        else if(choice == 7)
        {
            int s,d;

            cin >> s >> d;

            auto path =
                network.shortestPath(s,d);

            for(int x : path)
                cout << x << " ";
        }

        else if(choice == 8)
        {
            int id;

            cin >> id;

            auto rec =
                network.recommendFriends(id);

            for(int x : rec)
                cout << x << " ";
        }

        else if(choice == 9)
        {
            string name;

            cin >> name;

            network.searchUserByName(name);
        }

        else if(choice == 10)
        {
            int u1,u2;

            cin >> u1 >> u2;

            cout
            << network.mutualFriendsCount(
                u1,
                u2
               )
            << endl;
        }

        else if(choice == 11)
        {
            int id;

            cin >> id;

            network.removeUser(id);
        }

        else if(choice == 12)
        {
            int u1,u2;

            cin >> u1 >> u2;

            network.removeFriendship(
                u1,
                u2
            );
        }

        else if(choice == 13)
        {
            network.saveUsers("users.txt");
            network.saveFriendships("friendships.txt");

            cout << "Network Saved\n";
        }

        else if(choice == 14)
        {
            network.loadUsers("users.txt");
            network.loadFriendships("friendships.txt");

            cout << "Network Loaded\n";
        }
    }

    return 0;
}
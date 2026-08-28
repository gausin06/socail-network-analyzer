#include "D:/DSA Projects/Social Network/include/SocialGraph.h"

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

bool SocialGraph::addUser(int id,
                          const string& name,
                          int age,
                          const string& city)
{
    if(users.count(id))
        return false;

    users[id] = User(id, name, age, city);
    return true;
}

bool SocialGraph::removeUser(int id)
{
    if(!users.count(id))
        return false;

    for(auto& friendSet : friendships)
    {
        friendSet.second.erase(id);
    }

    friendships.erase(id);
    users.erase(id);

    return true;
}

bool SocialGraph::userExists(int id) const
{
    return users.count(id);
}

User* SocialGraph::getUser(int id)
{
    if(!users.count(id))
        return nullptr;

    return &users[id];
}

void SocialGraph::displayUser(int id) const
{
    auto it = users.find(id);

    if(it == users.end())
        return;

    const User& u = it->second;

    cout << "ID: " << u.id << endl;
    cout << "Name: " << u.name << endl;
    cout << "Age: " << u.age << endl;
    cout << "City: " << u.city << endl;
}

void SocialGraph::displayAllUsers() const
{
    for(const auto& p : users)
    {
        cout << p.second.id
             << " "
             << p.second.name
             << endl;
    }
}

bool SocialGraph::addFriendship(int user1,
                                int user2)
{
    if(user1 == user2)
        return false;

    if(!userExists(user1) ||
       !userExists(user2))
        return false;

    friendships[user1].insert(user2);
    friendships[user2].insert(user1);

    return true;
}

bool SocialGraph::removeFriendship(int user1,
                                   int user2)
{
    friendships[user1].erase(user2);
    friendships[user2].erase(user1);

    return true;
}

bool SocialGraph::areFriends(int user1,
                             int user2) const
{
    auto it = friendships.find(user1);

    if(it == friendships.end())
        return false;

    return it->second.count(user2);
}

void SocialGraph::displayFriends(int userId) const
{
    auto it = friendships.find(userId);

    if(it == friendships.end())
        return;

    cout << "Friends of "
         << userId
         << ": ";

    for(int id : it->second)
        cout << id << " ";

    cout << endl;
}

vector<int> SocialGraph::bfs(int startId)
{
    vector<int> result;

    if(!userExists(startId))
        return result;

    unordered_set<int> visited;
    queue<int> q;

    q.push(startId);
    visited.insert(startId);

    while(!q.empty())
    {
        int current = q.front();
        q.pop();

        result.push_back(current);

        for(int neighbor : friendships[current])
        {
            if(!visited.count(neighbor))
            {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    return result;
}

vector<int> SocialGraph::dfs(int startId)
{
    vector<int> result;

    if(!userExists(startId))
        return result;

    unordered_set<int> visited;
    stack<int> st;

    st.push(startId);

    while(!st.empty())
    {
        int current = st.top();
        st.pop();

        if(visited.count(current))
            continue;

        visited.insert(current);
        result.push_back(current);

        for(int neighbor : friendships[current])
        {
            if(!visited.count(neighbor))
                st.push(neighbor);
        }
    }

    return result;
}

bool SocialGraph::pathExists(int source,
                             int destination)
{
    vector<int> traversal = bfs(source);

    for(int node : traversal)
    {
        if(node == destination)
            return true;
    }

    return false;
}

vector<int> SocialGraph::shortestPath(int source,
                                      int destination)
{
    vector<int> path;

    unordered_map<int,int> parent;
    unordered_set<int> visited;

    queue<int> q;

    q.push(source);
    visited.insert(source);

    while(!q.empty())
    {
        int current = q.front();
        q.pop();

        if(current == destination)
            break;

        for(int neighbor : friendships[current])
        {
            if(!visited.count(neighbor))
            {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    if(!visited.count(destination))
        return path;

    int cur = destination;

    while(cur != source)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    path.push_back(source);

    reverse(path.begin(),
            path.end());

    return path;
}

vector<int> SocialGraph::recommendFriends(int userId)
{
    vector<int> recommendations;

    if(!userExists(userId))
        return recommendations;

    unordered_map<int,int> mutualCount;

    for(int friendId : friendships[userId])
    {
        for(int candidate : friendships[friendId])
        {
            if(candidate == userId)
                continue;

            if(areFriends(userId,
                          candidate))
                continue;

            mutualCount[candidate]++;
        }
    }

    for(auto& p : mutualCount)
    {
        recommendations.push_back(p.first);
    }

    return recommendations;
}

void SocialGraph::searchUserByName(
        const string& name) const
{
    bool found = false;

    for(const auto& p : users)
    {
        if(p.second.name == name)
        {
            displayUser(p.first);
            found = true;
        }
    }

    if(!found)
    {
        cout << "User not found\n";
    }
}

int SocialGraph::mutualFriendsCount(
        int user1,
        int user2) const
{
    if(!userExists(user1) ||
       !userExists(user2))
        return 0;

    int count = 0;

    auto it1 = friendships.find(user1);

    if(it1 == friendships.end())
        return 0;

    for(int friendId : it1->second)
    {
        if(friendships.at(user2)
                .count(friendId))
        {
            count++;
        }
    }

    return count;
}

bool SocialGraph::saveUsers(
        const string& filename) const
{
    ofstream fout(filename);

    if(!fout)
        return false;

    for(const auto& p : users)
    {
        const User& u = p.second;

        fout << u.id << ","
             << u.name << ","
             << u.age << ","
             << u.city << endl;
    }

    return true;
}

bool SocialGraph::loadUsers(
        const string& filename)
{
    ifstream fin(filename);

    if(!fin)
        return false;

    users.clear();

    string line;

    while(getline(fin,line))
    {
        string idStr;
        string name;
        string ageStr;
        string city;

        stringstream ss(line);

        getline(ss,idStr,',');
        getline(ss,name,',');
        getline(ss,ageStr,',');
        getline(ss,city,',');

        addUser(
            stoi(idStr),
            name,
            stoi(ageStr),
            city
        );
    }

    return true;
}

int SocialGraph::totalUsers() const
{
    return users.size();
}

int SocialGraph::totalFriendships() const
{
    int total = 0;

    for(const auto& p : friendships)
        total += p.second.size();

    return total / 2;
}

bool SocialGraph::saveFriendships(
        const string& filename) const
{
    ofstream fout(filename);

    if(!fout)
        return false;

    for(const auto& p : friendships)
    {
        int user1 = p.first;

        for(int user2 : p.second)
        {
            if(user1 < user2)
            {
                fout
                << user1
                << ","
                << user2
                << endl;
            }
        }
    }

    return true;
}

bool SocialGraph::loadFriendships(
        const string& filename)
{
    ifstream fin(filename);

    if(!fin)
        return false;

    friendships.clear();

    string line;

    while(getline(fin,line))
    {
        string user1Str;
        string user2Str;

        stringstream ss(line);

        getline(ss,user1Str,',');
        getline(ss,user2Str,',');

        int user1 = stoi(user1Str);
        int user2 = stoi(user2Str);

        addFriendship(user1,user2);
    }

    return true;
}
#ifndef SOCIALGRAPH_H
#define SOCIALGRAPH_H

#include "User.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

class SocialGraph
{
private:

    // Stores all users
    std::unordered_map<int, User> users;

    // Adjacency list
    std::unordered_map<int,
                       std::unordered_set<int>> friendships;

public:

    // User Operations
    bool addUser(int id,
                 const std::string& name,
                 int age,
                 const std::string& city);

    bool removeUser(int id);

    bool userExists(int id) const;

    User* getUser(int id);

    void displayUser(int id) const;

    void displayAllUsers() const;

    // Friendship Operations
    bool addFriendship(int user1,
                       int user2);

    bool removeFriendship(int user1,
                          int user2);

    bool areFriends(int user1,
                    int user2) const;

    void displayFriends(int userId) const;

    // Graph Algorithms
    std::vector<int> bfs(int startId);

    std::vector<int> dfs(int startId);

    bool pathExists(int source,
                    int destination);

    std::vector<int> shortestPath(int source,
                                  int destination);

    // Friend Recommendation
    std::vector<int> recommendFriends(int userId);

    // Search
    void searchUserByName(const std::string& name) const;

    // Mutual Friends
    int mutualFriendsCount(int user1,
                        int user2) const;

    // File Handling
    bool saveUsers(const std::string& filename) const;

    bool loadUsers(const std::string& filename);

    // Statistics
    int totalUsers() const;

    int totalFriendships() const;

    bool saveFriendships(const std::string& filename) const;

    bool loadFriendships(const std::string& filename);
};

#endif
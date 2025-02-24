#pragma once
#ifndef SOCIALNETWORKPROJECT_GRAPH_H
#define SOCIALNETWORKPROJECT_GRAPH_H

#include <unordered_map>
#include "Person.h"
#include "utils.h"

class Graph {
public:
    Graph() = default;
    Graph(const std::string& filename);
    Graph(const Graph& other);
    ~Graph();
    Graph& operator=(const Graph& other);
    std::unordered_map<int, Person*> getVertices() const;
    std::vector<int> suggestFriends(int person_id, int mode) const;
    int degreeCentrality(int personId);
    double clusteringCoefficient(int id) const;
    std::vector<std::vector<int>> girvanNewman(int iterations);
    size_t getSize() const;
    void addPerson(int id, Person* person);
    bool isPersonExists(int id) const;
    Person* getPerson(int id) const;
    void addFriendship(int id1, int id2);
    void removeFriendship(int id1, int id2);

private:
    std::unordered_map<int, Person*> vertices;
    std::vector<int> suggestFriendsByCommonFriends(const Person* person) const;
    std::vector<int> suggestFriendsByOccupation(const Person* person) const;
    std::vector<int> suggestFriendsByAge(const Person* person) const;
    bool hasCommonFriends(const Person* person1, const Person* person2) const;
    std::pair<int, int> getEdgeWithHighestBetweenness();
    void removeEdge(const std::pair<int, int> &edge);
    std::unordered_map<int, std::vector<int>> calculateShortestPaths(int sourceId) const;
    std::vector<std::vector<int>> detectCommunities();
    void depthFirstSearch(int nodeId, const Graph &graph, std::vector<int> &visited) const;
    std::unordered_map<std::pair<int, int>, double> calculateEdgeBetweenness() const;
};

#endif //SOCIALNETWORKPROJECT_GRAPH_H

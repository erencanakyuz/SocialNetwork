#include "Graph.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <functional>

namespace std {
    template<>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int>& p) const {
            auto h1 = hash<int>{}(p.first);
            auto h2 = hash<int>{}(p.second);
            return h1 ^ h2;
        }
    };
}

Graph::Graph(const std::string& filename) {
    *this = readData(filename);
}

Graph::Graph(const Graph& other) {
    for (const auto& id_and_person : other.vertices) {
        int id = id_and_person.first;
        Person* person = new Person(*id_and_person.second);
        vertices[id] = person;
    }
}

Graph::~Graph() {
    for (const auto& id_and_person : vertices) {
        delete id_and_person.second;
    }
}

std::unordered_map<int, Person*> Graph::getVertices() const {
    return vertices;
}

size_t Graph::getSize() const {
    return vertices.size();
}

bool Graph::isPersonExists(int id) const {
    return vertices.find(id) != vertices.end();
}

void Graph::addFriendship(int id1, int id2) {
    if (isPersonExists(id1) && isPersonExists(id2)) {
        vertices[id1]->addFriend(id2);
        vertices[id2]->addFriend(id1);
    }
}

void Graph::removeFriendship(int id1, int id2) {
    if (isPersonExists(id1) && isPersonExists(id2)) {
        vertices[id1]->removeFriend(id2);
        vertices[id2]->removeFriend(id1);
    }
}

void Graph::addPerson(int id, Person* person) {
    if (isPersonExists(id)) {
        delete vertices[id];
    }
    vertices[id] = person;
}

Person* Graph::getPerson(int id) const {
    if (isPersonExists(id)) {
        return vertices.at(id);
    } else {
        return nullptr;
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        for (const auto& id_and_person : vertices) {
            delete id_and_person.second;
        }
        vertices.clear();
        for (const auto& id_and_person : other.vertices) {
            int id = id_and_person.first;
            Person* person = new Person(*id_and_person.second);
            vertices[id] = person;
        }
    }
    return *this;
}


std::vector<int> Graph::suggestFriends(int person_id, int mode) const {
    std::vector<int> suggestedFriends;

    const Person* person = getPerson(person_id);
    if (person) {
        switch (mode) {
            case 1:
                suggestedFriends = suggestFriendsByCommonFriends(person);
                break;
            case 2:
                suggestedFriends = suggestFriendsByOccupation(person);
                break;
            case 3:
                suggestedFriends = suggestFriendsByAge(person);
                break;
            default:
                break;
        }
    }
    return suggestedFriends;
}

std::vector<int> Graph::suggestFriendsByCommonFriends(const Person* person) const {
    std::vector<int> suggestedFriends;

    const std::vector<int>& friends = person->getFriends();
    for (int friend_id : friends) {
        const Person* friend_person = getPerson(friend_id);
        if (friend_person) {
            const std::vector<int>& friend_friends = friend_person->getFriends();
            for (int friend_friend_id : friend_friends) {
                if (friend_friend_id != person->getId() && !person->isFriendWith(friend_friend_id)) {
                    suggestedFriends.push_back(friend_friend_id);
                }
            }
        }
    }
    return suggestedFriends;
}

std::vector<int> Graph::suggestFriendsByOccupation(const Person* person) const {
    std::vector<int> suggestedFriends;
    const std::string& occupation = person->getOccupation();
    for (const auto& id_and_person : vertices) {
        const Person* friend_person = id_and_person.second;
        if (friend_person->getId() != person->getId() && !person->isFriendWith(friend_person->getId())) {
            if (friend_person->getOccupation() == occupation) {
                suggestedFriends.push_back(friend_person->getId());
            }
        }
    }
    return suggestedFriends;
}

std::vector<int> Graph::suggestFriendsByAge(const Person* person) const {
    std::vector<int> suggestedFriends;
    int age = person->getAge();
    for (const auto& id_and_person : vertices) {
        const Person* friend_person = id_and_person.second;
        if (friend_person->getId() != person->getId() && !person->isFriendWith(friend_person->getId())) {
            if (friend_person->getAge() == age) {
                suggestedFriends.push_back(friend_person->getId());
            }
        }
    }
    return suggestedFriends;
}

int Graph::degreeCentrality(int personId) {
    if (isPersonExists(personId)) {
        Person* person = getPerson(personId);
        int degree = person->getFriends().size();
        std::cout << "Degree centrality of person " << personId << " is " << degree << std::endl;
        return degree;
    }
    return 0;
}

double Graph::clusteringCoefficient(int id) const {
    if (isPersonExists(id)) {
        Person* person = getPerson(id);
        std::vector<int> friends = person->getFriends();

        int friendPairs = 0;
        int totalPairs = friends.size() * (friends.size() - 1) / 2;

        for (int i = 0; i < friends.size(); i++) {
            for (int j = i + 1; j < friends.size(); j++) {
                if (getPerson(friends[i])->isFriendWith(friends[j])) {
                    friendPairs++;
                }
            }
        }
        return static_cast<double>(friendPairs) / totalPairs;
    } else {
        return 0.0;
    }
}

std::vector<std::vector<int>> Graph::girvanNewman(int iterations) {
    Graph tempGraph = *this;
    for (int i = 0; i < iterations; i++) {
        std::pair<int, int> edgeToRemove = getEdgeWithHighestBetweenness();
        tempGraph.removeEdge(edgeToRemove);
    }

    std::vector<std::vector<int>> communities = tempGraph.detectCommunities();
    return communities;
}


std::pair<int, int> Graph::getEdgeWithHighestBetweenness() {
    std::pair<int, int> edge;
    double maxBetweenness = -1.0;
    std::unordered_map<std::pair<int, int>, double> betweenness = calculateEdgeBetweenness();

    for (const auto& [currEdge, currBetweenness] : betweenness) {
        if (currBetweenness > maxBetweenness) {
            maxBetweenness = currBetweenness;
            edge = currEdge;
        }
    }
    return edge;
}

void Graph::removeEdge(const std::pair<int, int>& edge) {
    removeFriendship(edge.first, edge.second);
}

std::vector<std::vector<int>> Graph::detectCommunities() {
    std::vector<std::vector<int>> communities;
    Graph tempGraph = *this;

    while (tempGraph.getSize() > 0) {
        std::vector<int> community;
        int startNodeId = tempGraph.vertices.begin()->first;
        depthFirstSearch(startNodeId, tempGraph, community);
        communities.push_back(community);
        for (int nodeId : community) {
            tempGraph.vertices.erase(nodeId);
        }
    }
    return communities;
}

void Graph::depthFirstSearch(int nodeId, const Graph& graph, std::vector<int>& visited) const {
    std::stack<int> stack;
    stack.push(nodeId);
    while (!stack.empty()) {
        int currNodeId = stack.top();
        stack.pop();
        if (std::find(visited.begin(), visited.end(), currNodeId) != visited.end()) {
            continue;
        }
        visited.push_back(currNodeId);
        const Person* person = graph.getPerson(currNodeId);
        if (person) {
            for (int friendId : person->getFriends()) {
                stack.push(friendId);
            }
        }
    }
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};


std::unordered_map<std::pair<int, int>, double> Graph::calculateEdgeBetweenness() const {
    std::unordered_map<std::pair<int, int>, double> betweenness;
    for (const auto& [nodeId, _] : vertices) {
        std::unordered_map<int, std::vector<int>> shortestPaths = calculateShortestPaths(nodeId);

        for (const auto& [targetId, path] : shortestPaths) {
            for (size_t i = 0; i < path.size() - 1; ++i) {
                int fromId = path[i];
                int toId = path[i + 1];
                std::pair<int, int> edge = std::make_pair(std::min(fromId, toId), std::max(fromId, toId));
                betweenness[edge]++;
            }
        }
    }
    return betweenness;
}

std::unordered_map<int, std::vector<int>> Graph::calculateShortestPaths(int sourceId) const {
    std::unordered_map<int, std::vector<int>> shortestPaths;
    std::queue<int> queue;
    std::unordered_map<int, int> distance;
    std::unordered_map<int, int> prev;
    queue.push(sourceId);
    distance[sourceId] = 0;

    while (!queue.empty()) {
        int currNodeId = queue.front();
        queue.pop();
        const Person* currPerson = getPerson(currNodeId);
        if (currPerson) {
            for (int friendId : currPerson->getFriends()) {
                if (distance.find(friendId) == distance.end()) {
                    queue.push(friendId);
                    distance[friendId] = distance[currNodeId] + 1;
                    prev[friendId] = currNodeId;
                }
            }
        }
    }
    for (const auto& [nodeId, _] : vertices) {
        if (nodeId != sourceId) {
            std::vector<int> path;
            int currNodeId = nodeId;

            while (prev.find(currNodeId) != prev.end()) {
                path.push_back(currNodeId);
                currNodeId = prev[currNodeId];
            }
            path.push_back(sourceId);
            std::reverse(path.begin(), path.end());

            shortestPaths[nodeId] = path;
        }
    }
    return shortestPaths;
}

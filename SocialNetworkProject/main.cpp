#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "Graph.h"
#include "Person.h"

class SocialNetworkAnalyzer {
private:
    Graph socialNetwork;

public:
    SocialNetworkAnalyzer();
    void loadData(const std::string& filename);
    void displayNetwork();
    void suggestFriends();
    void calculateDegreeCentrality();
    void calculateClusteringCoefficient();
    void detectCommunities();
};

SocialNetworkAnalyzer::SocialNetworkAnalyzer() {}

void SocialNetworkAnalyzer::loadData(const std::string& filename) {
    try {
        socialNetwork = readData(filename);
        std::cout << "Data loaded." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading network data: " << e.what() << std::endl;
    }
}

void SocialNetworkAnalyzer::displayNetwork() {
    size_t size = socialNetwork.getSize();
    std::cout << "The Social Network: " << std::endl;
    std::cout << "Number of users: " << size << std::endl;
    std::cout << "*******************************" << std::endl;
    for (const auto& id_and_person : socialNetwork.getVertices()) {
        const Person* person = id_and_person.second;
        std::cout << "ID: " << person->getId() << std::endl;
        std::cout << "Name: " << person->getName() << std::endl;
        std::cout << "Age: " << person->getAge() << std::endl;
        std::cout << "Gender: " << person->getGender() << std::endl;
        std::cout << "Occupation: " << person->getOccupation() << std::endl;
        std::cout << "Friends: ";
        const std::vector<int>& friends = person->getFriends();
        for (int friendId : friends) {
            std::cout << friendId << " ";
        }
        std::cout << std::endl;
        std::cout << "*******************************" << std::endl;
    }
}

//Girvan-Newman
void SocialNetworkAnalyzer::detectCommunities() {
    int iterations;
    std::cout << "Number of iterations for Girvan-Newman: ";
    std::cin >> iterations;
    std::vector<std::vector<int>> communities = socialNetwork.girvanNewman(iterations);
    size_t numCommunities = communities.size();
    std::cout << "Communities: " << numCommunities << std::endl;
    for (size_t i = 0; i < numCommunities; ++i) {
        std::cout << "The Community " << i + 1 << " consists of: ";
        for (int personId : communities[i]) {
            std::cout << personId << " ";
        }
        std::cout << std::endl;
    }
}

void SocialNetworkAnalyzer::calculateClusteringCoefficient() {
    int personId;
    std::cout << "Enter the ID of the person: ";
    std::cin >> personId;
    double clusteringCoefficient = socialNetwork.clusteringCoefficient(personId);
    std::cout << "Clustering coefficient for " << personId << " is " << clusteringCoefficient << std::endl;
}
void SocialNetworkAnalyzer::calculateDegreeCentrality() {
    int personId;
    std::cout << "Enter the ID of the person: ";
    std::cin >> personId;
    int centrality = socialNetwork.degreeCentrality(personId);
    std::cout << "Degree centrality for " << personId << " is " << centrality << std::endl;
}

void SocialNetworkAnalyzer::suggestFriends() {
    int personId;
    int mode;
    std::cout << "Enter the ID of the person: "<< std::endl;
    std::cin >> personId;
    std::cout << "Enter the mode: " << std::endl ;
    std::cout << "1. By Common Friends" << std::endl;
    std::cout << "2. By Occupation" << std::endl;
    std::cout << "3. By Age" << std::endl;
    std::cin >> mode;
    std::vector<int> suggestedFriends = socialNetwork.suggestFriends(personId, mode);
    std::cout << "Suggested friends for person " << personId << ": ";
    for (int friendId : suggestedFriends) {
        std::cout << friendId << " ";
    }
    std::cout << std::endl;
}



int main() {
    SocialNetworkAnalyzer analyzer;
    analyzer.loadData("../social_network.csv");
    int choice;
    do {
        std::cout << "Welcome to the Social Network Analyzer" << std::endl;
        std::cout << "1. Display the social network" << std::endl;
        std::cout << "2. Suggest friends" << std::endl;
        std::cout << "3. Calculate degree centrality for any user" << std::endl;
        std::cout << "4. Calculate clustering coefficient" << std::endl;
        std::cout << "5. Detect communities using the Girvan-Newman algorithm" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                analyzer.displayNetwork();
                break;
            case 2:
                analyzer.suggestFriends();
                break;
            case 3:
                analyzer.calculateDegreeCentrality();
                break;
            case 4:
                analyzer.calculateClusteringCoefficient();
                break;
            case 5:
                analyzer.detectCommunities();
                break;
            case 6:
                std::cout << "Exit" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
        std::cout << std::endl;
    } while (choice != 6);

    return 0;
}

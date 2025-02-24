#pragma once
#ifndef SOCIALNETWORKPROJECT_PERSON_H
#define SOCIALNETWORKPROJECT_PERSON_H

#include <string>
#include <vector>

class Person {
public:
    Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends);
    Person(const Person& other);
    int getId() const;
    void setId(int id);
    std::string getName() const;
    void setName(std::string name);
    int getAge() const;
    void setAge(int age);
    std::string getGender() const;
    std::string getOccupation() const;
    void addFriend(int friend_id);
    void removeFriend(int friend_id);
    std::vector<int> getFriends() const;
    bool isFriendWith(int friend_id) const;

private:
    int id;
    std::string name;
    int age;
    std::string gender;
    std::string occupation;
    std::vector<int> friends;
};
#endif //SOCIALNETWORKPROJECT_PERSON_H

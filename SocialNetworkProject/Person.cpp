#include "Person.h"
#include <string>
#include <vector>


Person::Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends)
        : id(id), name(name), age(age), gender(gender), occupation(occupation), friends(friends) {}

Person::Person(const Person& other)
        : id(other.id),
          name(other.name),
          age(other.age),
          gender(other.gender),
          occupation(other.occupation),
          friends(other.friends) {}


int Person::getId() const {
    return id;
}

void Person::setId(int id) {
    this->id = id;
}

std::string Person::getName() const {
    return name;
}

void Person::setName(std::string name) {
    this->name = name;
}

int Person::getAge() const {
    return age;
}

void Person::setAge(int age) {
    this->age = age;
}

std::string Person::getGender() const {
    return gender;
}

std::string Person::getOccupation() const {
    return occupation;
}

void Person::addFriend(int friend_id) {
    friends.push_back(friend_id);
}

void Person::removeFriend(int friend_id) {
    friends.erase(std::remove(friends.begin(), friends.end(), friend_id), friends.end());
}

std::vector<int> Person::getFriends() const {
    return friends;
}

bool Person::isFriendWith(int friend_id) const {
    return std::find(friends.begin(), friends.end(), friend_id) != friends.end();
}

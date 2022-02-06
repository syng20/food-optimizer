#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Review.h"

using namespace std;

class User {
public:
	User(string name) : name(name) {}
private:
	string name;
	vector<string> allergies;
	vector<string> dislikes;
	vector<string> likes;
	vector<Review> revs;
};

#endif
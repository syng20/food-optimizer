#ifndef RECIPE_H
#define RECIPE_H

#include <array>
#include <string>
#include <vector>

using namespace std;

class Recipe {
public:
	Recipe(string name, double s, double c, vector<string>& i, vector<double>& a, vector<string>& u, array<double, 6>& t) : 
		name(name), skilllevel(s), cooktime(c), ingr(i), amount(a), unit(u), taste(t) {}
	string toString() {
		string ret = name + " " + to_string(skilllevel) + " ( ";
		for (int i = 0; i < (int)ingr.size(); i++) {
			ret += ingr.at(i) + "(" + to_string(amount.at(i)) + " " + unit.at(i) + ") ";
		}
		ret += ") (" + to_string(taste[0]);
		for (int i = 1; i < taste.size(); i++) {
			double d = taste[i];
			ret += " " + to_string(d);
		}
		return ret + ")";
	}
	string toString1() {
		string ret = name + " ";
		for (string s : ingr)
			ret += s + " ";
		for (double d : amount)
			ret += to_string(d) + " ";
		for (string s : unit)
			ret += s + " ";
		return ret + "]";
	}
//private:
	string name; //name of the recipe
	double skilllevel; //skill level required for dish, 5 is can kinda cook, resulting in food
	double cooktime; //in minutes
	vector<string> ingr; //ingredients for this dish
	vector<double> amount; //amount of ingredient at the same position, what this means will need to be defined (ounces or cups?)
	vector<string> unit; //units for each amount
	//https://www.usda.gov/media/blog/2017/09/26/back-basics-all-about-myplate-food-groups
	//array<double, 8> serv; //servings of food: starch(0), protein(1), vegetables(2), fruit(3), dairy(4), fat(5)
	array<double, 6> taste; //how much of each taste this food is on a scale of 1 - 10: sweet(0), sour(1), salty(2), bitter(3), savory/umami(4)
};

#endif
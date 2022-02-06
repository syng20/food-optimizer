/*
Project made for sbhacks8. Food website that optimizes to the user's tastes

#Everything is on a scale from [1, 10]
#User data: allergies, preferences (scale), cooking skill level, health (optional), calorie counting (optional)
numattru, numentru = 5, 10
userdata = [[0.0 for x in range(numattru)] for y in range(numentru)]
#Recipe data: steps to make it, specific amounts of ingredients, tools needed (kitchen appliances), budget, meal prep for more than one meal
numattrr, numentrr = 8, 10
recidata = [[0.0 for x in range(numattrr)] for y in range(numentrr)]
#Review data (of the meal we recommend): how difficult was it? too salty? too spicy? overall satisfaction. More well done? Didn't like any of the ingredients?
numattrm, numentrm = 8, 10
mealdata = [[0.0 for x in range(numattrm)] for y in range(numentrm)]
#Food preferences categories: overarching preferences for kind of food, within each category, more specific preference for stuff
*/

#include <iostream> //for cout cin console, includes cout and cin to the std
#include <iomanip> //io manipulation
#include <string> //includes various string methods, like to_string, to std
#include <vector>
#include <array>
#include <fstream>
#include <map>
#include <ctype.h>
#include "User.h"
#include "Recipe.h"

using namespace std;

//finds the next space after the next end curly
int nextSANC(string& s, int pos) {
	return s.find('}', pos) + 1;
}
//returns the string between curlies
string betwcurly(string s, int pos) {
	int begcur = s.find('{', pos);
	int endcur = s.find('}', pos);
	return s.substr(begcur + 1, endcur - begcur - 1);
}

//pos at the space before the number
double nextDou(string s, int pos) {
	int space = s.find(' ', pos + 1);
	string sub = "";
	if (space != -1)
		sub = s.substr(pos + 1, space - pos - 1);
	else
		sub = s.substr(pos + 1);
	double d = 0;
	try { d = stod(sub); }
	catch (const invalid_argument& e) { throw e; }
	catch (const out_of_range& e) { throw e; }
	return d;
}

int nextSpace(string& s, int pos) {
	return s.find(' ', pos + 1);
}

//gets the name of this item. pos would be at the space before the name started.
string getName(string s, int pos) {
	char c = s.at(pos + 1);
	string ret = "";
	if (c == '\"') {
		ret = s.substr(pos + 2, s.find('\"', pos + 2) - pos - 2);
	}
	else {
		ret = s.substr(pos + 1, s.find(' ', pos + 1) - pos - 1);
	}
	return ret;
}

//bool b for if the name was in quotations (true)
int nextNamePos(string s, int pos, bool b) {
	int i = pos;
	if (b) {
		i = s.find('\"', pos + 2);
		if (i == (int)s.size() - 1)
			return -1;
	}
	return s.find(' ', i + 1);
}

void addInIVec(vector<string>& vec, string items) {
	string name = getName(items, 0);
	vec.push_back(name);
	int nnp = 0; //next name position
	char c = items.at(1);
	if (c == '\"')
		nnp = nextNamePos(items, 0, true);
	else
		nnp = nextNamePos(items, 0, false);
	while (nnp != -1) {
		name = getName(items, nnp);
		vec.push_back(name);
		c = items.at(nnp + 1);
		if (c == '\"')
			nnp = nextNamePos(items, nnp, true);
		else
			nnp = nextNamePos(items, nnp, false);
	}
}

void addInAUVec(vector<double>& amount, vector<string>& unit, string items) {
	double d = 0;
	string s = "";
	d = nextDou(items, 0);
	amount.push_back(d);
	int s1 = nextSpace(items, 0);
	if (s1 == -1) {return;}
	int s2 = nextSpace(items, s1);
	char c = items.at(s1 + 1);
	if (!isdigit(c)) {
		s = getName(items, s1);
		unit.push_back(s);
		if (s2 != -1) {
			s1 = s2;
			s2 = nextSpace(items, s1);
		}
		else {
			return;
		}
	}
	else {
		s = "quantity";
		unit.push_back(s);
	}
	while (s2 != -1) {
		d = nextDou(items, s1);
		amount.push_back(d);
		s1 = s2;
		s2 = nextSpace(items, s1);
		c = items.at(s1 + 1);
		if (!isdigit(c)) {
			s = getName(items, s1);
			if (s2 == -1) {
				unit.push_back(s);
				return;
			}
			s1 = s2;
			s2 = nextSpace(items, s1);
		}
		else {
			s = "quantity";
		}
		unit.push_back(s);
	}
	c = items.at(s1 + 1);
	if (!isdigit(c)) {
		s = getName(items, s1);
		unit.push_back(s);
	}
	else {
		d = nextDou(items, s1);
		amount.push_back(d);
		s = "quantity";
		unit.push_back(s);
	}
}

void addInTVec(array<double, 6>& taste, string tastes) {
	double d = nextDou(tastes, 0);
	taste[0] = d;
	int ns = 0;
	for (int i = 1; i < (int)taste.size(); i++) {
		ns = nextSpace(tastes, ns);
		d = nextDou(tastes, ns);
		taste[i] = d;
	}
}

void recipeparser(map<string, Recipe>& recipes, string line) {
	string name = betwcurly(line, 0);
	int sanc = nextSANC(line, 0); //space after next (end) curly
	double skilllevel = nextDou(line, sanc);
	int ns = nextSpace(line, sanc); //next space
	double cooktime = nextDou(line, ns);
	ns = nextSpace(line, ns);
	vector<string> ingr;
	string ingrs = " " + betwcurly(line, ns);
	addInIVec(ingr, ingrs);
	sanc = nextSANC(line, ns);
	vector<double> amount;
	vector<string> unit;
	string aus = " " + betwcurly(line, sanc);
	addInAUVec(amount, unit, aus);
	sanc = nextSANC(line, sanc);
	array<double, 6> taste;
	string ts = " " + betwcurly(line, sanc);
	addInTVec(taste, ts);
	Recipe r(name, skilllevel, cooktime, ingr, amount, unit, taste);
	recipes.insert(pair<string, Recipe>(name, r));
}

void reviewparser(vector<Review>& reviews, string line) {
	string name = betwcurly(line, 0);
	int sanc = nextSANC(line, 0);
	array<double, 6> revtas;
	string ts = " " + betwcurly(line, sanc);
	addInTVec(revtas, ts);
	sanc = nextSANC(line, sanc);
	int slf = nextDou(line, sanc);
	int ns = nextSpace(line, sanc);
	int rec = nextDou(line, sanc);
	Review r(name, revtas, slf, rec);
	reviews.push_back(r);
}

template<typename K, typename V>
void print_map(map<K, V>& m)
{
	for (auto pair : m) {
		cout << "{" << pair.first << ": " << pair.second.toString() << "}\n";
	}
}

template<typename T>
void print_vector(vector<T>& v)
{
	for (T e : v) {
		cout << "{" << e.toString() << "}\n";
	}
}

//ratios so that the least popular is now 1
array<double, 6> ratioedT(array<double, 6> tastes) {
	array<double, 6> rt = { 0 };
	double d = DBL_MAX;
	for (int i = 0; i < (int)tastes.size(); i++) {
		if (tastes[i] < d && tastes[i] != 0) {
			d = tastes[i];
		}
	}
	for (int i = 0; i < (int)tastes.size(); i++) {
		rt[i] = tastes[i] / d;
	}
	return rt;
}

double arrSim(array<double, 6> rtaste, array<double, 6> ratioTT) {
	double sim = 0;
	for (int i = 0; i < (int)rtaste.size(); i++) {
		//if (rtaste[i] != 0) //penalty for 0 categories
			sim += 10 - abs(rtaste[i] - ratioTT[i]);
	}
	return sim;
}

int main() {
	/*
	ofstream: Stream class to write on files
	ifstream: Stream class to read from files
	fstream: Stream class to both read and write from/to files.
	input/output
	*/
	map<string, Recipe> recipes;
	vector<Review> reviews;
	
	string line;

	//input
	ifstream inputfile("recipes.txt");
	if (inputfile.is_open())
	{
		while (getline(inputfile, line))
		{
			recipeparser(recipes, line);
		}
		inputfile.close();
		inputfile.clear(); //clears the flags
	}
	else cout << "Unable to open input file" << endl;
	inputfile.open("reviews.txt");
	if (inputfile.is_open())
	{
		while (getline(inputfile, line))
		{
			reviewparser(reviews, line);
		}
		inputfile.close();
		inputfile.clear(); //clears the flags
	}
	else cout << "Unable to open input file" << endl;

	/*
	print_map(recipes);
	cout << endl;
	print_vector(reviews);
	*/

	array<double, 6> totaltastes = { 0 }; //initialized to zero
	for (int i = 0; i < (int)reviews.size(); i++) {
		Review r = reviews.at(i);
		for (int j = 0; j < (int)totaltastes.size(); j++) {
			totaltastes[j] += r.revtas[j] * r.recom * recipes.find(r.rname)->second.taste[j];
		}
	}
	/*
	for (double d : tastes)
		cout << d << " ";
	cout << endl;
	*/
	string bestrecipe = "";
	double msim = 0;
	array<double, 6> rtaste = { 0 };
	array<double, 6> ratioTT = ratioedT(totaltastes);
	double sim = 0;
	for (auto pair : recipes) {
		rtaste = ratioedT(pair.second.taste);
		sim = arrSim(rtaste, ratioTT);
		if (sim > msim) {
			msim = sim;
			bestrecipe = pair.first;
		}
	}

	cout << bestrecipe << endl;

	return 0;
}
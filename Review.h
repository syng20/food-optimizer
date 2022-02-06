#ifndef REVIEW_H
#define REVIEW_H

#include <array>
#include <string>
#include <vector>
#include "Recipe.h"

using namespace std;

class Review {
public:
	Review(string r, array<double, 6>& re, double s, double rec) : rname(r), revtas(re), slf(s), recom(rec) {}
	string toString() {
		string ret = rname + " (" + to_string(revtas[0]);
		for (int i = 1; i < revtas.size(); i++) {
			double d = revtas[i];
			ret += " " + to_string(d);
		}
		ret += ") " + to_string(slf) + to_string(recom);
		return ret;
	}
//private:
	string rname; //points to the recipe this review is about
	array<double, 6> revtas; //review of the taste on a scale from 1-10, 5 being just right, for each taste kind
	double slf; //skill level fit 1- 10
	double recom; //how good was this reommendation 1 - 10
};

#endif
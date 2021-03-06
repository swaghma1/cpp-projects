// RoadsAndLibraries.cpp : Defines the entry pounsigned long for the console application.
//

#include "stdafx.h"


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

unsigned long getSizeOfConnectedComp(unsigned long iCityU, vector< vector<unsigned long> > * & ipCityMap, vector<unsigned long>& iVisitStatus) {
	unsigned long nbConnection = 0;
	for (unsigned long iCityV : (*ipCityMap)[iCityU]) {
		if (0 == iVisitStatus[iCityV]) {
			iVisitStatus[iCityV] = 1;
			nbConnection++;
			nbConnection = nbConnection + getSizeOfConnectedComp(iCityV, ipCityMap, iVisitStatus);
		}
	}
	return nbConnection;
}

unsigned long roadsAndLibraries(unsigned long n, unsigned long c_lib, unsigned long c_road, vector< vector<unsigned long> > * & ipCityMap) {
	// Complete this function
	unsigned long cost = 0;
	//unsigned long libCost = 0;

	//libCost = c_lib * n;

	vector<unsigned long> visitStatus(n, 0);
	vector<unsigned long> connectedComp;
	for (unsigned long iCity = 0; iCity < n; iCity++) {
		if (0 == visitStatus[iCity]) {
			visitStatus[iCity] = 1;
			connectedComp.push_back(getSizeOfConnectedComp(iCity, ipCityMap, visitStatus));
		}
	}

	unsigned long pathCost = connectedComp.size() * c_lib;
	cout << "Size Forest" << connectedComp.size() << endl;
	for (unsigned long comp : connectedComp) {
		cost = cost + c_lib;
		if (c_lib > c_road)
			cost = cost + (c_road*comp);
		else
			cost = cost + (c_lib*comp);
		//pathCost = pathCost +min( comp* c_road, comp* c_lib);
		/*if (0 > pathCost) {
			cout << "Comp = " << comp << endl;
			cout << "pathCost of " << comp << " = " << pathCost << endl;
		}*/

	}

	//cost = min(pathCost, libCost);

	return cost;
}

unsigned long main() {
	unsigned long q;
	ifstream inputFile("input.txt");
	string line;
	if (getline(inputFile, line))
	{
		istringstream buffer(line);
		buffer >> q;
	}
	//cin >> q;
	vector< vector<unsigned long> > *  pCityMap = NULL;
	for (unsigned long a0 = 0; a0 < q; a0++) {
		unsigned long n, m, cLib, cRoad = 0;
		n = m = cLib = cRoad = 0;
		if (getline(inputFile, line))
		{
			istringstream buffer(line);
			buffer >> n >> m >> cLib >> cRoad;
		}
		pCityMap = new vector< vector<unsigned long> >(n);
		for (unsigned long iRoad = 0; iRoad < m; iRoad++) {
			unsigned long cityU, cityV = 0;
			cityU = cityV = 0;
			if (getline(inputFile, line))
			{
				istringstream buffer(line);
				buffer >> cityU >> cityV;
			}

			//cin >> cityU >> cityV;
			(*pCityMap)[cityU - 1].push_back(cityV - 1);
			(*pCityMap)[cityV - 1].push_back(cityU - 1);
		}
		unsigned long result = roadsAndLibraries(n, cLib, cRoad, pCityMap);
		cout << result << endl;
		delete pCityMap; pCityMap = NULL;
	}
	return 0;
}



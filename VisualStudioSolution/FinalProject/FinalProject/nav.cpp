﻿#include "nav.h"

NavRoutes::NavRoutes(){
}

NavRoutes::NavRoutes(Map &data) {
	this->data = data;
	size[0] = this->data.getSize('x');
	size[1] = this->data.getSize('y');
}

NavRoutes::NavRoutes(Map &data, int start[], int end[]) {
	this->data = data;
	size[0] = this->data.getSize('x');
	size[1] = this->data.getSize('y');
	setStartPoint(start[0], start[1]);
	setEndPoint(end[0], end[1]);
}

void NavRoutes::setStartPoint(int x, int y) {
	startPoint[0] = y;
	startPoint[1] = x;
	currPoint[0] = y;
	currPoint[1] = x;
}

void NavRoutes::setEndPoint(int x, int y) {
	endPoint[0] = y;
	endPoint[1] = x;
}

int const NavRoutes::getX(){
	return currPoint[0];
}

int const NavRoutes::getY(){
	return currPoint[1];
}

Map NavRoutes::getMap(){
	return data;
}

int NavRoutes::getSX(){
	return startPoint[1];
}

int NavRoutes::getSY(){
	return startPoint[0];
}

int NavRoutes::getEX(){
	return endPoint[1];
}

int NavRoutes::getEY(){
	return endPoint[0];
}

bool NavRoutes::right() {
	if (currPoint[1] + 1 < size[1]) {
		if (!data.getData(currPoint[0], currPoint[1] + 1)) {
			//cout << "r" << endl;
			currPoint[1] += 1;
			return true;
		}
	}
	return false;
}

bool NavRoutes::left() {
	if (currPoint[1] - 1 >= 0) {
		if (!data.getData(currPoint[0], currPoint[1] - 1)) {
			//cout << "l" << endl;
			currPoint[1] -= 1;
			return true;
		}
	}
	return false;
}

bool NavRoutes::down() {
	if (currPoint[0] + 1 < size[0]) {
		if (!data.getData(currPoint[0] + 1, currPoint[1])) {
			//cout << "d" <<endl;
			currPoint[0] += 1;
			return true;
		}
	}
	return false;
}

bool NavRoutes::up() {
	if (currPoint[0] - 1 >= 0) {
		if (!data.getData(currPoint[0] - 1, currPoint[1])) {
			/*cout << "u" << endl;*/
			currPoint[0] -= 1;
			return true;
		}
	}
	return false;
}

bool NavRoutes::checkColl() {
	return currPoint[0] == endPoint[0] && currPoint[1] == endPoint[1];
}

void NavRoutes::print(list<char> listdata) {

	//border
	for (int a = 0; a < data.getSize('y'); a++) cout << "-";
	cout << "--";
	cout << endl;
	list<char>::iterator iter;
	vector<array<int,2>> allloc;
	vector<char> movement;
	for (iter = listdata.begin(); iter != listdata.end(); ++iter) {
		allloc.push_back({currPoint[0],currPoint[1]});
		switch (*iter) {
			case('r'):
				right();
				break;
			case('l'):
				left();
				break;
			case('u'):
				up();
				break;
			case('d'):
				down();
				break;
		}
		movement.push_back(*iter);
	}
	for (int i = 0; i < data.getSize('x'); i++) {
		cout << "|";
		char newChar;
		for (int a = 0; a < data.getSize('y'); a++) {
			bool cond = false;
			for (int b = 0; b <allloc.size() ; b++) {
				if (i == allloc[b][0] && a == allloc[b][1]) {
					newChar = movement[b];
					cond = true;
					break;
				}
			}
			if (i == startPoint[0] && a == startPoint[1]) cout << 'S';
			else if(i == endPoint[0] && a == endPoint[1]) cout << 'E';
			else if (cond && !data.getData(i, a) && newChar == 'r') printf(">");
			else if (cond && !data.getData(i, a) && newChar == 'l') printf("<");
			else if (cond && !data.getData(i, a) && newChar == 'u') printf("^");
			else if (cond && !data.getData(i, a) && newChar == 'd') printf("v");
			else if(data.getData(i, a)) cout << '*';
			else cout << ' ';
		}
		cout << "|" << endl;
	}
	//border
	for (int a = 0; a < data.getSize('y'); a++) cout << "-";
	cout << "--";
	cout << endl;

	//reset current pos
	currPoint[0] = startPoint[0];
	currPoint[1] = startPoint[1];
}
#include <bits/stdc++.h>
using namespace std;

static const int MAP_N = 20, MAP_M = 20;
class Agent {
public:
	 Agent() : delta(), x(-1), y(-1), id(-1) {};
	void set(const int&, const int&, const int&);
	void set(const int&, const int&);
	virtual void status() = 0;
	virtual ~Agent() {
		vector<pair<int,int> >().swap(delta);
	}
	pair<int, int>getPos();
	int getId();
	vector<pair<int, int> > reach();
	vector<pair<int, int> > delta;
protected:
	int x, y, id;
	void moveByDir(int, int);
};

 class Agent1 : public Agent {
//	using Agent:: Agent;
	public:
      Agent1();
	 ~Agent1() {};
	 void status();
 };

class Agent2 : public Agent {
	//using Agent:: Agent;
	public:
	 Agent2();
	 ~Agent2() {};
	 void status();
 };

 class Agent3 : public Agent {
	//using Agent:: Agent;
	public:
	Agent3();
	~Agent3() {};
	 void status();
 };


class Map {
	vector<shared_ptr<Agent>>lista_agenti;
	vector<vector<int> > matrix;

	public:
	Map() : lista_agenti() {
		matrix = vector<vector<int>>(MAP_N, vector<int>(MAP_M, -1));
	}
	~Map();
	template <class T>void spread(const vector<pair<int, int>>&);
	void distribuire();
	void play();
	pair<int, int>make_move(const int&);
	void printMap();
	void runda();
	void PrintChanges();
};

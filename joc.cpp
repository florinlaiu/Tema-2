#include <bits/stdc++.h>
#include "joc.h"
using namespace std;
Agent1:: Agent1() {
  for(int i = -2; i <= 2; ++i)
    for(int j = -2; j <= 1; ++j)
      if(i != 0 || j != 0)
        delta.emplace_back(i, j);
}
Agent2:: Agent2() {
  for(int i = -3; i <= 2; ++i)
    for(int j = -2; j <= 2; ++j)
      if(i != 0 || j != 0)
        delta.emplace_back(i, j);
}
Agent3:: Agent3() {
  for(int i = -1; i <= 1; ++i)
    for(int j = -3; j <= 2; ++j)
      if(i != 0 || j != 0)
        delta.emplace_back(i, j);
}
void Agent1:: status() {
  cout << "Am un agent de tip 1 la pozitia : " << x << ' ' << y << '\n';
}
void Agent2:: status() {
  cout << "Am un agent de tip 2 la pozitia : " << x << ' ' << y << '\n';
}
void Agent3:: status() {
  cout << "Am un agent de tip 3 la pozitia : " << x << ' ' << y << '\n';
}
void Agent::set(const int &nx, const int &ny, const int &gid) {
  x = nx;
  y = ny;
  id = gid;
}
void Agent::set(const int &nx, const int &ny) {
  x = nx;
  y = ny;
}
pair<int, int>Agent::getPos() {
  return make_pair(x, y);
}
int Agent::getId() {
  return id;
}

void Map:: printMap() {
  // configuratia hartii
  for(auto it : lista_agenti)
    it->status ();
}

Map:: ~Map() {
  vector<shared_ptr<Agent>>().swap(lista_agenti);
  vector<vector<int>>().swap(matrix);
}

template<class T>
void Map:: spread(const vector<pair<int, int> > &positions) {
  for(auto it : positions) {
    int give_id = lista_agenti.size() + 1;
    matrix[it.first][it.second] = give_id;
    T now;
    now.set(it.first, it.second, give_id);
    lista_agenti.push_back(make_shared<T>(now));
  }
}
void Map:: distribuire() {
  vector<pair<int, int> > all;
  for(int i = 0; i < MAP_M; ++i)
    for(int j = 0; j < MAP_N; ++j)
      all.emplace_back(i, j);
  random_shuffle(begin(all), end(all));
  spread<Agent1>(vector<pair<int, int>>(all.begin(), all.begin() + 8));
  spread<Agent2>(vector<pair<int, int>>(all.begin() + 10, all.begin() + 26));
  spread<Agent3>(vector<pair<int, int>>(all.begin() + 30, all.begin() + 60));

  for(auto it : lista_agenti)
    assert(matrix[it->getPos().first][it->getPos().second] == it->getId());
}

pair<int, int>Map::make_move(const int &from) {
  pair<int, int>curr = lista_agenti[from]->getPos();
  auto newPos = [&] (int dx, int dy) ->pair<int, int> {
    return {(curr.first + dx + MAP_N) % MAP_N, (curr.second + dy + MAP_M) % MAP_M};
  };
  for(auto it : lista_agenti[from]->delta) {
    pair<int, int>going = newPos(it.first, it.second);
    if(going != curr && matrix[going.first][going.second] != -1)
      return going;
  }
  int poz = rand() % lista_agenti[from]->delta.size();
  return newPos(lista_agenti[from]->delta[poz].first, lista_agenti[from]->delta[poz].second);
}

void Map:: runda() {
  int at = rand() % lista_agenti.size();

  pair<int, int>pos_at = lista_agenti[at]->getPos();
  matrix[pos_at.first][pos_at.second] = -1;

  pair<int, int>going = make_move(at);

  if(matrix[going.first][going.second] != -1) {
    int who = rand() % 2;
    if(who == 0) {
      lista_agenti.erase(lista_agenti.begin() + at);
    } else {
      int was = matrix[going.first][going.second];
      assert(was != -1);
      cout << lista_agenti[at]->getId() << " omoara pe " << was << " la pozitia " << going.first << ' ' << going.second << '\n';
      bool found = 0;
      matrix[going.first][going.second] = lista_agenti[at]->getId();
      lista_agenti[at]->set(going.first, going.second);
      for(int i = 0; i < (int)lista_agenti.size(); ++i) {
        if(i != at && lista_agenti[i]->getId() == was) {
          found = 1;
          lista_agenti.erase(lista_agenti.begin() + i);
          break;
        }
      }
      assert(found);
    }
  }

  else {
    //cout << "Nu am omorat nimic\n";
    matrix[going.first][going.second] = lista_agenti[at]->getId();
    lista_agenti[at]->set(going.first, going.second);
  }
}
void Map:: play() {

  int moves = 0;

  while((int)lista_agenti.size() > 1) {
    ++moves;
    runda();
  }
  cout << moves;
}

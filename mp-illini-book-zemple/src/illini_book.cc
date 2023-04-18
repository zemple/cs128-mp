#include "illini_book.hpp"

#include "utilities.hpp"
#include <fstream>

using namespace std;

IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
	fstream fs_people(people_fpath);
    fstream fs_relation(relations_fpath);
	string str;
	while (getline(fs_people, str)) {
		people.push_back(stoi(str));
		vector<pair<int, string>> neighbor;
		relations[stoi(str)] = neighbor;
	}
    fs_people.close();
	while (getline(fs_relation, str)) {
		vector<string> info = utilities::Split(str, ',');
        pair<int, string> p;
        p.first = stoi(info[1]);
        p.second = info[2];
		relations[stoi(info[0])].push_back(p);
        p.first = stoi(info[0]);
        p.second = info[2];
		relations[stoi(info[1])].push_back(p);
	}
}

IlliniBook::~IlliniBook() {}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    queue<int> bfs;
    map<int, bool> visited;
    bfs.push(uin_1);
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        if (visited.find(cur) == visited.end()) {
            visited[cur] = true;
            vector<pair<int, string>> relation = relations.at(cur);
            for (size_t i = 0; i < relation.size(); i++) {
                if (relation[i].first == uin_2) {
                    return true;
                }
                bfs.push(relation[i].first);
            }
        }
    }
    return false;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    queue<int> bfs;
    map<int, bool> visited;
    bfs.push(uin_1);
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        if (visited.find(cur) == visited.end()) {
            visited[cur] = true;
            vector<pair<int, string>> relation = relations.at(cur);
            for (size_t i = 0; i < relation.size(); i++) {
                if (relation[i].second == relationship) {
                    if (relation[i].first == uin_2) {
                        return true;
                    }
                    bfs.push(relation[i].first);
                }
            }
        }
    }
    return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    queue<int> bfs;
    map<int, bool> visited;
    bfs.push(uin_1);
    map<int, int> steps;
    steps[uin_1] = 0;
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        visited[cur] = true;
        vector<pair<int, string>> relation = relations.at(cur);
        for (size_t i = 0; i < relation.size(); i++) {
            if (relation[i].first == uin_2) {
                int result = steps[cur] + 1;
                return result;
            }
            if (visited.find(relation[i].first) == visited.end()) {
                bfs.push(relation[i].first);
                visited[relation[i].first] = true;
                steps[relation[i].first] = steps[cur] + 1;
            }
        }
    }
    return -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    queue<int> bfs;
    map<int, bool> visited;
    bfs.push(uin_1);
    map<int, int> steps;
    steps[uin_1] = 0;
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        visited[cur] = true;
        vector<pair<int, string>> relation = relations.at(cur);
        for (size_t i = 0; i < relation.size(); i++) {
            if (relation[i].second == relationship) {
                if (relation[i].first == uin_2) {
                    int result = steps[cur] + 1;
                    return result;
                }
                if (visited.find(relation[i].first) == visited.end()) {
                    bfs.push(relation[i].first);
                    visited[relation[i].first] = true;
                    steps[relation[i].first] = steps[cur] + 1;
                }
            }
        }
    }
    return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    queue<int> bfs;
    map<int, bool> visited;
    bfs.push(uin);
    map<int, int> steps;
    steps[uin] = 0;
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        visited[cur] = true;
        vector<pair<int, string>> relation = relations.at(cur);
        for (size_t i = 0; i < relation.size(); i++) {
            if (visited.find(relation[i].first) == visited.end()) {
                bfs.push(relation[i].first);
                visited[relation[i].first] = true;
                steps[relation[i].first] = steps[cur] + 1;
            }
        }
    }
    vector<int> vec;
    for(auto &step : steps) {
        if (step.second == n) {
            vec.push_back(step.first);
        }
    }
    return vec;
}

size_t IlliniBook::CountGroups() const {
    map<int, bool> visited;
    map<int, int> group;
    size_t groupNum = 0;
    for (auto &r : relations) {
        queue<int> bfs;
        bfs.push(r.first);
        if (group.find(r.first) == group.end()) {
            group[r.first] = groupNum;
            groupNum++;
        }
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();
            if (visited.find(cur) == visited.end()) {
                visited[cur] = true;
                vector<pair<int, string>> relation = relations.at(cur);
                for (size_t i = 0; i < relation.size(); i++) {
                    group[relation[i].first] = groupNum;
                    bfs.push(relation[i].first);
                }
            }
        }
    }
    return groupNum;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    map<int, bool> visited;
    map<int, int> group;
    size_t groupNum = 0;
    for (auto &r : relations) {
        queue<int> bfs;
        bfs.push(r.first);
        if (group.find(r.first) == group.end()) {
            group[r.first] = groupNum;
            groupNum++;
        }
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();
            if (visited.find(cur) == visited.end()) {
                visited[cur] = true;
                vector<pair<int, string>> relation = relations.at(cur);
                for (size_t i = 0; i < relation.size(); i++) {
                    if(relation[i].second == relationship) {
                        group[relation[i].first] = groupNum;
                        bfs.push(relation[i].first);
                    }
                }
            }
        }
    }
    return groupNum;
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    map<int, bool> visited;
    map<int, int> group;
    size_t groupNum = 0;
    for (auto &r : relations) {
        queue<int> bfs;
        bfs.push(r.first);
        if (group.find(r.first) == group.end()) {
            group[r.first] = groupNum;
            groupNum++;
        }
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();
            if (visited.find(cur) == visited.end()) {
                visited[cur] = true;
                vector<pair<int, string>> relation = relations.at(cur);
                for (size_t i = 0; i < relation.size(); i++) {
                    bool found = false;
                    for (size_t j = 0; j < relationships.size(); j++) {
                        if (relation[i].second == relationships[j]) {
                            found = true;
                            break;
                        }
                    }
                    if(found) {
                        group[relation[i].first] = groupNum;
                        bfs.push(relation[i].first);
                    }
                }
            }
        }
    }
    return groupNum;
}
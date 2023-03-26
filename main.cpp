/*
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

void flip(char arr[], int i){
    char aux;
    int start = 0;
    while (start < i) {
        aux = arr[start];
        arr[start] = arr[i];
        arr[i] = aux;
        start++;
        i--;
    }
}

std::string bfs(std::string start, std::string end, int& count){
    std::queue<std::string> q;
    std::set<std::string> visited;
    q.push(start);
    visited.insert(start);

    while (!q.empty()){
        std::string curr = q.front();
        q.pop();
        count++;

        if (curr == end){
            return curr;
        }

        for (int i = 1; i < curr.size(); i++){
            std::string next = curr;
            flip(&next[0], i);
            if (visited.count(next) == 0){
                q.push(next);
                visited.insert(next);
            }
        }
    }

    return "";
}

int main(){
    std::string pancake = "abcdefghijk";
    std::string pancakeEnd = pancake;
    random_shuffle(pancake.begin(), pancake.end());
    int count = 0;
    std::string result = bfs(pancake, pancakeEnd, count);
    std::cout << "Pancake: ";
    std::cout << pancake << std::endl;
    std::cout << std::endl;
    std::cout << "Pancake ordenado: ";
    std::cout << pancakeEnd << std::endl;
    std::cout << std::endl;
    if (result != ""){
        std::cout << "Pancake resuelto: " << result << std::endl;
    }
    else {
        std::cout << "No se encontro una solucion" << std::endl;
    }
    std::cout << "Nodos visitados: " << count << std::endl;
    return 0;
}
*/

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_map>

struct State {
    std::string pancakes;
    int g;
    int h;
    int f;
    State(std::string pancakes, int g, int h) : pancakes(pancakes), g(g), h(h), f(g + h) {}
};

struct StateCompare {
    bool operator()(const State& s1, const State& s2) const {
        return s1.f > s2.f;
    }
};

void flip(std::string& str, int i) {
    std::reverse(str.begin(), str.begin() + i + 1);
}

int heuristic(const std::string& s, const std::string& end) {
    int count = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != end[i]) {
            ++count;
        }
    }
    return count;
}

std::string astar(std::string start, std::string end, int& count) {
    std::priority_queue<State, std::vector<State>, StateCompare> q;
    std::unordered_map<std::string, int> gscore;
    q.emplace(start, 0, heuristic(start, end));
    gscore[start] = 0;
    count = 0;

    while (!q.empty()) {
        State curr = q.top();
        q.pop();
        ++count;

        if (curr.pancakes == end) {
            return curr.pancakes;
        }

        for (int i = 1; i < curr.pancakes.size(); ++i) {
            std::string next = curr.pancakes;
            flip(next, i);
            int new_g = curr.g + 1;
            if (gscore.find(next) == gscore.end() || new_g < gscore[next]) {
                gscore[next] = new_g;
                int new_h = heuristic(next, end);
                State next_state(next, new_g, new_h);
                q.push(next_state);
            }
        }
    }

    return "";
}

int main() {
    std::string pancake = "abcdefghijklmnopqrstuvwxyz";
    std::cout << "Pancake: " << pancake << std::endl;
    std::string pancakeEnd = pancake;
    std::random_shuffle(pancake.begin(), pancake.end());
    std::cout << "Pancake desordenado: " << pancake << std::endl;
    int count = 0;
    std::string result = astar(pancake, pancakeEnd, count);
    std::cout << "Pancake ordenado: " << pancakeEnd << std::endl;
    if (result != "") {
        std::cout << "Pancake resuelto: " << result << std::endl;
    } else {
        std::cout << "No se encontro una solucion" << std::endl;
    }
    std::cout << "Nodos visitados: " << count << std::endl;
    return 0;
}
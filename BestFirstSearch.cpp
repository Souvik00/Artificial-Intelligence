#include <bits/stdc++.h>
using namespace std;

typedef pair<int, string> NodePair;

vector<string> best_first_search(
    unordered_map<string, vector<string>> &graph,
    string start, string goal,
    unordered_map<string, int> &heuristic
) {
    priority_queue<NodePair, vector<NodePair>, greater<NodePair>> open_list;
    open_list.push({heuristic[start], start});

    vector<string> close_list;

    while (!open_list.empty()) {
        auto [current_heuristic, current_node] = open_list.top();
        open_list.pop();

        close_list.push_back(current_node);

        if (current_node == goal)
            break;

        for (const string &neighbor : graph[current_node]) {
            if (find(close_list.begin(), close_list.end(), neighbor) == close_list.end()) {
                open_list.push({heuristic[neighbor], neighbor});
            }
        }
    }

    if (find(close_list.begin(), close_list.end(), goal) != close_list.end())
        return close_list;
    else
        return {};
}

int main() {
    unordered_map<string, vector<string>> graph = {
        {"S", {"A", "B"}},
        {"A", {"C", "D"}},
        {"B", {"E", "F"}},
        {"C", {}},
        {"D", {}},
        {"E", {"H"}},
        {"F", {"I", "G"}},
        {"H", {}},
        {"I", {}},
        {"G", {}}
    };

    unordered_map<string, int> heuristic = {
        {"S", 14},
        {"A", 12},
        {"B", 5},
        {"C", 7},
        {"D", 3},
        {"E", 8},
        {"F", 2},
        {"G", 0},
        {"H", 4},
        {"I", 9}
    };

    string start = "S", goal = "G";
    vector<string> path = best_first_search(graph, start, goal, heuristic);

    if (!path.empty()) {
        cout << "Best-First Search Path: ";
        for (const string &node : path)
            cout << node << " ";
    } else {
        cout << "No path found.";
    }

    return 0;
}

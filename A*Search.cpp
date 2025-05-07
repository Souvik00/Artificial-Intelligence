#include <bits/stdc++.h>
using namespace std;

typedef pair<int, string> NodePair;

vector<string> a_star_search(
    unordered_map<string, vector<pair<string, int>>> &graph,
    string start, string goal,
    unordered_map<string, int> &heuristic
) {
    priority_queue<NodePair, vector<NodePair>, greater<NodePair>> open_list;
    open_list.push({heuristic[start], start});

    vector<string> close_list;
    unordered_map<string, int> g_cost;

    for (const auto &node : graph)
        g_cost[node.first] = INT_MAX;

    g_cost[start] = 0;

    while (!open_list.empty()) {
        auto [current_f, current_node] = open_list.top();
        open_list.pop();

        close_list.push_back(current_node);

        if (current_node == goal)
            break;

        for (auto &[neighbor, step_cost] : graph[current_node]) {
            if (find(close_list.begin(), close_list.end(), neighbor) == close_list.end()) {
                int temp_g = g_cost[current_node] + step_cost;
                if (temp_g < g_cost[neighbor]) {
                    g_cost[neighbor] = temp_g;
                    int f_cost = temp_g + heuristic[neighbor];
                    open_list.push({f_cost, neighbor});
                }
            }
        }
    }

    if (find(close_list.begin(), close_list.end(), goal) != close_list.end())
        return close_list;
    else
        return {};
}

int main() {
    unordered_map<string, vector<pair<string, int>>> graph = {
        {"S", {{"A", 1}, {"G", 10}}},
        {"A", {{"B", 2}, {"C", 1}}},
        {"B", {{"D", 5}}},
        {"C", {{"D", 3}, {"G", 4}}},
        {"D", {{"G", 2}}},
        {"G", {}}
    };

    unordered_map<string, int> heuristic = {
        {"S", 5},
        {"A", 3},
        {"B", 4},
        {"C", 2},
        {"D", 6},
        {"G", 0}
    };

    string start = "S", goal = "G";
    vector<string> visited_nodes = a_star_search(graph, start, goal, heuristic);

    if (!visited_nodes.empty()) {
        for (const string &node : visited_nodes)
            cout << node << " ";
    } else {
        cout << "No path found.";
    }

    return 0;
}

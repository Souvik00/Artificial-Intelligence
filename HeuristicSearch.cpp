#include <bits/stdc++.h>
using namespace std;

const vector<vector<int>> GOAL_STATE = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

const vector<pair<int, int>> MOVES = {
    {0, -1}, {0, 1}, {-1, 0}, {1, 0}
};

int heuristic(const vector<vector<int>> &state) {
    int distance = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (state[i][j] != 0 && state[i][j] != GOAL_STATE[i][j])
                distance++;
    return distance;
}

bool is_goal(const vector<vector<int>> &state) {
    return state == GOAL_STATE;
}

pair<int, int> find_blank(const vector<vector<int>> &state) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (state[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

vector<vector<vector<int>>> generate_moves(const vector<vector<int>> &state) {
    vector<vector<vector<int>>> moves;
    auto [blank_row, blank_col] = find_blank(state);
    for (auto [dr, dc] : MOVES) {
        int new_row = blank_row + dr, new_col = blank_col + dc;
        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            vector<vector<int>> new_state = state;
            swap(new_state[blank_row][blank_col], new_state[new_row][new_col]);
            moves.push_back(new_state);
        }
    }
    return moves;
}

string state_to_string(const vector<vector<int>> &state) {
    string s;
    for (auto &row : state)
        for (int num : row)
            s += to_string(num) + ",";
    return s;
}

void print_state(const vector<vector<int>> &state) {
    for (auto &row : state) {
        for (int num : row)
            cout << num << " ";
        cout << endl;
    }
}

vector<vector<vector<int>>> a_star_search(const vector<vector<int>> &start_state) {
    using StateInfo = tuple<int, int, vector<vector<int>>, vector<vector<vector<int>>>>;
    priority_queue<StateInfo, vector<StateInfo>, greater<StateInfo>> open_list;
    open_list.push({heuristic(start_state), 0, start_state, {}});

    unordered_set<string> visited;

    while (!open_list.empty()) {
        auto [f, g, current_state, path] = open_list.top();
        open_list.pop();

        if (is_goal(current_state))
            return path = path, path.push_back(current_state), path;

        string state_str = state_to_string(current_state);
        if (visited.count(state_str))
            continue;

        visited.insert(state_str);

        cout << "--------------------------------------------\n";
        int idx = 0;
        vector<int> heuristic_values;

        auto moves = generate_moves(current_state);
        for (auto &move : moves) {
            if (visited.count(state_to_string(move)) == 0) {
                print_state(move);
                cout << endl;
                int h = heuristic(move) + g + 1;
                cout << "Matrix " << ++idx << " : f(n) = " << h << endl;
                heuristic_values.push_back(h);
                vector<vector<vector<int>>> new_path = path;
                new_path.push_back(current_state);
                open_list.push({h, g + 1, move, new_path});
                cout << endl;
            }
        }

        if (!heuristic_values.empty()) {
            auto min_it = min_element(heuristic_values.begin(), heuristic_values.end());
            int min_idx = distance(heuristic_values.begin(), min_it);
            cout << "Expanding Matrix: " << min_idx + 1 << " (lowest heuristic value)\n\n";
        }
    }

    return {};
}

int main() {
    vector<vector<int>> start_state = {
        {2, 8, 3},
        {1, 6, 4},
        {7, 0, 5}
    };

    for (auto &row : start_state)
        print_state({row});
    cout << "\nExpanding the Start State\n\n";

    auto solution = a_star_search(start_state);

    if (!solution.empty()) {
        cout << "--------------------------------------------\n";
        cout << "Solution found! Steps:\n";
        for (auto &step : solution) {
            print_state(step);
            cout << endl;
        }
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}

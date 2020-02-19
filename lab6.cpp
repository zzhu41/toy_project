#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Node {
public:
    vector<string> neighbors;
    string name;
    int heuristic;
};

unordered_set<string> visited;
unordered_map<string,int> cost;
unordered_map<string,int> dist;
unordered_map<string, int> matrix;
unordered_map<string, Node*> nodeList;

int numberNodes = -1, numberEdges = -1;

void parseEdge(string line) {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < line.size(); i++) {
        if (isspace(line[i])) {
            if (index1 == -1) {
                index1 = i;
            } else if (index1 != -1 && index2 == -1) {
                index2 = i;
            }
        }
    }
    string node1, node2;
    node1 = line.substr(0,index1);
    node2 = line.substr(index1+1,index2-index1-1);
    int weight = stoi(line.substr(index2+1));
    matrix[node1 + "-" + node2] = weight;
    matrix[node2 + "-" + node1] = weight;
    nodeList[node1]->neighbors.push_back(node2);
    nodeList[node2]->neighbors.push_back(node1);
}

void parseNode(string line) {
    int index;
    for (int i = 0; i < line.size(); i++) {
        if (isspace(line[i])) {
            index = i;
            break;
        }
    }
    string nameOfNode = line.substr(0, index);
    int heu = stoi(line.substr(index+1));
    Node* newNode = new Node();
    newNode->name = nameOfNode;
    newNode->heuristic = heu;
    nodeList[nameOfNode] = newNode;
}

void loadGraph(string fileName) {
    ifstream myFile;
    myFile.open(fileName);
    string line;
    int count = 0;
    if (myFile.is_open()) {
        while (getline (myFile,line)) {
            if (count == 0) {
                numberNodes = stoi(line);
            }
            if (numberNodes != -1 && count == numberNodes + 2) {
                numberEdges = stoi(line);
            } else if (count > numberNodes + 2){
                parseEdge(line);
            } else if (count > 0 && count != numberNodes + 1){
                parseNode(line);
            }
            count++;
        }
    }
}

struct greedyCompFunc
{
    bool operator()(const Node* n1, const Node* n2)
    {
        return n1->heuristic > n2->heuristic;
    }
};

struct AStarCompFunc
{
    bool operator()(const string node1, const string node2)
    {
        int f1 = cost[node1]+nodeList[node1]->heuristic;
        int f2 = cost[node2] + nodeList[node2]->heuristic;
        return f1 > f2;
    }
};

struct DijkstraCompFunc
{
    bool operator()(const string n1, const string n2)
    {
        return dist[n1] > dist[n2];
    }
};

pair<string, string> searchAlgo(string searchType, string startNode, string goalNode) {
    string path = "";
    string expandedNode = "";
    unordered_map<string, string> prev;
    if (searchType == "Greedy") {
        priority_queue<Node*, vector<Node*>, greedyCompFunc> pq;
        pq.push(nodeList[startNode]);
        string prevNode = startNode;
        while(!pq.empty()) {
            Node* tmp = pq.top();
            pq.pop();
            visited.insert(tmp->name);
            expandedNode += (tmp->name + " ");
            path += (tmp->name + " ");
            for (int i = 0; i < tmp->neighbors.size(); i++) {
                if (tmp->neighbors[i] == goalNode) {
                    expandedNode += (tmp->neighbors[i] + " ");
                    path += (tmp->neighbors[i] + " ");
                    visited.clear();
                    cout<<"Expanded Node:"<<expandedNode<<endl;
                    cout<<"Path:"<<path<<endl;
                    return make_pair(path, expandedNode);
                }
                if (find(visited.begin(), visited.end(), tmp->neighbors[i]) == visited.end()) {
                    pq.push(nodeList[tmp->neighbors[i]]);
                }
            }
        }
        visited.clear();
    } else if (searchType == "A*") {
        priority_queue<string, vector<string>, AStarCompFunc> pq;
        pq.push(startNode);
        cost[startNode] = 0;
        visited.insert(startNode);
        while(!pq.empty()) {
            string tmp = pq.top();
            pq.pop();
            visited.insert(tmp);
            expandedNode += (tmp + " ");
            if (tmp == goalNode) {
                visited.clear();
                cost.clear();
                break;
            }
            for (int i = 0; i < nodeList[tmp]->neighbors.size(); i++) {
                if (visited.find(nodeList[tmp]->neighbors[i]) == visited.end()) {
                    cost[nodeList[tmp]->neighbors[i]] = matrix[tmp+"-"+nodeList[tmp]->neighbors[i]] + cost[tmp];
                    prev[nodeList[tmp]->neighbors[i]] = tmp;
                    pq.push(nodeList[tmp]->neighbors[i]);
                }
            }
        }
    } else if (searchType == "Dijkstra"){
        priority_queue<string, vector<string>, DijkstraCompFunc> pq;
        for (auto it: nodeList) {
            if (it.first == startNode) {
                dist[it.first] = 0;
            } else {
                dist[it.first] = INT_MAX;
            }
        }
        pq.push(startNode);
        while(!pq.empty()) {
            string tmp = pq.top();
            pq.pop();
            visited.insert(tmp);
            expandedNode += (tmp + " ");
            if (tmp == goalNode) {
                visited.clear();
                dist.clear();
                break;
            }
            for (int i = 0; i < nodeList[tmp]->neighbors.size(); i++) {
                if (visited.find(nodeList[tmp]->neighbors[i]) == visited.end()) {
                    int weight = matrix[tmp+"-"+nodeList[tmp]->neighbors[i]];
                    if (dist[nodeList[tmp]->neighbors[i]] > weight + dist[tmp]) {
                        dist[nodeList[tmp]->neighbors[i]] = weight + dist[tmp];
                        prev[nodeList[tmp]->neighbors[i]] = tmp;
                        pq.push(nodeList[tmp]->neighbors[i]);
                    }
                }
            }
        }
    } else {
        cout<<"INVALID"<<endl;
    }
    vector<string> pathArr;
    string lastVisited = prev[goalNode];
    pathArr.push_back(goalNode);
    pathArr.push_back(lastVisited);
    while(lastVisited != startNode) {
        lastVisited = prev[lastVisited];
        pathArr.push_back(lastVisited);
    }
    for (int i = pathArr.size()-1; i >=0;i-- ) {
        path += (pathArr[i] + " ");
    }
    visited.clear();
    cost.clear();
    dist.clear();
    cout<<"Path Found: "<<path<<endl;
    cout<<"Expanded Node: "<<expandedNode<<endl;
    return make_pair(path, expandedNode);
}

int main() {
    string line;
    loadGraph("lab6_sample_graph.txt");
    while(true) {
        cout<<"Start Node Name: (Case Sensitive)"<<endl;
        getline(cin, line);
        string start = line;
        cout<<"Goal Node Name: (Case Sensitive)"<<endl;
        getline(cin, line);
        string goal = line;
        cout<<"Method: Greedy, A* or Dijkstra"<<endl;
        getline(cin, line);
        string method = line;
        searchAlgo(method, start, goal);
    }
}
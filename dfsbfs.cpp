#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

// forward declaration of Edge
struct Edge;


struct Node {
  string name;
  bool visited;

  // vector holding Edges of that Node
  vector<Edge> edges;

  // constructor
  Node(string nodeName){
    this->name = nodeName;
    this->visited = false;
  }

  // Adding Edge the the Node
  void addEdge(Edge& edge){
    this->edges.push_back(edge);
  }
};

struct Edge {
  string name; 
  tuple <Node*, Node*> nodes;

  Edge(string edgeName, Node* nodeA, Node* nodeB){
    this->name = edgeName;
    this->nodes = make_tuple(nodeA, nodeB); 
  }
};

// depth first search
// works on connected graphs only
void dfs(Node* node){
  node->visited = true;


  for(Edge edge : node->edges){
    if(get<0>(edge.nodes) == node){
      if(get<1>(edge.nodes)->visited == false) {

        // if first node is the current node, call dfs on the other node
        dfs(get<1>(edge.nodes));
      }
    }else {
      if(get<0>(edge.nodes)->visited == false) {

        // if first node is not the current node, call dfs on it
        dfs(get<0>(edge.nodes)); 
      }
    }
  }
}
// end of dfs

void bfs(Node* node){
  queue<Node*> nodeQueue;
  node->visited = true;

  nodeQueue.push(node);

  while (!nodeQueue.empty()) {
    Node* currentNode = nodeQueue.front();
    nodeQueue.pop();


    for (Edge edge : currentNode->edges) {
      if (get<0>(edge.nodes) == currentNode) {
      // if the first node is the current one, mark visited and enqueue the other one
        if (get<1>(edge.nodes)->visited == false) {
          get<1>(edge.nodes)->visited = true;
          nodeQueue.push(get<1>(edge.nodes));
        }
      }else {
      // if the first node is not the current one, mark this one and enqueue it
        if (get<0>(edge.nodes)->visited == false) {
          get<0>(edge.nodes)->visited = true;
          nodeQueue.push(get<0>(edge.nodes));
        }
      }
    }
  }

}
// end of bfs

int main(){

  // vectors for outputting the Nodes and Edges 
  vector<Node*> nodes;
  vector<Edge*> edges;

  // creation of Nodes
  Node nodeA("nodeA");
  nodes.push_back(&nodeA);

  Node nodeB("nodeB");
  nodes.push_back(&nodeB);

  Node nodeC("nodeC");
  nodes.push_back(&nodeC);

  Node nodeD("nodeD");
  nodes.push_back(&nodeD);

  // creation of Edges and attaching them to corresponding Nodes
  Edge edgeAB("edgeAB", &nodeA, &nodeB);
  nodeA.addEdge(edgeAB);
  nodeB.addEdge(edgeAB);
  edges.push_back(&edgeAB);

  Edge edgeAC("edgeAC", &nodeA, &nodeC);
  nodeA.addEdge(edgeAC);
  nodeC.addEdge(edgeAC);
  edges.push_back(&edgeAC);

  Edge edgeCB("edgeCB", &nodeC, &nodeB);
  nodeC.addEdge(edgeCB);
  nodeB.addEdge(edgeCB);
  edges.push_back(&edgeCB);

  Edge edgeBD("edgeBD", &nodeB, &nodeD);
  nodeB.addEdge(edgeBD);
  nodeD.addEdge(edgeBD);
  edges.push_back(&edgeBD);

  // output the Nodes and their Edges
  for(Node* &node : nodes){
    cout << "Node: " << node->name << endl;
    for(int i = 0; i < node->edges.size(); i++){
        cout << "  Edges from Node: " << node->edges[i].name << endl;
    }
  }

  cout << "==========" << endl;

  // output the Edges and their Nodes
  for(Edge* &edge: edges){
    cout << "Edge: " << edge->name << endl;
        cout << "  Nodes from Edge: " << get<0>(edge->nodes)->name << endl;
        cout << "  Nodes from Edge: " << get<1>(edge->nodes)->name << endl;
  }

  cout << "==========" << endl;
  

  cout << "Depth first search:" << endl;
  dfs(&nodeA);

  cout << "==========" << endl;

  // output the visited status of all Nodes
  cout << "Visited Nodes: " << endl;
  for(Node* &node : nodes){
    cout << "Node: " << node->name << endl;
    cout << "  Node visted?: " << node->visited << endl;
  }

  cout << "==========" << endl;

  // output the visited status of all Nodes
  cout << "set Nodes to unvisited: " << endl;
  for(Node* &node : nodes){
    node->visited = false;
    cout << "Node: " << node->name << endl;
    cout << "  Node visted?: " << node->visited << endl;
  }

  cout << "==========" << endl;

  cout << "Breadth first search:" << endl;
  bfs(&nodeA);

  cout << "==========" << endl;

  // output the visited status of all Nodes
  cout << "Visited Nodes: " << endl;
  for(Node* &node : nodes){
    cout << "Node: " << node->name << endl;
    cout << "  Node visted?: " << node->visited << endl;
  }

  return 0;
}

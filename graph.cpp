/** This is a basic implementation of a
 * graph data structure. It is undirected,
 * meaning that there is no distinction between
 * edges going from A to B and edges going from
 * B to A.
 * 
 * Author:  Giovanni Stephens
 * Date:    15/05/2022
 */

#include <iostream>
#include <vector>
#include <string>

// Node
class node {
    public:
        /** Constructor
         * 
         * @param name The name of the node
         */
        node(std::string name) {
            this->name = name;
        }
        std::string name;
        std::vector<node*> edges;
};


class graph {
    public:
        /** Constructor*/
        graph() {
            this->nodes = std::vector<node*>();
        }

        /** Adds a node to the graph
         * 
         * @param name The name of the node
         */
        void add_node(std::string name) {
            this->nodes.push_back(new node(name));
        }

        /** Finds the node with the given name
         * 
         * @param name The name of the node to find.
         */
        node* get_node(std::string name) {
            for (int i = 0; i < this->nodes.size(); i++) {
                if (this->nodes[i]->name == name) {
                    return this->nodes[i];
                }
            }
            return nullptr;
        }

        /** Adds an edge between two nodes
         * 
         * @param from The name of the node to add the edge from
         * @param to The name of the node to add the edge to
         */
        void add_edge(std::string name1, std::string name2) {
            node* n1 = this->get_node(name1);
            node* n2 = this->get_node(name2);
            n1->edges.push_back(n2);
            n2->edges.push_back(n1);
        }


        /** Prints the graph*/
        void print() {
            for (auto node : this->nodes) {
                std::cout << node->name << ": ";
                for (auto edge : node->edges) {
                    std::cout << edge->name << " ";
                }
                std::cout << std::endl;
            }
        }

        std::vector<node*> get_nodes() {
            return this->nodes;
        }
        
    private:
        std::vector<node*> nodes;
};


int main() {
    graph g;
    g = graph();
    g.add_node("A");
    g.add_node("B");
    g.add_node("C");

    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "C");

    g.print();

    return 0;
}

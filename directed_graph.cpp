/** This is a basic directed graph implementation.
 * 
 * Author:  Giovanni Stephens
 * Date:    16/05/2022
 */

#include <iostream>
#include <vector>
#include <string>

class vertex {
    public:
        vertex(std::string name) {
            this->name = name;
        }
        std::string name;
        std::vector<vertex*> edges;
};

class graph {
    public:
        graph() {
            this->vertices = std::vector<vertex*>();
        }

        void add_vertex(std::string name) {
            vertex* v = new vertex(name);
            this->vertices.push_back(v);
        }

        void add_edge(std::string v1, std::string v2) {
            for (int i = 0; i < this->vertices.size(); i++) {
                if (this->vertices[i]->name == v1) {
                    for (int j = 0; j < this->vertices.size(); j++) {
                        if (this->vertices[j]->name == v2) {
                            this->vertices[i]->edges.push_back(this->vertices[j]);
                        }
                    }
                }
            }
        }

        void print_graph() {
            for (int i = 0; i < this->vertices.size(); i++) {
                std::cout << this->vertices[i]->name << ": ";
                for (int j = 0; j < this->vertices[i]->edges.size(); j++) {
                    std::cout << this->vertices[i]->edges[j]->name << " ";
                }
                std::cout << std::endl;
            }
        }
    private:
        std::vector<vertex*> vertices;
};

int main() {
    graph g;
    g = graph();
    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");

    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "C");

    g.print_graph();

    return 0;
}
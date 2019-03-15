/*
 * node_dists.hpp
 * Class header to calculate distances between graph nodes
 *
 * Some code modified from DBGWAS by Jacob L., Jaillard M., Lima L.
 * Please cite:
 *  Magali Jaillard, Maud Tournoud, Leandro Lima, Vincent Lacroix,
 *  Jean-Baptiste Veyrieras and Laurent Jacob, "Representing Genetic
 *  Determinants in Bacterial GWAS with Compacted De Bruijn Graphs", 2017,
 *  Cold Spring Harbor Labs Journals, doi:10.1101/113563.
 *  (url: http://www.biorxiv.org/content/early/2017/03/03/113563)
 *
 *  This code: John Lees
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/subgraph.hpp>

using namespace std;

//vertex informations
struct VertexInfo {
    string name;
    int length;
    int id;
};

//edge informations
struct EdgeInfo {
    int id;
    int weight;
};

// Use recommended typedefs
typedef boost::property<boost::vertex_index_t, std::size_t, VertexInfo> vertex_prop;
typedef boost::property<boost::edge_index_t, std::size_t, EdgeInfo> edge_prop;
typedef boost::adjacency_list <boost::setS, boost::vecS, boost::directedS, vertex_prop, edge_prop> adjlist_t;
typedef boost::subgraph< adjlist_t > graph_t;
typedef boost::graph_traits<adjlist_t>::vertex_descriptor MyVertex;
typedef boost::graph_traits<adjlist_t>::edge_descriptor MyEdge;

class Cdbg
{
   public:
        // Initialisation
        Cdbg(const string& dbgPrefix);
        Cdbg(const string& nodeFile, const string& edgeFile);

        // Non-modifying operations
        MyVertex get_vertex(const string& sequence) { return vertex(_seqs[sequence], _dbgGraph); }

        // Modifying operations
        vector<int> node_distance(const string& origin);

   protected:
      graph_t _dbgGraph;
      unordered_map<string, int> _seqs;
};

long int getNbLinesInFile(const string &filename);

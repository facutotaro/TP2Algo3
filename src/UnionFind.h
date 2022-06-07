#ifndef EJ2_UNIONFIND_H
#define EJ2_UNIONFIND_H

#include <vector>

using namespace std;

class UnionFind{
    public:
        UnionFind(int n);
        void makeSet(int n);
        int findSet(int j);
        void unionLink(int j, int k);
        void cambiarRaiz(int j);
        void reestablecer();
    
    private:
        vector<vector<int>> _parent;
        vector<int> _ranks;
};

#endif //EJ2_UNIONFIND_H

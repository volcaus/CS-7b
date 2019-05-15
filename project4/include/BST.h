
class BST {

public:

    struct node {

            int num;
            int den;
            int level;

            double value() {return double(num)/ double(den);}
            int getLevel() {return level;}

            node* left = NULL;
            node* right = NULL;
            node* parent;

            node(int n, int d);
    };

    BST(int lvl = 0);

    node* lowest();
    node* highest();
    node* find(int n, int d);

    void generate(int lvl);
    void addNode(int n, int d);

private:
    node* rootptr;
    int level;

};
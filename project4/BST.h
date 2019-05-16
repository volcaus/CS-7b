class BST {
private:
    int startN;
    int startD;
    int level;

    struct Node {
            Node(int n = 0, int d = 0, Node* parent = nullptr);

            int num;
            int den;
            int level = 0;

            double value() {return double(num) / double(den);}
            int getLevel() {return level;}

            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent;
    };

    Node root;
    Node* rootptr = &root;
    Node* currentptr = rootptr;

public:
    BST(int n = 0, int d = 0, int lvl = 0);

    Node* getRoot() {return (rootptr = nullptr ? nullptr : rootptr);}
    Node* getCurrent() {return (currentptr = nullptr ? nullptr : currentptr);}
    void setRoot(Node* n) {rootptr = n;}
    void setCurrent(Node* n) {currentptr = n;}
    Node* lowest(Node*);
    Node* highest(Node*);
    Node* find(int, int);
    Node* step(Node*, int);

    Node* addNode(double, double, Node*);
};
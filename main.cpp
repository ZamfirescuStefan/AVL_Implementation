#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

Node* newNode(int key)
{
    Node* node = new Node();

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return(node);

}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

int GetBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = GetBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValue( Node* n)
{
    Node *min = n;

    while( min -> left != NULL)
        min -> left = min -> left;

    return min;

}

Node* deleteNode(Node* node, int key)
{

    if (node == NULL)
        return node;

    if ( key < node -> key )
        node->left = deleteNode(node -> left, key);

    else if( key > node -> key )
        node -> right = deleteNode(node -> right, key);

    else
    {
        if( (node -> left == NULL) || (node -> right == NULL) )
        {
            Node *temp = NULL;
            if (node -> left  != NULL )
                temp = node -> left;
            else
                temp = node -> right;

            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;

            delete temp;
        }
        else
        {
            Node* temp = minValue(node -> right);

            node -> key = temp -> key;

            node -> right = deleteNode(node -> right, temp -> key);
        }
    }

    if (node == NULL)
        return node;

    node -> height = 1 + max(height(node -> left),
                             height(node -> right));

    int balance = GetBalance(node);

    if (balance > 1 && GetBalance(node -> left) >= 0)
        return rightRotate(node);

    if (balance > 1 && GetBalance(node -> left) < 0)
    {
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }

    if (balance < -1 && GetBalance(node -> right) <= 0)
        return leftRotate(node);

    if (balance < -1 && GetBalance(node -> right) > 0)
    {
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }
    return node;
}
void preOrder(Node *node)
{
    if(node != NULL)
    {
        cout << node -> key << " ";
        preOrder(node -> left);
        preOrder(node -> right);
    }
}

void afis_crescator(Node *node )
{
    if( node != NULL )
    {
        afis_crescator(node -> left);
        cout << node -> key << " ";
        afis_crescator(node -> right);
    }
}

Node *findMaxim ( Node *root){

    while( root -> right )
        root = root -> right;

    return root;

}

void findPredecessor (Node *node, Node *&pred, int key){

    if(node == NULL){
        pred = NULL;
        return ;
    }

    if ( node -> key == key ){

        if ( node -> left != NULL )
            pred = findMaxim(node -> left);

    }
    else
    if ( node -> key > key )    
        findPredecessor(node -> left,pred, key);
    else                   
    {
        pred = node;
        findPredecessor(node -> right, pred, key);
    }

}

void findSuccessor(Node *node, Node *&succ, int key)
{
    if(node == NULL)
    {
        succ = NULL;
        return ;
    }

    if( node -> key == key )
    {
        if(node -> right != NULL)
            succ = minValue(node -> right);

    }
    else
    if(node -> key < key)
        findSuccessor(node -> right, succ, key);
    else
    {
        succ = node;
        findSuccessor(node -> left, succ, key);
    }

}
void wait(){
    char go_next;
    std::cout << "\n\n\n";
    std::cout << "Press any key to continue...\n";
    std::cin >> go_next;
    cin.get();
}
Node *root = NULL;
void menu() {
    bool run = true;
    int option;
    while(run) {
        system("clear");
        if(root != NULL) {
            std::cout << "The AVL is:\n";
            afis_crescator(root);
            std::cout << '\n';
        }
        std::cout << "Options:\n";
        std::cout << "1) Add a new number.\n";
        std::cout << "2) Delete a number number.\n";
        std::cout << "3) Show preorder\n";
        std::cout << "4) Show predecesor of a number \n";
        std::cout << "5) Show successor of a number \n";
        std::cout << "0) Exit.\n\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        int number; 
        if (option == 1){
            system("clear");
            std::cout << "                          --- Insert a number --- \n\n\n";
            std::cout << "Enter a number: ";
            std::cin >> number;
            root = insert(root, number);
            
            system("clear");
        }
        if (option == 2){
            system("clear");
            std::cout << "                          --- Delete a number --- \n\n\n";
            std::cout << "Enter a number: ";
            std::cin >> number;
            root = deleteNode(root, number);
            
            system("clear");
        }
        if (option == 3){
            system("clear");
            std::cout << "                          --- The preorder is  --- \n\n\n";
            afis_crescator(root);
            wait();
            system("clear");
        }
        if (option == 4){
            system("clear");
            std::cout << "The predecessor of a number \n\n\n";
            std::cout << "Enter a number: ";
            std::cin >> number;
            system("clear");
            Node *pred = NULL;
            findPredecessor(root, pred, number);
            if (pred)
                std::cout << "The predecessor of " << number << " is " << pred -> key << "\n";
            else
                std::cout << number << "This item has no predecessor \n";
            
            wait();
            system("clear");
        }
        if (option == 5){
            system("clear");
            std::cout << "The successor of a number \n\n\n";
            
            std::cout << "Enter a number: ";
            std::cin >> number;
            system("clear");
            Node *pred = NULL;
            Node *succ = NULL;
            findSuccessor(root, succ, number);
            if ( succ )
                cout << "The succesor of " << number << " is " << succ -> key << "\n";
            else
                cout << number << "This item has no successor \n";

            wait();

            system("clear");
        }
        if (option == 0) {
            system("clear");
            std::cout << "The Program has ended...\n\n\n";
            run = false;
        }
        
    }
}
int main () {
    
    menu();
    
}

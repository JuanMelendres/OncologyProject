#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//AVL tree node 
struct Node { 
    int key; 
    char nombre[30];
    char apellidos[30];
    char cancer[30];
    char medicamento[25];
    bool habilitado;
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
  
//Function to get height of the tree 
int height(struct Node* N) { 
    if (N == NULL) {
        return 0; 
    }
    return N->height; 
} 
  
//Function to get maximum of two integers 
int max(int a, int b) { 
    return (a > b)? a : b; 
} 
  
//Helper function that allocates a new node
struct Node* newNode(int key, char nom[30], char ape[30], char cancer[30], char med[25]) { 
    struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
    node->key = key;
    strcpy(node->nombre, nom);
    strcpy(node->apellidos, ape);
    strcpy(node->cancer, cancer);
    strcpy(node->medicamento, med);
    node->habilitado = true;
    node->left = NULL; 
    node->right = NULL; 
    node->height = 1;
    return(node); 
} 
  
//A utility function to right rotate subtree rooted with y 
struct Node* rightRotate(struct Node* y) { 
    struct Node* x = y->left; 
    struct Node* T2 = x->right;  
    x->right = y; 
    y->left = T2; 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
    return x; 
} 
  
//A utility function to left rotate subtree rooted with x 
struct Node* leftRotate(struct Node* x) { 
    struct Node* y = x->right; 
    struct Node* T2 = y->left;  
    y->left = x; 
    x->right = T2; 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
    return y; 
} 
  
//Get Balance factor of node N 
int getBalance(struct Node* N) { 
    if (N == NULL) {
        return 0; 
    }
    return height(N->left) - height(N->right); 
} 
  
struct Node* insert(struct Node* node, int key, char nom[30], char ape[30], char cancer[30], char med[25]) { 
    if (node == NULL) {
        return(newNode(key, nom, ape, cancer, med)); 
    }
    if (key < node->key) {
        node->left  = insert(node->left, key, nom, ape, cancer, med); 
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, nom, ape, cancer, med); 
    }
    else {
        return node; 
    }
    //Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right)); 
    //Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node); 
    //If this node becomes unbalanced, then there are 4 cases 
    //Left Left Case 
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node); 
    }
    //Right Right Case 
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node); 
    }
    //Left Right Case 
    if (balance > 1 && key > node->left->key) { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
    //Right Left Case 
    if (balance < -1 && key < node->right->key) { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
    return node; 
} 

//Find a specific node's key in the tree 
struct Node* find(struct Node* root, int key) {
    if(root == NULL) {
        return NULL;
    }
    if(key < root->key) {
        return find(root->left, key);
    }
    else if(key > root->key){
        return find(root->right, key);
    }
    return root;
}

//find a node and return true if is in the tree
bool findKey(struct Node* root, int key) {
    if(root == NULL) {
        return NULL;
    }
    if(key < root->key) {
        return find(root->left, key);
    }
    else if(key > root->key){
        return find(root->right, key);
    }
    return true;
}

//Find minimum node's key
struct Node* findMin(struct Node* root) {
    if(root == NULL) {
        return NULL;
    }
    else if(root->left == NULL) {
        return root;
    }
    else
        return findMin(root->left);
}
 
//Find maximum node's key
struct Node* findMax(struct Node* root) {
    if(root != NULL) {
        while(root->right != NULL) {
            root = root->right;
        }
    }
    return root;
}

//Get key of a node
int get(struct Node* root) {
    return root->key;
} 

//Computes the number of nodes in a tree.
int avlSize(struct Node* root)  {   
    if (root == NULL) { 
        return 0; 
    }
    else {  
        return(avlSize(root->left) + 1 + avlSize(root->right));   
    }
} 

//Enable Node
void enableNode(struct Node* node, int id) {
    struct Node* current = find(node, id); 
    if (current->habilitado == false) {
        current->habilitado = true;
    }
}

//Disable Node
void disableNode(struct Node* node, int id) {
    struct Node* current = find(node, id); 
    if (current->habilitado == true) {
        current->habilitado = false;
    }
}

//Given a non-empty binary search tree, return the node with minimum key value found in that tree
struct Node* minValueNode(struct Node* node) { 
    struct Node* current = node; 
    while (current->left != NULL) {
        current = current->left; 
    }
    return current; 
} 
  
//Recursive function to delete a node with given key
struct Node* deleteNode(struct Node* root, int key) { 
    if (root == NULL) {
        return root; 
    }
    //If the key to be deleted is smaller than the root's key
    if (key < root->key) {
        root->left = deleteNode(root->left, key); 
    }
    //If the key to be deleted is greater than the root's key
    else if(key > root->key) {
        root->right = deleteNode(root->right, key); 
    }
    //if key is same as root's key, then This is the node to be deleted 
    else { 
        //node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ) { 
            struct Node *temp = root->left ? root->left : root->right; 
            //No child case 
            if (temp == NULL) { 
                temp = root; 
                root = NULL; 
            } 
            else { //One child case 
                *root = *temp; //Copy the contents of the non-empty child
            } 
            free(temp); 
        } 
        else{ 
            //node with two children: Get the inorder 
            //successor (smallest in the right subtree) 
            struct Node* temp = minValueNode(root->right); 
            //Copy the inorder successor's data to this node 
            root->key = temp->key; 
            //Delete the inorder successor 
            root->right = deleteNode(root->right, temp->key); 
        } 
    }
    //If the tree had only one node then return 
    if (root == NULL) {
      return root; 
    }
    //STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), height(root->right)); 
    //STEP 3: GET THE BALANCE FACTOR OF THIS NODE
    int balance = getBalance(root); 
    //If this node becomes unbalanced, then there are 4 cases Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root); 
    }
    //Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0) { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
    //Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root); 
    }
    //Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
    return root; 
} 

//Function to change data in the AVL Tree
struct Node* changeKey(struct Node* root, int id, char nom[30], char ape[30], char cancer[30], char med[25]) { 
    root = deleteNode(root, id); 
    root = insert(root, id, nom, ape, cancer, med); 
    return root; 
}

//Print preOrder traversal of the tree.
void preOrder(struct Node* root) {
    if (root == NULL) {
        return; 
    }
    if (root->habilitado != false){
        printf(" %d ", root->key); 
        printf("%s ", root->nombre);
        printf("%s ", root->apellidos);
        printf("%s ", root->cancer);
        printf("%s ", root->medicamento);
        printf("\n");
    } 
    preOrder(root->left);   
    preOrder(root->right); 
} 

//Print inOrder traversal of the tree.
void inOrder(struct Node* root) {
    if (root == NULL) {
        return; 
    }
    inOrder(root->left); 
    if (root->habilitado != false){
        printf(" %d ", root->key); 
        printf("%s ", root->nombre);
        printf("%s ", root->apellidos);
        printf("%s ", root->cancer);
        printf("%s ", root->medicamento);
        printf("\n");
    }   
    inOrder(root->right); 
} 

//Print postOrder traversal of the tree.
void postOrder(struct Node* root) {
    if (root == NULL) {
        return; 
    }     
    postOrder(root->left); 
    postOrder(root->right);
    if (root->habilitado != false){
        printf(" %d ", root->key); 
        printf("%s ", root->nombre);
        printf("%s ", root->apellidos);
        printf("%s ", root->cancer);
        printf("%s ", root->medicamento);
        printf("\n");
    }
}

//Print nodes at a given level
void givenLevel(struct Node* root, int level) { 
    if (root == NULL) {
        return; 
    }
    if (level == 1) {
        if (root->habilitado != false){
            printf(" %d ", root->key); 
            printf("%s ", root->nombre);
            printf("%s ", root->apellidos);
            printf("%s ", root->cancer);
            printf("%s ", root->medicamento);
            printf("\n");
        }
    }
    else if (level > 1) { 
        givenLevel(root->left, level-1); 
        givenLevel(root->right, level-1); 
    } 
} 

//Function to print level order traversal a tree
void levelOrder(struct Node* root) { 
    int h = height(root); 
    for (int i = 1; i <= h; i++) 
        givenLevel(root, i); 
}

//Function to print REVERSE level order traversal a tree
void reverseLevelOrder(struct Node* root) { 
    int h = height(root); 
    for (int i = h; i >= 1; i--) {
        givenLevel(root, i); 
    }
} 

//Print DFS traversal of the tree.
void DFS(struct Node* root) {
    if (root){
        if (root->left){
            DFS(root->left);
        }
        if (root->right){
            DFS(root->right);
        }
        printf("%d ", root->key); 
        printf("%s ", root->nombre);
        printf("%s ", root->apellidos);
        printf("%s ", root->cancer);
        printf("%s \n", root->medicamento);
    }
}

//This function stores a tree in a file
void serialize(struct Node* root, FILE *fp) { 
    if (root == NULL) { 
        return; 
    } 
    if (root->habilitado != false) {
        fprintf(fp, "%d ", root->key); 
        fprintf(fp, "%s ", root->nombre);
        fprintf(fp, "%s ", root->apellidos);
        printf("%s ", root->cancer);
        fprintf(fp, "%s \n", root->medicamento);
        serialize(root->left, fp); 
        serialize(root->right, fp); 
    }
} 

//Print range of node of the tree.
void printRange(struct Node *root, int k1, int k2) { 
    if (NULL == root) {
        return; 
    }
    if (k1 < root->key) {
        printRange(root->left, k1, k2); 
    }
    if (k1 <= root->key && k2 >= root->key) {
        printf("%d ", root->key); 
        printf("%s ", root->nombre);
        printf("%s ", root->apellidos);
        printf("%s ", root->cancer);
        printf("%s \n", root->medicamento);
    }
    if (k2 > root->key) {
        printRange(root->right, k1, k2); 
    }
}

//for sorting alphabetically
void alphabetic(struct Node *root){
    if(root != NULL){
        alphabetic(root->left);
        if (root->habilitado != false){
            printf(" %d ", root->key); 
            printf("%s ", root->nombre);
            printf("%s ", root->apellidos);
            printf("%s ", root->cancer);
            printf("%s ", root->medicamento);
            printf("\n");
        }
        alphabetic(root->right);
    }
}

static int myCompare (const void * a, const void * b) { 
    return strcmp (*(const char **) a, *(const char **) b); 
} 
  
void sort(const char *arr[], int n) { 
    qsort (arr, n, sizeof (const char *), myCompare); 
} 
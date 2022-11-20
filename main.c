#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

// A struct being an item in a particular category.
typedef struct itemNode {

  char name[31];
  int count;
  struct itemNode *left, *right;

} itemNode;

// A struct being a category name.
typedef struct treeNameNode {

  char treeName[31];
  struct treeNameNode *left, *right;
  itemNode *theTree;

} treeNameNode;

FILE *inPtr, *outPtr;

// This function creates a tree name node being a category name for a BST of items.
treeNameNode* createTreeNameNode() {

  treeNameNode *node = (treeNameNode*)malloc(sizeof(treeNameNode));

  char name[31];
  fscanf(inPtr, "%s", name);
  
  strcpy(node->treeName, name);
  node->left = NULL;
  node->right = NULL;
  node->theTree = NULL;

  return node;

}

// This function creates an item node being an item under a category node.
itemNode* createItemNode() {

  itemNode *node = (itemNode*)malloc(sizeof(itemNode));

  char name[31];
  int count;
  fscanf(inPtr, "%s", name);
  fscanf(inPtr, "%d", &count);
  
  strcpy(node->name, name);
  node->count = count;
  node->left = NULL;
  node->right = NULL;

  return node;

}

// This function creates and builds a BST for the tree name nodes or categories.
treeNameNode* buildNameTree(treeNameNode *root, treeNameNode *node) {

  // Case when the BST is empty.
  if (root == NULL) {

    return node;

  }

  // Go left if the node data is smaller than the current node in ASCII or go right otherwise.
  if (strcmp(root->treeName, node->treeName) > 0) {

    // Keep traversing to the left side until the condition is met (Reaches a leaf node) and adds the node to the tree.
    if (root->left != NULL) {

      root->left = buildNameTree(root->left, node);

    }

    else {

      root->left = node;

    }

  }

  else {

    // Keep traversing to the right side until the condition is met (Reaches a leaf node) and adds the node to the tree.
    if (root->right != NULL) {

      root->right = buildNameTree(root->right, node);

    }

    else {

      root->right = node;

    }

  }

  return root;

}

// This function creates and builds an BST for the item nodes.
itemNode* buildItemTree(itemNode *root, itemNode *node) {

  // Case when the BST is empty.
  if (root == NULL) {

    return node;

  }

  // Go left if the node data is smaller than the current node in ASCII or go right otherwise.
  if (strcmp(root->name, node->name) > 0) {

    // Keep traversing to the left side until the condition is met (Reaches a leaf node) and adds the node to the tree.
    if (root->left != NULL) {

      root->left = buildItemTree(root->left, node);

    }

    else {

      root->left = node;

    }

  }

  else {

    // Keep traversing to the right side until the condition is met (Reaches a leaf node) and adds the node to the tree.
    if (root->right != NULL) {

      root->right = buildItemTree(root->right, node);

    }

    else {

      root->right = node;

    }

  }

  return root;

}

// This function returns a node with the smallest value in ASCII of the item BST. (Also can be used for minimum of subtrees)
itemNode* minValueItemNode(itemNode *root) {

  // Case if BST is empty.
  if (root == NULL) {

    return root;

  }

  // Keep traversing to the left until a node with no left child is reached because of how BST are structured.
  if (root->left != NULL) {

    return minValueItemNode(root->left);

  }

  return root;

}

// This function returns a node with the smallest value in ASCII of the tree name BST. (Also can be used for minimum of subtrees)
treeNameNode* minValueTreeNameNode(treeNameNode *root) {

  // Case if BST is empty.
  if (root == NULL) {

    return root;

  }

  // Keep traversing to the left until a node with no left child is reached because of how BST are structured.
  if (root->left != NULL) {

    return minValueTreeNameNode(root->left);

  }

  return root;

}

// This function deletes a node of an item BST. The argument node is the node you wish to delete.
itemNode* deleteItemNode(itemNode *root, itemNode *node) {

  // Case if BST is empty or the node doesn't exist in the item BST.
  if (root == NULL) {

    return root;

  }

  // Conditionals if the node is smaller or larger than the current node in ASCII and traverse through the nodes if they are met.
  if (strcmp(root->name, node->name) > 0) {

    root->left = deleteItemNode(root->left, node);

  }

  else if (strcmp(root->name, node->name) < 0) {

    root->right = deleteItemNode(root->right, node);

  }

  // If the node has been found.
  else {

    // The two conditionals checks if the node found has one child (Works for the nodes with no children) and deletes accordingly.
    if (root->left == NULL) {

      itemNode *temp = root->right;
      free(root);
      return temp;

    }

    else if (root->right == NULL) {

      itemNode *temp = root->left;
      free(root);
      return temp;

    }

    // This deletion method are for nodes with two children.
    else {

      // Finds the minimum value of the right subtree of the node target.
      // Copies the data of temp into the target node and removes the original temp node.
      itemNode *temp = minValueItemNode(root->right);
      strcpy(root->name, temp->name);
      root->count = temp->count;
      root->right = deleteItemNode(root->right, temp);

    }

  }

  return root;

}

// This function deletes a node of a tree name BST. The argument node is the node you wish to delete.
treeNameNode* deleteTreeNameNode(treeNameNode *root, treeNameNode *node) {

  // Case if BST is empty or the node doesn't exist in the tree name BST.
  if (root == NULL) {

    return root;

  }

  // Conditionals if the node is smaller or larger than the current node in ASCII and traverse through the nodes if they are met.
  if (strcmp(root->treeName, node->treeName) > 0) {

    root->left = deleteTreeNameNode(root->left, node);

  }

  else if (strcmp(root->treeName, node->treeName) < 0) {

    root->right = deleteTreeNameNode(root->right, node);

  }

  // If the node has been found.
  else {

    // The two conditionals checks if the node found has one child (Works for the nodes with no children) and deletes accordingly.
    if (root->left == NULL) {

      treeNameNode *temp = root->right;
      free(root);
      return temp;

    }

    else if (root->right == NULL) {

      treeNameNode *temp = root->left;
      free(root);
      return temp;

    }

    // This deletion method are for nodes with two children.
    else {

      // Finds the minimum value of the right subtree of the node target.
      // Copies the data of temp into the target node and removes the original temp node.
      treeNameNode *temp = minValueTreeNameNode(root->right);
      strcpy(root->treeName, temp->treeName);
      root->theTree = temp->theTree;
      root->right = deleteTreeNameNode(root->right, temp);

    }

  }

  return root;

}

// Deletes the entire item BST of a tree name node.
void deleteTree(itemNode *root) {

  // Uses a post order type of recursion to free all of the item nodes.
  if (root != NULL) {

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);

  }

}

// This function calculates the total number of items in a tree name node.
int countItems(itemNode *root) {

  // Adds the root, left, and right nodes recursively.
  if (root != NULL) {
    
    return root->count + countItems(root->left) + countItems(root->right);

  }

  return 0;

}

// This function searches for a particular tree name node with the name target as one of the arguments.
treeNameNode* searchNameNode(treeNameNode *root, char name[31]) {

  // Function only work when the tree name BST isn't empty or reaches it if the node isn't found.
  if (root != NULL) {

    // The conditionals practically uses binary search to reach the target node.
    if (strcmp(root->treeName, name) > 0) {

      return searchNameNode(root->left, name);

    }

    else if (strcmp(root->treeName, name) < 0) {

      return searchNameNode(root->right, name);

    }

    else {

      return root;

    }

  }

  return root;
  
}

// This function searches for a particular item node with the name target as one of the arguments.
itemNode* searchItemNode(itemNode *root, char name[31]) {

  // Function only work when the item BST isn't empty or reaches it if the node isn't found.
  if (root != NULL) {

    // The conditionals practically uses binary search to reach the target node.
    if (strcmp(root->name, name) > 0) {

      return searchItemNode(root->left, name);

    }

    else if (strcmp(root->name, name) < 0) {

      return searchItemNode(root->right, name);

    }

    else {

      return root;

    }

  }

  return root;
  
}

// This function calculates the total number of items before the node in an item BST. (The target node is one of the arguments)
int itemsBefore(itemNode *root, itemNode *node) {

  // Function only works if the BST isn't empty.
  // If it reaches a leaf node, don't count the NULL nodes after.
  if (root != NULL) {

    // Traverse to the left of the target node or traverse through all of the smaller nodes if the target node is the root node of the BST.
    if (strcmp(root->name, node->name) >= 0) {
        
      return itemsBefore(root->left, node);

    }

    // The smaller nodes are addes and taken care of and the add 1 each time you traverse to the right.
    else {

      return 1 + itemsBefore(root->left, node) + itemsBefore(root->right, node);

    }
    
  }

  return 0;

}

// This function calculates the height of a BST.
int height(itemNode *root) {

  // Height is -1 if there are no nodes of a BST or subtrees.
  if (root == NULL) {

    return -1;

  }
  
  else {

    // Saves the left height and right height of a BST.
    int left = height(root->left);
    int right = height(root->right);

    // It will compare the current left and right heights of the subtrees on the same level and will add 1 to the larger value and the root of the subtree returns that value. (The height of a BST is the longest path from the root to a leaf)
    if (left > right) {

    return left + 1;

    }

    else {

      return right + 1;

    }

  }

}

// This function will go through the whole tree name BST and print them in order using the in order recursion.
void traverse_in_traverseTreeName(treeNameNode *root) {

  if (root != NULL) {
    
    traverse_in_traverseTreeName(root->left);
    printf("%s ", root->treeName);
    fprintf(outPtr, "%s ", root->treeName);
    traverse_in_traverseTreeName(root->right);

  }

}

// This function will go through the whole item BST and print them in order using the in order recursion.
void traverse_in_traverseItem(itemNode *root) {

  if (root != NULL) {
    
    traverse_in_traverseItem(root->left);
    printf("%s ", root->name);
    fprintf(outPtr, "%s ", root->name);
    traverse_in_traverseItem(root->right);

  }

}

// This function is only used to maintain the formatting of the output code.
void traverse_in_traverse(treeNameNode *root) {

  if (root != NULL) {
    
    traverse_in_traverse(root->left);
    printf("===%s===\n", root->treeName);
    fprintf(outPtr, "===%s===\n", root->treeName);
    traverse_in_traverseItem(root->theTree);
    printf("\n");
    fprintf(outPtr, "\n");
    traverse_in_traverse(root->right);

  }

}

// This function frees all of the item BST and its respective tree name node. (Uses post order recursion so that freeing the dynamically allocated memory won't cause memory leaks).
void freeAllTrees(treeNameNode *root) {

  if (root != NULL) {

    freeAllTrees(root->left);
    freeAllTrees(root->right);
    deleteTree(root->theTree);
    free(root);

  }
  
}

int main(void) {

  atexit(report_mem_leak);

  // All of the necessary variables to make the functions functional.
  int N, I, Q, num, left, right, difference;
  char treeName[31], itemName[31], query[31];
  treeNameNode *tree = NULL, *target = NULL;
  itemNode *item = NULL;
  
  inPtr = fopen("in.txt", "r");
  outPtr = fopen("out.txt", "w");
  fscanf(inPtr, "%d %d %d", &N, &I, &Q);

  // For loop builds the tree name BST with N number of nodes.
  for (int i = 0; i < N; i++) {

    treeNameNode *temp = createTreeNameNode();
    tree = buildNameTree(tree, temp);

  }

  // For loop builds the item BST with I number of nodes.
  for (int i = 0; i < I; i++) {

    fscanf(inPtr, "%s", treeName);
    itemNode *temp = createItemNode();
    target = searchNameNode(tree, treeName);
    target->theTree = buildItemTree(target->theTree, temp);

  }

  // Prints out the necessary stuff.
  traverse_in_traverseTreeName(tree);
  printf("\n");
  fprintf(outPtr, "\n");
  traverse_in_traverse(tree);

  // This for loop takes care of all of the queries.
  // All of the (target != NULL) and (item != NULL) you will see throughout the query checkers are used to ensure whether the target tree name and the target item of the target tree name exist respectively.
  for (int i = 0; i < Q; i++) {

    // Reads the query commands (first string) in each line. 
    fscanf(inPtr, "%s", query);

    // Do this when the first string of the line reads "search."
    if (strcmp(query, "search") == 0) {
      
      fscanf(inPtr, "%s", treeName);
      fscanf(inPtr, "%s", itemName);

      // Finds the particular tree name node of the tree name BST.
      target = searchNameNode(tree, treeName);

      if (target != NULL) {

        // Finds the particular item node of the item BST.
        item = searchItemNode(target->theTree, itemName);

        if (item != NULL) {

          printf("%d %s found in %s\n", item->count, itemName, treeName);
          fprintf(outPtr, "%d %s found in %s\n", item->count, itemName, treeName);
    
        }

        else {

          printf("%s not found in %s\n", itemName, treeName);
          fprintf(outPtr, "%s not found in %s\n", itemName, treeName);

        }

      }

      else {

        printf("%s does not exist\n", treeName);
        fprintf(outPtr, "%s does not exist\n", treeName);

      }

    }

    // Do this when the first string of the line reads "item_before."
    else if (strcmp(query, "item_before") == 0) {

      fscanf(inPtr, "%s", treeName);
      fscanf(inPtr, "%s", itemName);

      // Finds the particular tree name node of the tree name BST.
      target = searchNameNode(tree, treeName);

      if (target != NULL) {

        // Finds the particular item node of the item BST.
        item = searchItemNode(target->theTree, itemName);

        if (item != NULL) {

          num = itemsBefore(target->theTree, item);
          
          printf("item before %s: %d\n", itemName, num);
          fprintf(outPtr, "item before %s: %d\n", itemName, num);

        }

      }
        
    }

    // Do this when the first string of the line reads "height_balance."
    else if (strcmp(query, "height_balance") == 0) {

      fscanf(inPtr, "%s", treeName);

      // Finds the particular tree name node of the tree name BST.
      target = searchNameNode(tree, treeName);

      if (target != NULL) {

        // Find the left and right subtress and take the absolute value of the difference. 
        left = height(target->theTree->left);
        right = height(target->theTree->right);
        difference = abs(right-left);

        // This conditional will check if the item BST of a tree name node is balanced.
        if (difference < 1) {

          printf("%s: left height %d, right height %d, difference %d, balanced\n", treeName, left, right, difference);
          fprintf(outPtr, "%s: left height %d, right height %d, difference %d, balanced\n", treeName, left, right, difference);

        }

        else {

          printf("%s: left height %d, right height %d, difference %d, not balanced\n", treeName, left, right, difference);
          fprintf(outPtr, "%s: left height %d, right height %d, difference %d, not balanced\n", treeName, left, right, difference);

        }

      }

    }

    // Do this when the first string of the line reads "count."
    else if (strcmp(query, "count") == 0) {

      fscanf(inPtr, "%s", treeName);

      // Finds the particular tree name node of the tree name BST.
      target = searchNameNode(tree, treeName);

      if (target != NULL) {

        num = countItems(target->theTree);
        
        printf("%s count %d\n", treeName, num);
        fprintf(outPtr, "%s count %d\n", treeName, num);

      }

    }

    // Do this when the first string of the line reads "reduce."
    else if (strcmp(query, "reduce") == 0) {

      fscanf(inPtr, "%s", treeName);
      fscanf(inPtr, "%s", itemName);
      fscanf(inPtr, "%d", &num);

      // Finds the particular tree name node of the tree name BST.
      target = searchNameNode(tree, treeName);

      if (target != NULL) {

        // Finds the particular item node of the item BST.
        item = searchItemNode(target->theTree, itemName);

        if (item != NULL) {

          // Do this when the first string of the line reads "search."
          item->count -= num;

          // If the count of an item goes to 0 or below, then delete that item.
          if (item->count <= 0) {

            target->theTree = deleteItemNode(target->theTree, item);

          }

          printf("%s reduced\n", itemName);
          fprintf(outPtr, "%s reduced\n", itemName);

        }

      }

    }

    // Do this when the first string of the line reads "delete."
    else if (strcmp(query, "delete") == 0) {

      fscanf(inPtr, "%s", treeName);
      fscanf(inPtr, "%s", itemName);

      // Finds the particular tree name node of the tree name BST.
      target = searchNameNode(tree, treeName);

      if (target != NULL) {

        // Finds the particular item node of the item BST.
        item = searchItemNode(target->theTree, itemName);

        if (item != NULL) {

          target->theTree = deleteItemNode(target->theTree, item);

        }
        
        printf("%s deleted from %s\n", itemName, treeName);
        fprintf(outPtr, "%s deleted from %s\n", itemName, treeName);

      }

    }

    // Do this when the first string of the line reads "delete_name."
    else if (strcmp(query, "delete_name") == 0) {

      fscanf(inPtr, "%s", treeName);

      // Finds the particular tree name node.
      target = searchNameNode(tree, treeName);

      if (target != NULL) {

        // Delete the entire item BST first then the respective tree name node.
        deleteTree(target->theTree);
        tree = deleteTreeNameNode(tree, target);

        printf("%s deleted\n", treeName);
        fprintf(outPtr, "%s deleted\n", treeName);
        
      }

    }

  }

  // Frees the rest of the memory when everything is done.
  freeAllTrees(tree);
  
  return 0;
  
}
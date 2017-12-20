#include "RBTree.h"



RBTree::RBTree()
{
	node = nullptr;
}

TreeStruct* RBTree::newTree(int key, int info,TreeStruct* parent) {
	TreeStruct *curr = new TreeStruct;
	curr->info = info;
	curr->key = key;
	curr->right = curr->left = nullptr;
  curr->parent = parent;
  curr->black = false;
	return curr;
}

void RBTree::setLeft(TreeStruct* curr, int key, int info) {
  curr->left = newTree(key, info, curr);
}

void RBTree::setRight(TreeStruct* curr, int key, int info) {
  curr->right = newTree(key, info, curr);
}

TreeStruct * RBTree::grandparent(TreeStruct* curr) {
  if ((curr != nullptr) && (curr->parent != nullptr))
    return curr->parent->parent;
  else
    return nullptr;
}


TreeStruct * RBTree::uncle(TreeStruct* curr) {
  TreeStruct *g = grandparent(curr);
  if (g == nullptr)
    return nullptr; // No grandparent means no uncle
  if (curr->parent == g->left)
    return g->right;
  else
    return g->left;
}

void RBTree::insert1(TreeStruct* n) {
  if (n->parent == nullptr)
    n->black = true;
  else
    insert2(n);
}

void RBTree::insert2(TreeStruct* n) {
  if (n->parent->black)
    return;
  else
    insert3(n);
}

void RBTree::insert3(TreeStruct* n) {
  TreeStruct *u = uncle(n), *g;

  if ((u != NULL) && (!u->black)) {
    n->parent->black = true;
    u->black = true;
    g = grandparent(n);
    g->black = false;
    insert1(g);
  }
  else {
    insert4(n);
  }
}

void RBTree::insert4(TreeStruct* n) {
  TreeStruct *g = grandparent(n);

  if ((n == n->parent->right) && (n->parent == g->left)) {
    rotateLeft(n->parent);
    n = n->left;
  }
  else if ((n == n->parent->left) && (n->parent == g->right)) {
    rotateRight(n->parent);
    n = n->right;
  }
  insert5(n);
}

void RBTree::insert5(TreeStruct* n) {
  TreeStruct *g = grandparent(n);

  n->parent->black = true;
  g->black = false;
  if ((n == n->parent->left) && (n->parent == g->left)) {
    rotateRight(g);
  }
  else {
    rotateLeft(g);
  }
}

bool RBTree::exist(int key) {
  TreeStruct* curr, *next;
  curr = next = node;
  while (next != nullptr) {
    curr = next;
    if (key < curr->key)
      next = curr->left;
    if (key > curr->key)
      next = curr->right;
    if (key == curr->key) {
      return true;
    }
  }
  return false;
}

void RBTree::erase(int key) {
  if (!exist(key))
    return;
  TreeStruct* curr, *next;
  curr = next = node;
  while (next != nullptr) {
    curr = next;
    if (key < curr->key)
      next = curr->left;
    if (key > curr->key)
      next = curr->right;
    if (key == curr->key) {
      delete1(curr); //Умеет удалять только простые случаи
      return;
    }
  }
}

void RBTree::delete1(TreeStruct* n) {
  if (n == node) {
    node = nullptr;
    return;
  }
  if (!n->right && !n->left) {//Если это лист
    if (n->parent->right == n)
      n->parent->right = nullptr;
    else
      n->parent->left = nullptr;
  return;
  }
  else {
    if ((n->left && n->right == nullptr) || (n->right && n->left == nullptr)) {
      if (n->right)
        if (n->parent->right == n)
          n->parent->right = n->right;
        else
          n->parent->left = n->right;
      else
        if (n->parent->right == n)
          n->parent->right = n->left;
        else
          n->parent->left = n->left;
    }
    else
      delete2(n);
  }
}

void RBTree::delete2(TreeStruct* n) {

}

void RBTree::insert(int key, int info) {
	TreeStruct* curr,*next;
	if (node == nullptr) {
		node = newTree(key, info);
		node->black = true;
    node->key = key;
    node->info = info;
	}
	curr = next = node;
	while (next != nullptr) {
		curr = next;
		if (key < curr->key)
			  next = curr->left;
		if (key > curr->key)
			next = curr->right;
    if (key == curr->key) {
      curr->info = info;
      return;
    }
	}
  if (key < curr->key) {
    setLeft(curr, key, info);
    next = curr->left;
  }
  else {
    setRight(curr, key, info);
    next = curr->right;
  }
  insert1(next);
}

void RBTree::rotateLeft(TreeStruct* n) {
  TreeStruct *pivot = n->right;

  pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
  if (n->parent != nullptr) {
    if (n->parent->left == n)
      n->parent->left = pivot;
    else
      n->parent->right = pivot;
  }

  n->right = pivot->left;
  if (pivot->left != nullptr)
    pivot->left->parent = n;

  n->parent = pivot;
  pivot->left = n;
  if (n == node)
    node = pivot;
}

void RBTree::rotateRight(TreeStruct* n) {
  TreeStruct *pivot = n->left;
  pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
  if (n->parent != nullptr) {
    if (n->parent->left == n)
      n->parent->left = pivot;
    else
      n->parent->right = pivot;
  }
  n->left = pivot->right;
  if (pivot->right != nullptr)
    pivot->right->parent = n;

  n->parent = pivot;
  pivot->right = n;
  if (n == node)
    node = pivot;
}

int RBTree::get(int key) {
  TreeStruct* curr, *next;
  curr = next = node;
  if (exist(key))
    while (next != nullptr) {
      curr = next;
      if (key < curr->key)
        next = curr->left;
      if (key > curr->key)
        next = curr->right;
      if (key == curr->key) {
        return curr->info;
      }
    }
}

RBTree::~RBTree()
{
  delete node;
}
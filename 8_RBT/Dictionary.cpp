/*****************************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa8
 * Dictionary.cpp
 * Implementation file for Dictionary ADT
 ******************************************************/

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>
#define RED 1
#define BLACK 0

using namespace std;

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    inOrderString(s, R->left);
    s.append(R->key);
    s.append(" : ");
    s.append(std::to_string(R->val));
    s.append("\n");
    inOrderString(s, R->right);
  }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    s.append(R->key);
    s.append("\n");
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N) {
  if (R != N) {
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
  }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node *R) {
  if (R == nil) {
    return;
  }
  postOrderDelete(R->left);
  postOrderDelete(R->right);
  R->parent = nullptr;
  R->left = nullptr;
  R->right = nullptr;
  delete R;
  num_pairs--;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
  if (k == R->key) {
    return R;
  } else if (R == nil) {
    return nil;
  } else if (k < R->key) {
    return search(R->left, k);
  } else {
    return search(R->right, k);
  }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node *R) {
  if (R != nil) {
    while (R->left != nil) {
      R = R->left;
    }
    return R;
  }
  return nil;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R) {
  if (R != nil) {
    while (R->right != nil) {
      R = R->right;
    }
    return R;
  }
  return nil;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findNext(Node *N) {
  if (N->right != nil) {
    return findMin(N->right);
  }
  Node *y = N->parent;
  while (y != nil && N == y->right) {
    N = y;
    y = y->parent;
  }
  return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node *N) {
  if (N->left != nil) {
    return findMax(N->left);
  }
  Node *y = N->parent;
  while (y != nil && N == y->left) {
    N = y;
    y = y->parent;
  }
  return y;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node *N) {
  Node *y = N->right;
  N->right = y->left;
  if (y->left != nil) {
    y->left->parent = N;
  }
  y->parent = N->parent;
  if (N->parent == nil) {
    this->root = y;
  } else if (N == N->parent->left) {
    N->parent->left = y;
  } else {
    N->parent->right = y;
  }
  y->left = N;
  N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node *N) {
  Node *y = N->left;
  N->left = y->right;
  if (y->right != nil) {
    y->right->parent = N;
  }
  y->parent = N->parent;
  if (N->parent == nil) {
    this->root = y;
  } else if (N == N->parent->right) {
    N->parent->right = y;
  } else {
    N->parent->left = y;
  }
  y->right = N;
  N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node *N) {
  while (N->parent->color == RED) {
    if (N->parent == N->parent->parent->left) {
      Node *y = N->parent->parent->right;
      if (y->color == RED) {
        N->parent->color = BLACK;
        y->color = BLACK;
        N->parent->parent->color = RED;
        N = N->parent->parent;
      } else {
        if (N == N->parent->right) {
          N = N->parent;
          LeftRotate(N);
        }
        N->parent->color = BLACK;
        N->parent->parent->color = RED;
        RightRotate(N->parent->parent);
      }
    } else {
      Node *y = N->parent->parent->left;
      if (y->color == RED) {
        N->parent->color = BLACK;
        y->color = BLACK;
        N->parent->parent->color = RED;
        N = N->parent->parent;
      } else {
        if (N == N->parent->left) {
          N = N->parent;
          RightRotate(N);
        }
        N->parent->color = BLACK;
        N->parent->parent->color = RED;
        LeftRotate(N->parent->parent);
      }
    }
  }
  this->root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node *u, Node *v) {
  if (u->parent == nil) {
    this->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node *N) {
  while (N != this->root && N->color == BLACK) {
    if (N == N->parent->left) {
      Node *w = N->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        N->parent->color = RED;
        LeftRotate(N->parent);
        w = N->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        N = N->parent;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          RightRotate(w);
          w = N->parent->right;
        }
        w->color = N->parent->color;
        N->parent->color = BLACK;
        w->right->color = BLACK;
        LeftRotate(N->parent);
        N = this->root;
      }
    } else {
      Node *w = N->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        N->parent->color = RED;
        RightRotate(N->parent);
        w = N->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        N = N->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          LeftRotate(w);
          w = N->parent->left;
        }
        w->color = N->parent->color;
        N->parent->color = BLACK;
        w->left->color = BLACK;
        RightRotate(N->parent);
        N = this->root;
      }
    }
  }
  N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node *N) {
  Node *y = N;
  Node *x;
  int y_original_color = y->color;
  if (N->left == nil) {
    x = N->right;
    RB_Transplant(N, N->right);
  } else if (N->right == nil) {
    x = N->left;
    RB_Transplant(N, N->left);
  } else {
    y = findMin(N->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == N) {
      x->parent = y;
    } else {
      RB_Transplant(y, y->right);
      y->right = N->right;
      y->right->parent = y;
    }
    RB_Transplant(N, y);
    y->left = N->left;
    y->left->parent = y;
    y->color = N->color;
  }
  if (y_original_color == BLACK) {
    RB_DeleteFixUp(x);
  }
}

// Class Constructors & Destructors
// ----------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = 0;
}

// Creates new Dictionary in the empty state.
Dictionary::Dictionary() {
  nil = new Node("none", 0);
  root = nil;
  current = nil;
  num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary &D) {
  nil = new Node("none", 0);
  root = nil;
  current = nil;
  num_pairs = D.num_pairs;
  preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
  while (num_pairs > 0) {
    clear();
  }
  delete nil;
}

// Access functions
// --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const { return num_pairs; }

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
  if (search(root, k) != nil) {
    return true;
  }
  return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType &Dictionary::getValue(keyType k) const {
  if (search(root, k) == nil) {
    throw invalid_argument("getValue(): Dictionary does not contain key k");
  }
  Node *N = search(root, k);
  return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const {
  if (current == nil || current == nullptr) {
    return false;
  }
  return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
  if (hasCurrent() == false) {
    throw invalid_argument("currentKey(): Current iterator is undefined");
  }
  return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType &Dictionary::currentVal() const {
  if (hasCurrent() == false) {
    throw invalid_argument("currentVal(): Current iterator is undefined");
  }
  return current->val;
}

// Manipulation procedures
// -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
  nil = new Node("none", 0);
  nil->parent = nil;
  nil->left = nil;
  nil->right = nil;
  root = nil;
  current = nil;
  num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with
// v, otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
  if (search(root, k) != nil) {
    Node *N = search(root, k);
    N->val = v;
  } else {
    Node *z = new Node(k, v);
    Node *x = this->root;
    Node *y = nil;
    while (x != nil) {
      y = x;
      if (k < x->key) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    z->parent = y;
    if (y == nil) {
      this->root = z;
    } else if (k < y->key) {
      y->left = z;
    } else if (k > y->key) {
      y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    RB_InsertFixUp(z);
    num_pairs++;
  }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then
// current becomes undefined. Pre: contains(k).
void Dictionary::remove(keyType k) {
  Node *z = search(root, k);
  if (z == nil) {
    throw invalid_argument("remove(): Dictionary does not contain key k");
  }
  if (z == current) {
    current = nil;
  }
  RB_Delete(z);
  num_pairs--;
  return;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
  if (num_pairs > 0) {
    current = findMin(root);
  }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
  if (num_pairs > 0) {
    current = findMax(root);
  }
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
  if (hasCurrent() == false) {
    throw invalid_argument("next(): Current iterator is undefined");
  }
  if (current == findMax(root)) {
    current = nil;
  } else {
    current = findNext(current);
  }
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
  if (hasCurrent() == false) {
    throw invalid_argument("next(): Current iterator is undefined");
  }
  if (current == findMin(root)) {
    current = nil;
  } else {
    current = findPrev(current);
  }
}

// Other Functions
// ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key,
// value) pairs are separated by a newline "\n" character, and the items
// key and value are separated by the sequence space-colon-space " : ".
// The pairs are arranged in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
  string s = "";
  inOrderString(s, root);
  return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
  string s = "";
  preOrderString(s, root);
  return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key,
// value) pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const {
  string a = "";
  string b = "";
  this->preOrderString(a, this->root);
  D.preOrderString(b, D.root);
  return a == b;
}

// Overloaded Operators
// ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined
// by member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
  return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as
// defined by member function equals().
bool operator==(const Dictionary &A, const Dictionary &B) {
  return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary &Dictionary::operator=(const Dictionary &D) {
  if (this != &D) {
    Dictionary temp = D;
    std::swap(nil, temp.nil);
    std::swap(root, temp.root);
    std::swap(current, temp.current);
    std::swap(num_pairs, temp.num_pairs);
  }
  return *this;
}

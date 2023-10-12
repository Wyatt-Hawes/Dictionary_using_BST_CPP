#include "Dictionary.h"
#include<iostream>
#include<string>
#include <string>      
#include <sstream>


Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;

}

bool Dictionary::is_null(Node* R) const{
    return (R == nil);
}


Dictionary::Node* Dictionary::contains_node(keyType k) const{
    Node* curr = root;

    while (true){

        if(k.compare(curr->key) < 0){
            if(is_null(curr->left)){
                return nil;
            }
            curr = curr->left;
        }else if (k.compare(curr->key) > 0){
            if(is_null(curr->right)){
                return nil;
            }
            curr = curr->right;
        }else{
            return curr;
        }
        
    }
    return nil;
}

Dictionary::Node* Dictionary::findMin(Node* R){
    Node* c = R;
    while((!is_null(c->left))){
        c = c->left;
    }
    return c;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    Node* c = R;
    while(!(is_null(c->right))){
        c = c->right;
    }
    return c;
}

Dictionary::Dictionary(){
    Node *n = new Node("", -1);
    nil = n;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
   
    nil = new Node("", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
    
}

Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete(nil);
}


void Dictionary::postOrderDelete(struct Node* R){
    if(is_null(R)){
        return;
    }

    
    if((!is_null(R->left))){

        postOrderDelete(R->left);
    }

    if((!is_null(R->right))){

        postOrderDelete(R->right);
    }


    if(is_null(R->parent)){
        root = nil;
    }else if (R->key.compare(R->parent->left->key) == 0){
        R->parent->left = nil;
    }else{
        R->parent->right = nil;
    }
    num_pairs--;
    delete(R);
    return;
}

//Access Functions
int Dictionary::size() const{
    return num_pairs;
}

keyType* contains_call_keytype;
valType* contains_call_valtype;
bool Dictionary::contains(keyType k) const{
    Node* curr = root;

    while (curr != nullptr){

        if(k.compare(curr->key) == 0){
            contains_call_valtype = &curr->val;
            contains_call_keytype = &curr->key;
            return true;
        }else if(k.compare(curr->key) < 0){
            curr = curr->left;
        }else{
            curr = curr->right;
        }
    }
    return false;
}

valType& Dictionary::getValue(keyType k) const{
    if(contains(k)){
        return *contains_call_valtype;
    }
    throw std::invalid_argument("Dictionary: getValue(): given key doesn't exist\n");
}

bool Dictionary::hasCurrent() const{
    if(is_null(current)){
        //printf("false\n");
        return false;
    }
    return true;
}

keyType Dictionary::currentKey() const{
    if(hasCurrent()){
        return current->key;
    }
    else{
        throw std::invalid_argument("Dictionary: currentKey(): current does not exist\n");
    }
}

valType& Dictionary::currentVal() const{
    if(hasCurrent()){
        return current->val;
    }
    else{
        throw std::invalid_argument("Dictionary: currentVal(): current does not exist\n");
    }
}

void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
}



void Dictionary::setValue(keyType k, valType v){

    Node* y = nil;
    Node* x = root;
    while(is_null(x) == false){

        y = x;
        int comp = k.compare(x->key);
        if(comp < 0){
            x = x->left;
        }else if(comp > 0){
            x = x->right;
        }else{
            x->val = v;
            return;
        }
    }
    num_pairs++;
    Node* z = new Node(k,v);
    z->parent = y;
    z->left = nil;
    z->right = nil;

    if(is_null(y)){
        root = z;
    }else if (z->key.compare(y->key)< 0){
        y->left = z;
    }else{
        y->right = z;
    }
}
void Dictionary::transplant(Node* u, Node* v){
    Node* par = u->parent;
    if(is_null(par)){
        root = v;
    }else if (u == par->left){
        par->left = v;
    }else{
        par->right = v;
    }

    if (is_null(v) == false){
        v->parent = par;
    }
}
void Dictionary::remove(keyType k){

    Node* z = contains_node(k);
    if(is_null(z)){
        throw std::logic_error("Dictionary: remove(): Key does not exist\n");
    }

    if(is_null(z->left)){
        transplant(z, z->right);
    }
    else if (is_null(z->right)){
        transplant(z, z->left);
    }else{
        Node* y = findMin(z->right);

        if(y->parent != z){
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    num_pairs--;
    if(current == z){
        current = nil;
    }
    delete(z);

}

void Dictionary::begin(){
    if(num_pairs == 0){
        return;
    }
    Node* c = root;
    while (c->left != nil){
        c = c->left;
    }
    current = c;
}

void Dictionary::end(){
    if(num_pairs == 0){
        return;
    }
    Node* c = root;
    while (c->right != nil){
        c = c->right;
    }
    current = c;
}

void Dictionary::next(){
    Node* c = current;
    if(current == nil){
        throw std::range_error("Dictionary: Next(): No current node, cant find next\n");
    }

    if(is_null(current->right) == false){
        current = current->right;
        return;
    }
    c = c->parent;
    
    while(c->key.compare(current->key) <= 0){
        c = c->parent;

        if(is_null(c)){
            current = nil;
            return;
        }
    }
    current = c;
    return;
}

void Dictionary::prev(){
    Node* c = current;
    if(current == nil){
        throw std::range_error("Dictionary: prev(): No current node, cant find next\n");
    }

    if(is_null(current->left) == false){
        current = current->left;
        return;
    }
    c = c->parent;
    while(c->key.compare(current->key) >= 0){
        c = c->parent;
        if(is_null(c)){
            current = nil;
            return;
        }
    }
    current = c;
    return;
}

std::string col = " : ";
std::string newL = "\n";
                                                        //const
void Dictionary::inOrderString(std::ostream& output,Node* R) const{
    if(is_null(R)){
        return;
    }

    if(is_null(R->left) == false){
        inOrderString(output, R->left);
    }

    output << (R->key + col + std::to_string(R->val) + newL);

    if(is_null(R->right) == false){
        inOrderString(output, R->right);
    }

    return;
}

void Dictionary::preOrderString(std::ostream& output, Node* R) const{
    if(is_null(R)){
        return;
    }
    output << (R->key+ newL);
    
    if(is_null(R->left) == false){
        preOrderString(output, R->left);
    }

    if(is_null(R->right) == false){
        preOrderString(output, R->right);
    }

}

std::string Dictionary::to_string() const{
    std::stringstream s;
    Node* r = root;
    inOrderString(s, r);
    return s.str();

}

std::string Dictionary::pre_string() const{
    std::stringstream s;
    Node* r = root;
    preOrderString(s, r);
    return s.str();
}


bool Dictionary::equals(const Dictionary& D) const{
    std::string A = to_string();
    std::string B = D.to_string();

    if(A.compare(B) == 0){
        return true;
    }
    return false;
}


void Dictionary::preOrderCopy(Node*R, Node* N){

    if(R->key.compare(N->key) == 0){
        return;
    }

    setValue(R->key, R->val);

    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D){
    D.inOrderString(stream, D.root);
    return stream;
}

bool operator==( const Dictionary& A, const Dictionary& B){
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ){

    clear();
    preOrderCopy(D.root, nil);

    return *this;
}

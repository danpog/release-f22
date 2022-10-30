/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    if (root == NULL){
        return V();
    }
    BST<K, V>::Node* pointer = find(root, key);
    if (pointer -> key == key) {
        return pointer -> value;
    } 
    return V();
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (key > subtree -> key) {
        if (subtree -> right == NULL || subtree -> right -> key == key) {
            return subtree -> right;
        } else  {
            return find(subtree -> right, key);
        }
    } else if (key < subtree -> key) {
        if (subtree -> left == NULL || subtree -> left -> key == key) {
            return subtree -> left;
        } else {
            return find(subtree -> left, key);
        }
    } else {
        // Should only run if root
        return subtree;
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    Node* to_insert = new Node(key, value);
    if (root == NULL) {
        root = to_insert;
    } else {
        BST<K, V>::Node* & pointer = find(root, key);
        if (pointer == NULL) {
            pointer = to_insert;
        } else {
            delete to_insert;
        }
    }
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    K temp_key = first -> key;
    V temp_value = first -> value;
    first->value = second -> value;
    first->key = second -> key;
    second -> value = temp_value;
    second -> key = temp_key;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // Only zero child case
    BST<K, V>::Node*& pointer = find(root, key);
    if (pointer -> key == key && pointer -> right == NULL && pointer -> left == NULL) {
        delete pointer;
        pointer = nullptr;
    } else {
        remove(pointer, key);
    }
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // One child case
    if (subtree -> right == NULL ^ subtree -> left == NULL) {
        Node* to_remove = subtree;
        subtree = subtree -> right == NULL ? subtree -> left : subtree -> right;
        delete to_remove;
    } else {
        Node* IOP = subtree;
        if (IOP -> left -> right == NULL) {
            swap(IOP -> left, subtree);
            if (IOP -> left -> left == NULL && IOP -> left -> right == NULL) {
                delete IOP -> left;
                IOP -> left = NULL;
            } else {
                remove(IOP -> left, key);
            }
        } else {
            IOP = subtree -> left;
            while (IOP -> right -> right != NULL) {
                IOP = IOP -> right;
            }
            swap(IOP -> right, subtree);
            if (IOP -> right -> left == NULL && IOP -> right -> right == NULL) {
                delete IOP -> right;
                IOP -> right = NULL;
            } else {
                remove(IOP -> left, key);
            }
        }
    }
    
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> bst;
    for (size_t i = 0; i < inList.size(); i++) {
        K key = inList.at(i).first;
        V value = inList.at(i).second;
        bst.insert(key, value);
    }
    return bst;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::sort(inList.begin(), inList.end());
    std::vector<int> to_return;
    do {
        BST<K, V> current = listBuild(inList);
        size_t height = size_t(current.height());
        while(height >= to_return.size()) {
            to_return.push_back(0);
        }
        to_return.at(height)++;

    } while (std::next_permutation(inList.begin(), inList.end()));
    return to_return;
}

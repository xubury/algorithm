#ifndef BST_H
#define BST_H

#include <vector>

template <typename T>
class BinarySearchTree {
   public:
    BinarySearchTree();

    std::size_t Size();

    void Insert(const T &val);

    bool Search(const T &val);

    const T &At(std::size_t node);

    std::size_t Left(std::size_t node);

    std::size_t Right(std::size_t node);

    bool Valid(std::size_t node);

   private:
    std::vector<T> m_tree;
    std::vector<bool> m_valids;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {}

template <typename T>
const T &BinarySearchTree<T>::At(std::size_t node) {
    return m_tree.at(node);
}

template <typename T>
std::size_t BinarySearchTree<T>::Left(std::size_t node) {
    return node * 2 + 1;
}

template <typename T>
std::size_t BinarySearchTree<T>::Right(std::size_t node) {
    return node * 2 + 2;
}

template <typename T>
bool BinarySearchTree<T>::Valid(std::size_t node) {
    return node < Size() && m_valids.at(node);
}

template <typename T>
std::size_t BinarySearchTree<T>::Size() {
    return m_tree.size();
}

template <typename T>
void BinarySearchTree<T>::Insert(const T &val) {
    std::size_t id = 0;
    while (Valid(id)) {
        if (val < m_tree[id]) {
            id = Left(id);
        } else if (val > m_tree[id]) {
            id = Right(id);
        } else {
            return;
        }
    }
    m_tree.resize(id + 1);
    m_valids.resize(id + 1);
    m_tree.at(id) = val;
    m_valids.at(id) = true;
}

template <typename T>
bool BinarySearchTree<T>::Search(const T &val) {
    std::size_t id = 0;
    while (Valid(id)) {
        if (val < m_tree[id]) {
            id = Left(id);
        } else if (val > m_tree[id]) {
            id = Right(id);
        } else {
            return true;
        }
    }
    return false;
}

#endif /* BST_H */

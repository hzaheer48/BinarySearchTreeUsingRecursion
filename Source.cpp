#include<iostream>
#include<queue>
#include<stack>
using namespace std;
template<typename T>
struct BNode {
	T data;
	BNode<T>* left, * right;
};
enum traversal { IN_ORDER, PRE_ORDER, POST_ORDER, LEVEL_ORDER };
template<typename T>
int count_nodes(const BNode<T>* ptr) {
	//base case
	if (ptr == NULL) {
		return 0;
	}
	else {
		return 1 + count_nodes(ptr->right) + count_nodes(ptr->left);
	}
}
template<typename T>
void insert_r(BNode<T>*& ptr, const T& val) {
	if (ptr == NULL) {
		ptr = new BNode<T>;
		ptr->data = val;
		ptr->left = NULL;
		ptr->right = NULL;
	}
	else if (val < ptr->data) {
		insert_r(ptr->left, val);
	}
	else if (val > ptr->data) {
		insert_r(ptr->right, val);
	}
	else {
		throw("Duplicate Keys NOT Allowed!");
	}
}
template<typename T>
T max_iter(const BNode<T>* ptr) {
	if (ptr == NULL) {
		throw("Empty tree!");
	}
	while (ptr != NULL) {
		if (ptr->right == NULL) {
			return ptr->data;
		}
		else {
			ptr = ptr->right;
		}
	}
}
template<typename T>
T min_iter(const BNode<T>* ptr) {
	if (ptr == NULL) {
		throw("Empty tree!");
	}
	while (ptr != NULL) {
		if (ptr->left == NULL) {
			return ptr->data;
		}
		else {
			ptr = ptr->left;
		}
	}
}
template<typename T>
T max_r(const BNode<T>* ptr) {
	if (ptr == NULL) {
		throw("Empty tree!");
	}
	if (ptr->right == NULL) {
		return ptr->data;
	}
	else {
		return max_r(ptr->right);
	}
}
template<typename T>
T min_r(const BNode<T>* ptr) {
	if (ptr == NULL) {
		throw("Empty tree!");
	}
	if (ptr->left == NULL) {
		return ptr->data;
	}
	else {
		return min_r(ptr->left);
	}
}
template<typename T>
T predecessor(const BNode<T>* ptr) {
	if (ptr->left == NULL) {
		throw("Predecessor not found");
	}
	else {
		return max_r(ptr->left);
	}
}
template<typename T>
T successor(const BNode<T>* ptr) {
	if (ptr->right == NULL) {
		throw("Successor not found");
	}
	else {
		return min_r(ptr->right);
	}
}
template<typename T>
bool find_r(const BNode<T>* ptr, T& val) {
	if (ptr == NULL) {
		return false;
	}
	if (ptr->data == val) {
		val = ptr->data;
		return true;
	}
	else if (val < ptr->data) {
		return find_r(ptr->left, val);
	}
	else if (val > ptr->data) {
		return find_r(ptr->right, val);
	}
}
template<typename T>
void erase_node(BNode<T>*& ptr) {
	if (ptr->left == NULL && ptr->right == NULL) {
		delete ptr;
		ptr = NULL;
	}
	else if (ptr->right == NULL) {
		BNode<T>* temp;
		temp = ptr->left;
		delete ptr;
		ptr = temp;
	}
	else if (ptr->left == NULL) {
		BNode<T>* temp;
		temp = ptr->right;
		delete ptr;
		ptr = temp;
	}
	else {
		T pred = predecessor(ptr);
		ptr->data = pred;
		erase_r(ptr->left, pred);


		/*BNode<T>* pred, * prev;
		prev = NULL;
		pred = ptr->left;
		while (pred->right != NULL) {
			prev = pred;
			pred = pred->right;
		}
		ptr->data = pred->data;
		if (prev != NULL) {
			prev->right = pred->left;
		}
		else {
			ptr->left = pred->left;
		}
		delete pred;*/


		/*BNode<T>* pred;
		pred = ptr->left;
		while (pred->right != NULL) {
			pred = pred->right;
		}
		ptr->data = pred->data;
		T val = pred->data;
		erase_r(ptr->left, val);*/
	}
}
template<typename T>
bool erase_r(BNode<T>*& ptr, const T& val) {
	if (ptr == NULL) {
		return false;
	}
	if (ptr->data == val) {
		erase_node(ptr);
		return true;
	}
	else if (val < ptr->data) {
		return erase_r(ptr->left, val);
	}
	else if (val > ptr->data) {
		return erase_r(ptr->right, val);
	}
}
template<typename T>
bool similarTrees_r(BNode<T>* t1, BNode<T>* t2) {
	if (t1 == NULL && t2 == NULL) {
		return true;
	}
	if (t1 != NULL && t2 != NULL) {
		return similarTrees_r(t1->left, t2->left) && similarTrees_r(t1->right, t2->right);
	}
	return false;
}
template<typename T>
void traverse_in(const BNode<T>* ptr, queue<T>& q) {
	if (ptr != NULL) {
		//in-order traversal
		traverse_in(ptr->left, q);
		q.push(ptr->data);
		traverse_in(ptr->right, q);
	}
}
template<typename T>
void traverse_pre(const BNode<T>* ptr, queue<T>& q) {
	if (ptr != NULL) {
		//pre-order traversal
		q.push(ptr->data);
		traverse_pre(ptr->left, q);
		traverse_pre(ptr->right, q);
	}
}
template<typename T>
void traverse_post(const BNode<T>* ptr, queue<T>& q) {
	if (ptr != NULL) {
		//post-order traversal
		traverse_post(ptr->left, q);
		traverse_post(ptr->right, q);
		q.push(ptr->data);
	}
}
template<typename T>
void traverse_level(BNode<T>* ptr, queue<T>& q) {
	queue<BNode<T>*> temp_q;
	temp_q.push(ptr);
	while (!temp_q.empty()) {
		BNode<T>* temp;
		temp = temp_q.front();
		temp_q.pop();
		q.push(temp->data);
		if (temp->left != NULL) {
			temp_q.push(temp->left);
		}
		if (temp->right != NULL) {
			temp_q.push(temp->right);
		}
	}
}
template<typename T>
void make_empty_r(const BNode<T>* ptr) {
	if (ptr != NULL) {
		make_empty_r(ptr->left);
		make_empty_r(ptr->right);
		delete ptr;
	}
}
template<typename T>
void copy_tree(const BNode<T>* src, BNode<T>*& dest) {
	if (src == NULL) {
		dest = NULL;
	}
	else {
		dest = new BNode<T>;
		dest->data = src->data;
		copy_tree(src->left, dest->left);
		copy_tree(src->right, dest->right);
	}
}
template<typename T>
class BST {
	BNode<T>* root;
	queue<T> q_in, q_pre, q_post, q_level;
public:
	BST() {
		root = NULL;
	}
	BST(const BST<T>& src) {
		copy_tree(src.root, root);
	}
	void operator=(const BST<T>& src) {
		make_empty();
		copy_tree(src.root, root);
	}
	~BST() {
		make_empty_r(root);
	}
	void make_empty() {
		make_empty_r(root);
		root = NULL;
	}
	//recursive solution for insert
	void insert(const T& val) {
		insert_r(root, val);
	}
	bool find(T& val) const {
		return find_r(root, val);
	}
	void reset(traversal type = IN_ORDER) {
		switch (type) {
		case IN_ORDER:
			q_in = queue<T>();
			traverse_in(root, q_in);
			break;
		case PRE_ORDER:
			q_pre = queue<T>();
			traverse_pre(root, q_pre);
			break;
		case POST_ORDER:
			q_post = queue<T>();
			traverse_post(root, q_post);
			break;
		case LEVEL_ORDER:
			q_level = queue<T>();
			traverse_level(root, q_level);
			break;
		}
	}
	bool is_last(traversal type = IN_ORDER) {
		switch (type) {
		case IN_ORDER:
			return q_in.empty();
		case PRE_ORDER:
			return q_pre.empty();
		case POST_ORDER:
			return q_post.empty();
		case LEVEL_ORDER:
			return q_level.empty();
		}
	}
	T get_next(traversal type = IN_ORDER) {
		if (is_last(type)) {
			throw("Last value reached");
		}
		T val;
		switch (type) {
		case IN_ORDER:
			val = q_in.front();
			q_in.pop();
			break;
		case PRE_ORDER:
			val = q_pre.front();
			q_pre.pop();
			break;
		case POST_ORDER:
			val = q_post.front();
			q_post.pop();
			break;
		case LEVEL_ORDER:
			val = q_level.front();
			q_level.pop();
			break;
		}
		return val;
	}
	int length() const {
		return count_nodes(root);
	}
	bool similarTrees(const BST<T>& t) {
		return similarTrees_r(root, t.root);
	}
	T max() const {
		return max_iter(root);
	}
	T min() const {
		return min_iter(root);
	}
	//iterative solution for insert
	void insert_iter(const T& val) {
		BNode<T>* n;
		n = new BNode<T>;
		n->data = val;
		n->right = NULL;
		n->left = NULL;
		if (root == NULL) {
			root = n;
		}
		else {
			BNode<T>* temp;
			temp = root;
			while (true) {
				if (val < temp->data) {
					if (temp->left == NULL) {
						temp->left = n;
						break;
					}
					else {
						temp = temp->left;
					}
				}
				else if (val > temp->data) {
					if (temp->right == NULL) {
						temp->right = n;
						break;
					}
					else {
						temp = temp->right;
					}
				}
				else {
					throw("Duplicate Keys NOT Allowed!");
				}
			}
		}
	}
	bool find_iter(T& val) const {
		BNode<T>* temp;
		temp = root;
		while (temp != NULL) {
			if (temp->data == val) {
				val = temp->data;
				return true;
			}
			if (val < temp->data) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		return false;
	}
	bool erase(const T& val) {
		return erase_r(root, val);
	}
	bool empty() const {
		return root == NULL;
	}
};
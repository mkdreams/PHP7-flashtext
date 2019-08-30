#include "Tree.h"

TreeNode::TreeNode()
	:next(NULL) {

}

Tree::Tree() {
	this->root = new TreeNode();
}

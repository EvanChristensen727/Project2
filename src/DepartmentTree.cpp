#include "../include/DepartmentTree.h"

DepartmentTree::DepartmentTree(){}

bool DepartmentTree::addDepartment(std::string name, std::string parentName){
	if (root == nullptr){
		root = new DepartmentNode(name);
		return true;
	}
	else{
		DepartmentNode* parent = SearchTree(parentName);
		if(parent == nullptr){return false;}
		else if(SearchTree(name) != nullptr){return false;}
		else{
			DepartmentNode* newNode = new DepartmentNode(name);
			parent->addChild(newNode);
			newNode->setParent(parent);
			return true;
		}
		
	}
}

DepartmentNode* DepartmentTree::SearchTree(std::string name){
	return SearchTree(root, name); 
}

DepartmentNode* DepartmentTree::SearchTree(DepartmentNode* current, std::string name){
	if (current == nullptr){
		return nullptr;
	}
	else{
		std::string currentName = current->getName();
		if(currentName == name){
			return current;
		}
		else{
			for(DepartmentNode* child : current->getChildren()){
					DepartmentNode* result = SearchTree(child, name);
					if(result != nullptr){return result;}
			}
			return nullptr;
		}
 	}
}

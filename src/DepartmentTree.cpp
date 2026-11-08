#include "../include/DepartmentTree.h"
#include "../include/Campus.h"
#include <cctype>
#include <iostream>

DepartmentTree::DepartmentTree(){}

DepartmentTree::~DepartmentTree(){
	deleteTree(root);
}

void DepartmentTree::deleteTree(DepartmentNode* current){
	if(current == nullptr){
		return;
	}
	for(DepartmentNode* child : current->getChildren()){
		deleteTree(child);
	}
	delete current;

}

bool DepartmentTree::addDepartment(std::string name, std::string parentName){
	parentName = Campus::trimName(parentName);
	name = Campus::trimName(name);
	if(name.empty()){
		std::cout << "invalid entry" << std::endl;
		return false;
	}
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
		if(lowerCase(currentName) == lowerCase(name)){
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

std::string DepartmentTree::lowerCase(std::string target){
	for(char& letter : target){
		letter = tolower(static_cast<unsigned char>(letter));
	}
	return target;
}

void DepartmentTree::displayHierarchy(){
	if(root == nullptr){
		std::cout <<"Tree is empty" << std::endl;
		return;
	}
	displayHierarchy(0, root);
}

void DepartmentTree::displayHierarchy(int depth, DepartmentNode* current){
	int counter = 0;
	if(current == nullptr){
		return;
	}
	while(counter < depth * 4){
		std::cout << " ";
		counter++;
	}
	std::cout << current->getName() << std::endl;
	for(DepartmentNode* child : current->getChildren()){
		displayHierarchy(depth+1, child);
	}

}

void DepartmentTree::preorderTraversal(){
	if(root == nullptr){
		std::cout <<"Tree is empty" << std::endl;
		return;
	}
	preorderTraversal(root);
}

void DepartmentTree::preorderTraversal(DepartmentNode* current){
	if(current == nullptr){
		return;
	}
	std::cout << current->getName() << std::endl;
	for(DepartmentNode* child : current->getChildren()){
		preorderTraversal(child);
	}
}

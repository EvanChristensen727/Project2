#include "../include/DepartmentTree.h"
#include "../include/Campus.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>

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

void DepartmentTree::displayDepartment(DepartmentNode* current){
	if (current == nullptr){
		std::cout << "invalid entry" << std::endl;
		return;
	}
	std::cout << "Name: " << current->getName() << std::endl;
	if(current->getParent() == nullptr){
		std::cout << "Parent: NONE" << std::endl;
	}
	else{
		std::cout << "Parent: " << current->getParent()->getName() << std::endl;
	}
	std::cout<< "Direct Children: " << current->getChildren().size() << std::endl;
	int depth = 0;
	DepartmentNode* node = current;
	while(node->getParent() != nullptr){
		depth += 1;
		node = node->getParent();
	}
	std::cout << "Depth: " << depth << std::endl;

}

bool DepartmentTree::loadDepartment(std::string fileName){
	std::ifstream inputFile;
	std::string line;
	int counter = 0;
	int rejected = 0;
	int accepted = 0;
	inputFile.open(fileName);
	if(!inputFile.is_open()){
		std::cout << fileName << " failed to open" << std::endl;
		return false;
	}
	while(getline(inputFile, line)){
		std::string departmentName, parentName;
		line = Campus::trimName(line);
		std::stringstream ss(line);
		counter ++;
		if(line.empty() || line[0] == '#'){
			continue;
		}
		else{
			if(line.find('|') == std::string::npos){
				std::cout << "WARNING! " << fileName << " at " << counter << " too few fields." <<std::endl;
				rejected++;
				continue;
			}
			getline(ss, departmentName, '|');
			getline(ss, parentName);
			departmentName = Campus::trimName(departmentName);
			parentName = Campus::trimName(parentName);
				if (departmentName.empty() || parentName.empty()){
					std::cout << "WARNING " << fileName << " at " << counter << " has empty fields." << std::endl;
					rejected++;
					continue;
				}
			if(parentName.find('|') != std::string::npos){
				std::cout << "WARNING! " << fileName << " at " << counter << " contains too many fields." << std::endl;
				rejected++;
				continue;
			}
			if (root == nullptr){
				if (lowerCase(parentName) != "none"){
					std::cout << "WARNING: " << fileName <<" Root parent must be NONE at: " << counter << std::endl;
					rejected++;
					continue;
				}
			}
			else if(lowerCase(parentName) == "none"){
				std::cout << "WARNING:" << fileName << " another root is not allowed at: " << counter << std::endl;
				rejected++;
				continue;
			}
			if(addDepartment(departmentName, parentName)){
				accepted++;
			}
			else{
				rejected++;
				if (SearchTree(departmentName)){
					std::cout << "Warning! " << fileName << " at " << counter << " duplicate department" << std::endl;
				}
				else{
					std::cout << "Warning! " << fileName << " at " << counter << " Unknown parent: " << parentName << std::endl;
				}
			}
		}
	}
	std::cout << "Departments loaded: " << accepted << std::endl;
	std::cout << "Departments rejected: " << rejected << std::endl;
	return true;
}

bool DepartmentTree::isEmpty() const{
	return(root == nullptr);
}

#include "../include/DepartmentNode.h"

DepartmentNode::DepartmentNode(std::string name){
	this->name = name;
	this->parent = nullptr;
}

std::string DepartmentNode::getName() const{
	return name;
}

DepartmentNode* DepartmentNode::getParent() const{
	return parent;
}

std::vector<DepartmentNode*> DepartmentNode::getChildren() const{
	return children;
}

void DepartmentNode::addChild(DepartmentNode* child){
	children.push_back(child);	
}

void DepartmentNode::setParent(DepartmentNode* parent){
	this->parent = parent;	
}

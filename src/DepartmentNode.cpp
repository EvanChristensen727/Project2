#include "../include/DepartmentNode.h"
//base constructor
DepartmentNode::DepartmentNode(std::string name){
	this->name = name;
	this->parent = nullptr;
}
//returns node department name
std::string DepartmentNode::getName() const{
	return name;
}
//returns current nodes parent node
DepartmentNode* DepartmentNode::getParent() const{
	return parent;
}
//builds vector of current nodes childrem
std::vector<DepartmentNode*> DepartmentNode::getChildren() const{
	return children;
}
//add a child to current node
void DepartmentNode::addChild(DepartmentNode* child){
	children.push_back(child);	
}
//set a nodes parent
void DepartmentNode::setParent(DepartmentNode* parent){
	this->parent = parent;	
}

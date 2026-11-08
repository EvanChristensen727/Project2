#pragma once
#include <vector>
#include <string>



class DepartmentNode{

	public:

	DepartmentNode(std::string name);
	std::string getName() const;
	DepartmentNode* getParent() const;
	std::vector<DepartmentNode*> getChildren() const;
	void addChild(DepartmentNode* child);
	void setParent(DepartmentNode* parent);

	private:
		DepartmentNode* parent;
		std::vector<DepartmentNode*> children;
		std::string name;

};

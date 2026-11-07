#pragma once
#include "DepartmentNode.h"
#include <string>


class DepartmentTree{
	public:
		DepartmentTree();
		bool addDepartment(std::string name, std::string parentName);
		DepartmentNode* SearchTree(std::string name);
		void displayHierarchy();
		void preorderTraversal();

	private:

		DepartmentNode* root = nullptr;
		//recursive helpers
		DepartmentNode* SearchTree(DepartmentNode* current, std::string name);
		void displayHierarchy(int depth, DepartmentNode* current);
		void preorderTraversal(DepartmentNode* current);

};

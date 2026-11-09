#pragma once
#include "DepartmentNode.h"
#include <string>


class DepartmentTree{
	public:
		DepartmentTree();
		~DepartmentTree();
		bool addDepartment(std::string name, std::string parentName);
		DepartmentNode* SearchTree(std::string name);
		void displayHierarchy();
		void preorderTraversal();
		std::string lowerCase(std::string target);

	private:
		
		DepartmentNode* root = nullptr;
		//recursive helpers
		void deleteTree(DepartmentNode* current);
		DepartmentNode* SearchTree(DepartmentNode* current, std::string name);
		void displayHierarchy(int depth, DepartmentNode* current);
		void preorderTraversal(DepartmentNode* current);

};

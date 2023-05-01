#ifndef AI_TREENODE
#define AI_TREENODE

#include <string>
#include <vector>
namespace Rain {
	namespace AI {
		enum BTNodeType {
			Parallel,
			Selection,
			Sequence,
			Action,
			Condition,
			Decorator,
		};
		class TreeNode
		{
		public:
			std::string name;
			BTNodeType type;


			TreeNode();
			TreeNode(std::string i_name, std::string i_type, std::vector<TreeNode*> i_children);
			TreeNode(std::string i_name, std::string i_type);

			void AddChild(TreeNode* treeNode);

			virtual bool Update() = 0;
		private:
			std::vector<TreeNode*> children;

		};
	}
}

#endif // !AI_BEHAVIORTREE

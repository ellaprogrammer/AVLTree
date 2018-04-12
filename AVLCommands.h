#include <memory>
#include <string>

//typedef std::shared_ptr Node;

class BST;

class BSTNode {
 public:
 	BSTNode(int key);
 	BSTNode(int key, std::shared_ptr<BSTNode> parent); //weak
 	bool IsLeaf() const;
 	bool IsMissingChild() const;
 	bool HasLeftChild() const;
 	bool HasRightChild() const;
 	void DeleteChild(std::shared_ptr<BSTNode> v);
 	void ReplaceChild(std::shared_ptr<BSTNode> v, std::shared_ptr<BSTNode> u);
 	int height_of(std::shared_ptr<BSTNode> v) ;
 	int max(int a, int b);
 	int get_Balance(std::shared_ptr<BSTNode> v)  ;
 	int height_;
 	int balance_;

 //private:
  int key_;
  std::shared_ptr<BSTNode> parent_; //weak
  std::shared_ptr<BSTNode> left_;
  std::shared_ptr<BSTNode> right_;

  private:

  friend class BST;
}; // class BSTNode

class BST {
 public:
 	BST();

 	int specialheight_of(std::shared_ptr<BSTNode> v);
 	void Insert(int key);
 	void Delete(int key);
 	bool Find(int key) const;
 	std::string JSON() ;
 	size_t size() const;
 	bool empty() const;
 	int DeleteMin();
 	int height_of(std::shared_ptr<BSTNode> v) ;
 	int max(int a, int b);
 	void right_Rotate(std::shared_ptr<BSTNode> y, std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> T2);
 	void left_Rotate(std::shared_ptr<BSTNode> y, std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> T2);
 	int get_Balance(std::shared_ptr<BSTNode> v) ;
 	bool missingLeftChild(std::shared_ptr<BSTNode> v) const;
 	bool missingRightChild(std::shared_ptr<BSTNode> v) const;
 	void DeleteBalance(std::shared_ptr<BSTNode> pastNode, int key);
 	void DeleteMinBalance(std::shared_ptr<BSTNode> pastNode, int key);

 	void left_2_Rotate(std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> y);
 	void right_2_Rotate(std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> y);

 	std::shared_ptr<BSTNode> root_;


 private:
	void DeleteLeaf(std::shared_ptr<BSTNode> currentNode);
	int DeleteMin(std::shared_ptr<BSTNode> currentNode);

 	//std::shared_ptr<BSTNode> root_;
 	size_t size_;
}; // class BST
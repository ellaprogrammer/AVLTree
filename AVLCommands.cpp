//add right and left rotate

//change insert, delete




#include "AVLCommands.h"

#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include <fstream>

#include "json.hpp"


BSTNode::BSTNode(int key) :
	key_(key),
	parent_(std::shared_ptr<BSTNode>()), //weak
	left_(nullptr),
	right_(nullptr) {}

BSTNode::BSTNode(int key, std::shared_ptr<BSTNode> parent) : //weak
	height_(1), //IS THIS RIGHT?
	key_(key),
	parent_(parent),
	left_(nullptr),
	right_(nullptr) {}

int BSTNode::height_of(std::shared_ptr<BSTNode> v){ //for checking heights in insert
    if (v == nullptr)
        return 0;

    return v->height_;
}

int BST::height_of(std::shared_ptr<BSTNode> v){ //for checking heights in insert
    if (v == nullptr)
        return 0;
    if ((missingLeftChild(v) && missingRightChild(v)) == true){
		return 0;
	}
    return v->height_;
}

int BST::specialheight_of(std::shared_ptr<BSTNode> v){
	if (v == nullptr)
        return 0;

    if ((missingLeftChild(v) && missingRightChild(v)) == true){
		return 0;
	}

    return max(height_of(v->left_), height_of(v->right_))+1;
}

int BSTNode::get_Balance(std::shared_ptr<BSTNode> v){
	if (v == nullptr){
		return 0;
	}

    return height_of(v->left_) - height_of(v->right_); //returns height at node v = -1,1,0, etc
}

int BST::get_Balance(std::shared_ptr<BSTNode> v){
	//std::cout << "In the correct get Balance function!" << std::endl << std::endl;
	if ((missingLeftChild(v) && missingRightChild(v)) == true){
		return 0;
	}

	if (missingLeftChild(v) == true){
		return (-1) - height_of(v->right_); //L - R, L missing (-1)
	}
	if (missingRightChild(v) == true){
		return height_of(v->left_) + 1; //L - R, R missing (- -1)
	}
	else{
		return height_of(v->left_) - height_of(v->right_); //returns height at node v = -1,1,0, etc
	}
}

bool BST::missingLeftChild(std::shared_ptr<BSTNode> v) const{
	return v->left_ == nullptr; //returns true if missing a left child
}

bool BST::missingRightChild(std::shared_ptr<BSTNode> v) const{
	return v->right_ == nullptr; //returns true if missing a right child
}

int BSTNode::max(int a, int b){
    return (a > b)? a : b;
}

int BST::max(int a, int b){
    return (a > b)? a : b;
}

bool BSTNode::IsLeaf() const {
	return left_ == nullptr && right_ == nullptr;
}

bool BSTNode::HasLeftChild() const {
	return left_ != nullptr;
}

bool BSTNode::HasRightChild() const {
	return right_ != nullptr;
}

void BSTNode::DeleteChild(std::shared_ptr<BSTNode> v) {
	if (left_ == v) {
		left_ = nullptr;
	} else if (right_ == v) {
		right_ = nullptr;
	} else {
		std::cerr << "BSTNode::DeleteChild Error: non-child passed as argument\n";
		exit(EXIT_FAILURE);
	}
}

void BSTNode::ReplaceChild(std::shared_ptr<BSTNode> v, std::shared_ptr<BSTNode> u) {
	if (left_ == u || right_ == u) {
		std::cerr << "BSTNode::ReplaceChild Error: child passed as replacement\n";
	}
	if (left_ == v) {
		left_ = u;
		u->parent_ = v->parent_;
	} else if (right_ == v) {
		right_ = u;
		u->parent_ = v->parent_;
	} else {
		std::cerr << "BSTNode::ReplaceChild Error: non-child passed as argument\n";
		exit(EXIT_FAILURE);
	}
}

BST::BST() : root_(nullptr), size_(0) {}


void BST::left_2_Rotate(std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> y){

//	std::cout<<"in left 2 rotate"<<std::endl;

	y->parent_ = x->parent_;
	x->parent_->left_ = y;
	x->parent_ = y;
	y->left_ = x; 

	return;

}

void BST::right_2_Rotate(std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> y){

//	std::cout<<"in right 2 rotate"<<std::endl;

	y->parent_ = x->parent_;
	x->parent_->right_ = y;
	x->parent_ = y;
	y->right_ = x; 

	return;

}

void BST::right_Rotate(std::shared_ptr<BSTNode> y, std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> T2){

	//std::cout<<"right_Rotate" << std::endl;

    if (T2 != nullptr){
    	//std::cout<<"if: " << std::endl;
    	x->parent_ = y->parent_; //dbl chk
    	if (y->parent_ == nullptr){
    		root_ = x;
    	}
    	else{ //only check if y was right or left child of its parent if it's not the root
    		if (y->parent_->right_ == y){ //if y was the right child of the parent, 
    									//redirect the parent's right child pointer to x
    			//std::cout<<"if 2: " << std::endl;
    			y->parent_->right_ = x;
    		}
    		if (y->parent_->left_ == y){
    			//std::cout<<"if 3:" << std::endl;
    			y->parent_->left_ = x; //changed to left
    		}
    	}

    	x->right_ = y; 
    	y->left_ = T2; 
    	y->parent_ = x;
    	T2->parent_ = y;
	}
	else{
		//std::cout<<"else" << std::endl;
		x->parent_ = y->parent_;
		
		if (y->parent_ == nullptr){
    		root_ = x;
    	}
    	else { //only check if y was right or left child of its parent if it's not the root
    		if (y->parent_->right_ == y){ //if y was the right child of the parent, 
    									//redirect the parent's right child pointer to x
    			//std::cout<<"E if 1: " << std::endl;
    			y->parent_->right_ = x;
    		}
    		if (y->parent_->left_ == y){
    			//std::cout<<"E if 2: " << std::endl;
    			y->parent_->left_ = x;
    		}
    	}

    	y->parent_ = x;
    	y->left_ = x->right_;
    	x->right_ = y;
	}

    // Update heights
    y->height_ = max(height_of(y->left_), height_of(y->right_))+1;
    x->height_ = max(height_of(x->left_), height_of(x->right_))+1;

    
    return;

}


void BST::left_Rotate(std::shared_ptr<BSTNode> y, std::shared_ptr<BSTNode> x, std::shared_ptr<BSTNode> T2){


	//std::cout<<"left_Rotate" << std::endl;

    if (T2 != nullptr){
    	x->parent_ = y->parent_;
    	if (y->parent_ == nullptr){
    		root_ = x;
    	}


    	else { //only check if y was right or left child of its parent if it's not the root
    		if (y->parent_->right_ == y){ //if y was the right child of the parent, 
    									//redirect the parent's right child pointer to x
    			//std::cout<<"E if 1: " << std::endl;
    			y->parent_->right_ = x;
    		}
    		if (y->parent_->left_ == y){
    			//std::cout<<"E if 2: " << std::endl;
    			y->parent_->left_ = x;
    		}
    	}

    	x->left_ = y;
    	y->right_ = T2;
    	y->parent_ = x;
    	T2->parent_ = y;
	}
	else{
		x->parent_ = y->parent_;
		if (y->parent_ == nullptr){
    		root_ = x;
    	}

    	else { //only check if y was right or left child of its parent if it's not the root
    		if (y->parent_->right_ == y){ //if y was the right child of the parent, 
    									//redirect the parent's right child pointer to x
    //			std::cout<<"E if 1: " << std::endl;
    			y->parent_->right_ = x;
    		}
    		if (y->parent_->left_ == y){
  //  			std::cout<<"E if 2: " << std::endl;
    			y->parent_->left_ = x;
    		}
    	}

    	y->parent_ = x;
    	y->right_ = x->left_;
    	x->left_ = y;

    	

	}

    // Update heights
    y->height_ = max(height_of(y->left_), height_of(y->right_))+1;
    x->height_ = max(height_of(x->left_), height_of(x->right_))+1;

    return;
}


void BST::Insert(int key) {
	//if the key is already inside the tree, don't add it
	if (root_ == nullptr) {
		root_ = std::make_shared<BSTNode>(key); //creates a root with the key to be inserted
		size_++;
		return;
	}
	std::shared_ptr<BSTNode> currentNode = root_, lastNode = nullptr; 
	while (currentNode != nullptr) {
		lastNode = currentNode; //temp

		if (currentNode->key_ == key){ //check for duplicates
			return;
		}

		currentNode = (key < currentNode->key_) ?
			currentNode->left_ : currentNode->right_; //if currentNode = (key < currentNode->key_) then currentNode->left_, else currentNode->right_
	}
	if (key < lastNode->key_) {
		lastNode->left_ = std::make_shared<BSTNode>(key, lastNode);
	} else {
		lastNode->right_ = std::make_shared<BSTNode>(key, lastNode);
	}
	size_++;


	//NEW CODE:
	std::shared_ptr<BSTNode> pastNode = lastNode;

	//std::cout <<"pastNode key: " << pastNode->key_ << std::endl;

	while(pastNode->parent_ != nullptr){

		//std::cout<<"Entering while loop..." << std::endl;
		
		pastNode = pastNode->parent_;
	
		//add one to the maximum of the left or right child
		pastNode->height_ = 1 + max(height_of(pastNode->left_), height_of(pastNode->right_)); //can prob just switch to lastNode->left_->height_

		int balance = get_Balance(pastNode);
		//std::cout << "balance: " << balance << "for the node: " << pastNode->key_ << std::endl;
		
    	// left_ left_ 
    	if (balance > 1 && key < pastNode->left_->key_){ 
    		//std::cout << "Root before! " << root_->key_ << std::endl;
    		//std::cout<<"Right rotate"<<std::endl;
        	right_Rotate(pastNode, pastNode->left_, pastNode->left_->right_);
        	//std::cout << "Root after! " << root_->key_ << std::endl;
        	return; 
        }
    	// right_ right_ 
    	if (balance < -1 && key > pastNode->right_->key_){ 
    		//std::cout << "Root before rotate! " << root_->key_ << std::endl;
    		//std::cout<<"Left Rotate"<<std::endl;
        	left_Rotate(pastNode, pastNode->right_, pastNode->right_->left_);
        	//std::cout << "Root after rotate! " << root_->key_ << std::endl;
        	return;
    	}

    	//YOU ARE HERE AND YOU JUST COMMENTED OUT RIGHT ROTATE TO FIGURE OUT IF YOURE USING LEFT ROT INCORRECTLY

    	// left_ right_ 
    	if (balance > 1 && key > pastNode->left_->key_){ 
    		//std::cout<<"Left Right rotate"<<std::endl; //seg fault in here
        	//left_2_Rotate(pastNode->left_, pastNode->left_->right_);
        	left_Rotate(pastNode->left_, pastNode->left_->right_, pastNode->left_->right_->left_); //FIX
        	right_Rotate(pastNode, pastNode->left_, pastNode->left_->right_); 

        	//std::cout<< "Done with Left Right" << std::endl;
        	return;
    	}

    	// right_ left_ 
    	if (balance < -1 && key < pastNode->right_->key_){ 
    		//std::cout<<"Right Left rotate"<<std::endl;
        	//right_2_Rotate(pastNode->right_, pastNode->right_->left_); //right 2 rotate
        	right_Rotate(pastNode->right_, pastNode->right_->left_, pastNode->right_->left_->right_);
        	left_Rotate(pastNode, pastNode->right_, pastNode->right_->left_); 
        	return;
    	}
    	//std::cout << "I made it to the end!!" << std::endl;
	}
	//std::cout << "I'm outside the while!!" << std::endl;

    return;
}

void BST::DeleteBalance(std::shared_ptr<BSTNode> pastNode, int key){

//	std::cout <<"pastNode key: " << pastNode->key_ << std::endl;

	while(pastNode->parent_ != nullptr){

//		std::cout<<"Entering while loop..." << std::endl;
		
		pastNode = pastNode->parent_;
	
		//add one to the maximum of the left or right child
		pastNode->height_ = 1 + max(height_of(pastNode->left_), height_of(pastNode->right_)); //can prob just switch to lastNode->left_->height_

		int balance = get_Balance(pastNode);
		//std::cout << "balance: " << balance << "for the node: " << pastNode->key_ << std::endl;
		
    	// left_ left_ 
    	if (balance > 1 && key < pastNode->left_->key_){ 
    		//std::cout << "Root before! " << root_->key_ << std::endl;
    		//std::cout<<"Right rotate"<<std::endl;
        	right_Rotate(pastNode, pastNode->left_, pastNode->left_->right_);
        	//std::cout << "Root after! " << root_->key_ << std::endl;
        	return; 
        }
    	// right_ right_ 
    	if (balance < -1 && key > pastNode->right_->key_){ 
    		//std::cout << "Root before rotate! " << root_->key_ << std::endl;
    		//std::cout<<"Left Rotate"<<std::endl;
        	left_Rotate(pastNode, pastNode->right_, pastNode->right_->left_);
        	//std::cout << "Root after rotate! " << root_->key_ << std::endl;
        	return;
    	}

    	//YOU ARE HERE AND YOU JUST COMMENTED OUT RIGHT ROTATE TO FIGURE OUT IF YOURE USING LEFT ROT INCORRECTLY

    	// left_ right_ 
    	if (balance > 1 && key > pastNode->left_->key_){ 
    		//std::cout<<"Left Right rotate"<<std::endl; //seg fault in here
        	//left_2_Rotate(pastNode->left_, pastNode->left_->right_);
        	left_Rotate(pastNode->left_, pastNode->left_->right_, pastNode->left_->right_->left_); //FIX
        	right_Rotate(pastNode, pastNode->left_, pastNode->left_->right_); 

        	//std::cout<< "Done with Left Right" << std::endl;
        	return;
    	}

    	// right_ left_ 
    	if (balance < -1 && key < pastNode->right_->key_){ 
    		//std::cout<<"Right Left rotate"<<std::endl;
        	//right_2_Rotate(pastNode->right_, pastNode->right_->left_); //right 2 rotate
        	right_Rotate(pastNode->right_, pastNode->right_->left_, pastNode->right_->left_->right_);
        	left_Rotate(pastNode, pastNode->right_, pastNode->right_->left_); 
        	return;
    	}
    	//std::cout << "I made it to the end!!" << std::endl;
	}
	return;
}

void BST::Delete(int key){
	std::shared_ptr<BSTNode> currentNode = root_;
	std::shared_ptr<BSTNode> temp = currentNode;
	std::shared_ptr<BSTNode> fowardRightNode = root_;
	std::shared_ptr<BSTNode> fowardLeftNode = root_;
	std::shared_ptr<BSTNode> lastNode = nullptr;
	
	while(currentNode!=nullptr){
		lastNode = currentNode;
//		std::cout << "lastNode: " << lastNode->key_ <<std::endl;
		if (currentNode->key_==key){
			break;
		}
		currentNode = (key < currentNode->key_) ? currentNode->left_ : currentNode->right_;	
		
	}

//		std::cout << "WHILE: " << std::endl;
		if(lastNode->key_ == key){
			if ((lastNode->key_ == root_->key_) && (missingLeftChild(lastNode) && missingRightChild(lastNode) == true)){
				//delete the tree?
				//std::cout<<"fuck tjis if";
				root_ = nullptr;
				lastNode = nullptr;
				size_ = 0;
				return;
			}
//			std::cout << " last node left: " << lastNode->left_ << std::endl;
			//fowardLeftNode = lastNode->right_->left_;
			if (lastNode->right_ == nullptr && lastNode->left_ == nullptr) {

				//std::cout << "before delete leaf" << std::endl;

				DeleteLeaf(lastNode);
				DeleteBalance(lastNode, key);
				//std::cout << "after delete leaf" << std::endl;
				
				return;
			}
//			std::cout << "find me " << std::endl;
			
			if (lastNode->right_ != nullptr){
//				std::cout << "lastNode->right_->key_: " << lastNode->right_->key_ << std::endl;
				
				fowardRightNode = lastNode->right_;
				if (fowardRightNode->left_ == nullptr){
//					std::cout << "here in loop: " << fowardRightNode->key_ << std::endl;
					
					if (lastNode->left_ == nullptr && fowardRightNode != nullptr){
						lastNode->parent_->left_ = fowardRightNode;
						fowardRightNode->parent_ = lastNode->parent_;
						DeleteBalance(fowardRightNode, key);
						return;
					}


					if (fowardRightNode->right_ != nullptr){ //to set up variables for next if's
						temp = fowardRightNode->right_;
						fowardRightNode->right_ = temp;
					}
					
					if (lastNode->parent_->left_ == lastNode){
						fowardRightNode->left_ = lastNode->left_;
						fowardRightNode->parent_ = lastNode->parent_;
					
						lastNode->parent_->left_ = fowardRightNode;
						lastNode->left_->parent_ = fowardRightNode;
						lastNode = nullptr;
						DeleteBalance(fowardRightNode, key);
						return;
					}
					if (lastNode->parent_->right_ == lastNode){
						fowardRightNode->left_ = lastNode->left_;
						fowardRightNode->parent_ = lastNode->parent_;

						lastNode->parent_->right_ = fowardRightNode;
						lastNode->left_->parent_ = fowardRightNode;
						lastNode = nullptr;
						DeleteBalance(fowardRightNode, key);
						return;
					}
				}
				if (fowardRightNode->left_ != nullptr){

					fowardLeftNode = fowardRightNode->left_;
				}
			}
//			std::cout << "fowNode: " << fowardRightNode->key_ << std::endl;

//			std::cout << "find me 2" << std::endl;
			//std::cout << "fowardRightNode: " << fowardLeftNode->key_ << std::endl;
			//we found the node, now we want to find its successor, right left most item
			if (lastNode->right_==nullptr){
//				std::cout << "lastNode 1: " << lastNode->key_ << std::endl;
				temp = lastNode->left_;
				temp->parent_=lastNode->parent_;
				lastNode->parent_->right_ = temp;
				lastNode=nullptr;
				DeleteBalance(temp, key);
				return;
			}

			if (fowardRightNode != nullptr){
//				std::cout << "find me 3" << std::endl;
				if(fowardLeftNode != nullptr){
//					std::cout << "find me 4" << std::endl;
					while(fowardLeftNode != nullptr){
//						std::cout << "find me 5" << std::endl;
//						std::cout << "fowardLeftNode: " << fowardLeftNode->key_ << std::endl;
						temp = fowardLeftNode;
						fowardLeftNode=fowardLeftNode->left_;
					}
				}
				else{
					temp=fowardRightNode;
				}
				temp->parent_->left_ = temp->right_;
				temp->parent_= lastNode->parent_;
				temp->left_ = lastNode->left_;
				temp->right_ = lastNode->right_;

				if (lastNode->right_ != nullptr){
				lastNode->right_->parent_ = temp;
				}
				if (lastNode->left_ != nullptr){
				lastNode->left_->parent_ = temp;
				}

				if (lastNode->parent_->left_ == lastNode){ 
				lastNode->parent_->left_ = temp;
				}
				if (lastNode->parent_->right_ == lastNode){
				lastNode->parent_->right_ = temp;
				}

				lastNode=nullptr;
				DeleteBalance(temp, key);
				return;
			}
			
		}
		return;
}

int BST::DeleteMin() {
	return DeleteMin(root_);

}


void BST::DeleteLeaf(std::shared_ptr<BSTNode> currentNode) {
	std::shared_ptr<BSTNode> parent = currentNode->parent_; //.lock();
	if (parent == nullptr) {
		// Delete root
		root_ = nullptr;
		size_--; assert(size_ == 0);
	} else {
		if (parent->right_ == currentNode) {
			parent->right_ = nullptr;
		} else if (parent->left_ == currentNode) {
			parent->left_ = nullptr;
		} else {
			std::cerr << "BST::DeleteLeaf Error: inconsistent state\n";
		}
		size_--; assert(size_ >= 0);
	}
}

void BST::DeleteMinBalance(std::shared_ptr<BSTNode> pastNode, int key){

	//min alone
	if(pastNode->parent_!=nullptr){
		pastNode=pastNode->parent_;
		pastNode->left_=nullptr;

		pastNode->height_ = 1 + max(height_of(pastNode->left_), height_of(pastNode->right_)); //can prob just switch to lastNode->left_->height_

		int balance = get_Balance(pastNode);
//		std::cout<<pastNode->key_<<std::endl;
//		std::cout<<balance<<std::endl;
//		std::cout<<"NOT YET"<<std::endl;
		if(balance < -1){
//			std::cout<<"IN if"<<std::endl;
			left_Rotate(pastNode, pastNode->right_, pastNode->right_->left_);
		}
		//if()

		return;
	}
	while(pastNode->parent_!=nullptr){

		pastNode=pastNode->parent_;

		pastNode->height_ = 1 + max(height_of(pastNode->left_), height_of(pastNode->right_)); //can prob just switch to lastNode->left_->height_

		int balance = get_Balance(pastNode);
//		std::cout<<pastNode->left_->key_<<std::endl;
//		std::cout<<pastNode->key_<<std::endl;
//		std::cout<<balance<<std::endl;
//		std::cout<<"NOT YET"<<std::endl;
		if(balance < -1){
//			std::cout<<"IN if"<<std::endl;
			left_Rotate(pastNode, pastNode->right_, pastNode->right_->left_);
		}

	}
}

int BST::DeleteMin(std::shared_ptr<BSTNode> currentNode) {
	std::shared_ptr<BSTNode> lastNode = nullptr;
	while (currentNode != nullptr) {
		lastNode = currentNode;
		currentNode = currentNode->left_;
	}
	int result = lastNode->key_;
	std::shared_ptr<BSTNode> parent = lastNode->parent_; //.lock();
	if (parent == nullptr) {
		// lastNode is root
		if (lastNode->right_ != nullptr) {
			root_ = lastNode->right_;
			lastNode->right_->parent_.reset();
		} else {
			root_ = nullptr;
		}
	} else {
		// lastNode under the root
		if (lastNode->right_ != nullptr) {
			parent->left_ = lastNode->right_;
			lastNode->right_->parent_ = parent;
//			std::cout<<"FUCK"<<std::endl;
			DeleteMinBalance(lastNode->right_, result);
//			std::cout<<"FUCK2"<<std::endl;
		} else {
//			std::cout<<"IHATE"<<std::endl;
			DeleteMinBalance(lastNode,result);
			parent->left_ = nullptr;
//			std::cout<<"IHATE2"<<std::endl;
			
		}
  }
  	//DeleteBalance(lastNode->right_, lastNode->right_->key_);
	size_--; assert(size_ >= 0);
	return result;
}

size_t BST::size() const {
	return size_;
}

bool BST::empty() const {
	return size_ == 0;
}

bool BST::Find(int key) const {
	std::shared_ptr<BSTNode> currentNode = root_;
	while (currentNode != nullptr) {
		if (currentNode->key_ == key) {
			return true;
		}
		currentNode = (key < currentNode->key_) ?
			currentNode->left_ : currentNode->right_;
	}
	return false;
}

std::string BST::JSON() {

//	std::cout << "\nIN JSON FUNCTION" << std::endl;

	nlohmann::json result;
	std::queue< std::shared_ptr<BSTNode> > nodes;

	if (root_ != nullptr) {
		result["root"] = root_->key_;
		nodes.push(root_);

		while (!nodes.empty()) { //infinite loop
			auto v = nodes.front();
			//std::cout << "WHILE: " << result.dump(2) + "\n";
			nodes.pop();
			std::string key = std::to_string(v->key_);
			v->balance_ = get_Balance(v);
			result[key]["balance factor"] = std::to_string(v->balance_ * -1);
			v->height_ = specialheight_of(v);
			result[key]["height"] = std::to_string(v->height_);
			if (v->left_ != nullptr) {
				result[key]["left"] = v->left_->key_;
				nodes.push(v->left_);
				//std::cout <<"1st if: "<< result.dump(2) + "\n";
			}
			if (v->right_ != nullptr) {
				result[key]["right"] = v->right_->key_;
				nodes.push(v->right_);
				//std::cout <<"2nd if: "<< result.dump(2) + "\n";
			}
			if (v->parent_ != nullptr) { //if (v->parent_.lock() != nullptr) {
				result[key]["parent"] = v->parent_->key_; //.lock()->key_;
				//std::cout <<"3rd if: "<< result.dump(2) + "\n";
			} 
			else {
				result[key]["root"] = true;
				//std::cout <<"else: "<< result.dump(2) + "\n";
			}
		}
	}
	result["height"] = root_->height_;
	result["root"] = root_->key_;
	result["size"] = size_;
	return result.dump(2) + "\n";
} 




int main(int argc, char const *argv[]) {
	
	std::ifstream inputFile;
	inputFile.open(argv[1]);
	nlohmann::json operations;
	if (inputFile.is_open()) {
		
		inputFile >> operations;
	} 

	BST nodes; //pq(maxHeapSize);

  for (auto itr = operations.begin(); itr != operations.end(); ++itr) {

  	
  	if (itr.key() != "metadata") {
  
  	 if (itr.value()["operation"] == "Insert") {
  	 		unsigned int key = itr.value()["key"];
//  	 		std::cout << "key: " << key << std::endl;
			nodes.Insert(key);
		} 
	if (itr.value()["operation"] == "DeleteMin") {
			nodes.DeleteMin();
		}

	if (itr.value()["operation"] == "Delete") {	
			unsigned int key = itr.value()["key"];	
			nodes.Delete(key);
	} 

	}
	else{
		continue;
	}	
  }

  std::cout << nodes.JSON();
  
  return 0;
}




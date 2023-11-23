#include<iostream>
#include<string>
#include<sstream>


using namespace std;


//assignee node
bool Found = false; //global variable found.
bool isNullptr = false;
string useName; //global string for accessing the name in tasks.
string color; //for storing the color of the nodes.
struct assignee {
	string fname;
	string lname;
	string address;
	string DOB;
	string ID;
	assignee* left;
	assignee* right;
	assignee* parent;
	bool black = false;
	bool dBlack = false;
	assignee() {

	}
	void setDetails(string f, string l, string a, string d, int i) {
		fname = f;
		lname = l;
		address = a;
		DOB = d;
		ID = generateID(i);
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	string generateID(int ai) {
		string fault = "A";
		fault = fault.append(to_string(ai));
		if (fault.size() == 4) {
			return fault;
		}
		else {
			int size = fault.size();
			if (size == 2) {
				fault = fault.insert(1, "00");
			}
			else {
				fault = fault.insert(1, "0");
			}
		}
		return fault;
	}
};
struct task {
	int ID;
	string detail;
	int priority; //low means high and vice versa
	string aID;
	task* left;
	task* right;
	task* parent;
	string name = "";
	bool black = false;
	bool completed = false;
	bool dBlack = false;
	void setDetails(int i, string d, int p, string ai) {
		ID = i;
		detail = d;
		priority = p;
		aID = ai;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	
};
//queue class
class queue {
public:
	task* head;
	task* tail;
	int size;
	queue() {
		head = NULL;
		tail = NULL;
		size = 0;
	}
	bool isEmpty(){
		if (head == NULL) {
			return true;
		}
		return false;
	}
	void Enqueue(task* input,string name) {
		task* temp = new task;
		temp->setDetails(input->ID,input->detail,input->priority,input->aID);
		temp->name = name;
		temp->black = input->black;
		temp->right = NULL;
		temp->left = NULL;
		if (isEmpty()) {
			head = temp;
			tail = temp;
			size++;
		}
		else {
			task* ahead = tail;
			tail->right = temp;
			temp->left = tail;
			tail = temp;
			
			if (tail->priority == temp->priority) {
				string tempAID;
				int tempID;
				int tempPriority;
				string tempDeets;
				bool tempBlack;
				while (ahead->left != NULL && ahead->left->priority == ahead->priority) {
					//swap values;
					if (ahead->left->ID > ahead->ID) {
						tempAID = ahead->left->aID;
						tempID = ahead->left->ID;
						tempPriority = ahead->left->priority;
						tempDeets = ahead->left->detail;
						tempBlack = ahead->left->black;
						ahead->left->aID = ahead->aID;
						ahead->left->ID = ahead->ID;
						ahead->left->priority = ahead->priority;
						ahead->left->detail = ahead->detail;
						ahead->left->black = ahead->black;
						 ahead->aID = tempAID;
						 ahead->ID = tempID;
						 ahead->priority = tempPriority;
						 ahead->detail = tempDeets;
						 ahead->black = tempBlack;
					}
					ahead = ahead->left;
				}
			}
			size++;
		}
		temp = NULL;

	}
	void traverse(std::ostream& output) {
		task* search = head;
		while (search != NULL) {
			if (search->black) {
				color = "black";
			}
			else {
				color = "red";
			}
			output << search->ID << " (" << color << ")" << endl;
			search = search->right;
		}
	}
};
//the real deal
template<typename T>
class RB {
public:
	T* root;
	int number;
	bool Single;
	bool Double;
	int total;
		RB() :root(){
			root = NULL;
			number = 1;
			Single = false;
			Double = false;
			total = 0;
	}
		bool isEmpty() {
			if (root == NULL) {
				return true;
			}
			return false;
	}
	//insertions for assignees
	void insertA(string fn, string ln, string ad, string dob) {
		//root = insertAssignee(root, fn, ln, ad, dob);
	}
	void insertAssignee(string fn, string ln, string ad, string dob) {
		assignee* temp = new assignee;
		temp->setDetails(fn, ln, ad, dob,number);
		assignee* parent = NULL;
		assignee* add = root;
		number++;
		while (add != NULL) {
			parent = add;
			if (temp->ID < add->ID) {
				add = add->left;
			}
			else {
				add = add->right;
			}
		}
		temp->parent = parent;
		if (parent == NULL) {
			root = temp;
		}
		else if (temp->ID < parent->ID) {
			parent->left = temp;
		}
		else {
			parent->right = temp;
		}
		if (temp->parent == NULL) {
			temp->black = true;
			return;
		}
		if (temp->parent->parent == NULL) {
			return;
		}

		FixTree(temp);
	}
	
	void print2D(assignee* input, int space) {
		if (input == NULL) {
			return;
		}
		space += 10;
		print2D(input->right, space);
		cout << endl;
		for (int i = 1;i < space;i++) {
			cout << " ";
		}
		cout <<input->ID<<" "<< input->address << " " << input->black << endl;
		print2D(input->left, space);
	}void print2D(task* input, int space) {
		if (input == NULL) {
			return;
		}
		space += 10;
		print2D(input->right, space);
		cout << endl;
		for (int i = 1;i < space;i++) {
			cout << " ";
		}
		cout << input->detail << " "<<input->black << endl;
		print2D(input->left, space);
	}
	
	
	//insertions for assignees
	//insertions for tasks
	/*void insertT(int i, string d, int p, string ai) {
		root = insertTask(root, i, d, p, ai);
	}*/
	
	void insertTask(int i, string d, int p, string ai) {
		task* temp = new task;
		temp->setDetails(i, d, p, ai);
		task* parent = NULL;
		task* add = root;
		total++;
		while (add != NULL) {
			parent = add;
			if (p < add->priority) {
				add = add->left;
			}
			else {
				add = add->right;
			}
		}
		temp->parent = parent;
		if (parent == NULL) {
			root = temp;
		}
		else if (temp->priority < parent->priority) {
			parent->left = temp;
		}
		else {
			parent->right = temp;
		}

		if (temp->parent == NULL) {
			temp->black = true;
			return;
		}

		if (temp->parent->parent == NULL) {
			return;
		}

		FixTree(temp);
	}
	void FixTree(T*& k) { //k is the newly inserted node.
		T* u; //temp variable to store pointer

		while (!k->parent->black) {
			/*if (k->parent == NULL || k->parent->parent->right) {
				throw std::runtime_error("null reference");
			}*/
			if (k->parent == k->parent->parent->right) { //k->parent == k->parent->parent->right
				case1(k, u);
			}
			else {
				case2(k, u);
			}
			if (k == root) {
				break;
			}
		}
		root->black = true;
	}
	
	void leftRotate(T* x) {
		T* y = x->right;
		x->right = y->left;
		if (y->left != NULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	void rightRotate(T* x) {
		T* y = x->left;
		x->left = y->right;
		if (y->right != NULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
	void case1(T*& k, T*& u) {
		u = k->parent->parent->left;
		//cout << "here" << endl;
		if (u != NULL) {
			if (!u->black) {
				u->black = true;
				k->parent->black = true;
				k->parent->parent->black = false;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->left) { //k->priority < k->parent->priority && k->parent->priority < k->parent->parent->priority
					k = k->parent;
					rightRotate(k);
					//cout << k->priority << endl;
				}

				k->parent->black = true;
				k->parent->parent->black = false;
				leftRotate(k->parent->parent);
			}
		}
		else {
			if (k == k->parent->left) { //k->priority < k->parent->priority && k->parent->priority < k->parent->parent->priority
				k = k->parent;
				rightRotate(k);
				//cout << k->priority << endl;
			}

			k->parent->black = true;
			k->parent->parent->black = false;
			leftRotate(k->parent->parent);
		}
	}
	void case2(T*& k, T*& u) {
		u = k->parent->parent->right;
		if (u != NULL) {
			if (!u->black) {
				//cout << "here" << endl;
				u->black = true;
				k->parent->black = true;
				k->parent->parent->black = false;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->right) {
					//cout << "here" << endl;
					k = k->parent;
					leftRotate(k);
				}
				//cout << "HERE" << endl;
				k->parent->black = true;
				k->parent->parent->black = false;
				rightRotate(k->parent->parent);
			}
		}
		else {
			//cout << "HERE" << endl;
			if (k == k->parent->right) {
				//cout << "here" << endl;
				k = k->parent;
				leftRotate(k);
			}
			//cout << "HERE" << endl;
			k->parent->black = true;
			k->parent->parent->black = false;
			rightRotate(k->parent->parent);
		}
	}
	//insertion for tasks
	//search funtions
	//assignee
	void search(assignee* find,string id,std::ostream& output) {
		if (find == NULL) {
			output << "ID not found" << endl;
			return;
			}
		if (find->ID == id) {
			output << "Name: " << find->fname <<" "<< find->lname << ", " << "Address: " << find->address << ", " 
				<< "DOB: " << find->DOB << ", " << "Assignee ID: " << find->ID << endl;
			return;
		}
		else {
			
			if (id < find->ID) {
				
				search(find->left, id,output);
			}
			else {
				
				search(find->right, id,output);
			}
		}
	}
	void searchID(string id,std::ostream& output) {
		 search(root, id,output);
	}
	void searchName(assignee* traverse, string first, string last, std::ostream& output) {
		if (traverse == NULL) {
			return;
		}
		searchName(traverse->left, first, last, output);
		if (traverse->fname == first && traverse->lname == last) {
			cout << "Color: " << traverse->black << endl;
			output << "Name: " << traverse->fname << " " << traverse->lname << ", " << "Address: " << traverse->address
				<< ", " << "DOB: " << traverse->DOB << ", " << "Assignee ID: " << traverse->ID << endl;
		}
		searchName(traverse->right, first, last, output);

	}
	void searchName(string first, string last, std::ostream& output) {
		searchName(root, first, last, output);
	}
	//rotations assignee
	
	//rotations assignee
	//display for no task found
	void searchNoTask(task* find,string id) {
		if (find == NULL) {
			return;
		}
		searchNoTask(find->left, id);
		if (find->aID == id) {
			Found = true;
		}
		searchNoTask(find->right, id);
	}
	void searchNoTask(string id) {
		return searchNoTask(root, id);
	}
	void notask(RB<task> &tree, std::ostream& output) {
		notask(root, tree, output);
		Found = false;
	}
	void notask(assignee* value, RB<task>& tree, std::ostream& output) {
		if (value == NULL) {
			return;
		}
		notask(value->left, tree, output);
		tree.searchNoTask(value->ID);
		if (!Found) {
			output << "Name: " << value->fname << " " << value->lname << ", " << "Address: " << value->address
			<< ", " << "DOB: " << value->DOB << ", " << "Assignee ID: " << value->ID << endl;
			Found = false;
		}
		notask(value->right, tree, output);
	}
	void shift(task* find, string id1, string id2) {
		if (find == NULL) {
			return;
		}
		shift(find->left, id1, id2);
		if (find->aID == id1) {
			find->aID = id2;
		}
		shift(find->right, id1, id2);
	}
	//searching and returning a ID name.
	void getName(assignee* find, string id) {
		if (find == NULL) {
			return;
		}
		getName(find->left, id);
		if (find->ID == id) {
			useName = find->fname;
		}
		getName(find->right, id);
	}
	void taskQueue(task* traverse,RB<assignee>& tree, std::ostream& output) {
		if (traverse == NULL) {
			return;
		}
		taskQueue(traverse->left, tree, output);
		tree.getName(tree.root, traverse->aID);
		if (!traverse->completed) {
			output << "Task ID: " << traverse->ID << ", " << "Description: " << traverse->detail << ", " << "Priority: " << traverse->priority << ", " << "Assignee: " << useName << " " << "("
				<< traverse->aID << ")" << endl;
		}
		taskQueue(traverse->right, tree, output);
	}
	//deletions here. Scary
	//first following simple bst deletion.
	void DeleteAssignee(string id, RB<task>& tree) {
		bool originallyBlack;
		assignee* x = new assignee;
		assignee* y = new assignee;
		assignee* saveY = new assignee;
		if (root == NULL) {
			return;
		}
		assignee* find = root;
		while (find != NULL) {
			if (find->ID == id) {
				break;
			}
			if (find->ID > id) {
				find = find->left;
			}
			else if(find->ID < id){
				find = find->right;
			}
		}
		//before deleting the assignee we check whether the assignee has a task alloted to them or not.
		// if there is a task alloted then we do not delete the following assignee.
		y = find;
		originallyBlack = find->black;
		//having issues if the node to be deleted is leaf and black or has children and is red.
		tree.searchNoTask(id);
		if (Found) {
			Found = false;
			return;
		}
		//parent pointer linkages are being kept so accessing the sibling is easier.
		//checking the various cases for deletion.
		if (find->left == NULL && find->right == NULL) {
			//case for either a black node or a red node.
			
			
			if (find->parent && !find->black) {
				x = find;
				if (find == find->parent->left) {
					find->parent->left = NULL;
				}
				else if(find==find->parent->right) {
					find->parent->right = NULL;
				}
			}
			else if (find->parent && find->black) {
				//double black case
				isNullptr = true;
				x->black = true;
				saveY = find->parent;
				if (find == find->parent->left) {

					find->parent->left = x;
					x->parent = find->parent;
					find->parent = NULL;
				}
				else if (find == find->parent->right) {
					find->parent->right = x;
					x->parent = find->parent;
					find->parent = NULL;
				}
			}
		}
		//case 2 with atleast one child.
		//check if child is on the left or on the right.
		
		else if (find->left == NULL) {
			//in this case the child is on the right side.
			 x = find->right;
			subTreeLink(find, find->right);
			//delete find;
		}
		else if (find->right == NULL) {
			//in this case the child is on the left side.
			x = find->left;
			subTreeLink(find, find->left);
			//delete find;
		}
		////case 3 with two children.
		else { //both pointers are found to be having values in them.
			 InorderPredecessor(find->left,y);
			 originallyBlack = y->black;
				 saveY = y;
			 if (y->left == NULL) {
				 y->left = x;
				 x = y->left;
				 isNullptr = true;
			 }
			 else {
				 x = y->left;
			 }
			 x->black = true; //treating x as a null node not a new node.
			if (y->parent == find) {
				x->parent = y;
			}
			else {
				subTreeLink(y, x);
				y->left = find->left;
				y->left->parent = y;
			}
			subTreeLink(find, y);
			y->right = find->right;
			y->right->parent = y;
			y->black = find->black;
		}

		delete find;
		if (originallyBlack) {
			cout << "Double Black" << endl;
			DelFix(x);
		}
		if (isNullptr) {
			saveY->left = NULL;
			isNullptr = false;
		}
	}
	void DeleteTask(int p,int id) {
		bool originallyBlack;
		task* x = new task;
		task* y = new task;
		task* saveY = new task;
		total--;
		if (root == NULL) {
			return;
		}
		task* find = root;
		while (find != NULL) {
			if (find->ID == id) {
				break;
			}
			if (find->priority > p) {
				find = find->left;
			}
			else if (find->priority <= p) {
				find = find->right;
			}
		}
		//before deleting the assignee we check whether the assignee has a task alloted to them or not.
		// if there is a task alloted then we do not delete the following assignee.
		//cout << "This is task delete" << " " << find->ID << endl;
		y = find;
		cout << find->black << " inside delte" << endl;
		originallyBlack = find->black;
		//having issues if the node to be deleted is leaf and black or has children and is red.
		/*searchNoCompleted(find->ID,find->priority);
		if (!Found) {
			Found = false;
			return;
		}*/
		//parent pointer linkages are being kept so accessing the sibling is easier.
		//checking the various cases for deletion.
		if (find->left == NULL && find->right == NULL) {
			//case for either a black node or a red node.


			if (find->parent && !find->black) {
				x = find;
				if (find == find->parent->left) {
					find->parent->left = NULL;
				}
				else if (find == find->parent->right) {
					find->parent->right = NULL;
				}
			}
			else if (find->parent && find->black) {
				//double black case
				isNullptr = true;
				x->black = true;
				saveY = find->parent;
				if (find == find->parent->left) {

					find->parent->left = x;
					x->parent = find->parent;
					find->parent = NULL;
				}
				else if (find == find->parent->right) {
					find->parent->right = x;
					x->parent = find->parent;
					find->parent = NULL;
				}
			}
		}
		//case 2 with atleast one child.
		//check if child is on the left or on the right.

		else if (find->left == NULL) {
			//in this case the child is on the right side.
			x = find->right;
			subTreeLink(find, find->right);
			//delete find;
		}
		else if (find->right == NULL) {
			//in this case the child is on the left side.
			x = find->left;
			subTreeLink(find, find->left);
			//delete find;
		}
		////case 3 with two children.
		else { //both pointers are found to be having values in them.
			InorderPredecessor(find->left, y);
			originallyBlack = y->black;
			saveY = y;
			if (y->left == NULL) {
				y->left = x;
				x = y->left;
				isNullptr = true;
				x->black = true;  //treating x as a null node not a new node.
			}
			else {
				x = y->left;
			}
			
			if (y->parent == find) {
				x->parent = y;
			}
			else {
				saveY = y->parent;
				subTreeLink(y, x);
				y->left = find->left;
				y->left->parent = y;
				saveY->right = NULL;
			}
			subTreeLink(find, y);
			y->right = find->right;
			y->right->parent = y;
			y->black = find->black;
			cout << "color: " << y->black << endl;
		}

		delete find;
		cout << "I reached  here" << endl;
		if (originallyBlack) {
			cout << "Double Black" << endl;
			DelFix(x);
		}
		if (isNullptr) {
			saveY->left = NULL;
			isNullptr = false;
		}
	}
	void DelFix(T*& value) { //the real deal starts here.
		T* sibling = NULL;
		bool elseCondition = true;
		//cout << value->parent->ID << endl;
		while (value != root && value->black) { //we have a double black case.
			cout << "counter" << endl;
			elseCondition = true;
			if (value == value->parent->left) {
				sibling = value->parent->right;
				//cout << value->ID << endl;
				if (!sibling->black) {
					sibling->black = true;
					value->parent->black = false;
					leftRotate(value->parent);
					sibling = value->parent->right;
					
					//cout << sibling->ID << endl;
				}
				//check if sibling has both children as red or not.
				if ((sibling->left == NULL && sibling->right == NULL)) { //
						cout << "case 21" << endl;
						sibling->black = false;
						value = value->parent;
						elseCondition = false;
					}
				else if (sibling->left == NULL && sibling->right!=NULL) {
					if (sibling->right->black) {
						sibling->black = false;
						value = value->parent;
						elseCondition = false;
					}
				}
				else if (sibling->left!=NULL && sibling->right == NULL) {
					if (sibling->left->black) {
						sibling->black = false;
						value = value->parent;
						elseCondition = false;
						elseCondition = false;
					}
				}
				else if (sibling->left->black && sibling->right->black) {
						cout << "case 22" << endl;
						sibling->black = false;
						value = value->parent;
						elseCondition = false;
					}
				
				 if(elseCondition) {
						if (sibling->right == NULL) {
							cout << "case 31" << endl;
							sibling->left->black = true;
								sibling->black = false;
								cout << "case31" << endl;
								rightRotate(sibling);
								sibling = value->parent->right;
							cout << "case 31 exit" << endl;
						}
						else if (sibling->right->black) {
							cout << "case 32" << endl;
							sibling->left->black = true;
							sibling->black = false;
							rightRotate(sibling);
							sibling = value->parent->right;
						}
							cout << "case 4" << endl;
							sibling->black = value->parent->black;
							value->parent->black = true;
							sibling->right->black = true;
							leftRotate(value->parent);
							value = root;
					}
					

			}
			else {
				cout << "else case" << endl;
				sibling = value->parent->left;
				if (!sibling->black) {
					sibling->black = true;
					value->parent->black = false;
					leftRotate(value->parent);
						
						sibling = value->parent->left;
				}
				if ((sibling->left == NULL && sibling->right == NULL)) { //
					cout << "case 21" << endl;
					sibling->black = false;
					value = value->parent;
					elseCondition = false;
				}
				else if (sibling->left == NULL && sibling->right != NULL) {
					if (sibling->right->black) {
						sibling->black = false;
						value = value->parent;
						elseCondition = false;
					}
				}
				else if (sibling->left != NULL && sibling->right == NULL) {
					if (sibling->left->black) {
						sibling->black = false;
						value = value->parent;
						elseCondition = false;
						elseCondition = false;
					}
				}
				else if (sibling->left->black && sibling->right->black) {
					cout << "case 22" << endl;
					sibling->black = false;
					value = value->parent;
					elseCondition = false;
				}
				if (elseCondition) {
					if (sibling->left == NULL) {
						sibling->left->black = true;
						sibling->black = false;
						rightRotate(sibling);
						sibling = value->parent->left;
					}
					else if (sibling->left->black) {
						sibling->left->black = true;
						sibling->black = false;
						rightRotate(sibling);
						sibling = value->parent->left;
					}
					sibling->black = value->parent->black;
					value->parent->black = true;
					sibling->right->black = true;
					leftRotate(value->parent);
					value = root;
				}
			}
		}
		value->black = true;
	}
	void subTreeLink(T* value, T* vChild) {
		if (value == root) {
			root = vChild;
		}
		else if (value == value->parent->left) {
			value->parent->left = vChild;
		}
		else {
			value->parent->right = vChild;
		}
		vChild->parent = value->parent; //where vChild is the child node of value.
	}
	void InorderPredecessor(T* find,T*& assign) {
		while (find->right != NULL) {
			find = find->right;
		}
		assign = find;
	}
	//deletions
	// 
	void updateTask(int id, int newPriority) {
		task* update = new task;
		upDatePriority(root, id, update); //storing all details of the task whose priority is to be updated.
		cout <<"UPdate ID: " << update->ID << endl;
		DeleteTask(update->priority, update->ID);
		//print2D(root, 10);
		insertTask(update->ID, update->detail, newPriority, update->aID);
		//task* storeUpdate = update;

	}
	void deleteTheTask(int id) {
		task* find = new task;
		upDatePriority(root, id, find);
		cout << "FInd: " << find->priority << endl;
		DeleteTask(find->priority, find->ID);
	}
	void completeTask(task* find,int id) {
		if (find == NULL) {
			return;
		}
		completeTask(find->left, id);
		if (find->ID == id) {
			find->completed = true;
		}
		completeTask(find->right, id);
	}
	//print tasks in order
	void inorderTasks(task* traverse, std::ostream& output) {
		if (traverse == NULL) {
			return;
		}
		inorderTasks(traverse->left, output);
		if (traverse->black) {
			color = "black";
		}
		else {
			color = "red";
		}
		output << traverse->ID << " (" << color << ")" << endl;
		inorderTasks(traverse->right, output);
	}
	void inorderTasks(task* traverse, queue& Task,RB<assignee>& tree) {
		if (traverse == NULL) {
			return;
		}
		inorderTasks(traverse->left, Task,tree);
		tree.getName(tree.root, traverse->aID);
		Task.Enqueue(traverse,useName);
		inorderTasks(traverse->right, Task,tree);
	}
	void inOrderAssignee(assignee* traverse, std::ostream& output) {
		if (traverse == NULL) {
			return;
		}
		inOrderAssignee(traverse->left, output);
		if (traverse->black) {
			color = "black";
		}
		else {
			color = "red";
		}
		output << traverse->ID << " (" << color << ")" << endl;
		inOrderAssignee(traverse->right, output);
	}
	void displayAssignee(assignee* traverse, std::ostream& output) {
		if (traverse == NULL) {
			return;
		}
		displayAssignee(traverse->left, output);
		output << "Name: " << traverse->fname << " " << traverse->lname << ", " << "Address: " << traverse->address
			<< ", " << "DOB: " << traverse->DOB << ", " << "Assignee ID: " << traverse->ID << endl;
		displayAssignee(traverse->right, output);
	}
	void searchNoCompleted(int id, int priority) {
		task* check = root;
		while (check != NULL) {
			if (check->ID == id) {
				break;
			}
			else if (check->priority <= priority) {
				check = check->right;
			}
			else if (check->priority > priority) {
				check = check->left;
			}
		}
		if (!check->completed) {
			Found = true;
		}
	}
	void upDatePriority(task* traverse, int id,task*& reference) {
		if (traverse == NULL) {
			return;
		}
		upDatePriority(traverse->left, id,reference);
		if (traverse->ID == id) {
			reference->setDetails(traverse->ID, traverse->detail, traverse->priority, traverse->aID);
			return;
		}
		upDatePriority(traverse->right, id, reference);
	}
	void HighestPriority(std::ostream& output) {
		task* high = root;
		while (high->left != NULL) {
			high = high->left;
		}
		traverseHigh(root, high->priority, output);
	}
	//helper to traverse all the same priority tasks.
	void traverseHigh(task* traverse,int priority, std::ostream& output) {
		if (traverse == NULL) {
			return;
		}
		if (traverse->priority > priority) {
			return;
		}
		traverseHigh(traverse->left, priority, output);
		if (traverse->priority == priority) {
			output << "Task ID: " << traverse->ID << ", " << "Description: " << traverse->detail << ", " << "Priority: " << traverse->priority << ", " << "Assignee: " << useName << " " << "("
				<< traverse->aID << ")" << endl;
		}
		traverseHigh(traverse->right, priority, output);
	}
	void taskbyassignee(task* traverse, string aid, std::ostream& output) {
		if (traverse == NULL) {
			return;
		}
		taskbyassignee(traverse->left, aid, output);
		if (traverse->aID == aid) {
			output << "Task ID: " << traverse->ID << ", " << "Description: " << traverse->detail << ", " << "Priority: " << traverse->priority << ", " << "Assignee: " << useName << " " << "("
				<< traverse->aID << ")" << endl;
		}
		taskbyassignee(traverse->right, aid, output);
	}
	void completedTask(task* traverse, std::ostream& output,RB<assignee>& tree) {
		if (traverse == NULL) {
			return;
		}
		completedTask(traverse->left, output,tree);
		tree.getName(tree.root, traverse->aID);
		if (traverse->completed) {
			output<< "Task ID: " << traverse->ID << ", " << "Description: " << traverse->detail << ", " << "Priority: " << traverse->priority << ", " << "Assignee: " << useName << " " << "("
				<< traverse->aID << ")" << endl;
		}
		completedTask(traverse->right, output,tree);
	}
	void priorityRange(task* traverse, int r1, int r2, std::ostream& output,RB<assignee>& tree) {
		if (traverse == NULL) {
			return;
		}
		priorityRange(traverse->left, r1, r2, output,tree);
		tree.getName(tree.root, traverse->aID);
		if (traverse->priority >= 1 && traverse->priority <= 2) {
			output  << "Task ID: " << traverse->ID << ", " << "Description: " << traverse->detail << ", " << "Priority: " << traverse->priority << ", " << "Assignee: " << useName << " " << "("
				<< traverse->aID << ")" << endl;
		}
		priorityRange(traverse->right, r1, r2, output, tree);
	}
};
//red black tree ends here
//taskManagement class
class taskManagementSystem {
public:
	RB<assignee> people; //will be made on the basis of the ID which is always increasing so the addition is always on the right.
	RB<task> work; //will be made on the basis of priority of task if low then high and vice versa.
	void addAssignee(string fn, string ln, string ad, string dob) {
		people.insertAssignee(fn, ln, ad, dob);
	}
	void addTask(int i, string d, int p, string ai) {
		work.insertTask(i, d, p, ai);
	}
	void displaybyID(std::stringstream& output, string id) {
		people.searchID(id, output);
	}
	void displaybyname(std::ostream& output,string first,string last) {
		people.searchName(first, last, output);
	}
	void AssigneeWithNoTask(std::ostream& output) {
		people.notask(work, output);
	}
	void printTaskQueue(std::ostream& output) {
		//since tasks are alr in order of priority using inorder traversal.
		work.taskQueue(work.root, people, output);
	}
	void ShiftTask(string id1,string id2) {
		work.shift(work.root, id1, id2);
	}
	void DeleteAssignee(string id) {
		people.DeleteAssignee(id,work);
	}
	void DisplayAssignee(std::ostream& output) {
		people.displayAssignee(people.root, output);
	}
	void PrintTreeInorder(std::ostream& output) {
		queue Task;
		work.inorderTasks(work.root,Task,people);
		Task.traverse(output);
	}
	void AssigneeInOrder(std::ostream& output) {
		people.inOrderAssignee(people.root, output);
	}
	void completeTask(int id) {
		work.completeTask(work.root, id);
	}
	void updateTaskPriority(int id, int priority) {
		work.updateTask(id, priority);
	}
	void findHighestPriorityTask(std::ostream& output) {
		work.HighestPriority(output);
	}
	void findTasksByAssignee(string aid,std::ostream& output) {
		people.getName(people.root, aid);
		output << "Tasks Assigned to "<< "\""<<useName<<" (" << aid <<")\":\n";
		work.taskbyassignee(work.root, aid, output);
	}
	void deleteTask(int id) {
		work.deleteTheTask(id);
	}
	void displayCompletedTasks(std::ostream& output) {
		output << "Completed Tasks:\n";
		work.completedTask(work.root, output,people);
	}
	void searchTasksByPriorityRange(int rangeLeft, int rangeRight, std::ostream& output) {
		output << "Tasks within Priority Range" << " (" << rangeLeft << " to " << rangeRight << "):\n";
		work.priorityRange(work.root, rangeLeft, rangeRight, output, people);
	}
	void countTotalTasks(std::ostream& output) {
		output << "Total Tasks in the System: " << work.total << "\n";
	}
};

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cstring>
using namespace std;

typedef enum {entry,head}tagfield;

typedef struct {
	int col;
	int row;
	int value;}entry_Node;
	
typedef struct matrixNode * Pointer_Node;

struct matrixNode{
	Pointer_Node down,right;
	tagfield tag;
	union {
		entry_Node entry;
		Pointer_Node next;}u;
};

vector <string>Input_Splitted;

//..........................Function Used.....................
bool Seperation(string);
int getValue();
Pointer_Node mread();
void mwrite(Pointer_Node);
Pointer_Node mtranspose(Pointer_Node);
Pointer_Node mmult(Pointer_Node,Pointer_Node);


int Number_Matrix=0; 

int main (){
	Pointer_Node MatrixA=mread();
	Pointer_Node MatrixB=mread();
	cout<<"b Transpose"<<endl;
	Pointer_Node MatrixB_Tran=mtranspose(MatrixB);
	mwrite(MatrixB_Tran);
	Pointer_Node MatrixC=mmult(MatrixA,MatrixB);
	if(MatrixC){
		cout<<"a*b transpose"<<endl;
		cout<<"numRows="<<MatrixC->u.entry.row<<",numcols="<<MatrixC->u.entry.col;
		cout<<"The Matrix by row,column and value:"<<endl;
		mwrite(MatrixC);}
	else {
		cout<<"Error, the matrix cant multiply"<<endl;}
}

bool Seperation(string input){
	istringstream ss(input);
	char Split_char=' ';
	string temp;
	while(getline(ss,temp,Split_char)){
		Input_Splitted.push_back(temp);
	}
	if (Input_Splitted.size()<1)
		return false;
	else 
		return true;
}

int getValue(){
	int temp=stoi(Input_Splitted.at(0),NULL);
	Input_Splitted.erase(Input_Splitted.begin());
	return temp;
}

Pointer_Node mread(){
	Pointer_Node tempNode;//temporaty pointer to a node
	int Number_Element=0;
	Input_Splitted.clear();
	cout<<"Please enter the number of row , column and non-zero term"<<endl;
	string stringtemp;
	do{
		getline(cin,stringtemp);
	if (Seperation(stringtemp)){
		int Number_Row=getValue(),Number_Column=getValue();
		int Number_NonZero=getValue(),Number_Head;
		Pointer_Node Ini_Node=new matrixNode();
		Ini_Node->u.entry.row=Number_Row;
		Ini_Node->u.entry.col=Number_Column;
		Ini_Node->u.entry.value=Number_NonZero;
		if(Number_Row>Number_Column){
			Number_Head=Number_Row;}
		else {
			Number_Head=Number_Column;}
		Pointer_Node Header_Node[Number_Head];
		for (int i=0;i<Number_Head;i++){
			tempNode=new matrixNode;
			Header_Node[i]=tempNode;
			Header_Node[i]->right=tempNode;
			Header_Node[i]->u.next=tempNode;
			Header_Node[i]->tag=head;
		}
		int temp_Col,temp_Row,temp_Value,current_row=0;
		//variable to store row , column and value for each line
		cout<<"Start enter the matrix :"<<endl;
		Pointer_Node lastNode=Header_Node[0];//To record the last node of each row
		current_row=0;
		while(Number_Element<Number_NonZero){
			getline(cin,stringtemp);
			if(Seperation(stringtemp)){
				temp_Row=getValue();
				temp_Col=getValue();
				temp_Value=getValue();
				if(temp_Row!=current_row){
					lastNode->right=Header_Node[current_row];
					current_row=temp_Row;
					lastNode=Header_Node[current_row];
				}
				tempNode=new matrixNode;
				lastNode->right=tempNode;
				tempNode->u.entry.col=temp_Col;
				tempNode->u.entry.row=temp_Row;
				tempNode->u.entry.value=temp_Value;
				tempNode->tag=entry;
				lastNode=lastNode->right;
				Header_Node[temp_Col]->u.next->down=tempNode;
				Header_Node[temp_Col]->u.next=tempNode;
				Number_Element++;
				}
			}	
		lastNode->right=Header_Node[current_row];

		for (int i=0;i<Number_Column;i++){
			Header_Node[i]->u.next->down=Header_Node[i];
		}
		for (int i=0;i<Number_Head-1;i++){
			//number_head -1 because the last node.next need to linked to the initial>node
			Header_Node[i]->u.next=Header_Node[i+1];
		}
		Header_Node[Number_Head-1]->u.next=Ini_Node;
		Ini_Node->right=Header_Node[0];
		Number_Matrix++;
		return Ini_Node;
	}
	else {
		cout<<"Please enter valid number"<<endl;
	}
	}while(!Seperation(stringtemp));
}

void mwrite(Pointer_Node k){
	int Number_Column=k->u.entry.col;
	int Number_Row=k->u.entry.row;
	int Number_Head;
	if(Number_Row>Number_Column){
		Number_Head=Number_Row;}
	else {
		Number_Head=Number_Column;}
	Pointer_Node Current_Header=k->right;
	while(Current_Header!=k){
		Pointer_Node tempNode=Current_Header->right;
		while(tempNode!=Current_Header){
			cout<<tempNode->u.entry.row<<" "<<tempNode->u.entry.col<<" ";
			cout<<tempNode->u.entry.value<<endl;
			tempNode=tempNode->right;
		}
		Current_Header=Current_Header->u.next;
	}
}

Pointer_Node mtranspose(Pointer_Node k){
	int Number_Column=k->u.entry.col;
	int Number_Row=k->u.entry.row;
	int Number_NonZero=k->u.entry.value;
	int Number_Head;
	if(Number_Row>Number_Column){
		Number_Head=Number_Row;}
	else {
		Number_Head=Number_Column;}
	cout<<"Number of row:"<<Number_Column<<",Number of column:"<<Number_Row<<endl;
	cout<<"The matrix by row,column and value:"<<endl;
	Pointer_Node Ini_Node=new matrixNode(),tempNode,Current_Header,lastNode;
	Ini_Node->u.entry.row=Number_Column;
	Ini_Node->u.entry.col=Number_Row;
	Ini_Node->u.entry.value=Number_NonZero;
	Pointer_Node Header_Node[Number_Head];
	for (int i=0;i<Number_Head;i++){
		tempNode=new matrixNode;
		Header_Node[i]=tempNode;
		Header_Node[i]->right=tempNode;
		Header_Node[i]->u.next=tempNode;
		Header_Node[i]->tag=head;
	}
	int temp_Row,temp_Col,temp_Value,Col_index=0;
	Pointer_Node temp_New_Node;
	Current_Header=k->right;
	while(Current_Header!=k){
		tempNode=Current_Header->down;
		lastNode=Header_Node[Col_index];
		while(tempNode!=Current_Header){
			temp_Row=tempNode->u.entry.col;
			temp_Col=tempNode->u.entry.row;
			temp_Value=tempNode->u.entry.value;
			temp_New_Node=new matrixNode;
			temp_New_Node->u.entry.row=temp_Row;
			temp_New_Node->u.entry.col=temp_Col;
			temp_New_Node->u.entry.value=temp_Value;
			lastNode->right=temp_New_Node;
			lastNode=lastNode->right;
			Header_Node[temp_Col]->u.next->down=temp_New_Node;
			Header_Node[temp_Col]->u.next=temp_New_Node;
			tempNode=tempNode->down;
		}
		lastNode->right=Header_Node[Col_index++];
		Current_Header=Current_Header->u.next;
	}
	for (int i=0;i<Number_Column;i++){
		Header_Node[i]->u.next->down=Header_Node[i];
	}
	for (int i=0;i<Number_Head-1;i++){
		//number_head -1 because the last node.next need to linked to the initial>node
		Header_Node[i]->u.next=Header_Node[i+1];
	}
	Header_Node[Number_Head-1]->u.next=Ini_Node;
	Ini_Node->right=Header_Node[0];
	Number_Matrix++;
	return Ini_Node;
}

Pointer_Node mmult(Pointer_Node A,Pointer_Node B){
	//Assung B is transpose 
	int Number_Row=B->u.entry.col;
	int Number_Col=A->u.entry.col;
	if (Number_Col!=Number_Row){
		return NULL;}
	else {
		Pointer_Node tempNode,Ini_Node;
		Number_Row=A->u.entry.row;
		Number_Col=B->u.entry.row;
		int Number_Head,sum=0;
		if(Number_Row>Number_Col){
			Number_Head=Number_Row;}
		else {
			Number_Head=Number_Col;}
		Ini_Node=new matrixNode;
		Ini_Node->u.entry.col=Number_Col;
		Ini_Node->u.entry.row=Number_Row;
		Pointer_Node Header_Node[Number_Head];
		for (int i=0;i<Number_Head;i++){
			tempNode=new matrixNode;
			Header_Node[i]=tempNode;
			Header_Node[i]->right=tempNode;
			Header_Node[i]->u.next=tempNode;
			Header_Node[i]->tag=head;
		}
		Pointer_Node temp_Head_A,temp_Head_B,tempA,tempB,lastNode;
		temp_Head_A=A->right;
		while(temp_Head_A!=A){
			tempA=temp_Head_A->right;
			temp_Head_B=B->right;
			int current_col=tempA->u.entry.row,current_row;
			while(temp_Head_B!=B){
				tempB=temp_Head_B->right;
				current_row=tempB->u.entry.row;
				lastNode=Header_Node[current_col];
				while(tempB!=temp_Head_B&&tempA!=temp_Head_A){
					if(tempB->u.entry.col==tempA->u.entry.col){
						sum+=tempB->u.entry.value*tempA->u.entry.value;					
						tempA=tempA->right;						
						tempB=tempB->right;
					}
					else if(tempB->u.entry.col>tempA->u.entry.col){
						tempA=tempA->right;
					}
					else if(tempB->u.entry.col<tempA->u.entry.col){
						tempB=tempB->right;}
				}
				if(sum){
					tempNode=new matrixNode;
					lastNode->down=tempNode;
					tempNode->u.entry.col=current_row;
					tempNode->u.entry.row=current_col;
					tempNode->u.entry.value=sum;
					tempNode->tag=entry;
					lastNode=lastNode->down;
					Header_Node[current_row]->u.next->right=tempNode;
					Header_Node[current_row]->u.next=tempNode;
					sum=0;
				}
				temp_Head_B=temp_Head_B->u.next;
				tempA=temp_Head_A->right;
			}
			lastNode->down=Header_Node[current_col];
			temp_Head_A=temp_Head_A->u.next;
		}
		for (int i=0;i<Number_Row;i++){
			Header_Node[i]->u.next->right=Header_Node[i];
		}
		for (int i=0;i<Number_Head-1;i++){
		//number_head -1 because the last node.next need to linked to the initial>node
		Header_Node[i]->u.next=Header_Node[i+1];
		}
		Header_Node[Number_Head-1]->u.next=Ini_Node;
		Ini_Node->right=Header_Node[0];	
		return Ini_Node;
	}
}








					



		



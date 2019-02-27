--The whole structure is quite similar to the representation of matrix 

--Function sepration will seperate the string entered by white space.The result after the seperation is then store into a vector.If the seperation is completed , return true, else return false.

--Function getvalue is get the string from the vector and convert it into integer. The first element in the vector is then deleted.

--Pointer_Node is a pointer to the matrix node. Matrix node contain two Pointer_Node and one union . The union has two element. One is Pointer_Node while the other is entry_node;

--At first , mread() is called.

--When mread() is call,it will demands user to enter the number of column , number of row and non zero term .It will then pass the string to function seperation. If the seperation succeed , the value will then obtained by calling function getvalue();If the sepration failed , the function will print error and demands user to enter the number agian . The function won't exit if the seperation keep fail(the string entered cant be seperated).

--After this , mread() will start creating node and link them together .The remaining code is as same as the code mentioned at the textbook .Only the Ini_node that has to pointer to the firs Header_Node is returned. 

--mread() will be called twice to allow user entered two matrix.

--Function mtranspose will be called next ().The Pointer_Node to be transpose will pass to the function .

--First it will record the number of row , column and no -zero term of the matrix .Number of head will be equal to either number of row or column by considering which one is larger . The number of colum will be the number of row for the new matrix ,while the number of row is the other way around.The number of non -zero term will remain the same .Accroding to the number of Head, HeaderNode[number_of_Head] and Ini_Node is declare and defined.

--After tranpose , the first column of the initial matrix will be the first row of the new matrix. The last header node's next pointer will point toward Ini_node.If temp_node = Ini_Node right , while temp_node not equal to Ini_Node, the tranpose will carried out .The function will go through the whole matrix column bu column .

--mtranpose will go through each node and get the row , column and value. The row term and col term is inversed term remain the same .The function will then create node using the same code as mread() and set the value .

--Same as mread(),only the Ini_Node of the new transpose matrix is returned.

--Function mwrite() is a function that print out row ,column and value of each node of a matrix.Same as mtranspose , the pointer of Ini_Node of the matrix to be printed need to passed to the function .

--Within the function , a temporary pointer is created ,temp,and equal to Ini_Node->right(Points toward the first Header_Node).While temp not equal to Ini_Node , the function is carry on. Another temporary pointer ,tempB,is created and equal to temp->right.While tempB not equal temp , it will print out the row , column and value term and move to the next(tempB->right).If tempB equal to temp , temp will move to the next Header_node and the procedure is repeat.

--The number of row in A will be the number of row for the result while the number of row in B will be the number of column for the result .After determined the number of head(using the same comparision ,which one is larger),Header_Node[number_of_head] and In_Node is declared and defined .

--A temporary pointer ,temp_Head_A,is declare and equal to A->right(First Header node).If temp_Head_A not equal to A, the function will carry on .For each row in matrix A ,we need to go through the whole matrix B and carry out the multiplication if both the non zero term are in the same column.Therefore , another temporary node ,temp_Head_B ,is declare and equal to B->right. Each time we enter a new row of Matrix A , temp_Head_B will be equal to B->right and the function continue . 

--Integer sum is use to store the result if both term multiply. The row term of matrix A will indicate the col term of sum while the row term of matrixB will indicate the row term of the sum .

--The function continue by go through the row of A and B . If the non zero term are at the same col , multiplication is carried out . If the col term in tempB is smaller than tempA , move tempB one node to the right .If tempA is smaller, move tempA to the right . The while loop is exit when either A or B rech the next row. Node is created if the sum not equal to 0 . The node is linked as same as mread() function . But not like mread()function , which link node by row first , mmult will link node by column first . Because while going through  , the non zero term of the first column will be determined first instead of the non zero term of the first row .

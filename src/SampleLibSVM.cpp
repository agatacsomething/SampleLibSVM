//============================================================================
// Name        : SampleLibSVM.cpp
// Author      : agata
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "libsvm-3.20/svm.h"
using namespace std;

void TestXOR();

int main() {
	cout << "Testing out simple XOR problem" << endl; // prints !!!Hello World!!!
	TestXOR();
	return 0;
}

void TestXOR(){
	char input_file_name[1024];
	char model_file_name[1024];
	const char *error_msg;

	struct svm_parameter param;     // set by parse_command_line
	struct svm_problem prob;        // set by read_problem
	//struct svm_model *model;
	struct svm_node *x_space;
	param.svm_type = C_SVC;
	param.kernel_type = RBF;
	param.degree = 3;
	param.gamma = 0.5;
	param.coef0 = 0;
	param.nu = 0.5;
	param.cache_size = 100;
	param.C = 1;
	param.eps = 1e-3;
	param.p = 0.1;
	param.shrinking = 1;
	param.probability = 0;
	param.nr_weight = 0;
	param.weight_label = NULL;
	param.weight = NULL;


	//Problem definition-------------------------------------------------------------
	prob.l = 4;

	//x values matrix of xor values
	double matrix[prob.l][2];
	matrix[0][0] = 1;
	matrix[0][1] = 1;

	matrix[1][0] = 1;
	matrix[1][1] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 1;

	matrix[3][0] = 0;
	matrix[3][1] = 0;


	//This part i have trouble understanding
	svm_node** x = new svm_node *[prob.l];

	//Trying to assign from matrix to svm_node training examples
	for (int row = 0;row <prob.l; row++){
		svm_node* x_space = new svm_node[3];
		for (int col = 0;col < 2;col++){
			x_space[col].index = col;
			x_space[col].value = matrix[row][col];
		}
		x_space[2].index = -1;      //Each row of properties should be terminated with a -1 according to the readme
		x[row] = x_space;
	}

	prob.x = x;

	//yvalues
	prob.y = new double[prob.l];
	prob.y[0] = -1;
	prob.y[1] = 1;
	prob.y[2] = 1;
	prob.y[3] = -1;

	//Train model---------------------------------------------------------------------
	svm_model *model = svm_train(&prob,&param);


	//Test model----------------------------------------------------------------------
	svm_node* testnode = new svm_node[3];
	testnode[0].index = 0;
	testnode[0].value = 1;
	testnode[1].index = 1;
	testnode[1].value = 0;
	testnode[2].index = -1;

	//This works correctly:
	double retval = svm_predict(model,testnode);
	printf("retval: %f\n",retval);


	svm_destroy_param(&param);
	free(prob.y);
	free(prob.x);
}

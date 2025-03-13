#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>
#include "ldshr.h"
#include <math.h>

double  reduction(int n, int mean, int seed);
double sum(double input, double total);
double reduce(double(*f)(double, double), node * head);
void map(double(*f)(double), node * head);

double * getload_1_svc(void * nothing,struct svc_req *rqp)
{
	double *load = malloc(sizeof(double));
	getloadavg(load,3);
	return load;
};

double * sumqroot_gpu_1_svc(values * input, struct svc_req *rqp)
{
	double *value = malloc(sizeof(double));
	*value = reduction(input->n,input->m,input->s);
	return value;
};

double * sumqroot_lst_1_svc(node * head, struct svc_req * rqp)
{
	double *sum = malloc(sizeof(double));

	map(&qroot, head);

	*sum = reduce(&sum_function, head);
	
	return sum;
};

double reduce(double(*f)(double, double), node * head)
{
	double total  = 0;
	while(head != NULL)
	{
		total  = (*f)(head->value, total );
		head = head->next;
	}
	return total ;
	
}

double sum(double input, double total)
{
	return input + total;
}

void map(double(*f)(double), node * head)
{
	while(head != NULL)
	{
		head->value = (*f)(head->value);
		head = head->next;
	}
}
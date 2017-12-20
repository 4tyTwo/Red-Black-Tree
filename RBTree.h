#pragma once
#include<iostream>
struct TreeStruct {
	int info;
	int key;
	bool black; //True - ������, false - �������
	TreeStruct* right;
	TreeStruct* left;
  TreeStruct* parent;
};
class RBTree
{
public:
	RBTree();
	void insert(int key, int info);
	void erase(int key);
	int  get(int key);
  bool exist(int key);
  void print(TreeStruct* der, int h = 0);
  TreeStruct * node;
	~RBTree();
private:
 // TreeStruct * node;
  TreeStruct * grandparent(TreeStruct* curr);
  TreeStruct * uncle(TreeStruct* curr);
	TreeStruct* newTree(int key,int info,TreeStruct* parent = nullptr);
  void insert1(TreeStruct* n);
  void insert2(TreeStruct* n);
  void insert3(TreeStruct* n);
  void insert4(TreeStruct* n);
  void insert5(TreeStruct* n);
  void delete1(TreeStruct* n); //��� 6 ������� ���� �� ���������, �� ��� �� ������� � � ������� ������ 2 ������� ������
  void delete2(TreeStruct* n);
  /*void delete3(TreeStruct* n);
  void delete4(TreeStruct* n);
  void delete5(TreeStruct* n);
  void delete6(TreeStruct* n);*/
  void rotateLeft(TreeStruct* curr);
  void rotateRight(TreeStruct* curr);
	void setRight(TreeStruct* curr,int key, int info);
	void setLeft(TreeStruct* curr, int key, int info);
};


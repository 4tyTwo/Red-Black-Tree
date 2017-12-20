#include "RBTree.h"
#include "TempRB.h"
#include<string>

void printTree(TreeStruct *der, int h)
{
  if (der)
  {
    printTree(der->left, h + 1);
    for (int i = 0; i < h; i++)
    {
      std::cout << "   ";;
    }
    std::cout << der->info << std::endl;
    printTree(der->right, h + 1);
  }
}

int main() {
  TempRB<int, std::string> TempTree;
  RBTree tree;
  char c;
  for (int i = 0; i < 20; i++)
    TempTree.insert(i,"mama"+std::to_string(i));
  printTree(tree.node, 0);
  tree.erase(18);
  printTree(tree.node, 0);
  system("pause");
  return 0;
}
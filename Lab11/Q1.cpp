#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int EMPTY = NULL; // 用 NULL 代表沒有節點

class TreeNode {
public:
    int value;// 節點值
    TreeNode* left;// 左子節點
    TreeNode* right;// 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//初始化節點
};

class BinaryTree {
public:
    TreeNode* root;// 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) {// 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;//建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]);// 建立根節點 (陣列第一個元素)
        q.push(&root);// 將根節點的指標加入queue

        size_t i = 1;// 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);// 添加左子節點
                    q.push(&((*nodePtr)->left));// 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);// 添加右子節點
                    q.push(&((*nodePtr)->right));// 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

    void Depth_first_search(TreeNode* node) {//深度優先搜尋
        if (node == nullptr) return;
        cout << node->value << " ";// 訪問當前節點的值
        Depth_first_search(node->left);// 遞迴遍歷左子樹
        Depth_first_search(node->right);// 遞迴遍歷右子樹
    }

    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將左子節點的指標加入queue
        }
    }

    // 計算特定層數的節點數值總和
    void printLevelSum(int target_level) {
        // 【防禦性編程】檢查非法的負數輸入
        if (target_level < 0) {
            cout << "Invalid layer number. Layer must be >= 0." << endl;
            return;
        }

        // 【防禦性編程】檢查空樹狀況
        if (root == nullptr) {
            cout << "The tree is empty." << endl;
            return;
        }

        queue<TreeNode*> q;
        q.push(root);
        int current_level = 0; 

        while (!q.empty()) {
            int level_size = q.size(); 
            int level_sum = 0;

            // 一次處理完當前層的所有節點
            for (int i = 0; i < level_size; ++i) {
                TreeNode* current = q.front();
                q.pop();

                level_sum += current->value;

                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }

            // 找到目標層數，輸出結果並結束函數
            if (current_level == target_level) {
                cout << "The sum of level " << target_level << " is: " << level_sum << endl;
                return;
            }

            current_level++;
        }

        // 【防禦性編程】若 queue 空了卻還沒對應到 target_level，代表超出樹高
        cout << "The layer exceeds the tree height." << endl;
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    cout << "DFS Result: ";
    tree.Depth_first_search(tree.root);
    cout << endl;

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl; // 這裡會換行

    // 互動式輸入區塊
    int input_layer;
    cout << "Please enter the layer to query,starting from 0: ";
    
    // 【防禦性編程】確保使用者輸入的是合法的整數，避免輸入英文等非數字導致無窮迴圈或崩潰
    if (cin >> input_layer) {
        tree.printLevelSum(input_layer);
    } else {
        cout << "Invalid input! Please enter an integer." << endl;
    }

    system("pause");
    return 0;
}

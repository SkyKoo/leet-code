/*
 * @lc app=leetcode.cn id=590 lang=cpp
 * @lcpr version=30116
 *
 * [590] N 叉树的后序遍历
 *
 * https://leetcode.cn/problems/n-ary-tree-postorder-traversal/description/
 *
 * algorithms
 * Easy (78.80%)
 * Likes:    318
 * Dislikes: 0
 * Total Accepted:    149.9K
 * Total Submissions: 188.9K
 * Testcase Example:  '[1,null,3,2,4,null,5,6]'
 *
 * 给定一个 n 叉树的根节点 root ，返回 其节点值的 后序遍历 。
 * 
 * n 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：root = [1,null,3,2,4,null,5,6]
 * 输出：[5,6,3,2,4,1]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 输入：root =
 * [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * 输出：[2,6,14,11,7,3,12,8,4,13,9,10,5,1]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 节点总数在范围 [0, 10^4] 内
 * 0 <= Node.val <= 10^4
 * n 叉树的高度小于或等于 1000
 * 
 * 
 * 
 * 
 * 进阶：递归法很简单，你可以使用迭代法完成此题吗?
 * 
 */


// @lcpr-template-start
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// @lcpr-template-end
// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    // vector<int> postorder(Node* root) {
    //     vector<int> res;
    //     post(root, res);
    //     return res;
    // }
    // void post(Node* node, vector<int>& res) {
    //     if (node == nullptr)
    //         return;
        
    //     for (auto n : node->children) {
    //         post(n, res);
    //     }
    //     res.push_back(node->val);
    // }
    vector<int> postorder(Node* root) {
        vector<int> res;
        if (root == nullptr)
            return res;

        stack<Node*> st;
        Node* p = root;
        Node* last = nullptr;
        while (p != nullptr || !st.empty()) {
            while (p != nullptr) {
                st.push(p);
                if (!p->children.empty())
                    p = p->children.front();
                else
                    p = nullptr;
            }
            p = st.top();
            st.pop();
            if (p->children.empty() || p->children.back() == last) {
                res.push_back(p->val);
                last = p;
                p = nullptr;
            } else {
                st.push(p);
                if (!p->children.empty())
                    p = p->children.front();
                else {
                    p = nullptr;
                }
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,null,3,2,4,null,5,6]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]\n
// @lcpr case=end

 */

